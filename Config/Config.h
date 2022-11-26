//
// Created by Antony on 26.11.2022.
//
#include <iostream>
#include <vector>
#ifndef LAB3_SOUND_PROCESSOR_CONFIG_H
#define LAB3_SOUND_PROCESSOR_CONFIG_H
class Config{
public:
    std::vector<std::string> action ;
    Config(){
        action = {"mute", "0", "30"};
    }
};
#endif //LAB3_SOUND_PROCESSOR_CONFIG_H
