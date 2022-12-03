//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_MUTER_H
#define LAB3_SOUND_PROCESSOR_MUTER_H

#include "../Converter.h"

class Muter : public Converter {
private:
    int param1;
    int param2;
public:
    explicit Muter() = default;

    explicit Muter(int par1, int par2) : param1(par1), param2(par2) {}

    void get_description() override;

    void action(WAV &wav, std::vector<std::string> files) override;
};

#endif //LAB3_SOUND_PROCESSOR_MUTER_H
