#include "Rational.h"
#include <sstream>
#include <cmath>

void Rational::simplify() {
    if (denominator == Integer(0)) {
        throw std::runtime_error("Denominator cannot be zero");
    }
    
    if (numerator == Integer(0)) {
        denominator = Integer(1);
        return;
    }
    
    Integer gcd = Integer::gcd(numerator, denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;
    
    if (denominator.getSign()) {
        numerator.setSign(!numerator.getSign());
        denominator.setSign(false);
    }
}

// ========== КОНСТРУКТОРЫ ==========

Rational::Rational() : numerator(0), denominator(1) {}

Rational::Rational(const Integer& num, const Integer& den) 
    : numerator(num), denominator(den) {
    if (denominator == Integer(0)) {
        throw std::runtime_error("Denominator cannot be zero");
    }
    simplify();
}

Rational::Rational(int value) : numerator(value), denominator(1) {
    simplify();
}

Rational::Rational(double value) {
    if (std::isnan(value) || std::isinf(value)) {
        throw std::invalid_argument("Cannot create Rational from NaN or Infinity");
    }
    
    // Преобразуем double в дробь
    const int precision = 1000000; // 1e-6 точность
    int intPart = static_cast<int>(value);
    double fracPart = value - intPart;
    
    numerator = Integer(intPart * precision + static_cast<int>(std::round(fracPart * precision)));
    denominator = Integer(precision);
    simplify();
}

Rational::Rational(const std::string& str) {
    size_t pos = str.find('/');
    if (pos == std::string::npos) {
        // Целое число
        numerator = Integer(str);
        denominator = Integer(1);
    } else {
        numerator = Integer(str.substr(0, pos));
        denominator = Integer(str.substr(pos + 1));
        if (denominator == Integer(0)) {
            throw std::runtime_error("Denominator cannot be zero");
        }
    }
    simplify();
}

// ========== ГЕТТЕРЫ/СЕТТЕРЫ ==========

Integer Rational::getNumerator() const {
    return numerator;
}

Integer Rational::getDenominator() const {
    return denominator;
}

void Rational::setNumerator(const Integer& num) {
    numerator = num;
    simplify();
}

void Rational::setDenominator(const Integer& den) {
    if (den == Integer(0)) {
        throw std::runtime_error("Denominator cannot be zero");
    }
    denominator = den;
    simplify();
}

// ========== ПРЕДИКАТЫ ==========

bool Rational::isProper() const {
    return numerator < denominator && numerator.isPositiveNumber();
}

bool Rational::isImproper() const {
    return numerator >= denominator || numerator.isNegativeNumber();
}

bool Rational::isPositive() const {
    return numerator.isPositiveNumber() && denominator.isPositiveNumber();
}

bool Rational::isNegative() const {
    return numerator.isNegativeNumber() || denominator.isNegativeNumber();
}

bool Rational::areSameObject(const Rational& a, const Rational& b) {
    return &a == &b;
}

// ========== МЕТОДЫ ДЛЯ ПОЛУЧЕНИЯ ЗНАЧЕНИЙ ==========

Rational Rational::reciprocal() const {
    if (numerator == Integer(0)) {
        throw std::runtime_error("Cannot take reciprocal of zero");
    }
    Rational result(denominator, numerator);
    result.simplify();
    return result;
}

Rational Rational::simplified() const {
    Rational result(*this);
    result.simplify();
    return result;
}

Integer Rational::integerPart() const {
    return numerator / denominator;
}

Rational Rational::fractionalPart() const {
    Integer intPart = numerator / denominator;
    Integer fracNum = numerator - intPart * denominator;
    Rational result(fracNum, denominator);
    result.simplify();
    return result;
}

// ========== МЕТОДЫ ДЛЯ МОДИФИКАЦИИ ==========

void Rational::simplifyInPlace() {
    simplify();
}

void Rational::reciprocalInPlace() {
    if (numerator == Integer(0)) {
        throw std::runtime_error("Cannot take reciprocal of zero");
    }
    std::swap(numerator, denominator);
    simplify();
}

// ========== АРИФМЕТИЧЕСКИЕ ОПЕРАТОРЫ ==========

Rational Rational::operator+() const {
    return *this;
}

Rational Rational::operator-() const {
    Rational result(-numerator, denominator);
    result.simplify();
    return result;
}

Rational Rational::operator+(const Rational& other) const {
    Integer num = numerator * other.denominator + other.numerator * denominator;
    Integer den = denominator * other.denominator;
    Rational result(num, den);
    result.simplify();
    return result;
}

Rational Rational::operator-(const Rational& other) const {
    Integer num = numerator * other.denominator - other.numerator * denominator;
    Integer den = denominator * other.denominator;
    Rational result(num, den);
    result.simplify();
    return result;
}

Rational Rational::operator*(const Rational& other) const {
    Integer num = numerator * other.numerator;
    Integer den = denominator * other.denominator;
    Rational result(num, den);
    result.simplify();
    return result;
}

Rational Rational::operator/(const Rational& other) const {
    if (other.numerator == Integer(0)) {
        throw std::runtime_error("Division by zero");
    }
    Integer num = numerator * other.denominator;
    Integer den = denominator * other.numerator;
    Rational result(num, den);
    result.simplify();
    return result;
}

// ========== ПРИСВАИВАЮЩИЕ АРИФМЕТИЧЕСКИЕ ОПЕРАТОРЫ ==========

Rational& Rational::operator+=(const Rational& other) {
    *this = *this + other;
    return *this;
}

Rational& Rational::operator-=(const Rational& other) {
    *this = *this - other;
    return *this;
}

Rational& Rational::operator*=(const Rational& other) {
    *this = *this * other;
    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    *this = *this / other;
    return *this;
}

// ========== ОПЕРАТОРЫ СРАВНЕНИЯ ==========

bool Rational::operator==(const Rational& other) const {
    return numerator * other.denominator == other.numerator * denominator;
}

bool Rational::operator!=(const Rational& other) const {
    return !(*this == other);
}

bool Rational::operator<(const Rational& other) const {
    return numerator * other.denominator < other.numerator * denominator;
}

bool Rational::operator<=(const Rational& other) const {
    return *this < other || *this == other;
}

bool Rational::operator>(const Rational& other) const {
    return !(*this <= other);
}

bool Rational::operator>=(const Rational& other) const {
    return !(*this < other);
}

// ========== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ==========

std::string Rational::toString() const {
    if (denominator == Integer(1)) {
        return numerator.toString();
    }
    return numerator.toString() + "/" + denominator.toString();
}

std::ostream& operator<<(std::ostream& os, const Rational& num) {
    os << num.toString();
    return os;
}
