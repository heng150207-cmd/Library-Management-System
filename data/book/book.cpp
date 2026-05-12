#include "Book.hpp"

Book::Book() : id(0), year(0), available(true) {}

Book::Book(int id, std::string title, std::string author,
           int year, bool available)
    : id(id), title(title), author(author),
      year(year), available(available) {}

int         Book::getId()       const { return id; }
std::string Book::getTitle()    const { return title; }
std::string Book::getAuthor()   const { return author; }
int         Book::getYear()     const { return year; }
bool        Book::isAvailable() const { return available; }

void Book::setTitle (const std::string& v) { title     = v; }
void Book::setAuthor(const std::string& v) { author    = v; }
void Book::setYear  (int v)                { year      = v; }
void Book::setAvailable(bool v)            { available = v; }
void Book::borrow()     { available = false; }
void Book::returnBook() { available = true;  }
