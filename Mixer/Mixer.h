//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_MIXER_H
#define LAB3_SOUND_PROCESSOR_MIXER_H

#include "../Converter/Converter.h"

class Mixer : public Converter{
public:
    int mix();
};

#endif //LAB3_SOUND_PROCESSOR_MIXER_H
