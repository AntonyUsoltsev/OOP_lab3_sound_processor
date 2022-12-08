//
// Created by Antony on 26.11.2022.
//

#include "Config.h"

// Include check type of conversion, count of converter parameters, 0 <= time1 < time2 and extra address > 1.

std::vector<Action> Config::read_config() {
    std::ifstream fin(file_name);
    if (!fin.is_open())
        throw Exceptions("Config file didn't open");

    std::string line;
    int num_of_str = 0;
    while (std::getline(fin, line, '\n')) {
        num_of_str ++ ;

        if (line[0] == '#')
            continue;

        Action act;
        std::string num_bad_string = " (str " + std::to_string(num_of_str)+")";

        sscanf(line.c_str(), "%s", act.convert_type.c_str());

        if (strcmp(act.convert_type.c_str(), "mute") == 0 || strcmp(act.convert_type.c_str(), "slow") == 0) {
            if (sscanf(line.c_str(), "%s %d %d", act.convert_type.c_str(), &act.frst_arg, &act.sec_arg) != 3)
                throw Exceptions("Too few args in config file or wrong symbols" + num_bad_string);
            if (act.frst_arg >= act.sec_arg || act.frst_arg < 0 || act.sec_arg < 0)
                throw Exceptions("Wrong time arguments" + num_bad_string);
        }

        else if (strcmp(act.convert_type.c_str(), "mix") == 0) {
            if (sscanf(line.c_str(), "%s $%d %d", act.convert_type.c_str(), &act.frst_arg, &act.sec_arg) != 3)
                throw Exceptions("Too few args in config file or wrong symbols" + num_bad_string);
            if (act.frst_arg <= 1)
                throw Exceptions("Wrong address of extra file for mix" + num_bad_string);
            if (act.sec_arg < 0)
                throw Exceptions("Wrong time arguments" + num_bad_string);
        }
        else{
            throw Exceptions("Wrong type of conversion" + num_bad_string );
        }

        Action act2;
        act2.convert_type = act.convert_type.c_str();
        act2.frst_arg = act.frst_arg;
        act2.sec_arg = act.sec_arg;
        instructions.push_back(act2);
    }
    return instructions;
}
