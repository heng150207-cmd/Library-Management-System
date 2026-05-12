#include "Librarian.hpp"
#include "ExcelUtils.hpp"
#include "LabelMenu.hpp"
#include "Utils.hpp"
#include <iostream>
#include <algorithm>
#include <tabulate/table.hpp>
#include <xlnt/xlnt.hpp>

using namespace std;
using namespace tabulate;

void Librarian::showAllBooks(const vector<Book>& books) {
    LabelMenu::printTitleMenu("Show All Books", {
        {"1","Show in console (table)"},
        {"2","Export to Excel (books_export.xlsx)"}
    });
    cout << "Choose your option : "; int ch; cin >> ch;
    if (ch == 1) {
        clearScreen();
        cout << "\n  Total books: " << books.size() << "\n";
        LabelMenu::printBookTable(books); pauseScreen();
    } else if (ch == 2) {
        Librarian::exportBooksToExcel(books);
    } else { LabelMenu::printMsg(false, "Invalid choice."); pauseScreen(); }
}

void Librarian::exportBooksToExcel(const vector<Book>& books) {
    const string EXPORT_FILE = "books_export.xlsx";
    xlnt::workbook wb; auto ws = wb.active_sheet(); ws.title("All Books");
    const vector<string> headers = {"ID","Title","Author","Year","Status"};
    for (size_t c = 0; c < headers.size(); ++c)
        ws.cell(static_cast<xlnt::column_t>(c+1), 1).value(headers[c]);
    int row = 2;
    for (auto& b : books) {
        ws.cell(1,row).value(b.getId());   ws.cell(2,row).value(b.getTitle());
        ws.cell(3,row).value(b.getAuthor()); ws.cell(4,row).value(b.getYear());
        ws.cell(5,row).value(b.isAvailable() ? "Available" : "Borrowed"); ++row;
    }
    ws.cell(1,row).value("Total"); ws.cell(2,row).value(static_cast<int>(books.size()));
    ws.column_properties(xlnt::column_t(1)).width = 6;
    ws.column_properties(xlnt::column_t(2)).width = 38;
    ws.column_properties(xlnt::column_t(3)).width = 28;
    ws.column_properties(xlnt::column_t(4)).width = 8;
    ws.column_properties(xlnt::column_t(5)).width = 12;
    try { wb.save(EXPORT_FILE); LabelMenu::printMsg(true, "Exported to \"" + EXPORT_FILE + "\"."); }
    catch (const exception& e) { LabelMenu::printMsg(false, string("Export failed: ") + e.what()); }
    pauseScreen();
}

void Librarian::searchBook(const vector<Book>& books) {
    LabelMenu::printTitleMenu("Search Book By", {{"1","Title"},{"2","Author"},{"3","Year"}});
    cout << "Choose your option : "; int ch; cin >> ch;
    string kw; clearInput(); cout << "  Keyword : "; getline(cin, kw);
    string kwL = toLower(kw);
    vector<Book> res;
    for (auto& b : books) {
        string field = (ch==1) ? b.getTitle() : (ch==2) ? b.getAuthor() : to_string(b.getYear());
        if (toLower(field).find(kwL) != string::npos) res.push_back(b);
    }
    if (res.empty()) LabelMenu::printMsg(false, "No books found for \"" + kw + "\".");
    else { cout << "\n  Found " << res.size() << " result(s):\n"; LabelMenu::printBookTable(res); }
    pauseScreen();
}

static int nextBorrowId(const vector<BorrowRecord>& borrows) {
    int m = 0; for (auto& r : borrows) m = max(m, r.getId()); return m + 1;
}

