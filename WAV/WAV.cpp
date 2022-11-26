//
// Created by Antony on 26.11.2022.
//

#include "WAV.h"

void WAV::read_wav(FILE *fin) {
    fread(&wav_header, sizeof(wav_header), 1, fin);
    fseek(fin, wav_header.subchunk1Size - 16, SEEK_CUR); //skip wExtraFormatBytes & extra format bytes
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
}

void WAV::record_wav(FILE *fout) {

    fwrite(&wav_header, sizeof(wav_header), 1, fout);
    fwrite(&wav_chunk, sizeof(wav_chunk), 1, fout);

    for (int i = 0; i < samples_count; i++)
        fwrite(&data[i], sample_size, 1, fout);
}
