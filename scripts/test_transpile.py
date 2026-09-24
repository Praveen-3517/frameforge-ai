import re
import os

def transpile_java_to_c(java_code, filename):
    # Extract header docstring
    header_match = re.search(r'/\*\*?(.*?)\*/', java_code, re.DOTALL)
    header = header_match.group(0).strip() if header_match else "/* Problem Solution in C */"
    
    # Extract footer docstring
    all_comments = list(re.finditer(r'/\*(.*?)\*/', java_code, re.DOTALL))
    footer = ""
    if len(all_comments) > 1:
        last = all_comments[-1].group(0).strip()
        if "Complexity" in last:
            footer = last
    if not footer:
        footer = "/*\n * Time Complexity: O(N) or O(1) optimal.\n * Space Complexity: O(1) auxiliary.\n */"
    
    # Body between class declaration and end
    class_match = re.search(r'class\s+\w+\s*\{', java_code)
    if not class_match:
        return java_code
    
    body = java_code[class_match.end():]
    # Remove footer if inside body
    if footer in body:
        body = body[:body.rfind(footer)]
    # Remove last closing brace of class
    last_brace = body.rfind('}')
    if last_brace != -1:
        body = body[:last_brace]
        
    c_code = body
    
    # Replace Java types and constructs
    # Inner classes like ListNode
    c_code = re.sub(r'static\s+class\s+ListNode\s*\{[^}]*\}', 
                    'typedef struct ListNode {\n    int val;\n    struct ListNode* next;\n} ListNode;', c_code)
    c_code = re.sub(r'static\s+class\s+TreeNode\s*\{[^}]*\}', 
                    'typedef struct TreeNode {\n    int val;\n    struct TreeNode* left;\n    struct TreeNode* right;\n} TreeNode;', c_code)

    # Keywords & modifiers
    c_code = re.sub(r'\bpublic\s+static\s+', '', c_code)
    c_code = re.sub(r'\bprivate\s+static\s+', 'static ', c_code)
    c_code = re.sub(r'\bpublic\s+', '', c_code)
    c_code = re.sub(r'\bprivate\s+', 'static ', c_code)
    c_code = re.sub(r'\bfinal\s+', 'const ', c_code)
    c_code = re.sub(r'\bboolean\b', 'bool', c_code)
    
    # Constants
    c_code = re.sub(r'Integer\.MAX_VALUE', 'INT_MAX', c_code)
    c_code = re.sub(r'Integer\.MIN_VALUE', 'INT_MIN', c_code)
    c_code = re.sub(r'Long\.MAX_VALUE', 'LLONG_MAX', c_code)
    c_code = re.sub(r'Long\.MIN_VALUE', 'LLONG_MIN', c_code)
    c_code = re.sub(r'Byte\.MAX_VALUE', 'CHAR_MAX', c_code)
    c_code = re.sub(r'Byte\.MIN_VALUE', 'CHAR_MIN', c_code)
    c_code = re.sub(r'Short\.MAX_VALUE', 'SHRT_MAX', c_code)
    c_code = re.sub(r'Short\.MIN_VALUE', 'SHRT_MIN', c_code)
    c_code = re.sub(r'Double\.MAX_VALUE', 'DBL_MAX', c_code)
    c_code = re.sub(r'Double\.MIN_VALUE', 'DBL_MIN', c_code)
    c_code = re.sub(r'Float\.MAX_VALUE', 'FLT_MAX', c_code)
    c_code = re.sub(r'Float\.MIN_VALUE', 'FLT_MIN', c_code)
    c_code = re.sub(r'null\b', 'NULL', c_code)
    
    # Math
    c_code = re.sub(r'Math\.max\(([^,]+),\s*([^)]+)\)', r'(((\1) > (\2)) ? (\1) : (\2))', c_code)
    c_code = re.sub(r'Math\.min\(([^,]+),\s*([^)]+)\)', r'(((\1) < (\2)) ? (\1) : (\2))', c_code)
    c_code = re.sub(r'Math\.abs\(([^)]+)\)', r'abs(\1)', c_code)
    c_code = re.sub(r'Math\.pow\(([^,]+),\s*([^)]+)\)', r'pow(\1, \2)', c_code)
    c_code = re.sub(r'Math\.sqrt\(([^)]+)\)', r'sqrt(\1)', c_code)
    
    # main method signature
    c_code = re.sub(r'void\s+main\s*\([^)]*\)', 'int main(void)', c_code)
    
    # System.out.println / printf / print
    # Replace simple print statements
    def replace_println(match):
        arg = match.group(1).strip()
        if not arg:
            return 'printf("\\n");'
        # If it has string concatenation with +, handle simple cases
        if '"' in arg and '+' in arg:
            parts = [p.strip() for p in arg.split('+')]
            fmt = []
            args = []
            for p in parts:
                if p.startswith('"') and p.endswith('"'):
                    fmt.append(p[1:-1])
                else:
                    fmt.append("%d")
                    args.append(p)
            fmt_str = "".join(fmt) + "\\n"
            if args:
                return f'printf("{fmt_str}", {", ".join(args)});'
            else:
                return f'printf("{fmt_str}");'
        elif arg.startswith('"') and arg.endswith('"'):
            return f'printf("{arg[1:-1]}\\n");'
        else:
            return f'printf("%d\\n", {arg});'

    c_code = re.sub(r'System\.out\.println\((.*?)\);', replace_println, c_code)
    c_code = re.sub(r'System\.out\.printf\((.*?)\);', r'printf(\1);', c_code)
    c_code = re.sub(r'System\.out\.print\((.*?)\);', r'printf("%s", \1);', c_code)
    
    # Ensure return 0 in main
    if 'int main(void)' in c_code:
        # Check if return 0 is before the end of main
        main_idx = c_code.rfind('int main(void)')
        if 'return 0;' not in c_code[main_idx:]:
            # add return 0; before the last brace
            last_b = c_code.rfind('}')
            c_code = c_code[:last_b] + '    return 0;\n}'
    
    includes = """#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>

"""
    return f"{header}\n\n{includes}{c_code.strip()}\n\n{footer}\n"

print("Test transpiler ready.")
