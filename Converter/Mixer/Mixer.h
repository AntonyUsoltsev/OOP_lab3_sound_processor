//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_MIXER_H
#define LAB3_SOUND_PROCESSOR_MIXER_H

#include "../Converter.h"

class Mixer : public Converter {
public:
    int param1;
    int param2;

    explicit Mixer() = default;

    explicit Mixer(int par1, int par2) : param1(par1), param2(par2) {}

    void get_description() override {
        SetConsoleOutputCP(1251);
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
        std::cout << "\nMix converter (Mixer):\n";
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        std::cout << "  Config options: mix $mix_inp time;\n"
                     "\t$mix_inp ($int) - number of additional stream to mix (from 2),\n"
                     "\ttime (int) - insertion point ( (seconds from begin)\n"
                     "  Description:Each sample is the average of the corresponding samples of the input streams. \n"
                     "             The length of the output stream corresponds to the length of the main input stream. \n"
                     "             If the additional stream is longer than the main one, then part of it is cut off (not used),\n"
                     "             and if it is shorter, then the output stream outside it is equal to the main input stream."<<std::endl;
    }

    void action(WAV &wav, std::vector<std::string> files) override {
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
};

#endif //LAB3_SOUND_PROCESSOR_MIXER_H
