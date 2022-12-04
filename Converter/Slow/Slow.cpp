//
// Created by Antony on 04.12.2022.
//

#include "Slow.h"

void Slow::get_description() {
    SetConsoleOutputCP(1251);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
    std::cout << "\nSlow converter (Slower):\n";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    std::cout << "  Config options: slow time_1 time_2; 0 <= time_1 < time_2\n"
                 "\ttime_1 (int) - begin time (seconds from begin),\n"
                 "\ttime_2 (int) - end time (seconds from begin)\n"
                 "  Description: Slows down the audio in the input stream from time_1 to time_2 by half\n"
                 "               WARNING: after using slow converter, the length of input audio is increase"
              << std::endl;
}

void Slow::action(WAV &wav) {
    if (time2 * wav.wav_header.sampleRate > wav.samples_count) {
        throw Exceptions("Invalid end time in slow converter");
    }
    unsigned long k = wav.samples_count + (time2 - time1) * wav.wav_header.sampleRate * 1;
    auto *data2 = new unsigned long[k];

    for (unsigned long i = 0; i < time1 * wav.wav_header.sampleRate; i++)
        data2[i] = wav.data[i];

    unsigned long j = time1 * wav.wav_header.sampleRate;

    for (unsigned int i = time1 * wav.wav_header.sampleRate; i <= time2 * wav.wav_header.sampleRate; i++) {
        data2[j] = wav.data[i];
        j++;
        data2[j] = wav.data[i];
        j++;
    }

    for (unsigned long i = time2 * wav.wav_header.sampleRate + 1; i < wav.samples_count; i++) {
        data2[j] = wav.data[i];
        j++;
    }
    wav.data = data2;
    wav.samples_count = k; //j=k+1
    wav.wav_chunk.subchunkSize = k * wav.wav_header.bitsPerSample / 8;
}

