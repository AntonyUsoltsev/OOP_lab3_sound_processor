//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_CONVERTER_H
#define LAB3_SOUND_PROCESSOR_CONVERTER_H
class Converter{
public:
    Converter()=default;

    virtual ~Converter() = default;

    virtual int action() = 0;
};
#endif //LAB3_SOUND_PROCESSOR_CONVERTER_H
