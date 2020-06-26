#include <string>

#include "exception.hpp"

ParserException::ParserException(const std::string &msg) : msg(msg) {}

const char * ParserException::what() const noexcept {
    return msg.c_str();
}