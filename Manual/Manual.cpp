//
// Created by Antony on 04.12.2022.
//

#include "Manual.h"

void Manual::get_manual() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    std::cout << "Converters Info:";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    Muter muter;
    muter.get_description();
    Mixer mixer;
    mixer.get_description();
    Slow slow;
    slow.get_description();
}
