/*!
    Declarations for the nodes of the AST. Three node types exist for unary operators,
    binary operators and numbers. Evaluation of a node happens by calling the
    `evaluate()` method.
*/

#ifndef AST_HPP
#define AST_HPP

#include <memory>

#include "lexer.hpp"

//! Abstract class for an arithmatic expression AST node.
/*! Expression is an abstract class for arithmetic expressions. Expression
    nodes in the AST will implement this Expression class.
*/
class Expression {
    public:
        virtual ~Expression() {};
        //! Virtual method for evaluating the node.
        virtual long double evaluate() const = 0;
};

//! An AST representation for Unary Operators
class UnaOp : public Expression {
    public:
        //! UnaOp constructor.
        /*!
            \param exp Operand expression
            \param tok Token representing operator.
        */
        UnaOp(const Expression* exp, Token_t tok);
        //! Evaluate this node
        long double evaluate() const;

    private:
        //! Token type representing the operator.
        Token_t op;
        //! Operand expression
        std::unique_ptr<const Expression> oprand;
};

//! An AST representation for Unary Operators
class BinOp : public Expression
{
    public:
        //! UnaOp constructor.
        /*!
            \param lh Left operand expression
            \param tok Token representing operator.
            \param rh Right operand expression
        */
        BinOp(const Expression *lh, Token_t, const Expression *rh);
        //! Evaluate this node
        long double evaluate() const;

    private:
        //! Left operand expression
        std::unique_ptr<const Expression> lh;
        //! Right operand expression
        std::unique_ptr<const Expression> rh;
        //! Token type representing the operator.
        Token_t op;
};

//! An AST representation for numeric literals
class Number : public Expression
{
    public:
        //! Number constructor
        /*!
            \param val Value of the number.
        */
        Number(long double val);
        //! Returns the value of the number.
        long double evaluate() const;

    private:
        //! Value of the Number.
        long double value;
};

#endif