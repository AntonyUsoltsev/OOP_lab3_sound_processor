//
// Created by Antony on 26.11.2022.
//

#include "Muter.h"

void Muter::get_description() {
    SetConsoleOutputCP(1251);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
    std::cout << "\nMute converter (Muter):\n";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    std::cout << "  Config options: mute time_1 time_2;\n"
                 "\ttime_1 (int) - begin time (seconds from begin),\n"
                 "\ttime_2 (int) - end time (seconds from begin)\n"
                 "  Description: mute the input audio from time_1 to time_2, the rest - as in the input stream"
              << std::endl;
}

void Muter::action(WAV &wav, std::vector<std::string> files) {
    for (unsigned int i = param1 * wav.wav_header.sampleRate; i <= param2 * wav.wav_header.sampleRate; i++)
        wav.data[i] = 0;
}
