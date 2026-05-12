#include "Admin.hpp"
#include "ExcelUtils.hpp"
#include "LabelMenu.hpp"
#include "Utils.hpp"
#include <iostream>
#include <algorithm>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

static int nextBookId(const vector<Book>& books) {
    int m = 0; for (auto& b : books) m = max(m, b.getId()); return m + 1;
}

void Admin::addNewBook(vector<Book>& books) {
    string title, author; int year;
    clearInput();
    cout << "\n  Title  : "; getline(cin, title);
    cout << "  Author : "; getline(cin, author);
    cout << "  Year   : "; cin >> year;
    books.emplace_back(nextBookId(books), title, author, year, true);
    ExcelManager::saveBooks(books);
    LabelMenu::printMsg(true, "Book \"" + title + "\" added (ID=" + to_string(books.back().getId()) + ").");
    pauseScreen();
}

void Admin::editBook(vector<Book>& books) {
    int id; cout << "\n  Enter Book ID to edit: "; cin >> id;
    Book* b = nullptr;
    for (auto& bk : books) if (bk.getId() == id) { b = &bk; break; }
    if (!b) { LabelMenu::printMsg(false, "Book ID not found."); pauseScreen(); return; }

    Table cur;
    cur.add_row({"Field","Current Value"});
    cur.add_row({"Title",  b->getTitle()});
    cur.add_row({"Author", b->getAuthor()});
    cur.add_row({"Year",   to_string(b->getYear())});
    cur[0].format().font_style({FontStyle::bold});
    cout << "\n  Current data:\n" << cur;
    cout << "\n  (Press Enter to keep current value)\n\n";

    clearInput();
    auto ask = [](const string& lbl, const string& cur) -> string {
        cout << "  " << lbl << " [" << cur << "]: ";
        string v; getline(cin, v); return v.empty() ? cur : v;
    };
    b->setTitle (ask("Title  ", b->getTitle()));
    b->setAuthor(ask("Author ", b->getAuthor()));
    b->setYear  (stoi(ask("Year   ", to_string(b->getYear()))));
    ExcelManager::saveBooks(books);
    LabelMenu::printMsg(true, "Book updated successfully.");
    pauseScreen();
}

void Admin::deleteBook(vector<Book>& books, const vector<BorrowRecord>& borrows) {
    int id; cout << "\n  Enter Book ID to delete: "; cin >> id;
    auto it = find_if(books.begin(), books.end(), [id](const Book& b){ return b.getId()==id; });
    if (it == books.end()) { LabelMenu::printMsg(false, "Book not found."); pauseScreen(); return; }
    for (auto& r : borrows)
        if (r.getBookId()==id && r.getStatus()=="borrowed") {
            LabelMenu::printMsg(false, "Cannot delete — book is currently borrowed.");
            pauseScreen(); return;
        }
    char yn; cout << "  Confirm delete \"" << it->getTitle() << "\"? (y/n): "; cin >> yn;
    if (tolower(yn) != 'y') { cout << "  Cancelled.\n\n"; pauseScreen(); return; }
    string title = it->getTitle();
    books.erase(it);
    ExcelManager::saveBooks(books);
    LabelMenu::printMsg(true, "Book \"" + title + "\" deleted.");
    pauseScreen();
}
