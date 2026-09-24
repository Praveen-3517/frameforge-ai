import os
import re
import json
import sys

JAVA_ROOT = r'f:\AI tool\dsa-java'
C_ROOT = r'f:\AI tool\dsa-c'

with open(r'f:\AI tool\dsa_java_map.json', 'r', encoding='utf-8') as f:
    TOPICS_MAP = json.load(f)

from gen_readme import generate_topic_readme

def clean_doc_and_footer(content):
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

def remove_inner_classes(text):
    res = text
    while True:
        m = re.search(r'\b(static\s+)?class\s+(ListNode|TreeNode|Pair|MyLinkedList|DLLNode|Node)\b[^{]*\{', res)
        if not m:
            break
        start = m.start()
        brace_count = 0
        end = -1
        for i in range(m.end() - 1, len(res)):
            if res[i] == '{':
                brace_count += 1
            elif res[i] == '}':
                brace_count -= 1
                if brace_count == 0:
                    end = i + 1
                    break
        if end != -1:
            res = res[:start] + res[end:]
        else:
            break
    return res

def remove_outer_class(text):
    # Find outer class declaration
    m = re.search(r'\b(public\s+)?(final\s+)?class\s+\w+(\s+extends\s+\w+)?(\s+implements\s+[\w,\s]+)?\s*\{', text)
    if not m:
        return text
    start = m.end()
    # Find matching last brace
    last_brace = text.rfind('}')
    if last_brace != -1 and last_brace > start:
        return text[start:last_brace]
    return text[start:]

