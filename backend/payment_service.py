"""
╔══════════════════════════════════════════════════════════════════╗
║        Bittu AI — Live Razorpay Payment Service (Zero Deps)      ║
║                                                                  ║
║  Provides:                                                       ║
║   1. Direct Razorpay Order Creation via official REST API        ║
║   2. Cryptographic HMAC-SHA256 Payment Signature Verification    ║
║   3. Student-friendly ₹99/Month Pro Plan Subscription Store       ║
║   4. Pro Membership Expiry Tracking & Verification               ║
╚══════════════════════════════════════════════════════════════════╝
"""

import os
import time
import json
import hmac
import hashlib
import secrets
import logging
from datetime import datetime, timedelta
from pathlib import Path
from typing import Dict, Any, Optional

import httpx
from dotenv import load_dotenv

load_dotenv()

log = logging.getLogger("payment_service")

# ─────────────────────────────────────────────────────────────
# 1.  Configuration & Keys
# ─────────────────────────────────────────────────────────────

RAZORPAY_KEY_ID: str = os.getenv("RAZORPAY_KEY_ID", "rzp_live_TdAIqK8iA6DzsG").strip()
RAZORPAY_KEY_SECRET: str = os.getenv("RAZORPAY_KEY_SECRET", "4InJkA8NPiy9uDiBKFcnFnuc").strip()

RAZORPAY_ORDERS_URL = "https://api.razorpay.com/v1/orders"

DATA_DIR = Path(__file__).parent / "data"
DATA_DIR.mkdir(parents=True, exist_ok=True)
SUBSCRIBERS_FILE = DATA_DIR / "subscribers.json"


def _load_subscribers() -> Dict[str, Any]:
    """Safely loads active subscribers dictionary from disk."""
    if not SUBSCRIBERS_FILE.exists():
        return {}
    try:
        with open(SUBSCRIBERS_FILE, "r", encoding="utf-8") as f:
            return json.load(f)
    except Exception as e:
        log.error("Failed to read subscribers file: %s", e)
        return {}


