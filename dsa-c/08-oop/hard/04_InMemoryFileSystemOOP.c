/*
 * Problem Statement:
 * Design an In-Memory File System (LeetCode 588):
 * - ls: Given a path, if it is a file path, return a list containing only its name.
 *       If it is a directory path, return the list of file and directory names in alphabetical order.
 * - mkdir: Given a path, create a new directory according to the path if it doesn't exist.
 * - addContentToFile: If file doesn't exist, create it with given content. If it exists, append content.
 * - readContentFromFile: Return content from the specified file.
 * 
 * Asked in: Amazon, Google, Uber, Salesforce, Baidu
 */

#include <stdio.h>
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
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

abstract static class FSNode {
        const char* name;
        FSNode(const char* name) { this.name = name; }
        const char* getName() { return name; }
        abstract bool isDirectory();
    }

    static class FSFile extends FSNode {
        static const StringBuilder content = new StringBuilder();

        FSFile(const char* name) { super(name); }
        bool isDirectory() { return false; }
        void appendContent(const char* text) { content.append(text); }
        const char* getContent() { return content.toString(); }
    }

    static class FSDirectory extends FSNode {
        static const Map<const char*, FSNode> children = new HashMap<>();

        FSDirectory(const char* name) { super(name); }
        bool isDirectory() { return true; }
        Map<const char*, FSNode> getChildren() { return children; }
    }

    static class FileSystem {
        static const FSDirectory root = new FSDirectory("/");

        int* ls(const char* path) {
            FSNode node = traverse(path);
            int* res = new ArrayList<>();
            if (node == NULL) return res;

            if (!node.isDirectory()) {
                res.add(node.getName());
                return res;
            }

            FSDirectory dir = (FSDirectory) node;
            res.addAll(dir.getChildren().keySet());
            Collections.sort(res);
            return res;
        }

        void mkdir(const char* path) {
            const char*[] parts = path.split("/");
            FSDirectory curr = root;
            for (const char* part : parts) {
                if (part.isEmpty()) continue;
                curr.getChildren().putIfAbsent(part, new FSDirectory(part));
                curr = (FSDirectory) curr.getChildren().get(part);
            }
        }

        void addContentToFile(const char* filePath, const char* content) {
            int lastSlash = filePath.lastIndexOf('/');
            const char* dirPath = filePath.substring(0, MAX(1, lastSlash));
            const char* fileName = filePath.substring(lastSlash + 1);

            mkdir(dirPath);
            FSDirectory dir = (FSDirectory) traverse(dirPath);

            if (!dir.getChildren().containsKey(fileName)) {
                dir.getChildren().put(fileName, new FSFile(fileName));
            }
            FSFile file = (FSFile) dir.getChildren().get(fileName);
            file.appendContent(content);
        }

        const char* readContentFromFile(const char* filePath) {
            FSNode node = traverse(filePath);
            if (node instanceof FSFile) {
                return ((FSFile) node).getContent();
            }
            return "";
        }

        static FSNode traverse(const char* path) {
            if ((strcmp(path, "/") == 0)) return root;
            const char*[] parts = path.split("/");
            FSNode curr = root;

            for (const char* part : parts) {
                if (part.isEmpty()) continue;
                if (!curr.isDirectory()) return NULL;
                FSDirectory dir = (FSDirectory) curr;
                if (!dir.getChildren().containsKey(part)) return NULL;
                curr = dir.getChildren().get(part);
            }
            return curr;
        }
    }

    int main(void) {
        FileSystem fs = new FileSystem();

        printf("--- In-Memory File System Demo ---\n");
        printf("ls / : %d\n", fs.ls("/"));

        fs.mkdir("/a/b/c");
        fs.addContentToFile("/a/b/c/d", "hello");
        printf("ls / : %d\n", fs.ls("/"));
        printf("read /a/b/c/d : %d\n", fs.readContentFromFile("/a/b/c/d"));

        fs.addContentToFile("/a/b/c/d", " world");
        printf("read /a/b/c/d (after append) : %d\n", fs.readContentFromFile("/a/b/c/d"));
        return 0;
}

/*
 * Time Complexity: ls: O(m + k log k), mkdir: O(m), addContentToFile: O(m + len), readContent: O(m).
 * Space Complexity: O(total nodes and file contents).
 */
