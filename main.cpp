#include <iostream>
#include "boost/program_options.hpp"
#include "WAV/WAV.h"

int main() {
    FILE *fin = fopen("..//_Sound Processor Example Music/funkorama.wav", "rb");
    WAV wav;

    FILE *fout = fopen("result.wav", "wb");
    wav.record_wav(fout);
}