#pragma once
#include <string>
#include <vector>
#include "Book.hpp"
#include "BorrowRecord.hpp"

class LabelMenu {
public:
    static void printTitleMenu  (const std::string& label,
                                 const std::vector<std::pair<std::string,std::string>>& rows);
    static void printMsg        (bool ok, const std::string& msg);
    static void printBookTable  (const std::vector<Book>& books);
    static void printBorrowTable(const std::vector<BorrowRecord>& recs,
                                 bool showUser = true);
    static void showAuthMenu();
    static void showMainMenu(const std::string& role);
};
