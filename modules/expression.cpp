//
// Created by 1 on 28.01.2023.
//
#include "expression.h"

#include <utility>

Expression::Expression() = default;

Expression::~Expression() = default;

[[maybe_unused]] [[maybe_unused]] Expression::Expression(std::tuple<int, int> operands, char op)
        : opers{std::move(operands)}, op(op) {}

std::tuple<int, int> Expression::getOperands()
{
    return this->opers;
}

char Expression::getOperator() const
{
    return this->op;
}