#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

class Integer {
private:
    bool isNegative;          // true если число отрицательное
    std::vector<int> digits;  // цифры в обратном порядке (младший разряд - 0 индекс)
    
    void removeLeadingZeros();
    void normalize();
    
public:
    // Конструкторы
    Integer();
    explicit Integer(int value);
    explicit Integer(double value);
    explicit Integer(bool value);
    explicit Integer(const std::string& str);
    Integer(const Integer& other);
    Integer(Integer&& other) noexcept;
    
    // Деструктор
    ~Integer() = default;
    
    // Операторы присваивания
    Integer& operator=(const Integer& other);
    Integer& operator=(Integer&& other) noexcept;
    
    // Геттеры/сеттеры
    bool getSign() const;
    const std::vector<int>& getDigits() const;
    void setSign(bool sign);
    void setDigits(const std::vector<int>& newDigits);
    
    // Предикаты
    bool isEven() const;
    bool isOdd() const;
    bool isNegativeNumber() const;
    bool isPositiveNumber() const;
    bool isPrime() const;
    static bool areCoprime(const Integer& a, const Integer& b);
    static bool areSameObject(const Integer& a, const Integer& b);
    
    // Методы для вычислений
    static Integer gcd(const Integer& a, const Integer& b);
    static Integer lcm(const Integer& a, const Integer& b);
    std::vector<Integer> getPrimeDivisors() const;
    
    // Арифметические операторы
    Integer operator-() const;
    Integer operator+() const;
    
    Integer operator+(const Integer& other) const;
    Integer operator-(const Integer& other) const;
    Integer operator*(const Integer& other) const;
    Integer operator/(const Integer& other) const;
    Integer operator%(const Integer& other) const;
    
    // Присваивающие арифметические операторы
    Integer& operator+=(const Integer& other);
    Integer& operator-=(const Integer& other);
    Integer& operator*=(const Integer& other);
    Integer& operator/=(const Integer& other);
    Integer& operator%=(const Integer& other);
    
    // Инкремент/декремент
    Integer& operator++();
    Integer operator++(int);
    Integer& operator--();
    Integer operator--(int);
    
    // Операторы сравнения
    bool operator==(const Integer& other) const;
    bool operator!=(const Integer& other) const;
    bool operator<(const Integer& other) const;
    bool operator<=(const Integer& other) const;
    bool operator>(const Integer& other) const;
    bool operator>=(const Integer& other) const;
    
    // Вспомогательные методы
    std::string toString() const;
    int toInt() const;
    
    // Дружественные функции для тестов
    friend std::ostream& operator<<(std::ostream& os, const Integer& num);
};
