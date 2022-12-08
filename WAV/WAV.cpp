//
// Created by Antony on 26.11.2022.
//

#include "WAV.h"

// Include read WAV-file, check some header params and record converted audio to output WAV-file

WAV::WAV(std::string f_name, int priority) : file_name(std::move(f_name)) {
    if (priority == 1)
        data_file_name = "..//WAV/data.txt";
    else
        data_file_name = "..//WAV/extra_data.txt";
}

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
    fseek(fin, static_cast<long>(wav_header.subchunk1Size - 16), SEEK_CUR); //skip wExtraFormatBytes & extra format bytes
    check_rightness();

    while (true) {                                                                //find data chunk
        fread(&wav_chunk, sizeof(wav_chunk), 1, fin);
        if (*(unsigned long *) &wav_chunk.subchunkId == 0x61746164)               //data
            break;
        fseek(fin, static_cast<long>(wav_chunk.subchunkSize), SEEK_CUR);    //skip chunk data bytes
    }
    sample_size = wav_header.bitsPerSample / 8;
    samples_count = wav_chunk.subchunkSize * 8 / wav_header.bitsPerSample;
    cnt_smpl_sec = wav_header.sampleRate;

    FILE *data_file = fopen(data_file_name.c_str(), "wb");
    unsigned long *buffer;
    buffer = new unsigned long[cnt_smpl_sec];
    memset(buffer, 0, cnt_smpl_sec);
    for (int i = 0; i < samples_count / cnt_smpl_sec + 1; i++) {
        for (int j = 0; j < cnt_smpl_sec; j++)
            fread(&buffer[j], sample_size, 1, fin);
        for (int j = 0; j < cnt_smpl_sec; j++)
            fwrite(&buffer[j], sample_size, 1, data_file);
    }
    fclose(data_file);
    fclose(fin);
}

void WAV::record_wav(const std::string &file_out_name) {
    FILE *fout = fopen(file_out_name.c_str(), "wb");
    fwrite(&wav_header, sizeof(wav_header), 1, fout);
    fwrite(&wav_chunk, sizeof(wav_chunk), 1, fout);

    FILE *data_file = fopen(data_file_name.c_str(), "rb");
    unsigned long *buffer;
    buffer = new unsigned long[cnt_smpl_sec];
    memset(buffer, 0, cnt_smpl_sec);
    for (int i = 0; i < samples_count / cnt_smpl_sec + 1; i++) {
        for (int j = 0; j < cnt_smpl_sec; j++)
            fread(&buffer[j], sample_size, 1, data_file);
        for (int j = 0; j < cnt_smpl_sec; j++)
            fwrite(&buffer[j], sample_size, 1, fout);
    }
    delete buffer;
    fclose(data_file);
    fclose(fout);
}
