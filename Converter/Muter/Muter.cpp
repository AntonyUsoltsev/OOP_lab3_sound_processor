//
// Created by Antony on 26.11.2022.
//

#include "Muter.h"

void Muter::get_description() {
    SetConsoleOutputCP(1251);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
    std::cout << "\nMute converter (Muter):\n";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    std::cout << "  Config options: mute time_1 time_2; 0 <= time_1 < time_2\n"
                 "\ttime_1 (int) - begin time (seconds from begin),\n"
                 "\ttime_2 (int) - end time (seconds from begin)\n"
                 "  Description: mute the input audio from time_1 to time_2, the rest - as in the input stream"
              << std::endl;
}

void Muter::action(WAV &wav) {
    if (time2 * wav.cnt_smpl_sec > wav.samples_count)
        throw Exceptions("Invalid end time in mute converter");

    FILE *data_file = fopen(wav.data_file_name.c_str(), "rb+");
    unsigned long *buffer;
    buffer = new unsigned long[wav.cnt_smpl_sec];

    memset(buffer, 0, wav.cnt_smpl_sec);
    for (unsigned long i = time1; i <= time2; i++) {
        fseek(data_file, i * wav.cnt_smpl_sec * wav.sample_size, SEEK_SET);
        for (int j = 0; j < wav.cnt_smpl_sec; j++) {
            fread(&buffer[j], wav.sample_size, 1, data_file);
        }
        for (int j = 0; j < wav.cnt_smpl_sec; j++) {
            buffer[j] = 0;
        }
        fseek(data_file, i * wav.cnt_smpl_sec * wav.sample_size, SEEK_SET);
        for (int j = 0; j < wav.cnt_smpl_sec; j++) {
            fwrite(&buffer[j], wav.sample_size, 1, data_file);
        }
    }
    fclose(data_file);
}