def convert_body(raw_code, has_listnode=False, has_treenode=False):
    # 1. Strip package, imports, annotations
    c = re.sub(r'package\s+[\w\.]+;\s*', '', raw_code)
    c = re.sub(r'import\s+[\w\.\*]+;\s*', '', c)
    c = re.sub(r'@Override\s*', '', c)
    
    # 2. Balanced removal of inner classes
    c = remove_inner_classes(c)
    
    # 3. Balanced removal of outer class wrapper
    c = remove_outer_class(c)

    # 4. Constants & Meta properties (BEFORE type replacement)
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

    # 5. String & Char helper transformations
    c = re.sub(r'Integer\.toBinaryString\(', 'toBinaryString(', c)
    c = re.sub(r'Long\.toBinaryString\(', 'toBinaryString(', c)
    c = re.sub(r'(\w+)\.charAt\(([^)]+)\)', r'\1[\2]', c)
    c = re.sub(r'(\w+)\.length\(\)', r'((int)strlen(\1))', c)
    c = re.sub(r'(\w+)\.equals\(([^)]+)\)', r'(strcmp(\1, \2) == 0)', c)
    c = re.sub(r'(\w+)\.equalsIgnoreCase\(([^)]+)\)', r'(strcasecmp(\1, \2) == 0)', c)
    c = re.sub(r'(\w+)\.toCharArray\(\)', r'\1', c)
    c = re.sub(r'Character\.isLetter\(([^)]+)\)', r'isalpha(\1)', c)
    c = re.sub(r'Character\.isDigit\(([^)]+)\)', r'isdigit(\1)', c)
    c = re.sub(r'Character\.isLetterOrDigit\(([^)]+)\)', r'isalnum(\1)', c)
    c = re.sub(r'Character\.toLowerCase\(([^)]+)\)', r'tolower(\1)', c)
    c = re.sub(r'Character\.toUpperCase\(([^)]+)\)', r'toupper(\1)', c)

    # 6. Throw exception transformation
    c = re.sub(r'throw\s+new\s+[A-Za-z0-9_]+\s*\([^)]*\)\s*;', 'fprintf(stderr, "Exception: invalid argument\\n"); return 0;', c)

    # 7. Function return types and parameters with arrays
    c = re.sub(r'\b(int|long|double|char|bool|signed char|long long)\s*\[\]\s+(\w+)\s*\(', r'\1* \2(', c)
    c = re.sub(r'\b(int|long|double|char|bool|signed char|long long)\s*\[\]\[\]\s+(\w+)\s*\(', r'\1** \2(', c)

    c = re.sub(r'\b(int|long|double|char|bool|signed char|long long)\s*\[\]\s+(\w+)\b', r'\1* \2', c)
    c = re.sub(r'\b(int|long|double|char|bool|signed char|long long)\s*\[\]\[\]\s+(\w+)\b', r'\1** \2', c)

    c = re.sub(r'\b(int|long|double|char|bool|signed char|long long)\s*\[\]\s+(\w+)\s*=\s*\{', r'\1 \2[] = {', c)
    c = re.sub(r'\b(int|long|double|char|bool|signed char|long long)\s*\[\]\[\]\s+(\w+)\s*=\s*\{', r'\1* \2[] = {', c)

    # Modifiers
    c = re.sub(r'\bpublic\s+static\s+', '', c)
    c = re.sub(r'\bprivate\s+static\s+', 'static ', c)
    c = re.sub(r'\bprotected\s+static\s+', '', c)
    c = re.sub(r'\bpublic\s+', '', c)
    c = re.sub(r'\bprivate\s+', 'static ', c)
    c = re.sub(r'\bprotected\s+', '', c)
    c = re.sub(r'\bfinal\s+', 'const ', c)
    c = re.sub(r'\bboolean\b', 'bool', c)

    # Types
    c = re.sub(r'\bString\b', 'const char*', c)
    c = re.sub(r'\bInteger\b', 'int', c)
    c = re.sub(r'\bDouble\b', 'double', c)
    c = re.sub(r'\bBoolean\b', 'bool', c)
    c = re.sub(r'\bCharacter\b', 'char', c)
    c = re.sub(r'\bLong\b', 'long long', c)
    c = re.sub(r'\blong\b', 'long long', c)
    c = re.sub(r'\bbyte\b', 'signed char', c)
    c = re.sub(r'\bnull\b', 'NULL', c)
    c = re.sub(r'\b(List|ArrayList)<[^>]+>\s+(\w+)\s*\(', r'int* \2(', c)
    c = re.sub(r'\b(List|ArrayList)<[^>]+>', 'int*', c)

    # New array dynamic allocation: new int[n] -> (int*)malloc((n) * sizeof(int))
    c = re.sub(r'new\s+(int|long long|double|char|bool|signed char)\s*\[([^\]]+)\]', r'(\1*)malloc((\2) * sizeof(\1))', c)

    # Math
    c = re.sub(r'Math\.max\(([^,]+),\s*([^)]+)\)', r'MAX(\1, \2)', c)
    c = re.sub(r'Math\.min\(([^,]+),\s*([^)]+)\)', r'MIN(\1, \2)', c)
    c = re.sub(r'Math\.abs\(([^)]+)\)', r'abs(\1)', c)
    c = re.sub(r'Math\.pow\(([^,]+),\s*([^)]+)\)', r'pow(\1, \2)', c)
    c = re.sub(r'Math\.sqrt\(([^)]+)\)', r'sqrt(\1)', c)
    c = re.sub(r'Math\.floor\(([^)]+)\)', r'floor(\1)', c)
    c = re.sub(r'Math\.ceil\(([^)]+)\)', r'ceil(\1)', c)

    # Pointers for ListNode and TreeNode (with chained arrow loop)
    if has_listnode:
        c = re.sub(r'\bListNode\s+(\w+)\s*\(', r'ListNode* \1(', c)
        c = re.sub(r'\bListNode\s*(\*?)\s*(\w+)', r'ListNode* \2', c)
        for _ in range(4):
            c = re.sub(r'(\w+|->\w+)\.(val|next)\b', r'\1->\2', c)

    if has_treenode:
        c = re.sub(r'\bTreeNode\s+(\w+)\s*\(', r'TreeNode* \1(', c)
        c = re.sub(r'\bTreeNode\s*(\*?)\s*(\w+)', r'TreeNode* \2', c)
        for _ in range(4):
            c = re.sub(r'(\w+|->\w+)\.(val|left|right)\b', r'\1->\2', c)

    # arr.length
    c = re.sub(r'\b(\w+)\.length\b', r'n', c)

    # Arrays.toString
    c = re.sub(r'Arrays\.toString\(([^)]+)\)', r'"[array]"', c)
    c = re.sub(r'java\.util\.Arrays\.toString\(([^)]+)\)', r'"[array]"', c)

    # Main signature
    c = re.sub(r'void\s+main\s*\([^)]*\)', 'int main(void)', c)

    # Foreach loops
    def repl_foreach(m):
        var_type = m.group(1)
        var_name = m.group(2)
        arr_name = m.group(3)
        return f'for (size_t _idx = 0; _idx < sizeof({arr_name})/sizeof({arr_name}[0]); _idx++) {{\n        {var_type} {var_name} = {arr_name}[_idx];'

    c = re.sub(r'for\s*\(\s*(int|char|double|bool|long long)\s+(\w+)\s*:\s*(\w+)\s*\)\s*\{', repl_foreach, c)

    # System.out printing with re.DOTALL
    def repl_println(m):
        content = m.group(1).strip()
        if not content:
            return 'printf("\\n");'
        if content.startswith('"') and content.endswith('"'):
            clean_str = content[1:-1].replace('%n', '\\n')
            return f'printf("{clean_str}\\n");'
        if '+' in content:
            parts = [p.strip() for p in content.split('+')]
            fmt_parts = []
            arg_parts = []
            for p in parts:
                if p.startswith('"') and p.endswith('"'):
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

    c = re.sub(r'System\.out\.println\((.*?)\);', repl_println, c, flags=re.DOTALL)

    def repl_printf(m):
        content = m.group(1).strip()
        content = content.replace('%n', '\\n')
        return f'printf({content});'
        
    c = re.sub(r'System\.out\.printf\((.*?)\);', repl_printf, c, flags=re.DOTALL)
    c = re.sub(r'System\.out\.print\((.*?)\);', r'printf("%s", \1);', c, flags=re.DOTALL)

    # New object instantiation expressions
    c = re.sub(r'new\s+int\[\]\s*\{', '(int[]){', c)
    c = re.sub(r'new\s+int\[\]\[\]\s*\{', '(int*[]){', c)
    c = re.sub(r'new\s+ListNode\(([^)]*)\)', r'createNode(\1)', c)
    c = re.sub(r'new\s+TreeNode\(([^)]*)\)', r'createTreeNode(\1)', c)

    # Replace buildList definition inside class if present
    while True:
        m = re.search(r'\b(static\s+)?ListNode\*\s+buildList\s*\([^)]*\)\s*\{', c)
        if not m:
            break
        start = m.start()
        brace_count = 0
        end = -1
        for i in range(m.end() - 1, len(c)):
            if c[i] == '{':
                brace_count += 1
            elif c[i] == '}':
                brace_count -= 1
                if brace_count == 0:
                    end = i + 1
                    break
        if end != -1:
            c = c[:start] + c[end:]
        else:
            break

    # Replace buildList calls
    def repl_build_call(m):
        args = m.group(1).strip()
        if not args:
            return 'buildList(0, NULL)'
        nums = [x.strip() for x in args.split(',') if x.strip()]
        return 'buildList(' + str(len(nums)) + ', (int[]){' + ', '.join(nums) + '})'

    c = re.sub(r'\bbuildList\(([0-9,\s\-]+)\)', repl_build_call, c)

    # Ensure return 0 in main
    if 'int main(void)' in c:
        main_part = c[c.rfind('int main(void)'):]
        if 'return 0;' not in main_part:
            pos = c.rfind('}')
            if pos != -1:
                c = c[:pos] + '    return 0;\n}'

    return c

