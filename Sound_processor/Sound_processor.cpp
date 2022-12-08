//
// Created by Antony on 27.11.2022.
//

#include "Sound_processor.h"

Sound_processor::Sound_processor(const std::vector<Action> &instructions, const std::vector<std::string> &files) {
    Converters_Factory<std::string, Converter, int, int, std::vector<std::string>> conv_fact;
    conv_fact.add<Mixer>("mix");
    conv_fact.add<Muter>("mute");
    conv_fact.add<Slow>("slow");

    for (const Action &i: instructions)
        conv_list.push_back(conv_fact.get(i.convert_type)(i.frst_arg, i.sec_arg, files));
}

void Sound_processor::convert_audio(WAV &wav) {
    size_t con_count = conv_list.size();
    int cur = 1;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    for (auto cl: conv_list) {
        std::cout << "Converting " << cur * 100 / con_count << "%\n";
        cl->action(wav);
        cur++;
    }
    std::cout << "Converting done!\n";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    make_null();
}

void Sound_processor::make_null() {
    for (auto &cl: conv_list)
        delete cl;
}
