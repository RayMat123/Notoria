# Notoria
A Note Taking Console Based C++ App Project for University

# Note Management Application

This is a simple C++ program that allows users to manage notes through a Linked List, Binary Search Tree (BST), and undo operations using a custom stack. The application also saves and deletes note files based on their key.

## Features
- **Add Note**: Adds a new note with a unique key, title, and date.
- **Delete Note**: Deletes a note based on its unique key.
- **Undo Last Action**: Reverses the last action (add or delete).
- **Display Notes**: Shows all notes using both Linked List and Binary Search Tree representations.
- **File Operations**: Notes are saved in `.txt` files and deleted when removed from the system.

## Project Structure

### Linked List (Notes Storage)
The program uses a linked list to store notes. Each node contains:
- `key`: Unique identifier for the note.
- `title`: The title of the note.
- `date`: The date the note was created.

### Binary Search Tree (Notes Storage)
Notes are also stored in a Binary Search Tree (BST) to allow efficient searching and removal operations.

### Stack (Undo Operations)
A custom stack is implemented to store operations (add or delete) for the undo functionality.

### File Operations
Each note is saved in a `.txt` file named after its unique `key`, allowing for persistent storage on the system. Files are deleted when the corresponding note is deleted.

## Screenshots

### Main Menu

The main menu offers options to:
1. Add a new note
2. Delete an existing note
3. Undo the last action
4. Display all notes
5. Exit the application

### Adding a Note

When adding a note, the user provides:
- `Content (Key)`
- `Title`
- `Date`

### Deleting a Note

To delete a note, simply provide the `Key` of the note you want to remove.

### Undoing the Last Action


The "Undo Last Action" option allows you to reverse the last add or delete operation.

### Displaying Notes


You can view all the notes stored in the system, both in the linked list and the binary search tree format.

## How to Run the Program

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/Note-Management-App.git
