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

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class InMemoryFileSystemOOP {

    abstract static class FSNode {
        protected String name;
        public FSNode(String name) { this.name = name; }
        public String getName() { return name; }
        public abstract boolean isDirectory();
    }

    static class FSFile extends FSNode {
        private final StringBuilder content = new StringBuilder();

        public FSFile(String name) { super(name); }
        @Override public boolean isDirectory() { return false; }
        public void appendContent(String text) { content.append(text); }
        public String getContent() { return content.toString(); }
    }

    static class FSDirectory extends FSNode {
        private final Map<String, FSNode> children = new HashMap<>();

        public FSDirectory(String name) { super(name); }
        @Override public boolean isDirectory() { return true; }
        public Map<String, FSNode> getChildren() { return children; }
    }

    static class FileSystem {
        private final FSDirectory root = new FSDirectory("/");

        public List<String> ls(String path) {
            FSNode node = traverse(path);
            List<String> res = new ArrayList<>();
            if (node == null) return res;

            if (!node.isDirectory()) {
                res.add(node.getName());
                return res;
            }

            FSDirectory dir = (FSDirectory) node;
            res.addAll(dir.getChildren().keySet());
            Collections.sort(res);
            return res;
        }

        public void mkdir(String path) {
            String[] parts = path.split("/");
            FSDirectory curr = root;
            for (String part : parts) {
                if (part.isEmpty()) continue;
                curr.getChildren().putIfAbsent(part, new FSDirectory(part));
                curr = (FSDirectory) curr.getChildren().get(part);
            }
        }

        public void addContentToFile(String filePath, String content) {
            int lastSlash = filePath.lastIndexOf('/');
            String dirPath = filePath.substring(0, Math.max(1, lastSlash));
            String fileName = filePath.substring(lastSlash + 1);

            mkdir(dirPath);
            FSDirectory dir = (FSDirectory) traverse(dirPath);

            if (!dir.getChildren().containsKey(fileName)) {
                dir.getChildren().put(fileName, new FSFile(fileName));
            }
            FSFile file = (FSFile) dir.getChildren().get(fileName);
            file.appendContent(content);
        }

        public String readContentFromFile(String filePath) {
            FSNode node = traverse(filePath);
            if (node instanceof FSFile) {
                return ((FSFile) node).getContent();
            }
            return "";
        }

        private FSNode traverse(String path) {
            if (path.equals("/")) return root;
            String[] parts = path.split("/");
            FSNode curr = root;

            for (String part : parts) {
                if (part.isEmpty()) continue;
                if (!curr.isDirectory()) return null;
                FSDirectory dir = (FSDirectory) curr;
                if (!dir.getChildren().containsKey(part)) return null;
                curr = dir.getChildren().get(part);
            }
            return curr;
        }
    }

    public static void main(String[] args) {
        FileSystem fs = new FileSystem();

        System.out.println("--- In-Memory File System Demo ---");
        System.out.println("ls / : " + fs.ls("/"));

        fs.mkdir("/a/b/c");
        fs.addContentToFile("/a/b/c/d", "hello");
        System.out.println("ls / : " + fs.ls("/"));
        System.out.println("read /a/b/c/d : " + fs.readContentFromFile("/a/b/c/d"));

        fs.addContentToFile("/a/b/c/d", " world");
        System.out.println("read /a/b/c/d (after append) : " + fs.readContentFromFile("/a/b/c/d"));
    }
}

/*
 * Time Complexity: ls: O(m + k log k), mkdir: O(m), addContentToFile: O(m + len), readContent: O(m).
 * Space Complexity: O(total nodes and file contents).
 */
