/*!
    Definitions for methods of AST nodes
*/

#include "ast.hpp"

/* Unary Operator methods */

UnaOp::UnaOp(const Expression *expr, Token_t op) : op(op), oprand(expr) {}

long double UnaOp::evaluate() const {
    auto rand = oprand->evaluate();
    switch (op) {
        case MINUS:
          return (-rand);
          break;
        default:
          throw std::logic_error("Invalid prefix token");
    }
}

/* Binary operator methods */

BinOp::BinOp(const Expression *lh, Token_t op, const Expression *rh) : lh(lh), rh(rh), op(op) {}

long double BinOp::evaluate() const {
    auto lh_val = lh->evaluate();
    auto rh_val = rh->evaluate();
    switch (op) {
        case MINUS:
            return (lh_val - rh_val);
        case PLUS:
            return (lh_val + rh_val);
        case TIMES:
            return (lh_val * rh_val);
        case DIVIDE:
            return (lh_val / rh_val);
        default:
            throw std::logic_error("Invalid infix token");
    }
}

/* Number methods */

Number::Number(long double value) : value(value) {}

long double Number::evaluate() const {
    return value;
}