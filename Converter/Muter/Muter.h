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

    explicit Muter(int par1, int par2) : param1(par1), param2(par2) {}

    void action(WAV wav,std::vector<std::string> files) override {
        for (unsigned int i = param1 * wav.wav_header.sampleRate; i <= param2 * wav.wav_header.sampleRate; i++) {
            wav.data[i] = 0;
        }
    }
};

#endif //LAB3_SOUND_PROCESSOR_MUTER_H
