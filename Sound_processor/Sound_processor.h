//
// Created by Antony on 27.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_SOUND_PROCESSOR_H
#define LAB3_SOUND_PROCESSOR_SOUND_PROCESSOR_H

#include "..//WAV/WAV.h"
#include "..//Factory/Factory.h"
#include "..//Converter/Converter.h"
#include "..//Converter/Mixer/Mixer.h"
#include "..//Converter/Muter/Muter.h"
#include "..//Converter/Slow/Slow.h"
#include "..//Config/Config.h"

//TODO: time2>wav.len

class Sound_processor {
private:
    std::vector<Converter *> conv_list;
public:
    Sound_processor(const std::vector<Action>& instructions, const std::vector<std::string>& files);

    void convert_audio(WAV &wav);

    void make_null();

};

#endif //LAB3_SOUND_PROCESSOR_SOUND_PROCESSOR_H
