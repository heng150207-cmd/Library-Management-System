#pragma once
#include <vector>
#include <string>
#include "Book.hpp"
#include "User.hpp"
#include "BorrowRecord.hpp"

inline const std::string BOOKS_FILE   = "books.xlsx";
inline const std::string USERS_FILE   = "users.xlsx";
inline const std::string BORROWS_FILE = "borrows.xlsx";

class ExcelManager {
public:
    static std::vector<Book>         loadBooks();
    static void                      saveBooks  (const std::vector<Book>& v);
    static std::vector<User>         loadUsers();
    static void                      saveUsers  (const std::vector<User>& v);
    static std::vector<BorrowRecord> loadBorrows();
    static void                      saveBorrows(const std::vector<BorrowRecord>& v);
};
