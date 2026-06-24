#pragma once
#include "Integer.h"
#include <string>

class Rational {
private:
    Integer numerator;
    Integer denominator;
    
    void simplify();
    
public:
    // Конструкторы
    Rational();
    Rational(const Integer& num, const Integer& den);
    explicit Rational(int value);
    explicit Rational(double value);
    explicit Rational(const std::string& str);
    
    // Копирование и перемещение
    Rational(const Rational& other) = default;
    Rational(Rational&& other) noexcept = default;
    
    // Деструктор
    ~Rational() = default;
    
    // Операторы присваивания
    Rational& operator=(const Rational& other) = default;
    Rational& operator=(Rational&& other) noexcept = default;
    
    // Геттеры/сеттеры
    Integer getNumerator() const;
    Integer getDenominator() const;
    void setNumerator(const Integer& num);
    void setDenominator(const Integer& den);
    
    // Предикаты
    bool isProper() const;
    bool isImproper() const;
    bool isPositive() const;
    bool isNegative() const;
    static bool areSameObject(const Rational& a, const Rational& b);
    
    // Методы для получения значений
    Rational reciprocal() const;
    Rational simplified() const;
    Integer integerPart() const;
    Rational fractionalPart() const;
    
    // Методы для модификации
    void simplifyInPlace();
    void reciprocalInPlace();
    
    // Арифметические операторы
    Rational operator+() const;
    Rational operator-() const;
    
    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const;
    
    // Присваивающие арифметические операторы
    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);
    
    // Операторы сравнения
    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;
    bool operator<(const Rational& other) const;
    bool operator<=(const Rational& other) const;
    bool operator>(const Rational& other) const;
    bool operator>=(const Rational& other) const;
    
    // Вспомогательные методы
    std::string toString() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Rational& num);
};
