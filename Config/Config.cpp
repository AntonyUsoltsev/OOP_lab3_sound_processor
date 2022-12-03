//
// Created by Antony on 26.11.2022.
//

#include "Config.h"

std::vector<Action> Config::read_config() {
    std::ifstream fin(file_name);
    if (!fin.is_open())
        throw Exceptions("Config file didn't open");

    std::string line;
    while (std::getline(fin, line, '\n')) {
        if (line[0] == '#')
            continue;

        Action act;

        sscanf(line.c_str(), "%s", act.convert_type.c_str());

        if (!strcmp(act.convert_type.c_str(), "mute") && !strcmp(act.convert_type.c_str(), "mix") &&
            !strcmp(act.convert_type.c_str(), "slow"))
            throw Exceptions("Wrong type of conversion");

        if (strcmp(act.convert_type.c_str(), "mute") == 0 || strcmp(act.convert_type.c_str(), "slow") == 0)
            if (sscanf(line.c_str(), "%s %d %d", act.convert_type.c_str(), &act.frst_arg, &act.sec_arg) != 3)
                throw Exceptions("Too few args in config file or wrong symbols");

        if (strcmp(act.convert_type.c_str(), "mix") == 0)
            if (sscanf(line.c_str(), "%s $%d %d", act.convert_type.c_str(), &act.frst_arg, &act.sec_arg) != 3)
                throw Exceptions("Too few args in config file or wrong symbols");

        Action act2;
        act2.convert_type = act.convert_type.c_str();
        act2.frst_arg = act.frst_arg;
        act2.sec_arg = act.sec_arg;
        instructions.push_back(act2);
        //instructions.push_back(act);
    }

    return instructions;
}
