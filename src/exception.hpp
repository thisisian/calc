#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>

//! An exception class for parser exceptions.
class ParserException : public std::exception {
    public:
        const char* what() const noexcept;
        ParserException(const std::string&);
    private:
        std::string msg;
};

#endif