def generate_c_file(java_path, out_c_path):
    with open(java_path, 'r', encoding='utf-8') as f:
        java_code = f.read()

    header, footer = clean_doc_and_footer(java_code)
    has_listnode = 'ListNode' in java_code
    has_treenode = 'TreeNode' in java_code

    c_body = convert_body(java_code, has_listnode, has_treenode)

    boilerplate = """#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}
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

static ListNode* buildList(int count, int vals[]) {
    if (count <= 0) return NULL;
    ListNode* head = createNode(vals[0]);
    ListNode* curr = head;
    for (int i = 1; i < count; i++) {
        curr->next = createNode(vals[i]);
        curr = curr->next;
    }
    return head;
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
    full_c = f"{header}\n\n{boilerplate}\n{c_body.strip()}\n\n{footer}\n"
    
    os.makedirs(os.path.dirname(out_c_path), exist_ok=True)
    with open(out_c_path, 'w', encoding='utf-8') as f:
        f.write(full_c)

def run_build():
    total_generated = 0
    print("Beginning generation of C DSA repository (dsa-c)...")
    
    for topic, diffs in TOPICS_MAP.items():
        topic_dir = os.path.join(C_ROOT, topic)
        os.makedirs(topic_dir, exist_ok=True)
        
        easy_files = diffs.get('easy', [])
        med_files = diffs.get('medium', [])
        hard_files = diffs.get('hard', [])
        
        # 1. Topic README.md
        readme_content = generate_topic_readme(topic, easy_files, med_files, hard_files)
        with open(os.path.join(topic_dir, 'README.md'), 'w', encoding='utf-8') as f:
            f.write(readme_content)
            
        # 2. Files per difficulty
        for diff in ['easy', 'medium', 'hard']:
            files = diffs.get(diff, [])
            for jf in files:
                java_path = os.path.join(JAVA_ROOT, topic, diff, jf)
                c_filename = jf.replace('.java', '.c')
                c_path = os.path.join(topic_dir, diff, c_filename)
                
                generate_c_file(java_path, c_path)
                total_generated += 1
                
        print(f"[OK] Topic complete: {topic} ({len(easy_files) + len(med_files) + len(hard_files)} problems)")

    print(f"\n[DONE] Total C problem files generated: {total_generated}")

if __name__ == '__main__':
    run_build()
