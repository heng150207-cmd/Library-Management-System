#pragma once
#include <vector>
#include "BorrowRecord.hpp"
#include "User.hpp"

class History {
public:
    static void showAll      (const std::vector<BorrowRecord>& borrows);
    static void showMyHistory(const std::vector<BorrowRecord>& borrows,
                              const User* me);
};
