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
    std::string file_name; // Путь до wav файла который будет реализован в этом классе
    WAV_header wav_header; // Wav заголовок
    WAV_chunk wav_chunk;   // Chunk с data
    int sample_size;       // Размер сэмпла в байтах
    unsigned long samples_count; // Количество сэмплов в области данных
    unsigned long cnt_smpl_sec;
    unsigned long *data;   // Массив данных
    std::string data_file_name;  // Путь до файла с данными (без заголовка)
    //FILE *data_file;

    explicit WAV(std::string f_name,int priority) : file_name(std::move(f_name)) {
        if (priority == 1)
            data_file_name = "D:/Antony/Programing_C++/OOP/lab3_sound_processor/WAV/data.txt";
        else
            data_file_name = "D:/Antony/Programing_C++/OOP/lab3_sound_processor/WAV/extra_data.txt";

    }

    void read_wav();

    void check_rightness() const;

    void record_wav(const std::string& file_out_name);

};

#endif //LAB3_SOUND_PROCESSOR_WAV_H
