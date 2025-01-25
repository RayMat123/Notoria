#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// LinkedList Node
struct Node {
    string key;
    string title;
    string date;
    Node* next;
    Node(string k, string t, string d) : key(k), title(t), date(d), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}

    void insert(string key, string title, string date) {
        Node* newNode = new Node(key, title, date);
        newNode->next = head;
        head = newNode;
    }

    void remove(string key) {
        Node* current = head;
        Node* prev = nullptr;
        while (current && current->key != key) {
            prev = current;
            current = current->next;
        }
        if (current) {
            if (prev)
                prev->next = current->next;
            else
                head = current->next;
            delete current;
        }
    }

    void display() {
        Node* temp = head;
        while (temp) {
            cout << "Content: " << temp->key << endl;
            cout << "Title: " << temp->title << endl;
            cout << "Date: " << temp->date << endl;
            temp = temp->next;
        }
    }
};

// Stack for Undo Operations
class Stack {
private:
    struct StackNode {
        string operation;
        string key;
        StackNode* next;
        StackNode(string op, string k) : operation(op), key(k), next(nullptr) {}
    };
    StackNode* top;
public:
    Stack() : top(nullptr) {}

    void push(string operation, string key) {
        StackNode* newNode = new StackNode(operation, key);
        newNode->next = top;
        top = newNode;
    }

    pair<string, string> pop() {
        if (top) {
            pair<string, string> topData = {top->operation, top->key};
            StackNode* temp = top;
            top = top->next;
            delete temp;
            return topData;
        }
        return {"", ""};
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// Binary Search Tree Node
struct BSTNode {
    string key;
    string title;
    string date;
    BSTNode* left;
    BSTNode* right;
    BSTNode(string k, string t, string d) : key(k), title(t), date(d), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, string key, string title, string date) {
        if (!node) return new BSTNode(key, title, date);
        if (key < node->key)
            node->left = insert(node->left, key, title, date);
        else if (key > node->key)
            node->right = insert(node->right, key, title, date);
        return node;
    }

    BSTNode* remove(BSTNode* node, string key) {
        if (!node) return nullptr;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            BSTNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->title = temp->title;
            node->date = temp->date;
            node->right = remove(node->right, temp->key);
        }
        return node;
    }

    BSTNode* minValueNode(BSTNode* node) {
        BSTNode* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    void inorder(BSTNode* node) {
        if (node) {
            inorder(node->left);
            cout << "Content: " << node->key << ", Title: " << node->title << ", Date: " << node->date << endl;
            inorder(node->right);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(string key, string title, string date) {
        root = insert(root, key, title, date);
    }

    void remove(string key) {
        root = remove(root, key);
    }

    void display() {
        inorder(root);
    }
};

class NoteManager {
private:
    LinkedList notes;
    Stack undoStack;
    BST bst;

    void saveToFile(string key, string title, string date) {
        string filename = key + ".txt";
        ofstream file(filename);
        if (file.is_open()) {
            file << "Content: " << key << "\n";
            file << "Title: " << title << "\n";
            file << "Date: " << date << "\n";
            file.close();
        } else {
            cout << "Error opening file for saving note." << endl;
        }
    }

    void deleteFromFile(string key) {
        string filename = key + ".txt";
        ifstream file(filename);
        if (file) {
            file.close();
            remove(filename.c_str());
        } else {
            cout << "File not found for deletion." << endl;
        }
    }

public:
    void addNote(string key, string title, string date) {
        notes.insert(key, title, date);
        bst.insert(key, title, date);
        saveToFile(key, title, date);
        undoStack.push("add", key);
    }

    void deleteNote(string key) {
        notes.remove(key);
        bst.remove(key);
        deleteFromFile(key); 
        undoStack.push("delete", key);
    }

    void undoLastAction() {
        if (!undoStack.isEmpty()) {
            pair<string, string> lastAction = undoStack.pop();
            string operation = lastAction.first;
            string key = lastAction.second;
            if (operation == "add") {
                notes.remove(key);
                bst.remove(key);
                deleteFromFile(key); 
            } else if (operation == "delete") {
                cout << "Undo delete not supported yet." << endl;
            }
        }
    }

    void displayNotes() {
        cout << "Notes (Linked List):" << endl;
        notes.display();
        cout << "Notes (BST):" << endl;
        bst.display();
    }
};

int main() {
    NoteManager manager;
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Note\n";
        cout << "2. Delete Note\n";
        cout << "3. Undo Last Action\n";
        cout << "4. Display Notes\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string key, title, date;
            cout << "Enter Content: ";
            cin >> key;
            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Date: ";
            cin >> date;
            manager.addNote(key, title, date);
            break;
        }
        case 2: {
            string key;
            cout << "Enter Key to Delete: ";
            cin >> key;
            manager.deleteNote(key);
            break;
        }
        case 3:
            manager.undoLastAction();
            break;
        case 4:
            manager.displayNotes();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
