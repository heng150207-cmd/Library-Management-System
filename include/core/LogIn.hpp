#pragma once
#include <string>
#include <vector>
#include "User.hpp"

class LogIn {
public:
    static User* authenticate(std::vector<User>& users,
                              const std::string& username,
                              const std::string& password,
                              const std::string& chosenRole,
                              std::string&       outSessionRole);
    static bool loginPrompt(std::vector<User>& users,
                            User*&             outUser,
                            std::string&       outSessionRole);
};
