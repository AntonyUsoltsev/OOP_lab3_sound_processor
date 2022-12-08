//
// Created by Antony on 26.11.2022.
//

#include "Mixer.h"

void Mixer::get_description() {
    SetConsoleOutputCP(1251);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
    std::cout << "\nMix converter (Mixer):\n";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    std::cout << "  Config options: mix $mix_inp time;\n"
                 "\t$mix_inp ($int) - number of additional stream to mix (>= 2),\n"
                 "\ttime (int) - insertion point  (seconds from begin >= 0)\n"
                 "  Description: Each sample is the average of the corresponding samples of the input streams. \n"
                 "              The length of the output stream corresponds to the length of the main input stream. \n"
                 "              If the additional stream is longer than the main one, then part of it is cut off (not used),\n"
                 "              and if it is shorter, then the output stream outside it is equal to the main input stream."
              << std::endl;
}

Mixer::Mixer(int par1, int par2, const std::vector<std::string> &files) {
    if (files.size() >= par1) {
        extra_aud_file = files[par1 - 1];
        ins_time = par2;
        //   mix_file_name = "D:/Antony/Programing_C++/OOP/lab3_sound_processor/Converter/Slow/slow.txt";
    } else
        throw Exceptions("Too few program arguments: no second track");
}

void Mixer::action(WAV &wav) {
    if (ins_time * wav.wav_header.sampleRate > wav.samples_count)
        throw Exceptions("Invalid insertion time in mix converter");
    FILE *data_file = fopen(wav.data_file_name.c_str(), "rb+");
    WAV wav_second(extra_aud_file, 2);
    wav_second.read_wav();
    FILE *second_data = fopen(wav_second.data_file_name.c_str(), "rb");
    auto *buffer1 = new unsigned long[wav.cnt_smpl_sec];
    auto *buffer2 = new unsigned long[wav.cnt_smpl_sec];

    memset(buffer1, 0, wav.cnt_smpl_sec);
    memset(buffer2, 0, wav.cnt_smpl_sec);
    for (unsigned long i = ins_time; i < wav.samples_count / wav.cnt_smpl_sec + 1 &&
                                     i < wav_second.samples_count / wav_second.cnt_smpl_sec + 1; i++) {
        fseek(data_file, i * wav.cnt_smpl_sec * wav.sample_size, SEEK_SET);
        for (int j = 0; j < wav.cnt_smpl_sec; j++) {
            fread(&buffer1[j], wav.sample_size, 1, data_file);
            fread(&buffer2[j], wav.sample_size, 1, second_data);
        }
        for (int j = 0; j < wav.cnt_smpl_sec; j++) {
            buffer1[j] = (buffer1[j] + buffer2[j]) / 2;
        }
        fseek(data_file, i * wav.cnt_smpl_sec * wav.sample_size, SEEK_SET);
        for (int j = 0; j < wav.cnt_smpl_sec; j++) {
            fwrite(&buffer1[j], wav.sample_size, 1, data_file);
        }
    }
    fclose(data_file);
    fclose(second_data);
    delete[] buffer1;
    delete[] buffer2;
}
