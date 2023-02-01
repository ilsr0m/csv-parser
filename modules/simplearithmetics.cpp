//
// Created by 1 on 28.01.2023.
//
#include "simplearithmetics.h"
#include "error.h"

SimpleArithmetics::SimpleArithmetics() = default;

SimpleArithmetics::~SimpleArithmetics() = default;

int SimpleArithmetics::calculate(Expression e) {
    int a = std::get<0>(e.getOperands());
    int b = std::get<1>(e.getOperands());
    int result;
    switch (e.getOperator())
    {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if(b == 0) throw Runtime_error("imposible to divide by zero");
            result = a / b;
            break;
        default:
            throw Runtime_error("impossible to calculate");
    }
    return result;
}
