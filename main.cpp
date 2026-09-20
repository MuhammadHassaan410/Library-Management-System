#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    bool available;
    bool isBorrowed;
    string borrowedBy;

    Book(string t, string a) {
        title = t;
        author = a;
        available = true;
        isBorrowed = false;
        borrowedBy = "";
    }
};

class Customer {
public:
    string name;
    bool permanentCustomer;
    int totalFine;

    Customer(string n, bool permanent) {
        name = n;
        permanentCustomer = permanent;
        totalFine = 0;
    }
};

class Library {
private:
    vector<Book> books;
    vector<Customer> customers;

    Book* findBook(string title) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == title) {
                return &books[i];
            }
        }
        return NULL;
    }

    Customer* findCustomer(string name) {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].name == name) {
                return &customers[i];
            }
        }
        return NULL;
    }

public:
    void addBook(string title, string author) {
        books.push_back(Book(title, author));
        cout << "Book '" << title << "' added to the library.\n";
    }

    void addCustomer(string name, bool permanent) {
        customers.push_back(Customer(name, permanent));
        cout << "Customer '" << name << "' added.\n";
    }

    void showBooks() {
        if (books.empty()) {
            cout << "No books available in the library.\n";
            return;
        }

        cout << "Available Books:\n";

        for (int i = 0; i < books.size(); i++) {
            cout << i + 1 << ". '" << books[i].title
                 << "' by " << books[i].author;

            if (books[i].available) {
                cout << " (Available)\n";
            }
            else {
                cout << " (Borrowed by "
                     << books[i].borrowedBy << ")\n";
            }
        }
    }

    void showCustomers() {
        if (customers.empty()) {
            cout << "No customers registered yet.\n";
            return;
        }

        cout << "Registered Customers:\n";

        for (int i = 0; i < customers.size(); i++) {
            cout << i + 1 << ". " << customers[i].name;

            if (customers[i].permanentCustomer) {
                cout << " (Permanent Member)";
            }
            else {
                cout << " (Regular Member)";
            }

            cout << " | Total Fine: $"
                 << customers[i].totalFine << endl;
        }
    }

    void borrowBook(string title, string customerName) {
        Book* book = findBook(title);
        Customer* customer = findCustomer(customerName);

        if (book == NULL || customer == NULL) {
            cout << "Book or customer not found.\n";
            return;
        }

        if (!book->available) {
            cout << "Sorry, the book is already borrowed by "
                 << book->borrowedBy << ".\n";
            return;
        }

        book->available = false;
        book->isBorrowed = true;
        book->borrowedBy = customerName;

        cout << "You borrowed '" << book->title
             << "' by " << book->author << ".\n";
    }

    void returnBook(string title, string customerName) {
        Book* book = findBook(title);
        Customer* customer = findCustomer(customerName);

        if (book == NULL ||
            customer == NULL ||
            book->available ||
            book->borrowedBy != customerName) {

            cout << "Invalid return: book not found or "
                 << "not borrowed by this customer.\n";
            return;
        }

        int daysBorrowed;

        cout << "Enter number of days you borrowed the book: ";
        cin >> daysBorrowed;

        int extraDays = daysBorrowed - 7;
        int fineAmount = 0;

        if (extraDays > 0 && !customer->permanentCustomer) {
            fineAmount = extraDays * 5;
            customer->totalFine += fineAmount;

            cout << "You returned '" << book->title
                 << "' and incurred a fine of $"
                 << fineAmount << " for "
                 << extraDays << " extra days.\n";
        }
        else {
            cout << "You returned '" << book->title
                 << "' without a fine.\n";
        }

        book->available = true;
        book->isBorrowed = false;
        book->borrowedBy = "";
    }

    void searchBook(string query) {
        bool found = false;

        cout << "Search results for '" << query << "':\n";

        for (int i = 0; i < books.size(); i++) {
            if (books[i].title.find(query) != string::npos ||
                books[i].author.find(query) != string::npos) {

                cout << i + 1 << ". '"
                     << books[i].title << "' by "
                     << books[i].author;

                if (books[i].available) {
                    cout << " (Available)\n";
                }
                else {
                    cout << " (Borrowed by "
                         << books[i].borrowedBy << ")\n";
                }

                found = true;
            }
        }

        if (!found) {
            cout << "No books found matching '"
                 << query << "'.\n";
        }
    }

    void viewBorrowedBooks(string customerName) {
        bool found = false;

        cout << customerName
             << "'s borrowed books:\n";

        for (int i = 0; i < books.size(); i++) {
            if (books[i].borrowedBy == customerName) {
                cout << "- '" << books[i].title
                     << "' by " << books[i].author << "\n";
                found = true;
            }
        }

        if (!found) {
            cout << "No borrowed books found for "
                 << customerName << ".\n";
        }
    }
};

int main() {
    Library library;

    int choice;
    string title, author, customerName;
    bool permanent;

    do {
        cout << "\nLibrary Management System\n";

        cout << "1. Add Book\n";
        cout << "2. Add Customer\n";
        cout << "3. Show Books\n";
        cout << "4. Show Customers\n";
        cout << "5. Borrow Book\n";
        cout << "6. Return Book\n";
        cout << "7. Search Book\n";
        cout << "8. View Borrowed Books\n";
        cout << "9. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {

        case 1:
            cout << "Enter book title: ";
            getline(cin, title);

            cout << "Enter author: ";
            getline(cin, author);

            library.addBook(title, author);
            break;

        case 2:
            cout << "Enter customer name: ";
            getline(cin, customerName);

            cout << "Is this a permanent member? "
                 << "(1 for Yes, 0 for No): ";
            cin >> permanent;
            cin.ignore();

            library.addCustomer(customerName, permanent);
            break;

        case 3:
            library.showBooks();
            break;

        case 4:
            library.showCustomers();
            break;

        case 5:
            cout << "Enter your name: ";
            getline(cin, customerName);

            cout << "Enter book title to borrow: ";
            getline(cin, title);

            library.borrowBook(title, customerName);
            break;

        case 6:
            cout << "Enter your name: ";
            getline(cin, customerName);

            cout << "Enter book title to return: ";
            getline(cin, title);

            library.returnBook(title, customerName);
            break;

        case 7:
            cout << "Enter search query (title or author): ";
            getline(cin, title);

            library.searchBook(title);
            break;

        case 8:
            cout << "Enter your name: ";
            getline(cin, customerName);

            library.viewBorrowedBooks(customerName);
            break;

        case 9:
            cout << "Exiting the system...\n";
            break;

        default:
            cout << "You have selected an invalid choice! "
                 << "Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}
