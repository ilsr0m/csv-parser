//
// Created by 1 on 28.01.2023.
//
#pragma once

#pragma once
// class represents expression parts: 2 operands
// as a tuple<int,int> and an operator as a char variable
#include <iostream>
#include <tuple>

class Expression {
private:
    // tuple included 2 operands (first, second)
    std::tuple<int, int> opers;
    // operator
    char op;

public:
    Expression();

    [[maybe_unused]] Expression(std::tuple<int, int> operands, char op);

    ~Expression();

    // getters for private values
    std::tuple<int, int> getOperands();

    [[nodiscard]] char getOperator() const;
};