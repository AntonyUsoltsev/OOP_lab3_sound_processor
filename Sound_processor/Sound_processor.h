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
public :
    std::vector<Converter *> conv_list;

    Sound_processor(WAV &wav, const std::vector<Action>& instructions, const std::vector<std::string>& files) {
        create_converters(instructions, files);
        int con_count = instructions.size();
        int cur = 1;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
        for (auto cl: conv_list) {
            std::cout << "Converting "<<cur* 100/ con_count <<"%\n";
            //std::cout << "=";
            cl->action(wav);
            cur++;
        }
        std::cout << "Converting done!\n";
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        make_null();
    }

    void create_converters(const std::vector<Action>& instructions,  const std::vector<std::string>& files) {

        Converters_Factory<std::string, Converter, int, int, std::vector<std::string>> conv_fact;
        conv_fact.add<Mixer>("mix");
        conv_fact.add<Muter>("mute");
        conv_fact.add<Slow>("slow");

        for (const Action& i: instructions)
            conv_list.push_back(conv_fact.get(i.convert_type)(i.frst_arg, i.sec_arg, files));
    }

    void make_null() {
        for (auto &i: conv_list)
            delete i;
    }

};

#endif //LAB3_SOUND_PROCESSOR_SOUND_PROCESSOR_H
