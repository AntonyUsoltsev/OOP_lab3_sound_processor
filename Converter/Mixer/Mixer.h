//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_MIXER_H
#define LAB3_SOUND_PROCESSOR_MIXER_H

#include "../Converter.h"

class Mixer : public Converter {
private:
    std::string extra_aud_file;
    int ins_time;
public:
    explicit Mixer() = default;

    explicit Mixer(int par1, int par2,const std::vector<std::string>& files) {
        if (files.size() >= par1) {
            extra_aud_file = files[par1 - 1];
            ins_time = par2;
        } else
            throw Exceptions("Too few program arguments: no second track");
    }

    void get_description() override ;

    void action(WAV &wav) override;
};

#endif //LAB3_SOUND_PROCESSOR_MIXER_H
