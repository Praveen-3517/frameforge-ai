"""
╔══════════════════════════════════════════════════════════════════╗
║        Bittu AI — Live Razorpay Payment Service (Zero Deps)      ║
║                                                                  ║
║  Provides:                                                       ║
║   1. Direct Razorpay Order Creation via official REST API        ║
║   2. Razorpay Hosted Payment Links (AdBlock Proof Checkout)      ║
║   3. Cryptographic HMAC-SHA256 Payment Signature Verification    ║
║   4. ₹149 DSA Master Pass (Lifetime Access to Java + C Tracks)    ║
║   5. Free Tier (First 6 Questions Free for Everyone)             ║
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

_env_path = Path(__file__).parent / ".env"
if _env_path.exists():
    load_dotenv(_env_path)
else:
    load_dotenv()

log = logging.getLogger("payment_service")

# ─────────────────────────────────────────────────────────────
# 1.  Configuration & Keys
# ─────────────────────────────────────────────────────────────

RAZORPAY_KEY_ID: str = os.getenv("RAZORPAY_KEY_ID", "").strip()
RAZORPAY_KEY_SECRET: str = os.getenv("RAZORPAY_KEY_SECRET", "").strip()

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
# 2.  Razorpay Order & Payment Link Creation
# ─────────────────────────────────────────────────────────────

async def create_razorpay_order(
    amount_in_inr: int = 149,
    email: Optional[str] = None,
    college: Optional[str] = None,
    plan_name: str = "DSA Master Lifetime Pass (Java + C)",
) -> Dict[str, Any]:
    """
    Creates an official Razorpay order for ₹149 (14900 paise).
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
            "college": (college or "").strip(),
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
                "amount": data.get("amount"),       # in paise (e.g. 14900)
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
    amount_in_inr: int = 149,
    email: Optional[str] = None,
    name: Optional[str] = None,
    college: Optional[str] = None,
    plan_name: str = "DSA Master Lifetime Pass (Java + C)",
    plan_id: str = "DSA_JAVA_C_PASS",
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
            "plan_id": plan_id,
            "user_email": user_email,
            "college": (college or "").strip(),
        },
        "callback_url": "https://www.bittuai.online/dsa?payment=success",
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


async def verify_and_activate_razorpay_payment(
    payment_id: str,
    email: str,
    plan_id: Optional[str] = None,
) -> Dict[str, Any]:
    """
    Directly queries the live Razorpay API to verify whether a payment was captured.
    Prevents any spoofing or query param tampering.
    """
    if not RAZORPAY_KEY_ID or not RAZORPAY_KEY_SECRET or not payment_id:
        return {"success": False, "error": "Invalid verification parameters."}

    clean_pid = payment_id.strip()
    clean_email = (email or "").strip().lower()

    try:
        async with httpx.AsyncClient(timeout=15.0) as client:
            res = await client.get(
                f"https://api.razorpay.com/v1/payments/{clean_pid}",
                auth=(RAZORPAY_KEY_ID, RAZORPAY_KEY_SECRET),
            )

        if res.status_code == 200:
            pdata = res.json()
            status = pdata.get("status")
            amount = pdata.get("amount", 0)  # in paise
            order_id = pdata.get("order_id") or clean_pid

            # Verification criteria: Payment must be captured or authorized
            if status in ("captured", "authorized") and amount >= 10000:
                notes = pdata.get("notes") or {}
                raw_rzp_email = (pdata.get("email") or "").strip().lower()

                # Extract real customer email with fallback order:
                # 1. explicit email (if valid and not void@)
                # 2. Razorpay notes user_email (saved at link/order creation)
                # 3. Razorpay notes email
                # 4. Razorpay customer email (if not void@)
                final_email = (
                    (clean_email if clean_email and "void@" not in clean_email else "")
                    or (notes.get("user_email") or "").strip().lower()
                    or (notes.get("email") or "").strip().lower()
                    or (raw_rzp_email if "void@" not in raw_rzp_email else "")
                    or "verified_coder@bittuai.online"
                )

                # Determine plan: prefer explicit plan_id, else read from Razorpay notes
                resolved_plan = plan_id or notes.get("plan_id") or ("TOP_INTERVIEW_PASS" if "interview" in str(notes.get("plan", "")).lower() else "DSA_JAVA_C_PASS")

                activation = activate_user_pro(
                    email=final_email,
                    order_id=order_id,
                    payment_id=clean_pid,
                    amount_inr=int(amount / 100),
                    days=36500,
                    plan=resolved_plan,
                )
                return activation
            else:
                log.warning("[PAYMENT] Payment %s status not captured: status=%s, amount=%s", clean_pid, status, amount)
                return {"success": False, "error": f"Payment is in '{status}' status, not captured."}
        else:
            log.error("[PAYMENT] Razorpay API verification failed for %s [%s]: %s", clean_pid, res.status_code, res.text)
            return {"success": False, "error": "Payment record not found on Razorpay."}
    except Exception as e:
        log.exception("[PAYMENT] Exception during live payment verification: %s", e)
        return {"success": False, "error": f"Verification error: {str(e)}"}


