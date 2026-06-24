#pragma once
#include "Point2d.h"
#include <memory>

class Segment {
private:
    std::unique_ptr<Point2d> p1;
    std::unique_ptr<Point2d> p2;
    
public:
    // Конструкторы
    Segment();
    Segment(const Point2d& point1, const Point2d& point2);
    Segment(const Segment& other);
    Segment(Segment&& other) noexcept;
    
    // Деструктор
    ~Segment() = default;
    
    // Операторы присваивания
    Segment& operator=(const Segment& other);
    Segment& operator=(Segment&& other) noexcept;
    
    // Геттеры
    Point2d getP1() const;
    Point2d getP2() const;
    
    // Методы
    bool operator==(const Segment& other) const;
    bool intersects(const Segment& other) const;
    Real length() const;
    
    // Вспомогательные методы
    std::string toString() const;
};
