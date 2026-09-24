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

// ==========================================
    // 1. COMPOSITE DESIGN PATTERN
    // ==========================================
    interface FileSystemComponent {
        void print(const char* indent);
        long long getSize();
    }

    static class SimpleFile implements FileSystemComponent {
        static const const char* name;
        static const long long size;

        SimpleFile(const char* name, long long size) {
            this.name = name;
            this.size = size;
        }

        void print(const char* indent) {
            printf("%d- File: %d (%d KB)\n", indent, name, size);
        }

        long long getSize() { return size; }
    }

    static class DirectoryComponent implements FileSystemComponent {
        static const const char* name;
        static const int* children = new ArrayList<>();

        DirectoryComponent(const char* name) { this.name = name; }

        void add(FileSystemComponent comp) { children.add(comp); }

        void print(const char* indent) {
            printf("%d%d%d/\n", indent, Directory: ", name);
            for (FileSystemComponent child : children) {
                child.print(indent + "  ");
            }
        }

        long long getSize() {
            long long total = 0;
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
        static const const char* text;
        BasicTextView(const char* text) { this.text = text; }
        void render() { printf("%s", "[Text: \"" + text + "\"]"); }
    }

    abstract static class TextViewDecorator implements TextView {
        const TextView decoratedView;
        TextViewDecorator(TextView decoratedView) { this.decoratedView = decoratedView; }
        void render() { decoratedView.render(); }
    }

    static class BorderDecorator extends TextViewDecorator {
        BorderDecorator(TextView decoratedView) { super(decoratedView); }
        void render() {
            printf("%s", "|== ");
            super.render();
            printf("%s", " ==|");
        }
    }

    static class ScrollBarDecorator extends TextViewDecorator {
        ScrollBarDecorator(TextView decoratedView) { super(decoratedView); }
        void render() {
            super.render();
            printf("%s", " [Scrollbar Enabled]");
        }
    }

    int main(void) {
        printf("--- 1. Composite Pattern (File Hierarchy) ---\n");
        DirectoryComponent root = new DirectoryComponent("root");
        DirectoryComponent src = new DirectoryComponent("src");
        src.add(new SimpleFile("Main.java", 15));
        src.add(new SimpleFile("Utils.java", 8));

        root.add(src);
        root.add(new SimpleFile("README.md", 4));
        root.print("");
        printf("Total Hierarchy Size: " + root.getSize() + " KB\n");

        printf("\n--- 2. Decorator Pattern (UI Component Dynamic Wrapping) ---\n");
        TextView raw = new BasicTextView("Hello FrameForge");
        printf("%s", "Raw: "); raw.render(); printf("\n");

        TextView bordered = new BorderDecorator(raw);
        printf("%s", "Bordered: "); bordered.render(); printf("\n");

        TextView fullyDecorated = new ScrollBarDecorator(new BorderDecorator(raw));
        printf("%s", "Fully Decorated: "); fullyDecorated.render(); printf("\n");
        return 0;
}

/*
 * Time Complexity: Composite traversal: O(N); Decorator chaining: O(D) where D is decorators count.
 * Space Complexity: O(N) tree storage.
 */
