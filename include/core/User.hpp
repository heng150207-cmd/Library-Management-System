#pragma once
#include <string>

// ─────────────────────────────────────────────────────────────
//  User — library member / staff account
// ─────────────────────────────────────────────────────────────
class User {
    int         id;
    std::string username, password, role, fullName, email;

public:
    User();
    User(int id, std::string username, std::string password,
         std::string role, std::string fullName, std::string email);

    // Getters
    int         getId()       const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRole()     const;
    std::string getFullName() const;
    std::string getEmail()    const;

    // Setters
    void setRole(const std::string& v);
};
