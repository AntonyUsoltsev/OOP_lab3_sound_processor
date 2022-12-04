//
// Created by Antony on 26.11.2022.
//

#include "Mixer.h"

void Mixer::get_description() {
    SetConsoleOutputCP(1251);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
    std::cout << "\nMix converter (Mixer):\n";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    std::cout << "  Config options: mix $mix_inp time;\n"
                 "\t$mix_inp ($int) - number of additional stream to mix (>= 2),\n"
                 "\ttime (int) - insertion point  (seconds from begin >= 0)\n"
                 "  Description:Each sample is the average of the corresponding samples of the input streams. \n"
                 "             The length of the output stream corresponds to the length of the main input stream. \n"
                 "             If the additional stream is longer than the main one, then part of it is cut off (not used),\n"
                 "             and if it is shorter, then the output stream outside it is equal to the main input stream."
              << std::endl;
}

void Mixer::action(WAV &wav) {
    if (ins_time * wav.wav_header.sampleRate > wav.samples_count) {
        throw Exceptions("Invalid insertion time in mix converter");
    }
    WAV wav_second(extra_aud_file);
    wav_second.read_wav();
    unsigned int i = ins_time * wav.wav_header.sampleRate;
    while (i < wav.samples_count && i < wav_second.samples_count) {
        wav.data[i] = (wav_second.data[i] + wav.data[i]) / 2;
        i++;
    }
}