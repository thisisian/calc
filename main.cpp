#include <iostream>
#include <sstream>
#include <exception>
#include <stdlib.h>

#include "src/parser.hpp"
#include "src/exception.hpp"

//! Concatenate arguments into a single string
std::string concatArgs(int argc, char *argv[]) {
    if (argc <= 0) {
        return "";
    }
    std::stringstream ss;
    for (int i = 1; i < argc; ++i) {
        ss << argv[i];
    }
    return ss.str();
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        auto args = concatArgs(argc, argv);
        long double result;
        try {
            result = Parser::parse_and_eval(args);
        } catch (ParserException &e) {
            std::cerr << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << result << std::endl;
        exit(EXIT_SUCCESS);
    } else {
        std::string input;
        std::cout << "> ";
        while (std::getline(std::cin, input)) {
            if (input == "exit") {
                exit(EXIT_SUCCESS);
            }
            long double result;
            try {
                result = Parser::parse_and_eval(input);
            } catch (ParserException &e) {
                std::cout << e.what() << std::endl;
                std::cout << "> ";
                continue;
            }
            std::cout << result << std::endl;
            std::cout << "> ";
        }
    }
    return 0;
}
