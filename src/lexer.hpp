/*!
    Declarations for classes and methods relating to the lexer.
*/

#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <optional>

//! Enumeration for the types of tokens exist in the language */
enum Token_t { PLUS, MINUS, TIMES, DIVIDE, LPARENS, RPARENS, NUM };

//! Token in the language
/*! A token contains some token type and the text that was tokenized
*/
class Token {
    public:
        Token();
        //! Construct a token
        /*!  \param token Type of token.
             \param text Tokenized text.
        */
        Token(Token_t token, std::string text);
        //! Return the token type
        Token_t get_type() const;
        //! Return the tokenized text.
        std::string get_text() const;

    private:
        //! The type of the token.
        Token_t type;
        //! The tokenized text.
        std::string text;
};

//! Lexer class
/*! A Lexer class is instantiated with its underlying string.
    It provides a linear traversal over the input text and
    splits it into individual tokens for parsing.
*/

class Lexer {
    public:
        /*! Lexer constructor
            \param input Input text
        */
        Lexer(std::string input);
        /*! Returns the next token or return false if no more input exists
            Consumes input.
        */
        std::optional<Token> next();
        /*! Returns the next token or return false if no more input exists
            Does not consume input.
        */
        std::optional<Token> peek();

    private:
        //! Cursor into input string.
        size_t cursor;
        //! Input string to tokenize.
        std::string input;

        //! Tests if character is an operator symbol.
        static bool is_operator(char c);
        //! Returns the string of non-operator symbol. Consumes input.
        std::string get_name();
};

#endif