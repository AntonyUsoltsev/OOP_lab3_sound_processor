//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_WAV_H
#define LAB3_SOUND_PROCESSOR_WAV_H

#include <iostream>
//#include <stdio.h>
#include <vector>
#include <windows.h>

#include "..//Exceptions/Exceptions.h"

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
    std::string file_name;
    WAV_header wav_header;
    WAV_chunk wav_chunk;
    int sample_size;
    int samples_count;
    unsigned long *data;

    explicit WAV(std::string f_name) : file_name(std::move(f_name)) {}

    void read_wav();

    void check_rightness() const;

    void record_wav(const std::string& file_out_name);

};

#endif //LAB3_SOUND_PROCESSOR_WAV_H
