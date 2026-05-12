#include "LabelMenu.hpp"
#include "Utils.hpp"
#include <iostream>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

void LabelMenu::printMsg(bool ok, const string& msg) {
    Table t;
    t.add_row({(ok ? "OK" : "ERROR"), msg});
    t[0][0].format().font_color(ok ? Color::green : Color::red).font_style({FontStyle::bold});
    cout << "\n" << t << "\n\n";
}

void LabelMenu::printTitleMenu(const string& label,
                               const vector<pair<string,string>>& rows)
{
    clearScreen();
    Table t;
    t.add_row({"", "LIBRARY MANAGEMENT SYSTEM"});
    t.add_row({"NO", label});
    for (auto& r : rows) t.add_row({r.first, r.second});

    t.column(0).format().width(4);
    t.column(1).format().width(26);

    t[0][0].format().font_color(Color::cyan).font_style({FontStyle::bold})
                    .border_right("").padding_right(0);
    t[0][1].format().font_style({FontStyle::bold}).font_color(Color::cyan)
                    .font_align(FontAlign::center).padding_left(0);
    t[1][0].format().font_style({FontStyle::bold}).font_color(Color::white);
    t[1][1].format().font_style({FontStyle::bold}).font_color(Color::white);

    const Color palette[] = {
        Color::yellow, Color::magenta, Color::blue,
        Color::green,  Color::red,     Color::cyan
    };
    for (size_t i = 2; i < t.size(); ++i) {
        Color c = palette[(i-2) % 6];
        t[i][0].format().font_color(c).font_style({FontStyle::bold});
        t[i][1].format().font_color(c);
    }
    cout << "\n" << t << "\n";
}

void LabelMenu::printBookTable(const vector<Book>& books) {
    if (books.empty()) { printMsg(false, "No books found."); return; }
    Table t;
    t.add_row({"NO","Title","Author","Year","Status"});
    for (size_t i = 0; i < books.size(); ++i) {
        const Book& b = books[i];
        string status = b.isAvailable() ? "Available" : "Borrowed";
        t.add_row({to_string(i+1), b.getTitle(), b.getAuthor(), to_string(b.getYear()), status});
        size_t last = t.size()-1;
        t[last][4].format().font_color(b.isAvailable() ? Color::green : Color::red);
        if (!b.isAvailable()) t[last][4].format().font_style({FontStyle::bold});
    }
    for (size_t col = 0; col < 5; ++col)
        t[0][col].format().font_style({FontStyle::bold}).font_color(Color::cyan);
    cout << "\n" << t << "\n";
}

void LabelMenu::printBorrowTable(const vector<BorrowRecord>& recs, bool showUser) {
    if (recs.empty()) { printMsg(false, "No borrow records found."); return; }
    Table t;
    if (showUser) t.add_row({"ID","Username","Book Title","Borrow Date","Return Date","Status"});
    else          t.add_row({"ID","Book Title","Borrow Date","Return Date","Status"});
    for (auto& r : recs) {
        string ret = r.getReturnDate().empty() ? "-" : r.getReturnDate();
        if (showUser)
            t.add_row({to_string(r.getId()), r.getUsername(),
                       r.getBookTitle(), r.getBorrowDate(), ret, r.getStatus()});
        else
            t.add_row({to_string(r.getId()),
                       r.getBookTitle(), r.getBorrowDate(), ret, r.getStatus()});
        size_t last = t.size()-1, statusCol = showUser ? 5 : 4;
        t[last][statusCol].format().font_color(r.getStatus()=="borrowed" ? Color::yellow : Color::green);
    }
    size_t numCols = showUser ? 6 : 5;
    for (size_t col = 0; col < numCols; ++col)
        t[0][col].format().font_style({FontStyle::bold}).font_color(Color::cyan);
    cout << "\n" << t << "\n";
}

void LabelMenu::showAuthMenu() {
    printTitleMenu("Menu", {{"1","Login"},{"2","Register (new user)"}});
    cout << "Choose your option : ";
}

void LabelMenu::showMainMenu(const string& role) {
    printTitleMenu("Menu  [" + role + "]", {
        {"1","Add New Book"},  {"2","Edit Book Data"},
        {"3","Show All Books"},{"4","Delete Book Data"},
        {"5","Search Book Data"},{"6","Borrow Book"},
        {"7","Return Book"},  {"0","Logout"}
    });
    cout << "Choose your option : ";
}
