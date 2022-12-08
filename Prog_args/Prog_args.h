//
// Created by Antony on 01.12.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_PROG_ARGS_H
#define LAB3_SOUND_PROCESSOR_PROG_ARGS_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstring>
#include "boost/program_options.hpp"
#include "..//Exceptions/Exceptions.h"
#include "..//Manual/Manual.h"

namespace po = boost::program_options;

class Prog_args {
private:
    po::variables_map vm;
public:
    std::vector<std::string> files;
    std::string output;
    std::string config;

    Prog_args() = default;

    Prog_args(int argc, char **argv);

    static void check_extension(const std::string &str, const std::string &type, const std::string &extension);

    void check_rightness();

    static void call_help(const po::options_description &desc);

    ~Prog_args() = default;
};

#endif //LAB3_SOUND_PROCESSOR_PROG_ARGS_H
