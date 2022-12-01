//
// Created by Antony on 01.12.2022.
//
//sound_processor [-h] [-c config.txt output.wav input1.wav [input2.wav …]]

#include "Prog_args.h"

Prog_args::Prog_args(int argc, char **argv) {
    po::options_description desc("Description");
    desc.add_options()
            ("help", "help")
            ("config", po::value<std::string>(&config), "--config=path to config file")
            ("output", po::value<std::string>(&output), "--output=path to output file")
            ("files", po::value<std::vector<std::string> >(&files), "--files=path to input file");

    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }
    catch (po::error &e) {
        throw Exceptions(e.what());
    }
    if (vm.count("help")) {
        std::cout << desc << std::endl;
    }
    if (vm.count("config")) {
        std::cout << "config:"
                  << vm["config"].as<std::string>() << std::endl;
    }
    if (vm.count("output")) {
        std::cout << "output:"
                  << vm["output"].as<std::string>() << std::endl;
    }
    if (vm.count("files")) {
        for (int i = 0; i < files.size(); i++)
            std::cout << "file " << i+1 << ":" << vm["files"].as<std::vector<std::string>>()[i] << std::endl;
    }

}

