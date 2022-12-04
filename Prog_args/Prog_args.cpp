//
// Created by Antony on 01.12.2022.
//

#include "Prog_args.h"

/* Include check key rightness, the presence of the necessary keys (config, output, files[0] == input)
 * and extension of arguments (config == .txt, output = .wav, files = .wav)
 * Also shows the information of converters and information about command line arguments, if --help key has been insert.
*/

Prog_args::Prog_args(int argc, char **argv) {
    po::options_description desc("");
    desc.add_options()
            ("help", "help")
            ("config", po::value<std::string>(&config), "--config=path to config file (.txt)")
            ("output", po::value<std::string>(&output), "--output=path to output file (.wav)")
            ("files", po::value<std::vector<std::string> >(&files), "--files=path to input file (.wav)");

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
        std::cout << "\nCommand Line Info:\n";
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        std::cout << desc << std::endl;
        Manual::get_manual();
        std::string confirm;
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
        std::cout << "\nTo continue press any key, to stop insert stop\n";
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        std::cin>>confirm;
        fflush(stdin);
        if (!(strcmp(confirm.c_str(),"stop") && strcmp(confirm.c_str(),"STOP"))){
            throw Exceptions("Program stopped");
        }

    } else {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
        std::cout << "\nTO GET MANUAL INSERT --help KEY IN PROGRAM ARGUMENTS\n";
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    }
//    if (vm.count("config")) {
//        std::cout << "config:"
//                  << vm["config"].as<std::string>() << std::endl;
//    }
    if (!vm.count("config")) {
        throw Exceptions("Missing config txt file in program arguments");
    }
//    if (vm.count("output")) {
//        std::cout << "output:"
//                  << vm["output"].as<std::string>() << std::endl;
//    }
    if (!vm.count("output")) {
        throw Exceptions("Missing output wav file in program arguments");
    }
//    if (vm.count("files")) {
//        for (int i = 0; i < files.size(); i++)
//            std::cout << "file " << i + 1 << ":" << vm["files"].as<std::vector<std::string>>()[i] << std::endl;
//    }
    if (!vm.count("files")) {
        throw Exceptions("Missing input wav file in program arguments");
    }

    unsigned long len = config.length();
    std::string type = config.substr(len-3, 3);
    if (strcmp(type.c_str(),"txt") != 0)
        throw Exceptions("Invalid config file extension (need .txt)");

    len = output.length();
    type = output.substr(len-3, 3);
    if (strcmp(type.c_str(),"wav") != 0)
        throw Exceptions("Invalid output file extension (need .wav)");

    for (const auto& str :files){
        len = str.length();
        type = str.substr(len-3, 3);
        if (strcmp(type.c_str(),"wav") != 0)
            throw Exceptions("Invalid input file(s) extension (need .wav)");
    }



}

