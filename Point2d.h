#pragma once
#include "Real.h"
#include <cmath>

class Point2d {
private:
    Real x;
    Real y;
    
public:
    // Конструкторы
    Point2d();
    Point2d(const Real& x, const Real& y);
    Point2d(const Point2d& other) = default;
    Point2d(Point2d&& other) noexcept = default;
    
    // Виртуальный деструктор
    virtual ~Point2d() = default;
    
    // Операторы присваивания
    Point2d& operator=(const Point2d& other) = default;
    Point2d& operator=(Point2d&& other) noexcept = default;
    
    // Геттеры/сеттеры
    Real getX() const;
    Real getY() const;
    void setX(const Real& newX);
    void setY(const Real& newY);
    
    // Операторы
    bool operator==(const Point2d& other) const;
    
    // Методы
    bool isSamePoint(const Point2d& other) const;
    Real distanceTo(const Point2d& other) const;
};
