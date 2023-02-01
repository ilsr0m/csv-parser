#pragma once
#include <iostream>
#include <string>
#include <utility>

// error message class
template <int N>
class Error
{
private:
    std::string message;

public:
    explicit Error(std::string s) : message{std::move(s)} {}
    [[nodiscard]] std::string get_message() const { return message; }
    void put(std::ostream &os) const { os << message; };
};

using Syntax_error = Error<1>;
using File_error = Error<2>;
using Runtime_error = Error<3>;

template <int N>
std::ostream &operator<<(std::ostream &os, const Error<N> &x)
{
    x.put(os);
    return os;
}