#include "Point2d.h"
#include <cmath>

// ========== КОНСТРУКТОРЫ ==========

Point2d::Point2d() : x(0), y(0) {}

Point2d::Point2d(const Real& x, const Real& y) : x(x), y(y) {}

// ========== ГЕТТЕРЫ/СЕТТЕРЫ ==========

Real Point2d::getX() const {
    return x;
}

Real Point2d::getY() const {
    return y;
}

void Point2d::setX(const Real& newX) {
    x = newX;
}

void Point2d::setY(const Real& newY) {
    y = newY;
}

// ========== ОПЕРАТОРЫ ==========

bool Point2d::operator==(const Point2d& other) const {
    return x == other.x && y == other.y;
}

// ========== МЕТОДЫ ==========

bool Point2d::isSamePoint(const Point2d& other) const {
    return *this == other;
}

Real Point2d::distanceTo(const Point2d& other) const {
    Real dx = x - other.x;
    Real dy = y - other.y;
    
    // Используем sqrt через double (для упрощения)
    double dist = std::sqrt(dx.toDouble() * dx.toDouble() + 
                           dy.toDouble() * dy.toDouble());
    return Real(dist);
}
