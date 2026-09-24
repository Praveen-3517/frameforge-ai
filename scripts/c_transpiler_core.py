import os
import re
import subprocess

def clean_docstring(doc_text):
    if not doc_text:
        return ""
    return doc_text.strip()

def extract_docstring_and_footer(content):
    top_doc = ""
    footer = ""
    
    # Match first comment block
    first_match = re.search(r'/\*\*?(.*?)\*/', content, re.DOTALL)
    if first_match and first_match.start() < 100:
        top_doc = first_match.group(0).strip()
    
    # Match last comment block
    all_matches = list(re.finditer(r'/\*(.*?)\*/', content, re.DOTALL))
    if len(all_matches) > 1:
        last = all_matches[-1]
        if 'Complexity' in last.group(0):
            footer = last.group(0).strip()
    
    return top_doc, footer

print("Transpiler core helper initialized.")
