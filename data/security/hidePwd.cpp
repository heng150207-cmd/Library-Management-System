#include "HidePwd.hpp"
#include <iostream>

#ifdef _WIN32
  #include <conio.h>
#else
  #include <termios.h>
  #include <unistd.h>
#endif

using namespace std;

string HidePwd::readPassword() {
    string pwd;
#ifdef _WIN32
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') { if (!pwd.empty()) { pwd.pop_back(); cout << "\b \b" << flush; } }
        else { pwd += ch; cout << '*' << flush; }
    }
#else
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char ch;
    while (read(STDIN_FILENO, &ch, 1)==1 && ch!='\n') {
        if (ch==127||ch=='\b') { if (!pwd.empty()) { pwd.pop_back(); cout<<"\b \b"<<flush; } }
        else { pwd += ch; cout << '*' << flush; }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    cout << "\n"; return pwd;
}
