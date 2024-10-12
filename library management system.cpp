#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <set>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book(int id, string title, string author) : id(id), title(title), author(author), isIssued(false) {}

    void displayBookDetails() const {
        cout << "| " << setw(5) << id << " | " << setw(20) << title << " | " << setw(20) << author << " | " 
             << (isIssued ? "Issued" : "Available") << " |" << endl;
    }
};

class Node {
public:
    Book book;
    Node* next;

    Node(Book book) : book(book), next(nullptr) {}
};

class Library {
private:
    Node* head;
    set<int> bookIds; // To ensure unique book IDs

    Node* findBookNodeById(int id) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->book.id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    Node* findBookNodeByTitle(const string& title) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->book.title == title) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

public:
    Library() : head(nullptr) {}

    void addBook(const Book& book) {
        if (bookIds.find(book.id) != bookIds.end()) {
            cout << "Book ID already exists. Please enter a unique Book ID." << endl;
            return;
        }

        Node* newNode = new Node(book);
        newNode->next = head;
        head = newNode;
        bookIds.insert(book.id);
        cout << "Book added successfully: " << book.title << endl;
    }

    void searchBookById(int id) const {
        Node* node = findBookNodeById(id);
        if (node != nullptr) {
            node->book.displayBookDetails();
        } else {
            cout << "Book not found!" << endl;
        }
    }

    void searchBookByTitle(const string& title) const {
        Node* node = findBookNodeByTitle(title);
        if (node != nullptr) {
            node->book.displayBookDetails();
        } else {
            cout << "Book not found!" << endl;
        }
    }

    void issueBook(int id) {
        Node* node = findBookNodeById(id);
        if (node != nullptr && !node->book.isIssued) {
            node->book.isIssued = true;
            cout << "Book issued successfully: " << node->book.title << endl;
        } else {
            cout << "Book not found or already issued!" << endl;
        }
    }

    void returnBook(int id) {
        Node* node = findBookNodeById(id);
        if (node != nullptr && node->book.isIssued) {
            node->book.isIssued = false;
            cout << "Book returned successfully: " << node->book.title << endl;
        } else {
            cout << "Book not found or not issued!" << endl;
        }
    }

    void listAllBooks() const {
        vector<Book> bookList;
        Node* current = head;
        while (current != nullptr) {
            bookList.push_back(current->book);
            current = current->next;
        }

        // Sort books by ID
        sort(bookList.begin(), bookList.end(), [](const Book& a, const Book& b) {
            return a.id < b.id;
        });

        if (bookList.empty()) {
            cout << "No books in the library." << endl;
        } else {
            cout << "+-------+----------------------+----------------------+----------+" << endl;
            cout << "| ID    | Title                | Author               | Status   |" << endl;
            cout << "+-------+----------------------+----------------------+----------+" << endl;
            for (const auto& book : bookList) {
                book.displayBookDetails();
            }
            cout << "+-------+----------------------+----------------------+----------+" << endl;
        }
    }

    void deleteBook(int id) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && current->book.id != id) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Book not found!" << endl;
            return;
        }

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        bookIds.erase(current->book.id);
        cout << "Book deleted successfully: " << current->book.title << endl;
        delete current;
    }

    ~Library() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

void displayMenu() {
    cout << "\n+----------------------------------------+" << endl;
    cout << "|         Library Management System      |" << endl;
    cout << "+----------------------------------------+" << endl;
    cout << "| 1. Add New Book                        |" << endl;
    cout << "| 2. Search Book by ID                   |" << endl;
    cout << "| 3. Search Book by Title                |" << endl;
    cout << "| 4. Issue Book                          |" << endl;
    cout << "| 5. Return Book                         |" << endl;
    cout << "| 6. List All Books                      |" << endl;
    cout << "| 7. Delete Book                         |" << endl;
    cout << "| 8. Exit                                |" << endl;
    cout << "+----------------------------------------+" << endl;
    cout << "Enter your choice: ";
}

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer value." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

int main() {
    Library library;
    int choice, id;
    string title, author;

    while (true) {
        displayMenu();
        choice = getIntInput("");

        switch (choice) {
            case 1:
                id = getIntInput("Enter Book ID: ");
                title = getStringInput("Enter Book Title: ");
                author = getStringInput("Enter Book Author: ");
                library.addBook(Book(id, title, author));
                break;
            case 2:
                id = getIntInput("Enter Book ID to search: ");
                library.searchBookById(id);
                break;
            case 3:
                title = getStringInput("Enter Book Title to search: ");
                library.searchBookByTitle(title);
                break;
            case 4:
                id = getIntInput("Enter Book ID to issue: ");
                library.issueBook(id);
                break;
            case 5:
                id = getIntInput("Enter Book ID to return: ");
                library.returnBook(id);
                break;
            case 6:
                library.listAllBooks();
                break;
            case 7:
                id = getIntInput("Enter Book ID to delete: ");
                library.deleteBook(id);
                break;
            case 8:
                cout << "Exiting system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
