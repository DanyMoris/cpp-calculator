#include "calculator.h"
#include <cmath>

void Calculator::Set(Number n) {
    value_ = n;
}

Number Calculator::GetNumber() const {
    return value_;
}

void Calculator::Add(Number n) {
    value_ += n;
}

void Calculator::Sub(Number n) {
    value_ -= n;
}

void Calculator::Mul(Number n) {
    value_ *= n;
}

void Calculator::Div(Number n) {
    if (n != 0) {
        value_ /= n;
    }
}

void Calculator::Pow(Number n) {
    value_ = std::pow(value_, n);
}
