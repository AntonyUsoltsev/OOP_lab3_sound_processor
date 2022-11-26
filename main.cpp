#include <iostream>
#include "boost/program_options.hpp"
#include "WAV/WAV.h"
#include "Sound_processor/Sound_processor.h"

int main() {
    WAV wav;
    FILE *fin = fopen("..//_Music Example/funkorama.wav", "rb");
    wav.read_wav(fin);
    fclose(fin);

    Config config;

    Sound_processor sound_proc(wav,config);

    FILE *fout = fopen("result.wav", "wb");
    wav.record_wav(fout);
    fclose(fout);
}