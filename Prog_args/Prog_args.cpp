//
// Created by Antony on 01.12.2022.
//

#include "Prog_args.h"

Prog_args::Prog_args(int argc, char **argv) {
    po::options_description desc("");
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
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
        std::cout <<"\nCommand Line Info:\n";
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
        std::cout<< desc << std::endl;
        Manual::get_manual();

    }
    else{
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
        std::cout<<"\nTO GET MANUAL INSERT --help KEY IN PROGRAM ARGUMENTS\n";
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);

    }
//    if (vm.count("config")) {
//        std::cout << "config:"
//                  << vm["config"].as<std::string>() << std::endl;
//    }
    if(!vm.count("config")){
       throw Exceptions("Missing config txt file in program arguments");
    }
//    if (vm.count("output")) {
//        std::cout << "output:"
//                  << vm["output"].as<std::string>() << std::endl;
//    }
    if(!vm.count("output")){
        throw Exceptions("Missing output wav file in program arguments");
    }
//    if (vm.count("files")) {
//        for (int i = 0; i < files.size(); i++)
//            std::cout << "file " << i + 1 << ":" << vm["files"].as<std::vector<std::string>>()[i] << std::endl;
//    }
    if (!vm.count("files")){
        throw Exceptions("Missing input wav file in program arguments");
    }

}

