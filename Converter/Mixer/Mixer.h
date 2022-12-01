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

    explicit Mixer(int par1, int par2) : param1(par1), param2(par2) {}

    void action(WAV wav,std::vector<std::string> files) override {

    }
};

#endif //LAB3_SOUND_PROCESSOR_MIXER_H
