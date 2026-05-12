#pragma once
#include <string>

// ─────────────────────────────────────────────────────────────
//  BorrowRecord — one borrow/return transaction
// ─────────────────────────────────────────────────────────────
class BorrowRecord {
    int         id, userId, bookId;
    std::string username, bookTitle;
    std::string borrowDate, returnDate, status;

public:
    BorrowRecord();
    BorrowRecord(int id, int userId, int bookId,
                 std::string username, std::string bookTitle,
                 std::string borrowDate, std::string returnDate,
                 std::string status);

    // Getters
    int         getId()         const;
    int         getUserId()     const;
    int         getBookId()     const;
    std::string getUsername()   const;
    std::string getBookTitle()  const;
    std::string getBorrowDate() const;
    std::string getReturnDate() const;
    std::string getStatus()     const;

    // Setters
    void setReturnDate(const std::string& v);
    void setStatus    (const std::string& v);
};
