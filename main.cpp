#include <iostream>
#include <ctime>
#include "Prog_args/Prog_args.h"
#include "Sound_processor/Sound_processor.h"
#include "Exceptions/Exceptions.h"

int main(int argc, char **argv) {

    try {
        Prog_args prog_args(argc, argv);

        Config config(prog_args.config);
        std::vector<Action> instructions = config.read_config();

        clock_t clock = std::clock();

        WAV wav(prog_args.files[0],1);
        wav.read_wav();

        Sound_processor sound_proc(instructions, prog_args.files);
        sound_proc.convert_audio(wav);

        wav.record_wav(prog_args.output);

        clock_t clock2 = std::clock();
        std::cout<<clock2-clock;
        return 0;

    }
    catch (Exceptions &ex) {
        std::cout.flush();
        std::cerr << "\nERROR: " << ex.what_err();
        return ex.ret_code();
    }
    catch(std::exception &ex){
        std::cout.flush();
        std::cerr << "\nERROR: " << ex.what();
        return 1;
    }
}