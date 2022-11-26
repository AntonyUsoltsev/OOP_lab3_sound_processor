//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_WAV_H
#define LAB3_SOUND_PROCESSOR_WAV_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <windows.h>

//subchank1 -- format
//subchunk2 -- data

typedef struct WAV_header_struct {
    char chunkId[4];             //Содержит символы «RIFF» в ASCII кодировке 0x52494646. Является началом RIFF-цепочки.
    unsigned long chunkSize;     //	Это оставшийся размер цепочки, начиная с этой позиции. Иначе говоря, это размер файла минус 8, то есть, исключены поля chunkId и chunkSize.
    char format[4];              //Содержит символы «WAVE» 0x57415645
    char subchunk1Id[4];         //	Содержит символы "fmt " 0x666d7420
    unsigned long subchunk1Size; //	16 для формата PCM. Это оставшийся размер подцепочки, начиная с этой позиции.
    unsigned short audioFormat;  //Аудио формат, список допустипых форматов. ==1
    unsigned short numChannels;  //Количество каналов. Моно = 1, Стерео = 2 и т.д.
    unsigned long sampleRate;    //Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
    unsigned long byteRate;      //Количество байт, переданных за секунду воспроизведения.
    unsigned short blockAlign;   //	Количество байт для одного сэмпла, включая все каналы.
    unsigned short bitsPerSample;//	Количество бит в сэмпле. Так называемая «глубина» или точность звучания. 8 бит, 16 бит и т.д.
} WAV_header;

typedef struct WAV_chunk_struct {
    char subchunkId[4];          //	Содержит символы «data» 0x61746164 ИЛИ "LIST"
    unsigned long subchunkSize;  //	Количество байт в области данных.
} WAV_chunk;


class WAV {
public:
    WAV_header wav_header;
    WAV_chunk wav_chunk;
    int sample_size;
    int samples_count;
    unsigned long *data;

    void read_wav(FILE *fin) {
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
        fclose(fin);
    }

    void record_wav(FILE *fout) {

        fwrite(&wav_header, sizeof(wav_header), 1, fout);
        fwrite(&wav_chunk, sizeof(wav_chunk), 1, fout);

        for (int i = 0; i < samples_count; i++)
            fwrite(&data[i], sample_size, 1, fout);

        fclose(fout);
    }

};

#endif //LAB3_SOUND_PROCESSOR_WAV_H
