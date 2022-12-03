//
// Created by Antony on 02.12.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_SLOW_H
#define LAB3_SOUND_PROCESSOR_SLOW_H

#include "../Converter.h"

class Slow : public Converter {
public:
    int param1;
    int param2;

    explicit Slow() = default;

    void get_description() override {
        SetConsoleOutputCP(1251);
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
        std::cout << "\nSlow converter (Slower):\n";
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        std::cout <<"  Config options: slow time_1 time_2;\n"
                  "\ttime_1 (int) - begin time (seconds from begin),\n"
                  "\ttime_2 (int) - end time (seconds from begin)\n"
                  "  Description: Slows down the audio in the input stream from time_1 to time_2 by half\n"
                  "               WARNING: after using slow converter, the length of input audio is increase"<<std::endl;
    }

    explicit Slow(int par1, int par2) : param1(par1), param2(par2) {}

    void action(WAV &wav, std::vector<std::string> files) override {
        unsigned long k =
                wav.samples_count + (param2 * wav.wav_header.sampleRate - param1 * wav.wav_header.sampleRate) * 1;
        auto *data2 = new unsigned long[k];
        for (unsigned long i = 0; i < param1 * wav.wav_header.sampleRate; i++)
            data2[i] = wav.data[i];
        unsigned long j = param1 * wav.wav_header.sampleRate;
        for (unsigned int i = param1 * wav.wav_header.sampleRate; i <= param2 * wav.wav_header.sampleRate; i++) {
            data2[j] = wav.data[i];
            j++;
            data2[j] = wav.data[i];
            j++;
        }
        for (unsigned long i = param2 * wav.wav_header.sampleRate + 1; i < wav.samples_count; i++) {
            data2[j] = wav.data[i];
            j++;
        }
        wav.data = data2;
        wav.samples_count = k;
        wav.wav_chunk.subchunkSize = k * wav.wav_header.bitsPerSample / 8;
    }
};

#endif //LAB3_SOUND_PROCESSOR_SLOW_H
