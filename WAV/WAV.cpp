//
// Created by Antony on 26.11.2022.
//

#include "WAV.h"

void WAV::check_rightness() const {
    if (wav_header.subchunk1Size != 16)
        throw Exceptions("Audio format is incorrect");
    if (wav_header.numChannels != 1)
        throw Exceptions("Audio isn't mono");
    if (wav_header.sampleRate != 44100)
        throw Exceptions("Wrong sample rate");
}


void WAV::read_wav() {
    FILE *fin = fopen(file_name.c_str(), "rb");
    fread(&wav_header, sizeof(wav_header), 1, fin);
    fseek(fin, wav_header.subchunk1Size - 16, SEEK_CUR); //skip wExtraFormatBytes & extra format bytes
    check_rightness();
    while (true) { //go to data chunk
        fread(&wav_chunk, sizeof(wav_chunk), 1, fin);
        // printf("%c%c%c%c\t" "%li\n", wav_chunk.id[0], wav_chunk.id[1], chunk.id[2], chunk.id[3], chunk.size);
        if (*(unsigned long *) &wav_chunk.subchunkId == 0x61746164)
            break;
        fseek(fin, wav_chunk.subchunkSize, SEEK_CUR); //skip chunk data bytes
    }
    sample_size = wav_header.bitsPerSample / 8;
    samples_count = wav_chunk.subchunkSize * 8 / wav_header.bitsPerSample;

    data = new unsigned long[samples_count];
    memset(data, 0, sizeof(unsigned long) * samples_count);

    for (int i = 0; i < samples_count; i++)
        fread(&data[i], sample_size, 1, fin);

    fclose(fin);
}

void WAV::record_wav(const std::string& file_out_name) {
    FILE *fout = fopen(file_out_name.c_str(), "wb");
    fwrite(&wav_header, sizeof(wav_header), 1, fout);
    fwrite(&wav_chunk, sizeof(wav_chunk), 1, fout);

    for (int i = 0; i < samples_count; i++)
        fwrite(&data[i], sample_size, 1, fout);

    fclose(fout);
}

