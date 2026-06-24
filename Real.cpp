#include "Real.h"
#include <cmath>
#include <sstream>

void Real::normalize() {
    // Извлекаем целую часть из дробной, если она >= 1
    Integer intFromFrac = fractionalPart.integerPart();
    if (intFromFrac != Integer(0)) {
        integerPart = integerPart + intFromFrac;
        fractionalPart = fractionalPart.fractionalPart();
    }
    
    // Обрабатываем отрицательные числа
    if (integerPart.isNegativeNumber() && fractionalPart.isPositive()) {
        integerPart = integerPart - Integer(1);
        fractionalPart = Rational(Integer(1), Integer(1)) - fractionalPart;
    }
}

// ========== КОНСТРУКТОРЫ ==========

Real::Real() : integerPart(0), fractionalPart(0, 1) {}

Real::Real(const Integer& integer, const Rational& fractional)
    : integerPart(integer), fractionalPart(fractional) {
    normalize();
}

Real::Real(int value) : integerPart(value), fractionalPart(0, 1) {
    normalize();
}

Real::Real(double value) {
    if (std::isnan(value) || std::isinf(value)) {
        throw std::invalid_argument("Cannot create Real from NaN or Infinity");
    }
    
    double intPart;
    double fracPart = std::modf(value, &intPart);
    
    integerPart = Integer(static_cast<int>(intPart));
    fractionalPart = Rational(fracPart);
    normalize();
}

Real::Real(const std::string& str) {
    size_t pos = str.find('.');
    if (pos == std::string::npos) {
        integerPart = Integer(str);
        fractionalPart = Rational(0, 1);
    } else {
        std::string intStr = str.substr(0, pos);
        std::string fracStr = str.substr(pos + 1);
        
        integerPart = Integer(intStr);
        
        // Преобразуем дробную часть в Rational
        if (!fracStr.empty()) {
            Integer numerator(fracStr);
            Integer denominator = Integer(1);
            for (size_t i = 0; i < fracStr.length(); ++i) {
                denominator = denominator * Integer(10);
            }
            fractionalPart = Rational(numerator, denominator);
        } else {
            fractionalPart = Rational(0, 1);
        }
        normalize();
    }
}

// ========== ГЕТТЕРЫ/СЕТТЕРЫ ==========

Integer Real::getIntegerPart() const {
    return integerPart;
}

Rational Real::getFractionalPart() const {
    return fractionalPart;
}

void Real::setIntegerPart(const Integer& integer) {
    integerPart = integer;
    normalize();
}

void Real::setFractionalPart(const Rational& fractional) {
    fractionalPart = fractional;
    normalize();
}

// ========== ПРЕДИКАТЫ ==========

bool Real::isDecimal() const {
    return fractionalPart != Rational(0, 1);
}

bool Real::isNegative() const {
    return integerPart.isNegativeNumber() || 
           (integerPart == Integer(0) && fractionalPart.isNegative());
}

bool Real::isPositive() const {
    return integerPart.isPositiveNumber() || 
           (integerPart == Integer(0) && fractionalPart.isPositive());
}

// ========== АРИФМЕТИЧЕСКИЕ ОПЕРАТОРЫ ==========

Real Real::operator+() const {
    return *this;
}

Real Real::operator-() const {
    Real result(-integerPart, -fractionalPart);
    result.normalize();
    return result;
}

Real Real::operator+(const Real& other) const {
    // Складываем как Rational
    Rational thisRational = Rational(integerPart, Integer(1)) + fractionalPart;
    Rational otherRational = Rational(other.integerPart, Integer(1)) + other.fractionalPart;
    Rational sum = thisRational + otherRational;
    
    Integer intPart = sum.integerPart();
    Rational fracPart = sum.fractionalPart();
    
    Real result(intPart, fracPart);
    result.normalize();
    return result;
}

Real Real::operator-(const Real& other) const {
    Rational thisRational = Rational(integerPart, Integer(1)) + fractionalPart;
    Rational otherRational = Rational(other.integerPart, Integer(1)) + other.fractionalPart;
    Rational diff = thisRational - otherRational;
    
    Integer intPart = diff.integerPart();
    Rational fracPart = diff.fractionalPart();
    
    Real result(intPart, fracPart);
    result.normalize();
    return result;
}

Real Real::operator*(const Real& other) const {
    Rational thisRational = Rational(integerPart, Integer(1)) + fractionalPart;
    Rational otherRational = Rational(other.integerPart, Integer(1)) + other.fractionalPart;
    Rational product = thisRational * otherRational;
    
    Integer intPart = product.integerPart();
    Rational fracPart = product.fractionalPart();
    
    Real result(intPart, fracPart);
    result.normalize();
    return result;
}

Real Real::operator/(const Real& other) const {
    if (other == Real(0)) {
        throw std::runtime_error("Division by zero");
    }
    
    Rational thisRational = Rational(integerPart, Integer(1)) + fractionalPart;
    Rational otherRational = Rational(other.integerPart, Integer(1)) + other.fractionalPart;
    Rational quotient = thisRational / otherRational;
    
    Integer intPart = quotient.integerPart();
    Rational fracPart = quotient.fractionalPart();
    
    Real result(intPart, fracPart);
    result.normalize();
    return result;
}

// ========== ПРИСВАИВАЮЩИЕ АРИФМЕТИЧЕСКИЕ ОПЕРАТОРЫ ==========

Real& Real::operator+=(const Real& other) {
    *this = *this + other;
    return *this;
}

Real& Real::operator-=(const Real& other) {
    *this = *this - other;
    return *this;
}

Real& Real::operator*=(const Real& other) {
    *this = *this * other;
    return *this;
}

Real& Real::operator/=(const Real& other) {
    *this = *this / other;
    return *this;
}

// ========== ОПЕРАТОРЫ СРАВНЕНИЯ ==========

bool Real::operator==(const Real& other) const {
    return integerPart == other.integerPart && fractionalPart == other.fractionalPart;
}

bool Real::operator!=(const Real& other) const {
    return !(*this == other);
}

bool Real::operator<(const Real& other) const {
    if (integerPart != other.integerPart) {
        return integerPart < other.integerPart;
    }
    return fractionalPart < other.fractionalPart;
}

bool Real::operator<=(const Real& other) const {
    return *this < other || *this == other;
}

bool Real::operator>(const Real& other) const {
    return !(*this <= other);
}

bool Real::operator>=(const Real& other) const {
    return !(*this < other);
}

// ========== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ==========

std::string Real::toString() const {
    std::string result = integerPart.toString();
    if (fractionalPart != Rational(0, 1)) {
        // Преобразуем дробную часть в десятичную строку
        std::string fracStr = fractionalPart.toString();
        size_t pos = fracStr.find('/');
        if (pos != std::string::npos) {
            // Преобразуем дробь в десятичную
            Rational temp = fractionalPart;
            std::string decimal;
            Integer numerator = temp.getNumerator();
            Integer denominator = temp.getDenominator();
            
            for (int i = 0; i < 10; ++i) {
                numerator = numerator * Integer(10);
                Integer digit = numerator / denominator;
                numerator = numerator % denominator;
                decimal += digit.toString();
                if (numerator == Integer(0)) break;
            }
            result += "." + decimal;
        } else {
            result += "." + fracStr;
        }
    }
    return result;
}

double Real::toDouble() const {
    double result = static_cast<double>(integerPart.toInt());
    result += fractionalPart.getNumerator().toInt() / 
              static_cast<double>(fractionalPart.getDenominator().toInt());
    return result;
}

std::ostream& operator<<(std::ostream& os, const Real& num) {
    os << num.toString();
    return os;
}
