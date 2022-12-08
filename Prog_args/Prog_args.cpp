//
// Created by Antony on 01.12.2022.
//
#include "Prog_args.h"

#define WHITE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED

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
        throw Exceptions(e.what(), BAD_PROG_ARGS_KEY);
    }
    if (vm.count("help")) {
        call_help(desc);
    } else {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
        std::cout << "\nTO GET MANUAL INSERT --help KEY IN PROGRAM ARGUMENTS\n";
        SetConsoleTextAttribute(hStdOut, WHITE);
    }

    check_rightness();

}

void Prog_args::call_help(const po::options_description &desc) {

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    std::cout << "\nCommand Line Info:\n";
    SetConsoleTextAttribute(hStdOut, WHITE);

    std::cout << desc << std::endl;
    Manual::get_manual();

    std::string confirm;
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    std::cout << "\nTo continue press any key, to stop insert stop\n";
    SetConsoleTextAttribute(hStdOut, WHITE);
    std::cin >> confirm;
    fflush(stdin);

    if (strcmp(confirm.c_str(), "stop") == 0 || strcmp(confirm.c_str(), "STOP") == 0)
        throw Exceptions("Program stopped", PROGRAM_STOPPED);
}


void Prog_args::check_rightness() {
    if (!vm.count("config"))
        throw Exceptions("Missing config txt file in program arguments", MISSING_KEY);

    if (!vm.count("output"))
        throw Exceptions("Missing output wav file in program arguments", MISSING_KEY);

    if (!vm.count("files"))
        throw Exceptions("Missing input wav file in program arguments", MISSING_KEY);

    check_extension(config, "config", ".txt");
    check_extension(output, "output", ".wav");
    for (const auto &str: files)
        check_extension(str, "input", ".wav");
}

void Prog_args::check_extension(const std::string &str, const std::string &type, const std::string &extension) {
    unsigned long len = str.length();
    std::string ext = str.substr(len - 4, 4);
    if (strcmp(ext.c_str(), extension.c_str()) != 0) {
        std::string ex = "Invalid " + type + " file extension (need " + extension + ")";
        throw Exceptions(ex, BAD_PROG_ARGS_EXTENSION);
    }
}
