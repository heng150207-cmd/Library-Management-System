#pragma once
#include <vector>
#include "Book.hpp"
#include "BorrowRecord.hpp"
#include "User.hpp"

class Librarian {
public:
    static void showAllBooks(const std::vector<Book>& books);
    static void searchBook  (const std::vector<Book>& books);
    static void borrowBook  (std::vector<Book>& books,
                             std::vector<BorrowRecord>& borrows,
                             User* me, bool isLibrarianOrAdmin);
    static void returnBook  (std::vector<Book>& books,
                             std::vector<BorrowRecord>& borrows,
                             User* me, bool isLibrarianOrAdmin);
private:
    static void exportBooksToExcel(const std::vector<Book>& books);
};
