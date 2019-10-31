#include "huffman.hpp"

enum errors {v_flag_wrong_position, no_c_d_flag, too_few_arguments};
int main(int argc, char* argv[]) {
    std::vector<std::string> my_argv(argc);
    for (int i = 0; i < argc; ++i) {
        my_argv[i] = std::string(argv[i]);
    }
    if ((argc < 4)) {
        std::cout << "give at least 4 arguments" << std::endl;
        return too_few_arguments;
    }
    if ((argc == 5) && (my_argv[1] != "-v")) {
        std::cout << "-v flag should be placed before others" << std::endl;
        return v_flag_wrong_position;
    }
    if (((argc == 5) && (my_argv[2] != "-c") && (my_argv[2] != "-d")) || ((argc == 4) && (my_argv[1] != "-c") && (my_argv[1] != "-d"))) {
        std::cout << "no -c or -d flag" << std::endl;
        return no_c_d_flag;
    }
    bool flag_v = (argc == 5) ? (my_argv[1] == "-v") : (false);
    bool flag_c_d = (argc == 5) ? (my_argv[2] == "-c") : (my_argv[1] == "-c");
    run_coding_or_decoding(my_argv[argc - 2], my_argv[argc - 1], flag_v, flag_c_d);
    return 0;
}
