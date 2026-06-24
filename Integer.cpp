#include "Integer.h"
#include <cmath>
#include <sstream>

// ========== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ==========

void Integer::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    if (digits.size() == 1 && digits[0] == 0) {
        isNegative = false;
    }
}

void Integer::normalize() {
    removeLeadingZeros();
}

// ========== КОНСТРУКТОРЫ ==========

Integer::Integer() : isNegative(false) {
    digits.push_back(0);
}

Integer::Integer(int value) {
    if (value < 0) {
        isNegative = true;
        value = -value;
    } else {
        isNegative = false;
    }
    
    if (value == 0) {
        digits.push_back(0);
        return;
    }
    
    while (value > 0) {
        digits.push_back(value % 10);
        value /= 10;
    }
}

Integer::Integer(double value) {
    if (std::isnan(value) || std::isinf(value)) {
        throw std::invalid_argument("Cannot create Integer from NaN or Infinity");
    }
    
    if (value < 0) {
        isNegative = true;
        value = -value;
    } else {
        isNegative = false;
    }
    
    int intPart = static_cast<int>(std::round(value));
    if (intPart == 0) {
        digits.push_back(0);
        return;
    }
    
    while (intPart > 0) {
        digits.push_back(intPart % 10);
        intPart /= 10;
    }
}

Integer::Integer(bool value) : isNegative(false) {
    if (value) {
        digits.push_back(1);
    } else {
        digits.push_back(0);
    }
}

Integer::Integer(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("Empty string cannot be converted to Integer");
    }
    
    size_t start = 0;
    if (str[0] == '-') {
        isNegative = true;
        start = 1;
    } else if (str[0] == '+') {
        isNegative = false;
        start = 1;
    } else {
        isNegative = false;
    }
    
    for (size_t i = start; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            throw std::invalid_argument("Invalid character in numeric string");
        }
    }
    
    // Пропускаем ведущие нули
    while (start < str.length() && str[start] == '0') {
        start++;
    }
    
    if (start == str.length()) {
        digits.push_back(0);
        isNegative = false;
        return;
    }
    
    for (size_t i = str.length(); i > start; --i) {
        digits.push_back(str[i - 1] - '0');
    }
    normalize();
}

Integer::Integer(const Integer& other) 
    : isNegative(other.isNegative), digits(other.digits) {}

Integer::Integer(Integer&& other) noexcept 
    : isNegative(other.isNegative), digits(std::move(other.digits)) {
    other.digits.clear();
}

// ========== ОПЕРАТОРЫ ПРИСВАИВАНИЯ ==========

Integer& Integer::operator=(const Integer& other) {
    if (this != &other) {
        isNegative = other.isNegative;
        digits = other.digits;
    }
    return *this;
}

Integer& Integer::operator=(Integer&& other) noexcept {
    if (this != &other) {
        isNegative = other.isNegative;
        digits = std::move(other.digits);
        other.digits.clear();
    }
    return *this;
}

// ========== ГЕТТЕРЫ/СЕТТЕРЫ ==========

bool Integer::getSign() const {
    return isNegative;
}

const std::vector<int>& Integer::getDigits() const {
    return digits;
}

void Integer::setSign(bool sign) {
    isNegative = sign;
    if (digits.size() == 1 && digits[0] == 0) {
        isNegative = false;
    }
}

void Integer::setDigits(const std::vector<int>& newDigits) {
    digits = newDigits;
    normalize();
}

// ========== ПРЕДИКАТЫ ==========

bool Integer::isEven() const {
    return digits[0] % 2 == 0;
}

bool Integer::isOdd() const {
    return digits[0] % 2 != 0;
}

bool Integer::isNegativeNumber() const {
    return isNegative && !(digits.size() == 1 && digits[0] == 0);
}

bool Integer::isPositiveNumber() const {
    return !isNegative && !(digits.size() == 1 && digits[0] == 0);
}

