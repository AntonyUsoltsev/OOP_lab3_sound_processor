//
// Created by Antony on 01.12.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_PROG_ARGS_H
#define LAB3_SOUND_PROCESSOR_PROG_ARGS_H
#include <iostream>
#include "boost/program_options.hpp"
#include <string>
#include <vector>
#include "..//Exceptions/Exceptions.h"
#include "..//Manual/Manual.h"

//sound_processor [-h] [-c config.txt output.wav input1.wav [input2.wav …]]
namespace po = boost::program_options;

class Prog_args{
public:
    Prog_args()=default;
    Prog_args(int argc,char**argv);
    po::variables_map vm;
    std::vector<std::string> files;
    std::string output;
    std::string config;
};
#endif //LAB3_SOUND_PROCESSOR_PROG_ARGS_H
