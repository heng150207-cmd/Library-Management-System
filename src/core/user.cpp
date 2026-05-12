#include "User.hpp"

User::User() : id(0) {}

User::User(int id, std::string username, std::string password,
           std::string role, std::string fullName, std::string email)
    : id(id), username(username), password(password),
      role(role), fullName(fullName), email(email) {}

int         User::getId()       const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getRole()     const { return role; }
std::string User::getFullName() const { return fullName; }
std::string User::getEmail()    const { return email; }

void User::setRole(const std::string& v) { role = v; }
