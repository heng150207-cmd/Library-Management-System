#pragma once
#include <string>

// ─────────────────────────────────────────────────────────────
//  Book — represents a single library book
// ─────────────────────────────────────────────────────────────
class Book {
    int    id;
    std::string title, author;
    int    year;
    bool   available;

public:
    Book();
    Book(int id, std::string title, std::string author, int year, bool available);

    // Getters
    int         getId()       const;
    std::string getTitle()    const;
    std::string getAuthor()   const;
    int         getYear()     const;
    bool        isAvailable() const;

    // Setters
    void setTitle (const std::string& v);
    void setAuthor(const std::string& v);
    void setYear  (int v);
    void setAvailable(bool v);

    // Actions
    void borrow();
    void returnBook();
};