def _save_subscribers(data: Dict[str, Any]) -> bool:
    """Atomic write of subscribers data to disk."""
    try:
        temp_file = SUBSCRIBERS_FILE.with_suffix(".tmp")
        with open(temp_file, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
        temp_file.replace(SUBSCRIBERS_FILE)
        return True
    except Exception as e:
        log.error("Failed to save subscribers file: %s", e)
        return False


# ─────────────────────────────────────────────────────────────
# 2.  Razorpay Order Creation
# ─────────────────────────────────────────────────────────────

async def create_razorpay_order(
    amount_in_inr: int = 99,
    email: Optional[str] = None,
    plan_name: str = "DSA Pro Pass (1 Month)",
) -> Dict[str, Any]:
    """
    Creates an official Razorpay order for ₹99 (9900 paise).
    Uses standard HTTP Basic Auth with user's live credentials.
    """
    if not RAZORPAY_KEY_ID or not RAZORPAY_KEY_SECRET:
        log.error("Razorpay credentials missing from environment.")
        return {"success": False, "error": "Payment gateway credentials not configured."}

    # Razorpay amounts are represented in paise (1 INR = 100 paise)
    amount_paise = int(amount_in_inr * 100)
    receipt_id = f"rcpt_{int(time.time())}_{secrets.token_hex(3)}"

    payload = {
        "amount": amount_paise,
        "currency": "INR",
        "receipt": receipt_id,
        "notes": {
            "platform": "Bittu AI",
            "plan": plan_name,
            "user_email": (email or "").strip().lower(),
            "created_at": datetime.utcnow().isoformat(),
        },
    }

    log.info("[PAYMENT] Requesting Razorpay Order for amount INR %s (receipt=%s) ...", amount_in_inr, receipt_id)

    try:
        async with httpx.AsyncClient(timeout=15.0) as client:
            response = await client.post(
                RAZORPAY_ORDERS_URL,
                auth=(RAZORPAY_KEY_ID, RAZORPAY_KEY_SECRET),
                json=payload,
            )

        if response.status_code in (200, 201):
            data = response.json()
            log.info("[PAYMENT] Razorpay Order created successfully: %s", data.get("id"))
            return {
                "success": True,
                "order_id": data.get("id"),
                "amount": data.get("amount"),       # in paise (e.g. 9900)
                "amount_inr": amount_in_inr,
                "currency": data.get("currency", "INR"),
                "key_id": RAZORPAY_KEY_ID,
                "receipt": receipt_id,
                "plan_name": plan_name,
            }
        else:
            log.error("[PAYMENT] Razorpay Order creation failed [%s]: %s", response.status_code, response.text)
            err_msg = "Razorpay error"
            try:
                err_data = response.json()
                err_msg = err_data.get("error", {}).get("description", response.text)
            except Exception:
                err_msg = response.text
            return {"success": False, "error": f"Failed to create order: {err_msg}"}

    except Exception as e:
        log.error("[PAYMENT] Exception creating Razorpay order: %s", e)
        return {"success": False, "error": f"Payment service connection error: {str(e)}"}


async def create_razorpay_payment_link(
    amount_in_inr: int = 99,
    email: Optional[str] = None,
    name: Optional[str] = None,
    plan_name: str = "DSA Pro Pass (1 Month)",
) -> Dict[str, Any]:
    """
    Creates a Razorpay Hosted Payment Link (e.g. https://rzp.io/l/xxxxx)
    which works 100% reliably even if client-side adblockers block standard modals.
    """
    if not RAZORPAY_KEY_ID or not RAZORPAY_KEY_SECRET:
        return {"success": False, "error": "Payment gateway credentials not configured."}

    amount_paise = int(amount_in_inr * 100)
    ref_id = f"plink_{int(time.time())}_{secrets.token_hex(3)}"
    user_email = (email or "").strip().lower()

    payload = {
        "amount": amount_paise,
        "currency": "INR",
        "accept_partial": False,
        "reference_id": ref_id,
        "description": f"Bittu AI — {plan_name}",
        "customer": {
            "name": name or "Student Coder",
            "email": user_email or "student@bittuai.online",
        },
        "notify": {
            "sms": False,
            "email": bool(user_email)
        },
        "reminder_enable": False,
        "notes": {
            "platform": "Bittu AI",
            "plan": plan_name,
            "user_email": user_email,
        },
        "callback_url": "https://www.bittuai.online/dsa/top-interview-150?payment=success",
        "callback_method": "get"
    }

    try:
        async with httpx.AsyncClient(timeout=15.0) as client:
            response = await client.post(
                "https://api.razorpay.com/v1/payment_links",
                auth=(RAZORPAY_KEY_ID, RAZORPAY_KEY_SECRET),
                json=payload,
            )

        if response.status_code in (200, 201):
            data = response.json()
            return {
                "success": True,
                "payment_link": data.get("short_url") or data.get("url"),
                "link_id": data.get("id"),
                "amount_inr": amount_in_inr,
                "plan_name": plan_name,
            }
        else:
            log.error("[PAYMENT] Payment link creation failed [%s]: %s", response.status_code, response.text)
            return {"success": False, "error": f"Failed to create payment link: {response.text}"}
    except Exception as e:
        return {"success": False, "error": f"Payment link error: {str(e)}"}


# ─────────────────────────────────────────────────────────────
# 3.  Cryptographic HMAC-SHA256 Payment Verification
# ─────────────────────────────────────────────────────────────

def verify_razorpay_signature(
    order_id: str,
    payment_id: str,
    signature: str,
) -> bool:
    """
    Validates the cryptographic HMAC-SHA256 signature returned by Razorpay.
    Signature = HMAC_SHA256(order_id + "|" + payment_id, secret)
    Uses constant-time comparison to prevent timing side-channel attacks.
    """
    if not order_id or not payment_id or not signature or not RAZORPAY_KEY_SECRET:
        return False

    message = f"{order_id.strip()}|{payment_id.strip()}".encode("utf-8")
    secret = RAZORPAY_KEY_SECRET.strip().encode("utf-8")

    expected_signature = hmac.new(secret, message, hashlib.sha256).hexdigest()

    # Constant-time comparison
    is_valid = secrets.compare_digest(expected_signature, signature.strip())
    if is_valid:
        log.info("[PAYMENT] Razorpay signature verified successfully for order %s (payment %s)", order_id, payment_id)
    else:
        log.warning("[PAYMENT] Invalid Razorpay signature for order %s! Expected: %s, Got: %s", order_id, expected_signature, signature)
    return is_valid


# ─────────────────────────────────────────────────────────────
# 4.  Subscription Management & Activation
# ─────────────────────────────────────────────────────────────

def activate_user_pro(
    email: str,
    order_id: str,
    payment_id: str,
    amount_inr: int = 99,
    days: int = 30,
) -> Dict[str, Any]:
    """
    Activates Pro membership for 30 days and persists it to disk.
    """
    normalized_email = (email or "anonymous_pro@bittuai.online").strip().lower()
    now = datetime.utcnow()
    expires_at = now + timedelta(days=days)

    subscribers = _load_subscribers()
    sub_data = {
        "email": normalized_email,
        "is_pro": True,
        "plan": "DSA_PRO_MONTHLY",
        "amount_inr": amount_inr,
        "order_id": order_id,
        "payment_id": payment_id,
        "activated_at": now.isoformat() + "Z",
        "expires_at": expires_at.isoformat() + "Z",
        "expires_timestamp": int(expires_at.timestamp()),
    }

    subscribers[normalized_email] = sub_data
    _save_subscribers(subscribers)

    log.info("[PAYMENT] Pro Membership activated for %s until %s", normalized_email, expires_at.strftime("%Y-%m-%d %H:%M UTC"))
    return {
        "success": True,
        "is_pro": True,
        "email": normalized_email,
        "plan": "DSA_PRO_MONTHLY",
        "expires_at": sub_data["expires_at"],
        "message": "Welcome to Bittu AI DSA Pro! Top Interview Questions & Pro Perks Unlocked!",
    }


def get_user_pro_status(email: Optional[str]) -> Dict[str, Any]:
    """
    Checks whether the user currently has an active, unexpired Pro membership.
    """
    if not email:
        return {"is_pro": False, "plan": None, "expires_at": None}

    normalized_email = email.strip().lower()
    subscribers = _load_subscribers()
    record = subscribers.get(normalized_email)

    if not record or not record.get("is_pro"):
        return {"is_pro": False, "plan": None, "expires_at": None}

    # Check expiry
    try:
        expires_ts = record.get("expires_timestamp")
        if expires_ts and time.time() > expires_ts:
            log.info("Pro membership for %s has expired.", normalized_email)
            return {"is_pro": False, "plan": None, "expires_at": record.get("expires_at"), "expired": True}
    except Exception:
        pass

    return {
        "is_pro": True,
        "plan": record.get("plan", "DSA_PRO_MONTHLY"),
        "expires_at": record.get("expires_at"),
        "activated_at": record.get("activated_at"),
    }
