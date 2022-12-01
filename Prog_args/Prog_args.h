//
// Created by Antony on 01.12.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_PROG_ARGS_H
#define LAB3_SOUND_PROCESSOR_PROG_ARGS_H
#include <iostream>
#include "boost/program_options.hpp"
#include <string>
#include <vector>

//sound_processor [-h] [-c config.txt output.wav input1.wav [input2.wav …]]
namespace po = boost::program_options;

class Prog_args{
    Prog_args()=default;
    Prog_args(int argc,char**argv);

};
#endif //LAB3_SOUND_PROCESSOR_PROG_ARGS_H
