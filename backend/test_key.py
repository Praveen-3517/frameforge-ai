"""
Quick diagnostic — run this to check what API key is actually loaded.
Usage: .venv\Scripts\python.exe test_key.py
"""
import os
from dotenv import load_dotenv

load_dotenv()

key = os.getenv("OPENAI_API_KEY", "")

print("=" * 60)
print(f"Key starts with : {key[:20]}...")
print(f"Key ends with   : ...{key[-10:]}")
print(f"Key length      : {len(key)} characters")
print(f"Has # symbol    : {'#' in key}")
print(f"Has + symbol    : {'+' in key}")
print(f"Has spaces      : {' ' in key}")
print(f"Has quotes      : {key.startswith(chr(34)) or key.startswith(chr(39))}")
print("=" * 60)

# Now actually test the key against OpenAI
print("\nTesting key against OpenAI API...")
try:
    from openai import OpenAI
    client = OpenAI(api_key=key)
    response = client.models.list()
    print("✅ SUCCESS! Key is VALID! OpenAI responded correctly.")
except Exception as e:
    print(f"❌ FAILED: {e}")
    print("\nPossible reasons:")
    print("  1. Key is incomplete or corrupted")
    print("  2. OpenAI account has no billing set up")
    print("  3. Key was deleted on OpenAI platform")
