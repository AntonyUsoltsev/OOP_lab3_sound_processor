//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_MUTER_H
#define LAB3_SOUND_PROCESSOR_MUTER_H

#include "../Converter.h"

class Muter : public Converter {
public:
    int param1;
    int param2;

    explicit Muter() = default;


    void get_description() override {
        SetConsoleOutputCP(1251);
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED|FOREGROUND_BLUE);
        std::cout<< "\nMute converter (Muter):\n";
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);

        std::cout<<"  Config options: mute time_1 time_2;\n"
                        "\ttime_1 (int) - begin time (seconds from begin),\n"
                        "\ttime_2 (int) - end time (seconds from begin)\n"
                      "  Description: mute the input audio from time_1 to time_2, the rest - as in the input stream"<<std::endl;
    }

    explicit Muter(int par1, int par2) : param1(par1), param2(par2) {}

    void action(WAV &wav, std::vector<std::string> files) override {
        for (unsigned int i = param1 * wav.wav_header.sampleRate; i <= param2 * wav.wav_header.sampleRate; i++) {
            wav.data[i] = 0;
        }
    }
};

#endif //LAB3_SOUND_PROCESSOR_MUTER_H
