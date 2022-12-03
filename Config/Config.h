//
// Created by Antony on 26.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_CONFIG_H
#define LAB3_SOUND_PROCESSOR_CONFIG_H

#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
#include <fstream>
#include "..//Exceptions/Exceptions.h"

struct Action {
    std::string convert_type;
    int frst_arg;
    int sec_arg;
};

class Config {
private:
    std::vector<Action> instructions;
    std::string file_name;
public:

    explicit Config(std::string f_name) : file_name(std::move(f_name)) {}

    std::vector<Action> read_config();
};

#endif //LAB3_SOUND_PROCESSOR_CONFIG_H
