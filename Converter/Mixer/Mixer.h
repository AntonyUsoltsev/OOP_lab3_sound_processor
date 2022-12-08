//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_MIXER_H
#define LAB3_SOUND_PROCESSOR_MIXER_H

#include "../Converter.h"

// Each sample is the average of the corresponding samples of the input streams.

class Mixer : public Converter {
private:
    std::string extra_aud_file;
    int ins_time;
public:
    explicit Mixer() = default;

    explicit Mixer(int par1, int par2, const std::vector<std::string>& files);

    void get_description() override ;

    void action(WAV &wav) override;

    ~Mixer() override = default;
};

#endif //LAB3_SOUND_PROCESSOR_MIXER_H
