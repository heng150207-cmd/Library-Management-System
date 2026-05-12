#include "BorrowRecord.hpp"

BorrowRecord::BorrowRecord() : id(0), userId(0), bookId(0) {}

BorrowRecord::BorrowRecord(int id, int userId, int bookId,
                           std::string username, std::string bookTitle,
                           std::string borrowDate, std::string returnDate,
                           std::string status)
    : id(id), userId(userId), bookId(bookId),
      username(username), bookTitle(bookTitle),
      borrowDate(borrowDate), returnDate(returnDate), status(status) {}

int         BorrowRecord::getId()         const { return id; }
int         BorrowRecord::getUserId()     const { return userId; }
int         BorrowRecord::getBookId()     const { return bookId; }
std::string BorrowRecord::getUsername()   const { return username; }
std::string BorrowRecord::getBookTitle()  const { return bookTitle; }
std::string BorrowRecord::getBorrowDate() const { return borrowDate; }
std::string BorrowRecord::getReturnDate() const { return returnDate; }
std::string BorrowRecord::getStatus()     const { return status; }

void BorrowRecord::setReturnDate(const std::string& v) { returnDate = v; }
void BorrowRecord::setStatus    (const std::string& v) { status     = v; }
