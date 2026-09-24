import os
import re
import json

JAVA_ROOT = r'f:\AI tool\dsa-java'
C_ROOT = r'f:\AI tool\dsa-c'

def extract_meta(java_code):
    doc_match = re.search(r'/\*\*?(.*?)\*/', java_code, re.DOTALL)
    header = doc_match.group(0).strip() if doc_match else ""
    
    # footer
    all_comments = list(re.finditer(r'/\*(.*?)\*/', java_code, re.DOTALL))
    footer = ""
    if len(all_comments) > 1:
        last = all_comments[-1].group(0).strip()
        if "Complexity" in last:
            footer = last
    if not footer:
        footer = "/*\n * Time Complexity: O(N) or O(1) optimal as analyzed.\n * Space Complexity: O(1) auxiliary space.\n */"
    return header, footer

print("Generator helper loaded.")