void Librarian::borrowBook(vector<Book>& books, vector<BorrowRecord>& borrows,
                           User* me, bool isLibrarianOrAdmin)
{
    vector<Book> avail;
    for (auto& b : books) if (b.isAvailable()) avail.push_back(b);
    if (avail.empty()) { LabelMenu::printMsg(false, "No available books."); pauseScreen(); return; }
    cout << "\n  Available Books:\n"; LabelMenu::printBookTable(avail);

    if (!isLibrarianOrAdmin) {
        int cnt = 0;
        for (auto& r : borrows) if (r.getUserId()==me->getId() && r.getStatus()=="borrowed") cnt++;
        if (cnt >= 3) { LabelMenu::printMsg(false, "Borrow limit (max 3) reached."); pauseScreen(); return; }
    }

    int bookId; cout << "  Enter Book ID to borrow : "; cin >> bookId;
    Book* b = nullptr;
    for (auto& bk : books) if (bk.getId()==bookId) { b=&bk; break; }
    if (!b)               { LabelMenu::printMsg(false, "Book not found.");     pauseScreen(); return; }
    if (!b->isAvailable()){ LabelMenu::printMsg(false, "Book not available."); pauseScreen(); return; }
    for (auto& r : borrows)
        if (r.getUserId()==me->getId() && r.getBookId()==bookId && r.getStatus()=="borrowed")
            { LabelMenu::printMsg(false, "You already borrowed this book."); pauseScreen(); return; }

    b->borrow();
    borrows.emplace_back(nextBorrowId(borrows), me->getId(), bookId,
                         me->getUsername(), b->getTitle(), currentDate(), "", "borrowed");
    ExcelManager::saveBooks(books); ExcelManager::saveBorrows(borrows);

    auto& rec = borrows.back();
    Table receipt;
    receipt.add_row({"Borrow Receipt",""});
    receipt.add_row({"Borrow ID",   to_string(rec.getId())});
    receipt.add_row({"Borrower",    me->getFullName()});
    receipt.add_row({"Book Title",  b->getTitle()});
    receipt.add_row({"Borrow Date", rec.getBorrowDate()});
    receipt.add_row({"Due",         "Return within 14 days"});
    receipt[0].format().font_style({FontStyle::bold}).font_color(Color::green);
    cout << "\n" << receipt << "\n\n"; pauseScreen();
}

void Librarian::returnBook(vector<Book>& books, vector<BorrowRecord>& borrows,
                           User* me, bool isLibrarianOrAdmin)
{
    vector<BorrowRecord*> active;
    for (auto& r : borrows)
        if (r.getStatus()=="borrowed" && (isLibrarianOrAdmin || r.getUserId()==me->getId()))
            active.push_back(&r);
    if (active.empty()) { LabelMenu::printMsg(false, "No active borrows."); pauseScreen(); return; }

    vector<BorrowRecord> tmp; for (auto* p : active) tmp.push_back(*p);
    LabelMenu::printBorrowTable(tmp, isLibrarianOrAdmin);

    int bid; cout << "  Enter Borrow ID to return : "; cin >> bid;
    BorrowRecord* rec = nullptr;
    for (auto& r : borrows)
        if (r.getId()==bid && r.getStatus()=="borrowed" &&
            (isLibrarianOrAdmin || r.getUserId()==me->getId()))
            { rec=&r; break; }
    if (!rec) { LabelMenu::printMsg(false, "Record not found."); pauseScreen(); return; }

    for (auto& b : books) if (b.getId()==rec->getBookId()) { b.returnBook(); break; }
    rec->setReturnDate(currentDate()); rec->setStatus("returned");
    ExcelManager::saveBooks(books); ExcelManager::saveBorrows(borrows);

    Table sum;
    sum.add_row({"Return Summary",""});
    sum.add_row({"Borrow ID",   to_string(rec->getId())});
    sum.add_row({"Borrower",    rec->getUsername()});
    sum.add_row({"Book Title",  rec->getBookTitle()});
    sum.add_row({"Return Date", rec->getReturnDate()});
    sum.add_row({"Status",      "RETURNED"});
    sum[0].format().font_style({FontStyle::bold}).font_color(Color::green);
    sum[5][1].format().font_color(Color::green).font_style({FontStyle::bold});
    cout << "\n" << sum << "\n\n"; pauseScreen();
}
