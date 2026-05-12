#include "ExcelUtils.hpp"
#include <xlnt/xlnt.hpp>

static std::string cellStr(const xlnt::cell& c) {
    try { return c.to_string(); } catch (...) { return ""; }
}
static int cellInt(const xlnt::cell& c) {
    try { std::string s = c.to_string(); return s.empty() ? 0 : std::stoi(s); }
    catch (...) { return 0; }
}

std::vector<Book> ExcelManager::loadBooks() {
    std::vector<Book> out;
    xlnt::workbook wb;
    try { wb.load(BOOKS_FILE); } catch (...) { return out; }
    auto ws = wb.active_sheet(); bool skip = true;
    for (auto row : ws.rows(false)) {
        if (skip) { skip = false; continue; }
        if (row.empty()) continue;
        int id = cellInt(row[0]); if (id == 0) continue;
        std::string avStr = cellStr(row[4]);
        bool av = (avStr == "1" || avStr == "true" || avStr == "yes");
        out.emplace_back(id, cellStr(row[1]), cellStr(row[2]), cellInt(row[3]), av);
    }
    return out;
}
void ExcelManager::saveBooks(const std::vector<Book>& v) {
    xlnt::workbook wb; auto ws = wb.active_sheet(); ws.title("Books");
    ws.cell(1,1).value("ID");     ws.cell(2,1).value("Title");
    ws.cell(3,1).value("Author"); ws.cell(4,1).value("Year");
    ws.cell(5,1).value("Available");
    int row = 2;
    for (auto& b : v) {
        ws.cell(1,row).value(b.getId());    ws.cell(2,row).value(b.getTitle());
        ws.cell(3,row).value(b.getAuthor()); ws.cell(4,row).value(b.getYear());
        ws.cell(5,row).value(b.isAvailable() ? "1" : "0"); ++row;
    }
    wb.save(BOOKS_FILE);
}

std::vector<User> ExcelManager::loadUsers() {
    std::vector<User> out;
    xlnt::workbook wb;
    try { wb.load(USERS_FILE); } catch (...) { return out; }
    auto ws = wb.active_sheet(); bool skip = true;
    for (auto row : ws.rows(false)) {
        if (skip) { skip = false; continue; }
        if (row.empty()) continue;
        int id = cellInt(row[0]); if (id == 0) continue;
        out.emplace_back(id, cellStr(row[1]), cellStr(row[2]),
                         cellStr(row[3]), cellStr(row[4]), cellStr(row[5]));
    }
    return out;
}
void ExcelManager::saveUsers(const std::vector<User>& v) {
    xlnt::workbook wb; auto ws = wb.active_sheet(); ws.title("Users");
    ws.cell(1,1).value("ID");       ws.cell(2,1).value("Username");
    ws.cell(3,1).value("Password"); ws.cell(4,1).value("Role");
    ws.cell(5,1).value("FullName"); ws.cell(6,1).value("Email");
    int row = 2;
    for (auto& u : v) {
        ws.cell(1,row).value(u.getId());       ws.cell(2,row).value(u.getUsername());
        ws.cell(3,row).value(u.getPassword()); ws.cell(4,row).value(u.getRole());
        ws.cell(5,row).value(u.getFullName()); ws.cell(6,row).value(u.getEmail());
        ++row;
    }
    wb.save(USERS_FILE);
}

std::vector<BorrowRecord> ExcelManager::loadBorrows() {
    std::vector<BorrowRecord> out;
    xlnt::workbook wb;
    try { wb.load(BORROWS_FILE); } catch (...) { return out; }
    auto ws = wb.active_sheet(); bool skip = true;
    for (auto row : ws.rows(false)) {
        if (skip) { skip = false; continue; }
        if (row.empty()) continue;
        int id = cellInt(row[0]); if (id == 0) continue;
        out.emplace_back(id, cellInt(row[1]), cellInt(row[2]),
                         cellStr(row[3]), cellStr(row[4]),
                         cellStr(row[5]), cellStr(row[6]), cellStr(row[7]));
    }
    return out;
}
void ExcelManager::saveBorrows(const std::vector<BorrowRecord>& v) {
    xlnt::workbook wb; auto ws = wb.active_sheet(); ws.title("Borrows");
    ws.cell(1,1).value("ID");         ws.cell(2,1).value("UserID");
    ws.cell(3,1).value("BookID");     ws.cell(4,1).value("Username");
    ws.cell(5,1).value("BookTitle");  ws.cell(6,1).value("BorrowDate");
    ws.cell(7,1).value("ReturnDate"); ws.cell(8,1).value("Status");
    int row = 2;
    for (auto& r : v) {
        ws.cell(1,row).value(r.getId());         ws.cell(2,row).value(r.getUserId());
        ws.cell(3,row).value(r.getBookId());     ws.cell(4,row).value(r.getUsername());
        ws.cell(5,row).value(r.getBookTitle());  ws.cell(6,row).value(r.getBorrowDate());
        ws.cell(7,row).value(r.getReturnDate()); ws.cell(8,row).value(r.getStatus());
        ++row;
    }
    wb.save(BORROWS_FILE);
}