bool Integer::isPrime() const {
    if (isNegative || digits.size() == 1 && digits[0] < 2) {
        return false;
    }
    
    // Преобразуем в int для проверки (для простоты, хотя это нарушает идею длинной арифметики)
    // В реальном проекте нужно делать проверку на больших числах
    int num = toInt();
    if (num < 2) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

bool Integer::areCoprime(const Integer& a, const Integer& b) {
    return gcd(a, b) == Integer(1);
}

bool Integer::areSameObject(const Integer& a, const Integer& b) {
    return &a == &b;
}

// ========== МЕТОДЫ ДЛЯ ВЫЧИСЛЕНИЙ ==========

Integer Integer::gcd(const Integer& a, const Integer& b) {
    if (a == Integer(0)) {
        Integer result = b;
        result.isNegative = false;
        return result;
    }
    return gcd(b % a, a);
}

Integer Integer::lcm(const Integer& a, const Integer& b) {
    if (a == Integer(0) || b == Integer(0)) {
        return Integer(0);
    }
    Integer result = a / gcd(a, b) * b;
    result.isNegative = false;
    return result;
}

std::vector<Integer> Integer::getPrimeDivisors() const {
    std::vector<Integer> divisors;
    if (isNegative || toInt() <= 1) {
        return divisors;
    }
    
    int num = toInt();
    int n = num;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(Integer(i));
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        divisors.push_back(Integer(n));
    }
    return divisors;
}

// ========== АРИФМЕТИЧЕСКИЕ ОПЕРАТОРЫ ==========

Integer Integer::operator-() const {
    Integer result(*this);
    if (!(digits.size() == 1 && digits[0] == 0)) {
        result.isNegative = !result.isNegative;
    }
    return result;
}

Integer Integer::operator+() const {
    return *this;
}

Integer Integer::operator+(const Integer& other) const {
    if (isNegative == other.isNegative) {
        // Сложение чисел с одинаковыми знаками
        Integer result;
        result.isNegative = isNegative;
        result.digits.clear();
        
        size_t maxSize = std::max(digits.size(), other.digits.size());
        int carry = 0;
        
        for (size_t i = 0; i < maxSize || carry; ++i) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        result.normalize();
        return result;
    } else {
        // Сложение чисел с разными знаками = вычитание
        if (isNegative && !other.isNegative) {
            // (-a) + b = b - a
            Integer temp = *this;
            temp.isNegative = false;
            return other - temp;
        } else {
            // a + (-b) = a - b
            Integer temp = other;
            temp.isNegative = false;
            return *this - temp;
        }
    }
}

Integer Integer::operator-(const Integer& other) const {
    if (isNegative == other.isNegative) {
        // Вычитание чисел с одинаковыми знаками
        Integer a = *this;
        Integer b = other;
        bool resultNegative = false;
        
        // Сравниваем абсолютные значения
        if (a.digits.size() < b.digits.size()) {
            std::swap(a, b);
            resultNegative = true;
        } else if (a.digits.size() == b.digits.size()) {
            for (int i = a.digits.size() - 1; i >= 0; --i) {
                if (a.digits[i] < b.digits[i]) {
                    std::swap(a, b);
                    resultNegative = true;
                    break;
                } else if (a.digits[i] > b.digits[i]) {
                    break;
                }
            }
        }
        
        Integer result;
        result.digits.clear();
        int borrow = 0;
        
        for (size_t i = 0; i < a.digits.size(); ++i) {
            int diff = a.digits[i] - borrow;
            if (i < b.digits.size()) {
                diff -= b.digits[i];
            }
            
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits.push_back(diff);
        }
        
        // Если мы поменяли местами, то знак результата противоположный
        if (isNegative && !resultNegative) {
            result.isNegative = true;
        } else if (!isNegative && resultNegative) {
            result.isNegative = true;
        } else {
            result.isNegative = false;
        }
        
        result.normalize();
        return result;
    } else {
        // Вычитание чисел с разными знаками = сложение
        Integer temp = other;
        temp.isNegative = !temp.isNegative;
        return *this + temp;
    }
}

Integer Integer::operator*(const Integer& other) const {
    if (*this == Integer(0) || other == Integer(0)) {
        return Integer(0);
    }
    
    Integer result;
    result.digits.assign(digits.size() + other.digits.size(), 0);
    
    for (size_t i = 0; i < digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry; ++j) {
            int product = result.digits[i + j] + carry;
            if (j < other.digits.size()) {
                product += digits[i] * other.digits[j];
            }
            result.digits[i + j] = product % 10;
            carry = product / 10;
        }
    }
    
    result.isNegative = isNegative != other.isNegative;
    result.normalize();
    return result;
}

