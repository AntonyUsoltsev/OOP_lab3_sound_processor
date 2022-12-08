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
    std::string mute_file_name;
public:
    explicit Muter() = default;

    explicit Muter(int par1, int par2, const std::vector<std::string>& files) : time1(par1), time2(par2) {
        mute_file_name = "..//Converter/Muter/mute.txt";
    }

    void get_description() override;

    void action(WAV &wav) override;

    ~Muter() override = default;
};

#endif //LAB3_SOUND_PROCESSOR_MUTER_H
