//
// Created by Antony on 02.12.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_SLOW_H
#define LAB3_SOUND_PROCESSOR_SLOW_H

#include "../Converter.h"

class Slow : public Converter {
private:
    int param1;
    int param2;
public:
    explicit Slow() = default;

    explicit Slow(int par1, int par2) : param1(par1), param2(par2) {}

    void get_description() override;

    void action(WAV &wav, std::vector<std::string> files) override;
};


#endif //LAB3_SOUND_PROCESSOR_SLOW_H
