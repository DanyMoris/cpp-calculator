#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

template<class Number>
Number Pow(Number l_op, Number r_op) {
    if constexpr (std::is_integral_v<Number>) {
        return IntegerPow(l_op, r_op);
    } else {
        return std::pow(l_op, r_op);
    }
}

using Error = std::string;

template<typename Number>
class Calculator {
public:
    Calculator(Number init = {}) : number_(init) {
    }

    std::optional<Error> Add(Number r) {
        number_ += r;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number r){
        number_ -= r;
        return std::nullopt;
    }

    std::optional<Error> Div(Number r) {
        if constexpr (std::is_integral_v<Number> ||
                      std::is_same_v<Number, Rational>) {
            if (r == Number(0)) {
                return "Division by zero";
            }
        }

        number_ /= r;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number r) {
        number_ *= r;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number r){
        if constexpr (std::is_integral_v<Number> ||
                      std::is_same_v<Number, Rational>) {
            if (r == Number(0) && number_ == Number(0)) {
                return "Zero power to zero";
            }
            if constexpr (std::is_same_v<Number, Rational>) {
                if (r.GetDenominator() != 1) {
                    return "Fractional power is not supported";
                }
            } else {
                if (r < Number(0)) {
                    return "Integer negative power";
                }
            }
        }
        number_ = ::Pow(number_, r);
        return std::nullopt;
    }

    void Set(Number n) {
        number_ = n;
    }

    void Negate(Number n) {
        Set(n);
        Mul(-1);
    }

    void Save() {
        mem_ = number_;
    }

    void Load() {
        assert(mem_.has_value());
        number_ = mem_.value();
    }

    void ClearMemory() {
        mem_.reset();
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

    Number GetNumber() const {
        return number_;
    }

    std::string GetNumberRepr() const {
        return std::to_string(number_);
    }

private:
    Number number_;
    std::optional<Number> mem_;
};
