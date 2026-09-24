/*
 * Problem Statement:
 * Implement the Command Design Pattern with Undo/Redo Capability for a Text Editor:
 * - Command interface: execute(), undo().
 * - Concrete commands: InsertTextCommand, DeleteTextCommand.
 * - Invoker / CommandHistoryManager: tracks undo stack and redo stack.
 * - TextEditor receiver: maintains text buffer state.
 * 
 * Asked in: Microsoft, Adobe, Google, Canva, Figma
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

// Receiver
    static class TextEditor {
        static const StringBuilder content = new StringBuilder();

        void append(const char* text) { content.append(text); }

        void deleteLast(int length) {
            int start = MAX(0, ((int)strlen(content)) - length);
            content.delete(start, ((int)strlen(content)));
        }

        const char* getText() { return content.toString(); }
    }

    // Command Interface
    interface Command {
        void execute();
        void undo();
    }

    // Concrete Insert Command
    static class InsertCommand implements Command {
        static const TextEditor editor;
        static const const char* text;

        InsertCommand(TextEditor editor, const char* text) {
            this.editor = editor;
            this.text = text;
        }

        void execute() {
            editor.append(text);
        }

        void undo() {
            editor.deleteLast(((int)strlen(text)));
        }
    }

    // Invoker managing Undo / Redo stacks
    static class EditorHistoryManager {
        static const Deque<Command> undoStack = new ArrayDeque<>();
        static const Deque<Command> redoStack = new ArrayDeque<>();

        void executeCommand(Command cmd) {
            cmd.execute();
            undoStack.push(cmd);
            redoStack.clear(); // new operation invalidates redo history
        }

        bool undo() {
            if (undoStack.isEmpty()) {
                printf("Nothing to undo.\n");
                return false;
            }
            Command cmd = undoStack.pop();
            cmd.undo();
            redoStack.push(cmd);
            return true;
        }

        bool redo() {
            if (redoStack.isEmpty()) {
                printf("Nothing to redo.\n");
                return false;
            }
            Command cmd = redoStack.pop();
            cmd.execute();
            undoStack.push(cmd);
            return true;
        }
    }

    int main(void) {
        TextEditor editor = new TextEditor();
        EditorHistoryManager history = new EditorHistoryManager();

        printf("--- Command Pattern Undo/Redo System ---\n");
        history.executeCommand(new InsertCommand(editor, "Hello"));
        printf("Text: \"" + editor.getText() + "\"\n");

        history.executeCommand(new InsertCommand(editor, " World"));
        printf("Text: \"" + editor.getText() + "\"\n");

        history.executeCommand(new InsertCommand(editor, "!"));
        printf("Text: \"" + editor.getText() + "\"\n");

        printf("\nExecuting Undo:\n");
        history.undo();
        printf("After 1st Undo: \"" + editor.getText() + "\"\n");

        history.undo();
        printf("After 2nd Undo: \"" + editor.getText() + "\"\n");

        printf("\nExecuting Redo:\n");
        history.redo();
        printf("After Redo:     \"" + editor.getText() + "\"\n");
        return 0;
}

/*
 * Time Complexity: O(L) where L is string length inserted/undone; O(1) stack operations.
 * Space Complexity: O(total command history size).
 */
