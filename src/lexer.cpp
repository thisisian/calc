#include <string>
#include <optional>
#include "lexer.hpp"

/* Token method definitions */

Token::Token() : type(TIMES), text("") {}

Token::Token(Token_t ty, std::string info) : type(ty), text(info) {}

Token_t Token::get_type() const { return type; }

std::string Token::get_text() const { return text; }

/* Lexer method definitions */

Lexer::Lexer(std::string input) : cursor(0), input(input) {}

std::optional<Token> Lexer::next() {
    while(cursor < input.size() && input[cursor] == ' ') {
        cursor++;
    }

    if (cursor >= input.size()) {
        return {}; // No more input
    }

    auto c = input[cursor];
    Token ret;
    if (!is_operator(c)) {
        // Not an operator, collect the text of the token
        auto s = get_name();
        ret = Token(NUM, s);
    } else {
        switch (c) {
            case '+' :
                ret = Token(PLUS, "+");
                break;
            case '-' :
                ret = Token(MINUS, "-");
                break;
            case '*' :
                ret = Token(TIMES, "*");
                break;
            case '/' :
                ret = Token(DIVIDE, "/");
                break;
            case '(' :
                 ret = Token(LPARENS, "(");
                break;
            case ')' :
                ret = Token(RPARENS, ")");
                break;
            default:
                throw std::invalid_argument("Invalid token at character "
                                           + std::to_string(cursor));
        }
        cursor++;
    }
    return ret;
}

std::optional<Token> Lexer::peek() {
    auto cursor_backup = cursor;
    auto ret = next();
    cursor = cursor_backup;
    return ret;
}

std::string Lexer::get_name() {
    char c;
    auto old_cursor = cursor;
    while (cursor < input.size() &&
          !is_operator(c = input[cursor]) &&
          c != ' ') { // Consume input until we find an operator or whitespace
        cursor++;
    }
    return input.substr(old_cursor, cursor - old_cursor);
}

bool Lexer::is_operator(char c) {
    return (c == '*'
           || c == '/'
           || c == '+'
           || c == '-'
           || c == '('
           || c == ')');
}
