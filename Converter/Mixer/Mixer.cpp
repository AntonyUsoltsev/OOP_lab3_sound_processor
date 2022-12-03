//
// Created by Antony on 26.11.2022.
//

#include "Mixer.h"

void Mixer::get_description() {
    SetConsoleOutputCP(1251);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
    std::cout << "\nMute converter (Muter):\n";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    std::cout << "  Config options: mute time_1 time_2; time_1 < time_2\n"
                 "\ttime_1 (int) - begin time (seconds from begin),\n"
                 "\ttime_2 (int) - end time (seconds from begin)\n"
                 "  Description: mute the input audio from time_1 to time_2, the rest - as in the input stream"
              << std::endl;
}

void Mixer::action(WAV &wav, std::vector<std::string> files) {
    if (files.size() >= param1) {
        WAV wav_second(files[param1 - 1]);
        wav_second.read_wav();
        unsigned int i = param2 * wav.wav_header.sampleRate;
        while (i < wav.samples_count && i < wav_second.samples_count) {
            wav.data[i] = (wav_second.data[i] + wav.data[i]) / 2;
            i++;
        }
    } else {
        Exceptions("Too few program arguments: no second track");
    }
}
