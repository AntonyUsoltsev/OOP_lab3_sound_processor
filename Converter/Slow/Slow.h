//
// Created by Antony on 02.12.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_SLOW_H
#define LAB3_SOUND_PROCESSOR_SLOW_H

#include "../Converter.h"

// Slows down the audio in the input stream from time_1 to time_2 by half.

class Slow : public Converter {
private:
    int time1;
    int time2;
public:
    explicit Slow() = default;

    explicit Slow(int par1, int par2,const std::vector<std::string>& files) : time1(par1), time2(par2) {}

    void get_description() override;

    void action(WAV &wav) override;
};


#endif //LAB3_SOUND_PROCESSOR_SLOW_H
