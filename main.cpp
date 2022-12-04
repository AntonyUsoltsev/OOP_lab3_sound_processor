#include <iostream>
#include "Prog_args/Prog_args.h"
#include "WAV/WAV.h"
#include "Sound_processor/Sound_processor.h"
#include "Exceptions/Exceptions.h"
#include <ctime>

int main(int argc, char **argv) {
    clock_t clock = std::clock();
    try {
        Prog_args prog_args(argc, argv);

        Config config(prog_args.config);
        std::vector<Action> instructions = config.read_config();

        std::cout << "\nInstructions:\n";
        for (const auto &i: instructions) {
            std::cout << i.convert_type << " " << i.frst_arg << " " << i.sec_arg << '\n';
        }

        WAV wav(prog_args.files[0]);
        wav.read_wav();

        Sound_processor sound_proc(wav, instructions, prog_args.files);

        wav.record_wav(prog_args.output);

        clock_t clock2 = std::clock();
        std::cout<<clock2-clock;
        return 0;

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