Integer Integer::operator/(const Integer& other) const {
    if (other == Integer(0)) {
        throw std::runtime_error("Division by zero");
    }
    
    if (*this == Integer(0)) {
        return Integer(0);
    }
    
    // Простая реализация через вычитание (неэффективно, но работает)
    Integer a = *this;
    Integer b = other;
    bool resultNegative = a.isNegative != b.isNegative;
    a.isNegative = false;
    b.isNegative = false;
    
    if (a < b) {
        return Integer(0);
    }
    
    Integer result(0);
    Integer temp(0);
    
    // Умная реализация через длинное деление (упрощенно)
    // Берем по одной цифре
    Integer quotient(0);
    for (size_t i = a.digits.size(); i > 0; --i) {
        quotient = quotient * Integer(10) + Integer(a.digits[i - 1]);
        Integer count(0);
        while (quotient >= b) {
            quotient = quotient - b;
            count = count + Integer(1);
        }
        result = result * Integer(10) + count;
    }
    
    result.isNegative = resultNegative;
    if (result == Integer(0)) {
        result.isNegative = false;
    }
    return result;
}

Integer Integer::operator%(const Integer& other) const {
    if (other == Integer(0)) {
        throw std::runtime_error("Modulo by zero");
    }
    Integer quotient = *this / other;
    return *this - quotient * other;
}

// ========== ПРИСВАИВАЮЩИЕ АРИФМЕТИЧЕСКИЕ ОПЕРАТОРЫ ==========

Integer& Integer::operator+=(const Integer& other) {
    *this = *this + other;
    return *this;
}

Integer& Integer::operator-=(const Integer& other) {
    *this = *this - other;
    return *this;
}

Integer& Integer::operator*=(const Integer& other) {
    *this = *this * other;
    return *this;
}

Integer& Integer::operator/=(const Integer& other) {
    *this = *this / other;
    return *this;
}

Integer& Integer::operator%=(const Integer& other) {
    *this = *this % other;
    return *this;
}

// ========== ИНКРЕМЕНТ/ДЕКРЕМЕНТ ==========

Integer& Integer::operator++() {
    *this += Integer(1);
    return *this;
}

Integer Integer::operator++(int) {
    Integer temp = *this;
    ++(*this);
    return temp;
}

Integer& Integer::operator--() {
    *this -= Integer(1);
    return *this;
}

Integer Integer::operator--(int) {
    Integer temp = *this;
    --(*this);
    return temp;
}

// ========== ОПЕРАТОРЫ СРАВНЕНИЯ ==========

bool Integer::operator==(const Integer& other) const {
    if (isNegative != other.isNegative) return false;
    if (digits.size() != other.digits.size()) return false;
    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Integer::operator!=(const Integer& other) const {
    return !(*this == other);
}

bool Integer::operator<(const Integer& other) const {
    if (isNegative && !other.isNegative) return true;
    if (!isNegative && other.isNegative) return false;
    
    bool negative = isNegative;
    if (digits.size() != other.digits.size()) {
        return negative ? digits.size() > other.digits.size() 
                       : digits.size() < other.digits.size();
    }
    
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return negative ? digits[i] > other.digits[i] 
                           : digits[i] < other.digits[i];
        }
    }
    return false;
}

bool Integer::operator<=(const Integer& other) const {
    return *this < other || *this == other;
}

bool Integer::operator>(const Integer& other) const {
    return !(*this <= other);
}

bool Integer::operator>=(const Integer& other) const {
    return !(*this < other);
}

// ========== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ==========

std::string Integer::toString() const {
    if (digits.size() == 1 && digits[0] == 0) {
        return "0";
    }
    
    std::string result;
    if (isNegative) {
        result += "-";
    }
    
    for (int i = digits.size() - 1; i >= 0; --i) {
        result += std::to_string(digits[i]);
    }
    return result;
}

int Integer::toInt() const {
    int result = 0;
    for (int i = digits.size() - 1; i >= 0; --i) {
        result = result * 10 + digits[i];
    }
    return isNegative ? -result : result;
}

std::ostream& operator<<(std::ostream& os, const Integer& num) {
    os << num.toString();
    return os;
}
