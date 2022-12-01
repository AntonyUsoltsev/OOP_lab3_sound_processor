//
// Created by Antony on 01.12.2022.
//
#include <iostream>
#include <utility>

#ifndef LAB3_SOUND_PROCESSOR_EXCEPTIONS_H
#define LAB3_SOUND_PROCESSOR_EXCEPTIONS_H
class Exceptions: std::exception{
    std::string reason;

    public:
    explicit Exceptions(std::string res):reason(std::move(res)){}
    std::string what(){
        return this->reason;
    }
};
#endif //LAB3_SOUND_PROCESSOR_EXCEPTIONS_H
