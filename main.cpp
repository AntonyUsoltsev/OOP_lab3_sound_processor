#include <iostream>
#include "Prog_args/Prog_args.h"
#include "WAV/WAV.h"
#include "Sound_processor/Sound_processor.h"
#include "Exceptions/Exceptions.h"

int main(int argc, char **argv) {
    try {

        WAV wav("..//_Music Example/funkorama.wav");
        wav.read_wav();

        Config config("..//Config/Config.txt");
        std::vector<Action> instructions = config.read_config();

        for(auto i:instructions) {
            std::cout << i.convert_type <<" "<<i.frst_arg<<" "<<i.sec_arg<<'\n';

        }
        Sound_processor sound_proc(wav, instructions);

        wav.record_wav("result.wav");

    }
    catch (Exceptions &ex) {
        std::cerr << ex.what();
    }
}