#include <Windows.h>

#include "LogIn.hpp"
#include "SignUp.hpp"
#include "Admin.hpp"
#include "Librarian.hpp"
#include "ExcelUtils.hpp"
#include "LabelMenu.hpp"
#include "Animation.hpp"
#include "Utils.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static bool checkPermission(const string& role, int option) {
    if ((option==1||option==2||option==4) && role!="admin") {
        LabelMenu::printMsg(false, "Option " + to_string(option) + " requires Admin role.");
        return false;
    }
    return true;
}

static void seedDefaults(vector<User>& users, vector<Book>& books) {
    bool hasNew = false;
    for (auto& u : users) if (u.getUsername()=="Lyheng") { hasNew=true; break; }

    if (users.empty() || !hasNew) {
        vector<User> kept;
        for (auto& u : users) {
            const string& un = u.getUsername();
            if (un!="admin"&&un!="librarian"&&un!="user1"
                &&un!="Lyheng"&&un!="Phykay"&&un!="Nary")
                kept.push_back(u);
        }
        users = kept;
        users.insert(users.begin(), User(3,"Nary",  "168168","user",     "Nary",  "nary@mail.com"));
        users.insert(users.begin(), User(2,"Phykay","150207","librarian","Phykay","phykay@lib.com"));
        users.insert(users.begin(), User(1,"Lyheng","070308","admin",    "Lyheng","lyheng@lib.com"));
        ExcelManager::saveUsers(users);
    }

    if (books.empty()) {
        books.emplace_back( 1,"Don Quixote",              "Miguel de Cervantes",       1605,true);
        books.emplace_back( 2,"Romeo and Juliet",          "William Shakespeare",        1597,true);
        books.emplace_back( 3,"Les Miserables",            "Victor Hugo",                1862,true);
        books.emplace_back( 4,"The Divine Comedy",         "Dante Alighieri",            1320,true);
        books.emplace_back( 5,"War and Peace",             "Leo Tolstoy",                1869,true);
        books.emplace_back( 6,"Pride and Prejudice",       "Jane Austen",                1813,true);
        books.emplace_back( 7,"The Trial",                 "Franz Kafka",                1925,true);
        books.emplace_back( 8,"Faust",                     "Johann Wolfgang von Goethe", 1808,true);
        books.emplace_back( 9,"Madame Bovary",             "Gustave Flaubert",           1856,true);
        books.emplace_back(10,"The Brothers Karamazov",    "Fyodor Dostoevsky",          1880,true);
        books.emplace_back(11,"Dracula",                   "Bram Stoker",                1897,true);
        books.emplace_back(12,"Anna Karenina",             "Leo Tolstoy",                1878,true);
        books.emplace_back(13,"The Stranger",              "Albert Camus",               1942,true);
        books.emplace_back(14,"The Little Prince",         "Antoine de Saint-Exupery",   1943,true);
        books.emplace_back(15,"1984",                      "George Orwell",              1949,true);
        books.emplace_back(16,"Animal Farm",               "George Orwell",              1945,true);
        books.emplace_back(17,"The Metamorphosis",         "Franz Kafka",                1915,true);
        books.emplace_back(18,"A Tale of Two Cities",      "Charles Dickens",            1859,true);
        books.emplace_back(19,"Oedipus Rex",               "Sophocles",                  -429,true);
        books.emplace_back(20,"The Odyssey",               "Homer",                      -800,true);
        books.emplace_back(21,"Tum Teav",                  "Unknown",                    1915,true);
        books.emplace_back(22,"Kolap Pailin",              "Nhok Them",                  1936,true);
        books.emplace_back(23,"Phka Srapon",               "Nouk Savath",                1949,true);
        books.emplace_back(24,"Sophat",                    "Rim Kin",                    1961,true);
        books.emplace_back(25,"A New Sun Rises Over the Old Land","Suon Sorin",          1961,true);
        books.emplace_back(26,"The Anarchist",             "Soth Polin",                 1980,true);
        books.emplace_back(27,"First They Killed My Father","Loung Ung",                 2000,true);
        books.emplace_back(28,"Golden Silk",               "Sayon Syprasoeuth",          2009,true);
        ExcelManager::saveBooks(books);
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("cls");

    Animation::animationLoading();
    Animation::header();

    vector<Book>         books   = ExcelManager::loadBooks();
    vector<User>         users   = ExcelManager::loadUsers();
    vector<BorrowRecord> borrows = ExcelManager::loadBorrows();
    seedDefaults(users, books);

    User*  me          = nullptr;
    string sessionRole = "";

    while (true) {
        while (me == nullptr) {
            LabelMenu::showAuthMenu();
            int ch; cin >> ch;
            switch (ch) {
                case 1: LogIn::loginPrompt(users, me, sessionRole); break;
                case 2: SignUp::registerUser(users);                break;
                default: LabelMenu::printMsg(false,"Invalid choice."); pauseScreen();
            }
        }

        while (me != nullptr) {
            LabelMenu::showMainMenu(sessionRole);
            int ch; cin >> ch;
            if (!checkPermission(sessionRole, ch)) { pauseScreen(); continue; }
            bool isLib = (sessionRole=="admin"||sessionRole=="librarian");
            switch (ch) {
                case 1: Admin::addNewBook(books);                          break;
                case 2: Admin::editBook(books);                            break;
                case 3: Librarian::showAllBooks(books);                    break;
                case 4: Admin::deleteBook(books, borrows);                 break;
                case 5: Librarian::searchBook(books);                      break;
                case 6: Librarian::borrowBook(books, borrows, me, isLib);  break;
                case 7: Librarian::returnBook(books, borrows, me, isLib);  break;
                case 0:
                    cout << "\n  Goodbye, " << me->getFullName() << "!\n\n";
                    pauseScreen(); me=nullptr; sessionRole=""; break;
                default: LabelMenu::printMsg(false,"Invalid choice."); pauseScreen();
            }
        }
    }
    return 0;
}
