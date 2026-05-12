#include "SignUp.hpp"
#include "ExcelUtils.hpp"
#include "LabelMenu.hpp"
#include "Utils.hpp"
#include "HidePwd.hpp"
#include <iostream>
#include <algorithm>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

static int nextUserId(const vector<User>& users) {
    int m = 0; for (auto& u : users) m = max(m, u.getId()); return m + 1;
}

void SignUp::registerUser(vector<User>& users) {
    // ── Public registration: always creates a User account only.
    // ── Admin and Librarian accounts are created by an Admin after login.
    const string role = "user";

    LabelMenu::printTitleMenu("Register New Account", {
        {"", "Role is set to: User"}
    });

    string fullName, username, password, email;
    clearInput();
    cout << "\n  Full Name : "; getline(cin, fullName);
    cout << "  Username  : "; getline(cin, username);

    // Duplicate username check
    for (auto& u : users) {
        if (u.getUsername() == username) {
            LabelMenu::printMsg(false, "Username \"" + username + "\" already exists.");
            pauseScreen();
            return;
        }
    }

    cout << "  Password  : ";
    password = HidePwd::readPassword();
    cout << "  Email     : "; getline(cin, email);

    int newId = nextUserId(users);
    users.emplace_back(newId, username, password, role, fullName, email);
    ExcelManager::saveUsers(users);

    Table t;
    t.add_row({"REGISTRATION SUCCESS", ""});
    t.add_row({"ID",        to_string(newId)});
    t.add_row({"Full Name", fullName});
    t.add_row({"Username",  username});
    t.add_row({"Role",      role});
    t.add_row({"Email",     email});
    t.add_row({"Status",    "You can now log in!"});
    t[0].format().font_style({FontStyle::bold}).font_color(Color::green).font_align(FontAlign::center);
    t[6][1].format().font_color(Color::green).font_style({FontStyle::bold});
    cout << "\n" << t << "\n\n";
    pauseScreen();
}
