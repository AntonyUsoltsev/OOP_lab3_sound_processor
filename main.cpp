#include <iostream>
#include "Prog_args/Prog_args.h"
#include "WAV/WAV.h"
#include "Sound_processor/Sound_processor.h"
#include "Exceptions/Exceptions.h"

int main(int argc, char **argv) {
    try {

        Prog_args prog_args(argc, argv);

        WAV wav(prog_args.files[0]);
        wav.read_wav();

        Config config(prog_args.config);
        std::vector<Action> instructions = config.read_config();
        std::cout << "\nInstructions:\n";
        for (const auto &i: instructions) {
            std::cout << i.convert_type << " " << i.frst_arg << " " << i.sec_arg << '\n';
        }

        Sound_processor sound_proc(wav, instructions, prog_args.files);

        wav.record_wav(prog_args.output);

    }
    catch (Exceptions &ex) {
        std::cout.flush();
        std::cerr << "\nERROR: " << ex.what();
        return 1;
    }
    catch(std::exception &ex){
        std::cout.flush();
        std::cerr << "\nERROR: " << ex.what();
        return 2;
    }
}