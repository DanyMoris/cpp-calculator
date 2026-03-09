#pragma once

#include <iostream>
#include <algorithm>
#include <numeric>

class Rational{
public:

    friend inline std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend inline std::istream& operator>>(std::istream& is, Rational& r);

    Rational() : numerator_(0), denominator_(1) {}

    Rational(int numerator) : numerator_(numerator), denominator_(1) {}

    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        Reduction();
    }

    Rational(const Rational& other) : numerator_(other.numerator_), denominator_(other.denominator_) {}

    Rational Inv() const {
        return Rational(denominator_, numerator_);
    }

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    Rational operator+(const Rational& other) const {
        int newNumerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        int newDenominator = denominator_ * other.denominator_;
        Rational result(newNumerator, newDenominator);
        result.Reduction();
        return result;
    }

    Rational operator-(const Rational& other) const {
        int newNumerator = numerator_ * other.denominator_ - other.numerator_ * denominator_;
        int newDenominator = denominator_ * other.denominator_;
        Rational result(newNumerator, newDenominator);
        result.Reduction();
        return result;
    }

    Rational operator*(const Rational& other) const {
        int newNumerator = numerator_ * other.numerator_;
        int newDenominator = denominator_ * other.denominator_;
        Rational result(newNumerator, newDenominator);
        result.Reduction();
        return result;
    }

    Rational operator/(const Rational& other) const {
        int newNumerator = numerator_ * other.denominator_;
        int newDenominator = denominator_ * other.numerator_;
        Rational result(newNumerator, newDenominator);
        result.Reduction();
        return result;
    }


    Rational& operator+=(const Rational& other) {
        int newNumerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        int newDenominator = denominator_ * other.denominator_;
        numerator_ = newNumerator;
        denominator_ = newDenominator;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& other) {
        int newNumerator = numerator_ * other.denominator_ - other.numerator_ * denominator_;
        int newDenominator = denominator_ * other.denominator_;
        numerator_ = newNumerator;
        denominator_ = newDenominator;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        int newNumerator = numerator_ * other.numerator_;
        int newDenominator = denominator_ * other.denominator_;
        numerator_ = newNumerator;
        denominator_ = newDenominator;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        int newNumerator = numerator_ * other.denominator_;
        int newDenominator = denominator_ * other.numerator_;
        numerator_ = newNumerator;
        denominator_ = newDenominator;
        Reduction();
        return *this;
    }

    Rational& operator=(const Rational& other) {
        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
        Reduction();
        return *this;
    }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        if (r.denominator_ == 1) {
            os << r.numerator_;
        } else {
            os << r.numerator_ << " / " << r.denominator_;
        }
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Rational& r) {
        int numerator, denominator;
        char slash;

        if (!(is >> numerator)) {
            return is;
        }

        if (!(is >> std::ws >> slash)) {
            r = Rational(numerator, 1);
            is.clear();
            return is;
        }

        if (slash != '/') {
            r = Rational(numerator, 1);
            is.unget();
            return is;
        }
        if (!(is >> denominator) || (denominator == 0)) {
            is.setstate(std::ios::failbit);
            return is;
        }

        r = Rational(numerator, denominator);
        return is;
    }

    bool operator==(const Rational& other) const {
        return (numerator_ == other.numerator_) && (denominator_ == other.denominator_);
    }

    int operator<=> (const Rational& other) const {
        int diff = numerator_ * other.denominator_ - denominator_ * other.numerator_;
        if (diff > 0) {
            return 1;
        } else if (diff < 0) {
            return -1;
        } else {
            return 0;
        }
    }

private:
    int numerator_;
    int denominator_;

};