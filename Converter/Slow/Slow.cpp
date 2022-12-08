//
// Created by Antony on 04.12.2022.
//

#include "Slow.h"

void Slow::get_description() {
    SetConsoleOutputCP(1251);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
    std::cout << "\nSlow converter (Slower):\n";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    std::cout << "  Config options: slow time_1 time_2; 0 <= time_1 < time_2\n"
                 "\ttime_1 (int) - begin time (seconds from begin),\n"
                 "\ttime_2 (int) - end time (seconds from begin)\n"
                 "  Description: Slows down the audio in the input stream from time_1 to time_2 by half\n"
                 "               WARNING: after using slow converter, the length of input audio is increase"
              << std::endl;
}

void Slow::action(WAV &wav) {
    if (time2 * wav.cnt_smpl_sec > wav.samples_count)
        throw Exceptions("Invalid end time in slow converter");

    FILE *data_file = fopen(wav.data_file_name.c_str(), "rb");
    FILE *slow_file = fopen(slow_file_name.c_str(), "wb");
    unsigned long *buffer;
    buffer = new unsigned long[wav.cnt_smpl_sec * 2];

    memset(buffer, 0, wav.cnt_smpl_sec * 2);
    fseek(data_file, time1 * wav.cnt_smpl_sec * wav.sample_size, SEEK_SET);

    for (unsigned long t = time1; t <= time2; t++) {
        int ind = 0;
        for (int j = 0; j < wav.cnt_smpl_sec; j++) {
            fread(&buffer[ind], wav.sample_size, 1, data_file);
            ind += 2;
        }
        for (int j = 0; j < wav.cnt_smpl_sec * 2; j += 2) {
            buffer[j + 1] = buffer[j];
        }
        for (int j = 0; j < wav.cnt_smpl_sec * 2; j++) {
            fwrite(&buffer[j], wav.sample_size, 1, slow_file);
        }
    }
    for (unsigned long t = time2; t <= wav.samples_count / wav.cnt_smpl_sec + 1; t++) {
        for (int j = 0; j < wav.cnt_smpl_sec; j++) {
            fread(&buffer[j], wav.sample_size, 1, data_file);
        }
        for (int j = 0; j < wav.cnt_smpl_sec; j++) {
            fwrite(&buffer[j], wav.sample_size, 1, slow_file);
        }
    }
    fclose(data_file);
    fclose(slow_file);

    data_file = fopen(wav.data_file_name.c_str(), "rb+");
    slow_file = fopen(slow_file_name.c_str(), "rb");
    buffer = new unsigned long[wav.cnt_smpl_sec ];
    memset(buffer, 0, wav.cnt_smpl_sec );
    fseek(data_file, time1 * wav.cnt_smpl_sec * wav.sample_size, SEEK_SET);
    for (int i = time1; i < wav.samples_count /wav. cnt_smpl_sec +1; i++) {
        for (int j = 0; j < wav.cnt_smpl_sec; j++)
            fread(&buffer[j], wav.sample_size, 1, slow_file);
        for (int j = 0; j < wav.cnt_smpl_sec; j++)
            fwrite(&buffer[j], wav.sample_size, 1, data_file);
    }
    delete buffer;
    fclose(data_file);
    fclose(slow_file);
    unsigned long new_size = wav.samples_count + (time2 - time1) * wav.cnt_smpl_sec * 1;
    wav.samples_count = new_size;
    wav.wav_chunk.subchunkSize = new_size * wav.wav_header.bitsPerSample / 8;
}

