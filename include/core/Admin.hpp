#pragma once
#include <vector>
#include "Book.hpp"
#include "BorrowRecord.hpp"

class Admin {
public:
    static void addNewBook (std::vector<Book>& books);
    static void editBook   (std::vector<Book>& books);
    static void deleteBook (std::vector<Book>& books,
                            const std::vector<BorrowRecord>& borrows);
};
