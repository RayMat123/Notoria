#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Node for Linked List (for managing tags and titles dynamically)
struct Node {
    string data;
    Node* next;

    Node(string value) : data(value), next(nullptr) {}
};

// Linked List Implementation
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void addNode(const string& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void printList() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data;
            if (temp->next) cout << ", ";
            temp = temp->next;
        }
    }

    void clear() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    ~LinkedList() { clear(); }
};

// Class for Note
class Note {
public:
    string date;
    string title;
    LinkedList tags;
    string content;

    Note() {}

    void inputNote() {
        cout << "Enter Date (YYYY-MM-DD): ";
        cin >> date;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Tags (comma-separated): ";
        string tagInput;
        getline(cin, tagInput);
        processTags(tagInput);

        cout << "Enter Content: ";
        getline(cin, content);
    }

    void displayNote() const {
        cout << "Date: " << date << "\nTitle: " << title << "\nTags: ";
        tags.printList();
        cout << "\nContent: " << content << endl;
    }

    void saveNote() const {
        string fileName = title + "_" + date + ".txt";
        ofstream file(fileName);
        if (file.is_open()) {
            file << date << "\n" << title << "\n" << content;
            file.close();
            cout << "Note saved as " << fileName << "\n";
        } else {
            cerr << "Error: Could not save note.\n";
        }
    }

private:
    void processTags(const string& tagInput) {
        string tag;
        for (char ch : tagInput) {
            if (ch == ',') {
                if (!tag.empty()) {
                    tags.addNode(tag);
                    tag.clear();
                }
            } else {
                tag += ch;
            }
        }
        if (!tag.empty()) tags.addNode(tag);
    }
};

int main() {
    Note myNote;
    myNote.inputNote();
    myNote.displayNote();
    myNote.saveNote();

    return 0;
}
