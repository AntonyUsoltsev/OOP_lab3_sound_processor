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
#include "..//Config/Config.h"

//class Sound_processor {
//public :
//    std::vector<Converter *> conv_list;
//
//    Sound_processor(WAV &wav, std::vector<Action> instructions) {
//        create_converters(instructions);
//
//    }
//
//    void create_converters(std::vector<Action> instructions) {
//
//        Converters_Factory<std::string, Converter> conv_fact;
//        conv_fact.add<Mixer>("mix");
//        conv_fact.add<Muter>("mute");
//
//        for (Action i: instructions)
//            conv_list.push_back(conv_fact.get(i.convert_type)());
//    }
//
//
//};

#endif //LAB3_SOUND_PROCESSOR_SOUND_PROCESSOR_H
