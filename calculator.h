#pragma once
#include <cmath>

using Number = double;

class Calculator {
public:
    void Set(Number n);
    Number GetNumber() const;

    void Add(Number n);
    void Sub(Number n);
    void Mul(Number n);
    void Div(Number n);
    void Pow(Number n);

private:
    Number value_ = 0;
};
