#include <iostream>
using namespace std;

// Define the Book structure
struct Book {
    string title;
    string author;
    int publishedYear;
    string ISBN;
    Book* prev;
    Book* next;
};

// Function to create a new book record
Book* createNewBook(string title, string author, int publishedYear, string ISBN) {
    Book* newBook = new Book();
    newBook->title = title;
    newBook->author = author;
    newBook->publishedYear = publishedYear;
    newBook->ISBN = ISBN;
    newBook->prev = NULL;
    newBook->next = NULL;
    return newBook;
}

// Function to add a book to the doubly linked list
void addBook(Book* & head, string title, string author, int publishedYear, string ISBN) {
    Book* newBook = createNewBook(title, author, publishedYear, ISBN);
    if (head == NULL) {
        head = newBook;
    } else {
        Book* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newBook;
        newBook->prev = current;
    }
}

// Function to display book information
void displayBooks(Book* head) {
    Book* current = head;
    while (current != NULL) {
        cout << "Title: " << current->title << endl;
        cout << "Author: " << current->author << endl;
        cout << "Published Year: " << current->publishedYear << endl;
        cout << "ISBN: " << current->ISBN << endl << endl;
        current = current->next;
    }
}

// Function to search for a book by title or ISBN
Book* searchBook(Book* head, string query, bool byTitle = true) {
    Book* current = head;
    while (current != NULL) {
        if ((byTitle && current->title == query) || (!byTitle && current->ISBN == query)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to edit book information
void editBook(Book* book, string newTitle, string newAuthor, int newPublishedYear, string newISBN) {
    if (!newTitle.empty()) book->title = newTitle;
    if (!newAuthor.empty()) book->author = newAuthor;
    if (newPublishedYear != -1) book->publishedYear = newPublishedYear;
    if (!newISBN.empty()) book->ISBN = newISBN;
}

// Function to delete a book
void deleteBook(Book*& head, string query, bool byTitle = true) {
    Book* bookToDelete = searchBook(head, query, byTitle);
    if (bookToDelete == NULL) {
        cout << "Book not found." << endl;
        return;
    }
    if (bookToDelete->prev != NULL) {
        bookToDelete->prev->next = bookToDelete->next;
    } else {
        head = bookToDelete->next;
    }
    if (bookToDelete->next != NULL) {
        bookToDelete->next->prev = bookToDelete->prev;
    }
    delete bookToDelete;
}

int main() {
    Book* books = NULL;
    Book* foundBook = NULL;
    // Example usage
    addBook(books, "Title1", "Author 1", 2020, "ISBN1");
    addBook(books, "Title2", "Author 2", 2021, "ISBN2");
        int choice;
    string title, author, ISBN;
    int publishedYear;
    string query;

    do {
        cout << "========== Book Management System ==========" << endl;
        cout << "1. Add a book" << endl;
        cout << "2. Display all books" << endl;
        cout << "3. Search for a book" << endl;
        cout << "4. Edit a book" << endl;
        cout << "5. Delete a book" << endl;
        cout << "6. Exit" << endl;
        cout << "============================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book title: ";
                cin >> title;
                cout << "Enter book author: ";
                cin >> author;
                cout << "Enter published year: ";
                cin >> publishedYear;
                cout << "Enter ISBN: ";
                cin >> ISBN;
                addBook(books, title, author, publishedYear, ISBN);
                cout << "Book added successfully!" << endl;
                break;
            case 2:
                if (books == NULL) {
                    cout << "No books found." << endl;
                } else {
                    displayBooks(books);
                }
                break;
            case 3:
                cout << "Enter search query: ";
                cin >> query;
                cout << "Search by title? (1 for Yes, 0 for No): ";
                cin >> choice;
                foundBook = searchBook(books, query, choice == 1);
                if (foundBook == NULL) {
                    cout << "Book not found." << endl;
                } else {
                    displayBooks(foundBook);
                }
                break;
            case 4:
                cout << "Enter book title to edit: ";
                cin >> query;
                foundBook = searchBook(books, query);
                if (foundBook == NULL) {
                    cout << "Book not found." << endl;
                } else {
                    cout << "Enter new title (leave empty to keep existing title): ";
                    cin >> title;
                    cout << "Enter new author (leave empty to keep existing author): ";
                    cin >> author;
                    cout << "Enter new published year (-1 to keep existing published year): ";
                    cin >> publishedYear;
                    cout << "Enter new ISBN (leave empty to keep existing ISBN): ";
                    cin >> ISBN;
                    editBook(foundBook, title, author, publishedYear, ISBN);
                    cout << "Book edited successfully!" << endl;
                }
                break;
            case 5:
    cout << "Enter book title to delete: ";
    cin >> query;
    cout << "Search by title? (1 for Yes, 0 for No): ";
    cin >> choice;
    deleteBook(books, query, choice == 1);
           break;
            case 6:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;

    } while (choice != 6);

    return 0;
}
