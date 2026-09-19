/*
 * Problem Statement:
 * Implement Structural Design Patterns:
 * 1. Composite Pattern: Build a hierarchical File/Folder tree structure where files
 *    and folders are treated uniformly via an abstract Component.
 * 2. Decorator Pattern: Dynamically attach border and scrollbar visual decorators
 *    to UI components without modifying base classes.
 * 
 * Asked in: Adobe, Apple, Microsoft, Amazon
 */

import java.util.ArrayList;
import java.util.List;

class CompositeAndDecoratorPattern {

    // ==========================================
    // 1. COMPOSITE DESIGN PATTERN
    // ==========================================
    interface FileSystemComponent {
        void print(String indent);
        long getSize();
    }

    static class SimpleFile implements FileSystemComponent {
        private final String name;
        private final long size;

        public SimpleFile(String name, long size) {
            this.name = name;
            this.size = size;
        }

        @Override
        public void print(String indent) {
            System.out.println(indent + "- File: " + name + " (" + size + " KB)");
        }

        @Override
        public long getSize() { return size; }
    }

    static class DirectoryComponent implements FileSystemComponent {
        private final String name;
        private final List<FileSystemComponent> children = new ArrayList<>();

        public DirectoryComponent(String name) { this.name = name; }

        public void add(FileSystemComponent comp) { children.add(comp); }

        @Override
        public void print(String indent) {
            System.out.println(indent + "+ Directory: " + name + "/");
            for (FileSystemComponent child : children) {
                child.print(indent + "  ");
            }
        }

        @Override
        public long getSize() {
            long total = 0;
            for (FileSystemComponent child : children) total += child.getSize();
            return total;
        }
    }

    // ==========================================
    // 2. DECORATOR DESIGN PATTERN
    // ==========================================
    interface TextView {
        void render();
    }

    static class BasicTextView implements TextView {
        private final String text;
        public BasicTextView(String text) { this.text = text; }
        @Override
        public void render() { System.out.print("[Text: \"" + text + "\"]"); }
    }

    abstract static class TextViewDecorator implements TextView {
        protected final TextView decoratedView;
        public TextViewDecorator(TextView decoratedView) { this.decoratedView = decoratedView; }
        @Override
        public void render() { decoratedView.render(); }
    }

    static class BorderDecorator extends TextViewDecorator {
        public BorderDecorator(TextView decoratedView) { super(decoratedView); }
        @Override
        public void render() {
            System.out.print("|== ");
            super.render();
            System.out.print(" ==|");
        }
    }

    static class ScrollBarDecorator extends TextViewDecorator {
        public ScrollBarDecorator(TextView decoratedView) { super(decoratedView); }
        @Override
        public void render() {
            super.render();
            System.out.print(" [Scrollbar Enabled]");
        }
    }

    public static void main(String[] args) {
        System.out.println("--- 1. Composite Pattern (File Hierarchy) ---");
        DirectoryComponent root = new DirectoryComponent("root");
        DirectoryComponent src = new DirectoryComponent("src");
        src.add(new SimpleFile("Main.java", 15));
        src.add(new SimpleFile("Utils.java", 8));

        root.add(src);
        root.add(new SimpleFile("README.md", 4));
        root.print("");
        System.out.println("Total Hierarchy Size: " + root.getSize() + " KB");

        System.out.println("\n--- 2. Decorator Pattern (UI Component Dynamic Wrapping) ---");
        TextView raw = new BasicTextView("Hello FrameForge");
        System.out.print("Raw: "); raw.render(); System.out.println();

        TextView bordered = new BorderDecorator(raw);
        System.out.print("Bordered: "); bordered.render(); System.out.println();

        TextView fullyDecorated = new ScrollBarDecorator(new BorderDecorator(raw));
        System.out.print("Fully Decorated: "); fullyDecorated.render(); System.out.println();
    }
}

/*
 * Time Complexity: Composite traversal: O(N); Decorator chaining: O(D) where D is decorators count.
 * Space Complexity: O(N) tree storage.
 */
