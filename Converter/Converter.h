//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_CONVERTER_H
#define LAB3_SOUND_PROCESSOR_CONVERTER_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include "..//WAV/WAV.h"
#include "..//Exceptions/Exceptions.h"


class Converter {
public:
    Converter() = default;

    static void read_write_bef_conv(const int t1, FILE *fin, FILE *fout, const WAV &wav) {
        auto buff = new unsigned long[1];
        for (unsigned int i = 0; i < t1 * wav.wav_header.sampleRate; i++) {
            fread(&buff[0], wav.sample_size, 1, fin);
            fwrite(&buff[0], wav.sample_size, 1, fout);
        }
        delete[] buff;
    }
    static void read_write_aft_conv(const int t2, FILE *fin, FILE *fout, const WAV &wav) {
        auto buff = new unsigned long[1];
        for (unsigned int i = t2* wav.wav_header.sampleRate+1; i < wav.samples_count; i++) {
            fread(&buff[0], wav.sample_size, 1, fin);
            fwrite(&buff[0], wav.sample_size, 1, fout);
        }
        delete[] buff;
    }

    static void rewrite(FILE *fin, FILE *fout, const WAV& wav){
        auto buff = new unsigned long[1];
        for (int i = 0; i < wav.samples_count; i++) {
            fread(&buff, wav.sample_size, 1, fin);
            fwrite(&buff, wav.sample_size, 1, fout);
        }
        //delete[] buff; -----------------------???????
    }

    virtual void get_description() = 0;

    virtual void action(WAV &) = 0;

    virtual ~Converter() = default;

};

#endif //LAB3_SOUND_PROCESSOR_CONVERTER_H
