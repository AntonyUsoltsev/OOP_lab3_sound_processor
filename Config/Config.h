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
    std::vector<Action> instructions;
    std::string file_name;
public:
    //std::vector<Action> instructions;
    explicit Config(std::string f_name) : file_name(std::move(f_name)) {}

    std::vector<Action>  read_config() {
        std::ifstream fin(file_name);
        if (!fin.is_open())
            throw Exceptions("Config file didn't open");
        std::string line;
        while (std::getline(fin, line, '\n')) {
            if (line[0] == '#')
                continue;
            Action act;
            Action act2;
            sscanf(line.c_str(), "%s", act.convert_type.c_str());

            if (!strcmp(act.convert_type.c_str(), "mute") && !strcmp(act.convert_type.c_str(), "mix")&& !strcmp(act.convert_type.c_str(), "slow")) {
                throw Exceptions("Wrong type of conversion");
            }
            if (strcmp(act.convert_type.c_str(), "mute") == 0 || strcmp(act.convert_type.c_str(), "slow") == 0 )
                if (sscanf(line.c_str(), "%s %d %d", act.convert_type.c_str(), &act.frst_arg, &act.sec_arg) != 3) {
                    throw Exceptions("Too few args in file");
                }
            if (strcmp(act.convert_type.c_str(), "mix") == 0)
                if (sscanf(line.c_str(), "%s $%d %d", act.convert_type.c_str(), &act.frst_arg, &act.sec_arg) != 3) {
                    throw Exceptions("Too few args in file");
                }
            act2.convert_type = act.convert_type.c_str();
            act2.frst_arg = act.frst_arg;
            act2.sec_arg = act.sec_arg;
            instructions.push_back(act2);
            //instructions.push_back(act);
        }
        return instructions;
    }
};

#endif //LAB3_SOUND_PROCESSOR_CONFIG_H