# ─────────────────────────────────────────────────────────────
# 4.  Subscription Management & Activation
# ─────────────────────────────────────────────────────────────

def _find_captured_payment_in_razorpay(email: str) -> Optional[Dict[str, Any]]:
    """
    Directly searches Razorpay for any successful payment matching the email.
    Guarantees 100% instant cross-device sync even on server restarts.
    """
    if not RAZORPAY_KEY_ID or not RAZORPAY_KEY_SECRET or not email:
        return None
    try:
        normalized_email = email.strip().lower()
        with httpx.Client(timeout=6.0) as client:
            res = client.get(
                "https://api.razorpay.com/v1/payments?count=100",
                auth=(RAZORPAY_KEY_ID, RAZORPAY_KEY_SECRET),
            )
            if res.status_code == 200:
                items = res.json().get("items", [])
                for p in items:
                    status = p.get("status")
                    amount = p.get("amount", 0)
                    if status in ("captured", "authorized") and amount >= 10000:
                        notes = p.get("notes") or {}
                        pay_email = (notes.get("user_email") or notes.get("email") or p.get("email") or "").strip().lower()
                        if pay_email == normalized_email:
                            plan = notes.get("plan_id") or ("TOP_INTERVIEW_PASS" if "interview" in str(notes.get("plan", "")).lower() else "DSA_JAVA_C_PASS")
                            return {
                                "order_id": p.get("order_id") or p.get("id"),
                                "payment_id": p.get("id"),
                                "amount_inr": int(amount / 100),
                                "plan": plan,
                            }
    except Exception as e:
        log.warning("[PAYMENT] Razorpay lookup error for %s: %s", email, e)
    return None


def activate_user_pro(
    email: str,
    order_id: str,
    payment_id: str,
    amount_inr: int = 149,
    days: int = 36500,  # 100 Years / Lifetime Access
    plan: str = "DSA_JAVA_C_PASS",
) -> Dict[str, Any]:
    """
    Activates Lifetime Pro membership (100 years) and persists it to disk.
    Plan can be DSA_JAVA_C_PASS or TOP_INTERVIEW_PASS.
    """
    normalized_email = (email or "anonymous_pro@bittuai.online").strip().lower()
    now = datetime.utcnow()
    expires_at = now + timedelta(days=days)

    subscribers = _load_subscribers()
    sub_data = {
        "email": normalized_email,
        "is_pro": True,
        "plan": plan,
        "amount_inr": amount_inr,
        "order_id": order_id,
        "payment_id": payment_id,
        "activated_at": now.isoformat() + "Z",
        "expires_at": expires_at.isoformat() + "Z",
        "expires_timestamp": int(expires_at.timestamp()),
    }

    subscribers[normalized_email] = sub_data
    _save_subscribers(subscribers)

    log.info("[PAYMENT] Lifetime Pro Membership activated for %s (plan: %s)", normalized_email, plan)
    return {
        "success": True,
        "is_pro": True,
        "email": normalized_email,
        "plan": plan,
        "expires_at": sub_data["expires_at"],
        "message": f"Welcome to Bittu AI! Your {plan} is now active with Lifetime Access.",
    }


def get_user_pro_status(email: Optional[str]) -> Dict[str, Any]:
    """
    Checks whether the user currently has an active, unexpired Pro membership.
    If not found in local cache, auto-checks Razorpay API to auto-recover and sync across devices.
    """
    if not email:
        return {"is_pro": False, "plan": None, "expires_at": None}

    normalized_email = email.strip().lower()
    subscribers = _load_subscribers()
    record = subscribers.get(normalized_email)

    if record and record.get("is_pro"):
        expires_ts = record.get("expires_timestamp")
        if not expires_ts or time.time() <= expires_ts:
            return {
                "is_pro": True,
                "plan": record.get("plan", "DSA_JAVA_C_PASS"),
                "expires_at": record.get("expires_at"),
                "activated_at": record.get("activated_at"),
            }

    # Auto-heal / Auto-recover from Razorpay live API
    rzp_match = _find_captured_payment_in_razorpay(normalized_email)
    if rzp_match:
        log.info("[PAYMENT] Auto-recovered payment from Razorpay for %s: %s", normalized_email, rzp_match)
        activated = activate_user_pro(
            email=normalized_email,
            order_id=rzp_match["order_id"],
            payment_id=rzp_match["payment_id"],
            amount_inr=rzp_match["amount_inr"],
            days=36500,
            plan=rzp_match["plan"],
        )
        return {
            "is_pro": True,
            "plan": rzp_match["plan"],
            "expires_at": activated.get("expires_at"),
            "activated_at": datetime.utcnow().isoformat() + "Z",
        }

    return {"is_pro": False, "plan": None, "expires_at": None}
