import os
import re
import json

def extract_doc_and_footer(content):
    header_match = re.search(r'/\*\*?(.*?)\*/', content, re.DOTALL)
    header = header_match.group(0).strip() if header_match else "/* Problem Solution in C */"
    
    all_comments = list(re.finditer(r'/\*(.*?)\*/', content, re.DOTALL))
    footer = ""
    if len(all_comments) > 1:
        last = all_comments[-1].group(0).strip()
        if "Complexity" in last:
            footer = last
    if not footer:
        footer = "/*\n * Time Complexity: O(N) or O(1) optimal.\n * Space Complexity: O(1) auxiliary.\n */"
    return header, footer

def convert_java_body_to_c(body, has_listnode=False, has_treenode=False):
    c = body
    
    # Remove package and imports if any
    c = re.sub(r'package\s+[\w\.]+;\s*', '', c)
    c = re.sub(r'import\s+[\w\.\*]+;\s*', '', c)
    
    # Remove Java class wrappers: e.g. class Foo { ... }
    class_match = re.search(r'\b(public\s+)?(final\s+)?class\s+\w+(\s+extends\s+\w+)?(\s+implements\s+[\w,\s]+)?\s*\{', c)
    if class_match:
        c = c[class_match.end():]
        last_brace = c.rfind('}')
        if last_brace != -1:
            c = c[:last_brace]
            
    # Remove inner class definitions that we provide globally
    c = re.sub(r'static\s+class\s+ListNode\s*\{[^}]*\}', '', c)
    c = re.sub(r'static\s+class\s+TreeNode\s*\{[^}]*\}', '', c)
    c = re.sub(r'class\s+ListNode\s*\{[^}]*\}', '', c)
    c = re.sub(r'class\s+TreeNode\s*\{[^}]*\}', '', c)
    
    # 1. Constants & Meta properties (MUST BE BEFORE type replacement!)
    c = re.sub(r'Integer\.MAX_VALUE', 'INT_MAX', c)
    c = re.sub(r'Integer\.MIN_VALUE', 'INT_MIN', c)
    c = re.sub(r'Long\.MAX_VALUE', 'LLONG_MAX', c)
    c = re.sub(r'Long\.MIN_VALUE', 'LLONG_MIN', c)
    c = re.sub(r'Byte\.MAX_VALUE', 'SCHAR_MAX', c)
    c = re.sub(r'Byte\.MIN_VALUE', 'SCHAR_MIN', c)
    c = re.sub(r'Short\.MAX_VALUE', 'SHRT_MAX', c)
    c = re.sub(r'Short\.MIN_VALUE', 'SHRT_MIN', c)
    c = re.sub(r'Double\.MAX_VALUE', 'DBL_MAX', c)
    c = re.sub(r'Double\.MIN_VALUE', 'DBL_MIN', c)
    c = re.sub(r'Float\.MAX_VALUE', 'FLT_MAX', c)
    c = re.sub(r'Float\.MIN_VALUE', 'FLT_MIN', c)
    c = re.sub(r'Character\.MAX_VALUE', '255', c)
    c = re.sub(r'Character\.MIN_VALUE', '0', c)
    
    c = re.sub(r'Byte\.SIZE', '8', c)
    c = re.sub(r'Short\.SIZE', '16', c)
    c = re.sub(r'Integer\.SIZE', '32', c)
    c = re.sub(r'Long\.SIZE', '64', c)
    c = re.sub(r'Float\.SIZE', '32', c)
    c = re.sub(r'Double\.SIZE', '64', c)
    c = re.sub(r'Character\.SIZE', '8', c)
    
    c = re.sub(r'Byte\.BYTES', '1', c)
    c = re.sub(r'Short\.BYTES', '2', c)
    c = re.sub(r'Integer\.BYTES', '4', c)
    c = re.sub(r'Long\.BYTES', '8', c)
    c = re.sub(r'Float\.BYTES', '4', c)
    c = re.sub(r'Double\.BYTES', '8', c)
    c = re.sub(r'Character\.BYTES', '1', c)
    
    # Keywords
    c = re.sub(r'\bpublic\s+static\s+', '', c)
    c = re.sub(r'\bprivate\s+static\s+', 'static ', c)
    c = re.sub(r'\bprotected\s+static\s+', '', c)
    c = re.sub(r'\bpublic\s+', '', c)
    c = re.sub(r'\bprivate\s+', 'static ', c)
    c = re.sub(r'\bprotected\s+', '', c)
    c = re.sub(r'\bfinal\s+', 'const ', c)
    c = re.sub(r'\bboolean\b', 'bool', c)
    
    # 2. Java Types to C
    c = re.sub(r'\bString\b', 'const char*', c)
    c = re.sub(r'\bInteger\b', 'int', c)
    c = re.sub(r'\bDouble\b', 'double', c)
    c = re.sub(r'\bBoolean\b', 'bool', c)
    c = re.sub(r'\bCharacter\b', 'char', c)
    c = re.sub(r'\bLong\b', 'long long', c)
    c = re.sub(r'\blong\b', 'long long', c)
    c = re.sub(r'\bbyte\b', 'signed char', c)
    c = re.sub(r'\bnull\b', 'NULL', c)
    
    # Array types in signatures
    c = re.sub(r'\bint\[\]\[\]\b', 'int**', c)
    c = re.sub(r'\bchar\[\]\[\]\b', 'char**', c)
    c = re.sub(r'\bint\[\]\b', 'int*', c)
    c = re.sub(r'\bchar\[\]\b', 'char*', c)
    c = re.sub(r'\bdouble\[\]\b', 'double*', c)
    c = re.sub(r'\bbool\[\]\b', 'bool*', c)
    c = re.sub(r'\blong long\[\]\b', 'long long*', c)
    
    # Math functions
    c = re.sub(r'Math\.max\(([^,]+),\s*([^)]+)\)', r'MAX(\1, \2)', c)
    c = re.sub(r'Math\.min\(([^,]+),\s*([^)]+)\)', r'MIN(\1, \2)', c)
    c = re.sub(r'Math\.abs\(([^)]+)\)', r'abs(\1)', c)
    c = re.sub(r'Math\.pow\(([^,]+),\s*([^)]+)\)', r'pow(\1, \2)', c)
    c = re.sub(r'Math\.sqrt\(([^)]+)\)', r'sqrt(\1)', c)
    
    # Arrays.toString
    c = re.sub(r'Arrays\.toString\(([^)]+)\)', r'"[array]"', c)
    c = re.sub(r'java\.util\.Arrays\.toString\(([^)]+)\)', r'"[array]"', c)
    
    # main signature
    c = re.sub(r'void\s+main\s*\([^)]*\)', 'int main(void)', c)
    
    # System.out printing
    def repl_println(m):
        content = m.group(1).strip()
        if not content:
            return 'printf("\\n");'
        if content.startswith('"') and content.endswith('"'):
            return f'printf("{content[1:-1]}\\n");'
        if '+' in content:
            parts = [p.strip() for p in content.split('+')]
            fmt_parts = []
            arg_parts = []
            for p in parts:
                if p.startswith('"') and p.endswith('"'):
                    # Escape %n to \n in string literals
                    clean_str = p[1:-1].replace('%n', '\\n')
                    fmt_parts.append(clean_str)
                else:
                    fmt_parts.append("%d")
                    arg_parts.append(p)
            fmt = "".join(fmt_parts) + "\\n"
            if arg_parts:
                return f'printf("{fmt}", {", ".join(arg_parts)});'
            else:
                return f'printf("{fmt}");'
        return f'printf("%d\\n", {content});'

    c = re.sub(r'System\.out\.println\((.*?)\);', repl_println, c)
    
    # printf formatting (%n -> \n)
    def repl_printf(m):
        content = m.group(1).strip()
        content = content.replace('%n', '\\n')
        return f'printf({content});'
        
    c = re.sub(r'System\.out\.printf\((.*?)\);', repl_printf, c)
    c = re.sub(r'System\.out\.print\((.*?)\);', r'printf("%s", \1);', c)
    
    # New expressions
    c = re.sub(r'new\s+int\[\]\s*\{', '(int[]){', c)
    c = re.sub(r'new\s+int\[\]\[\]\s*\{', '(int*[]){', c)
    c = re.sub(r'new\s+ListNode\(([^)]*)\)', r'createNode(\1)', c)
    c = re.sub(r'new\s+TreeNode\(([^)]*)\)', r'createTreeNode(\1)', c)
    
    # Ensure main returns 0
    if 'int main(void)' in c:
        main_part = c[c.rfind('int main(void)'):]
        if 'return 0;' not in main_part:
            pos = c.rfind('}')
            if pos != -1:
                c = c[:pos] + '    return 0;\n}'
                
    return c

def build_c_source(java_path, filename):
    with open(java_path, 'r', encoding='utf-8') as f:
        java_code = f.read()
        
    header, footer = extract_doc_and_footer(java_code)
    
    has_listnode = 'ListNode' in java_code
    has_treenode = 'TreeNode' in java_code
    
    c_body = convert_java_body_to_c(java_code, has_listnode, has_treenode)
    
    boilerplate = """#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
"""
    if has_listnode:
        boilerplate += """
typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

static ListNode* createNode(int val) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) exit(1);
    node->val = val;
    node->next = NULL;
    return node;
}

static void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        free(tmp);
    }
}
"""
    if has_treenode:
        boilerplate += """
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

static TreeNode* createTreeNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) exit(1);
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
"""
    return f"{header}\n\n{boilerplate}\n{c_body.strip()}\n\n{footer}\n"
