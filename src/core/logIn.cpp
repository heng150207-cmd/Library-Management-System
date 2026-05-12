#include "LogIn.hpp"
#include "LabelMenu.hpp"
#include "Utils.hpp"
#include "HidePwd.hpp"
#include <iostream>

using namespace std;

static int roleRank(const string& r) {
    if (r == "admin")     return 3;
    if (r == "librarian") return 2;
    return 1;
}

User* LogIn::authenticate(vector<User>& users,
                          const string& username, const string& password,
                          const string& chosenRole, string& outSessionRole)
{
    for (auto& u : users) {
        if (u.getUsername() == username && u.getPassword() == password) {
            if (roleRank(chosenRole) > roleRank(u.getRole())) return nullptr;
            outSessionRole = chosenRole;
            return &u;
        }
    }
    return nullptr;
}

bool LogIn::loginPrompt(vector<User>& users, User*& outUser, string& outSessionRole) {
    LabelMenu::printTitleMenu("Select Your Role", {
        {"1","Admin"}, {"2","Librarian"}, {"3","User"}
    });
    cout << "Choose your role : ";
    int rc; cin >> rc;
    string chosenRole = (rc==1) ? "admin" : (rc==2) ? "librarian" : "user";

    string username, password;
    cout << "\n  Username : "; cin >> username;
    cout << "  Password : ";
    password = HidePwd::readPassword();

    string sessionRole;
    User* found = authenticate(users, username, password, chosenRole, sessionRole);
    if (!found) {
        LabelMenu::printMsg(false, "Invalid username/password or insufficient role.");
        pauseScreen();
        return false;
    }
    outUser = found; outSessionRole = sessionRole;
    clearScreen();
    LabelMenu::printMsg(true, "Welcome, " + found->getFullName() + "  [" + sessionRole + "]");
    pauseScreen();
    return true;
}
