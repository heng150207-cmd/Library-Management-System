#include "Animation.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

void Animation::animationLoading() {
    const int barWidth = 40;
    cout << "\n\n  Loading Library System...\n\n  [";
    for (int i = 0; i <= barWidth; ++i) {
        for (int j = 0; j < i;        ++j) cout << "\xE2\x96\x88";
        for (int j = i; j < barWidth; ++j) cout << "\xE2\x96\x91";
        int pct = static_cast<int>((i * 100.0) / barWidth);
        cout << "] " << pct << "%   \r" << flush;
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    cout << "\n\n";
}

void Animation::header() {
    Table t;
    t.add_row({"LIBRARY MANAGEMENT SYSTEM"});
    t.add_row({"OOP  |  Excel (xlnt)  |  Tabulate"});
    t.add_row({"Roles: Admin  |  Librarian  |  User"});
    t[0][0].format().font_style({FontStyle::bold}).font_color(Color::cyan).font_align(FontAlign::center);
    t[1][0].format().font_color(Color::yellow).font_align(FontAlign::center);
    t[2][0].format().font_color(Color::green).font_align(FontAlign::center);
    cout << "\n" << t << "\n\n";
}
