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

import java.util.ArrayDeque;
import java.util.Deque;

class CommandAndUndoRedoManager {

    // Receiver
    static class TextEditor {
        private final StringBuilder content = new StringBuilder();

        public void append(String text) { content.append(text); }

        public void deleteLast(int length) {
            int start = Math.max(0, content.length() - length);
            content.delete(start, content.length());
        }

        public String getText() { return content.toString(); }
    }

    // Command Interface
    interface Command {
        void execute();
        void undo();
    }

    // Concrete Insert Command
    static class InsertCommand implements Command {
        private final TextEditor editor;
        private final String text;

        public InsertCommand(TextEditor editor, String text) {
            this.editor = editor;
            this.text = text;
        }

        @Override
        public void execute() {
            editor.append(text);
        }

        @Override
        public void undo() {
            editor.deleteLast(text.length());
        }
    }

    // Invoker managing Undo / Redo stacks
    static class EditorHistoryManager {
        private final Deque<Command> undoStack = new ArrayDeque<>();
        private final Deque<Command> redoStack = new ArrayDeque<>();

        public void executeCommand(Command cmd) {
            cmd.execute();
            undoStack.push(cmd);
            redoStack.clear(); // new operation invalidates redo history
        }

        public boolean undo() {
            if (undoStack.isEmpty()) {
                System.out.println("Nothing to undo.");
                return false;
            }
            Command cmd = undoStack.pop();
            cmd.undo();
            redoStack.push(cmd);
            return true;
        }

        public boolean redo() {
            if (redoStack.isEmpty()) {
                System.out.println("Nothing to redo.");
                return false;
            }
            Command cmd = redoStack.pop();
            cmd.execute();
            undoStack.push(cmd);
            return true;
        }
    }

    public static void main(String[] args) {
        TextEditor editor = new TextEditor();
        EditorHistoryManager history = new EditorHistoryManager();

        System.out.println("--- Command Pattern Undo/Redo System ---");
        history.executeCommand(new InsertCommand(editor, "Hello"));
        System.out.println("Text: \"" + editor.getText() + "\"");

        history.executeCommand(new InsertCommand(editor, " World"));
        System.out.println("Text: \"" + editor.getText() + "\"");

        history.executeCommand(new InsertCommand(editor, "!"));
        System.out.println("Text: \"" + editor.getText() + "\"");

        System.out.println("\nExecuting Undo:");
        history.undo();
        System.out.println("After 1st Undo: \"" + editor.getText() + "\"");

        history.undo();
        System.out.println("After 2nd Undo: \"" + editor.getText() + "\"");

        System.out.println("\nExecuting Redo:");
        history.redo();
        System.out.println("After Redo:     \"" + editor.getText() + "\"");
    }
}

/*
 * Time Complexity: O(L) where L is string length inserted/undone; O(1) stack operations.
 * Space Complexity: O(total command history size).
 */
