#ifndef PARSER_HPP
#define PARSER_HPP

#include <map>
#include <exception>
#include "lexer.hpp"
#include "ast.hpp"

class InfixParser;
class PrefixParser;

//! A class for a Pratt Parser
/*!
    Implementation of Pratt Parser adapted (with modificaions) from
    Bob Nystrom's "Pratt Parsers: Expression Parsing Made Easy"
    (https://web.archive.org/web/20200528025335/http://journal.stuffwithstuff.com/2011/03/19/pratt-parsers-expression-parsing-made-easy/)

    Parsing is divided amongst smaller parsers. The main classes of these are
    PrefixParser and InfixParser.

    To parse an expression, we check the first token. If it's a well-formed
    expression, the first token will either be a parenthesis, unary
    operation or a number. Instances of `PrefixParser`s are given for each
    of these cases to parse the expression into an AST.

    We then check if the next token is an infix operation. If it is, we
    can parse this using an appropriate instance of `InfixParser`.

    Operator precedence is implemented by precedence climbing method.
    In this method, We keep track of the highest precedence seen so far
    (defaults to 0 at the top, or after using a PrefixParser). If we
    happen upon an infix operation with a precedence lower than that
    we've already seen, we return the AST for the previous operation.
    This AST becomes a child node of the operation with lower precedence.
    Otherwise, the AST becomes a parent node of the operation with higher
    precedence.
*/
class Parser {
    public:
        /*! Parser constructor
            \param lexer Lexer to pull tokens from while parsing
        */
        Parser(Lexer lexer);
        ~Parser();

        /*! Parse the expression provided by the lexer.
            \param min_precedence The precedence of the last seen binary operator.
                                  Defaults to 0 at the top of the input or when parsing
                                  unary operands.
        */
        const Expression *parse(int min_precedence);
        /*! Convenience function providing the lex->parse->evaluate pipeline
            \param input Input string to parse.
        */
        static long double parse_and_eval(std::string input);
        std::optional<Token> next();

    private:
        //! Lexer from which to pull token from
        Lexer lexer;
        //! Registry for prefix parsers
        std::map<Token_t, PrefixParser *> mPrefixParsers;
        //! Registery for infix parsers.
        std::map<Token_t, InfixParser *> mInfixParsers;
};

//! Abstract class for prefix parsers.
class PrefixParser {
    public:
        virtual ~PrefixParser() {};
        virtual const Expression * parse(Parser *parser, Token token) = 0;
};

//! Abstract class for infix parsers.
class InfixParser {
    public:
        virtual ~InfixParser() {};
        virtual const Expression * parse(Parser *parser,
                                 const Expression *left,
                                 Token token) = 0;
        virtual const int get_precedence() const = 0;
};

#endif