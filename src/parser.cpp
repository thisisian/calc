
#include <string>
#include <iostream>

#include "parser.hpp"
#include "ast.hpp"
#include "exception.hpp"

//! NumberParser is a class that provides a parser for numbers.
class NumberParser : public PrefixParser {
    const Expression * parse(Parser *parser, Token token) override {
        long double val;
        size_t idx;
        std::string s = token.get_text();
        bool parseFailed = false;
        try {
            val = std::stold(s, &idx);
        } catch (...) {
            parseFailed = true;
        }

        // Check if entire string was parsed
        if (parseFailed ||
            (s.size() > 1 && idx < s.size())) {
            throw ParserException("Failed to parse number: " + s);
        }
        return new Number(val);
    }
};

//! A class for parsing unary operators.
/*! UnaOpParser parses expressions with Unary operators at the head.
*/
class UnaOpParser : public PrefixParser {
    const Expression * parse(Parser *parser, Token token) override {
        const Expression * exp {parser->parse(0)};
        return new UnaOp(exp, token.get_type());
    }
};

//! A class for parsing expressions surrounded by parenthesis
/*! ParensParser provides a parser for expressions surrounded by parenthesis.
    If an expression is returned and the following token is not an RPARENS,
    an exception is thrown.
*/
class ParensParser : public PrefixParser {
    const Expression * parse(Parser *parser, Token token) override {
        const Expression * exp {parser->parse(0)};
        auto nextToken = parser->next();
        if (!nextToken || nextToken.value().get_type() != RPARENS) {
            throw ParserException("Unmatched parenthesis");
        }
        return exp;
    }
};

//! A class for parsing expressions that contain a binary operator.
class BinOpParser : public InfixParser {
    public:
        //! Construct the BinOpParser with a given precedence
        BinOpParser(int precedence) : precedence(precedence) {}
        /*! Parse a binary operator expression
            \param parser Parser responsible for parsing input text
            \param left Parsed expression to the left of operator
            \param token Token representing the binary operation
        */

        const Expression * parse(Parser *parser,
                                const Expression* left,
                                Token token) override {
            const Expression *right {parser->parse(precedence)};
            return new BinOp(left, token.get_type(), right);
        }

        //! Return the precedence of the operator the parser parses.
        const int get_precedence() const {
            return precedence;
        }
    private:
        const int precedence;
};


/*! When we construct the parser, we register each sub-expression parser
    with its given symbol.
*/
Parser::Parser(Lexer lexer) : lexer(lexer) {
    mPrefixParsers[MINUS] = new UnaOpParser();
    mPrefixParsers[NUM] = new NumberParser();
    mPrefixParsers[LPARENS] = new ParensParser();

    mInfixParsers[PLUS] = new BinOpParser(1);
    mInfixParsers[MINUS] = new BinOpParser(1);
    mInfixParsers[DIVIDE] = new BinOpParser(2);
    mInfixParsers[TIMES] = new BinOpParser(2);
}

Parser::~Parser() {
    for (auto [key, val] : mPrefixParsers) {
        delete val;
    }
    for (auto [key, val] : mInfixParsers) {
        delete val;
    }
}

long double Parser::parse_and_eval(std::string input) {
    auto lexer = Lexer(input);
    auto parser = Parser(input);
    const Expression *expression = parser.parse(0);
    if (parser.next()) {
        delete expression;
        throw ParserException("Syntax Error");
    }
    auto val = expression->evaluate();
    delete expression;
    return val;
}

const Expression * Parser::parse(int min_precedence) {
    auto mbToken = lexer.next();
    if (!mbToken) {
        throw ParserException("Unexpected end of input");
    }

    Token token = mbToken.value();
    if (mPrefixParsers.count(token.get_type()) == 0 ){
        throw ParserException("Failed to parse: " + token.get_text());
    }

    auto prefix = mPrefixParsers.at(token.get_type());
    auto left = prefix->parse(this, token);

    for (;;) {
        mbToken = lexer.peek();
        if (!mbToken) {
            // return if we're at end of input
            break;
        }
        token = mbToken.value();
        if (mInfixParsers.count(token.get_type()) == 0) {
            // return if this token doesn't represent an infix operation
            break;
        }
        auto infix = mInfixParsers.at(token.get_type());
        if (infix->get_precedence() <= min_precedence) {
            // return if this operation has less precedence
            // than the last operation we've encountered
            break;
        }
        lexer.next(); //consume this operation
        left = infix->parse(this, left, token);
    }

    return left;
}

std::optional<Token> Parser::next() { return lexer.next(); }
