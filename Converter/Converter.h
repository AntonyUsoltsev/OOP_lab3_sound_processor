//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_CONVERTER_H
#define LAB3_SOUND_PROCESSOR_CONVERTER_H

#include "..//WAV/WAV.h"

class Converter{
public:
    Converter()=default;

    virtual void action(WAV, std::vector<std::string>) = 0;

    virtual ~Converter() = default;

};
#endif //LAB3_SOUND_PROCESSOR_CONVERTER_H
