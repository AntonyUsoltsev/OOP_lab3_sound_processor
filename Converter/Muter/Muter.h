//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_MUTER_H
#define LAB3_SOUND_PROCESSOR_MUTER_H

#include "../Converter.h"

// Mute the input audio from time_1 to time_2, the rest - as in the input stream.

class Muter : public Converter {
private:
    int time1;
    int time2;
public:
    explicit Muter() = default;

    explicit Muter(int par1, int par2, const std::vector<std::string>& files) : time1(par1), time2(par2) {}

    void get_description() override;

    void action(WAV &wav) override;
};

#endif //LAB3_SOUND_PROCESSOR_MUTER_H
