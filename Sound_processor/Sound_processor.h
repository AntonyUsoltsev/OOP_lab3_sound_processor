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

class Sound_processor {
public :
    std::vector<Converter *> conv_list;

    Sound_processor(WAV &wav, std::vector<Action> instructions, std::vector<std::string> files) {
        create_converters(instructions);
        for (auto cl: conv_list) {
            cl->action(wav, files);
        }
        make_null();
    }

    void create_converters(std::vector<Action> instructions) {

        Converters_Factory<std::string, Converter, int, int> conv_fact;
        conv_fact.add<Mixer>("mix");
        conv_fact.add<Muter>("mute");
        conv_fact.add<Slow>("slow");

        for (Action i: instructions)
            conv_list.push_back(conv_fact.get(i.convert_type)(i.frst_arg, i.sec_arg));
    }

    void make_null() {
        for (auto &i: conv_list)
            delete i;
    }

};

#endif //LAB3_SOUND_PROCESSOR_SOUND_PROCESSOR_H
