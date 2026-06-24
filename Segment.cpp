#include "Segment.h"
#include <cmath>
#include <sstream>

// ========== КОНСТРУКТОРЫ ==========

Segment::Segment() 
    : p1(std::make_unique<Point2d>()), 
      p2(std::make_unique<Point2d>()) {}

Segment::Segment(const Point2d& point1, const Point2d& point2)
    : p1(std::make_unique<Point2d>(point1)),
      p2(std::make_unique<Point2d>(point2)) {}

Segment::Segment(const Segment& other)
    : p1(std::make_unique<Point2d>(*other.p1)),
      p2(std::make_unique<Point2d>(*other.p2)) {}

Segment::Segment(Segment&& other) noexcept
    : p1(std::move(other.p1)),
      p2(std::move(other.p2)) {}

// ========== ОПЕРАТОРЫ ПРИСВАИВАНИЯ ==========

Segment& Segment::operator=(const Segment& other) {
    if (this != &other) {
        p1 = std::make_unique<Point2d>(*other.p1);
        p2 = std::make_unique<Point2d>(*other.p2);
    }
    return *this;
}

Segment& Segment::operator=(Segment&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
    }
    return *this;
}

// ========== ГЕТТЕРЫ ==========

Point2d Segment::getP1() const {
    return *p1;
}

Point2d Segment::getP2() const {
    return *p2;
}

// ========== МЕТОДЫ ==========

bool Segment::operator==(const Segment& other) const {
    return (*p1 == *other.p1 && *p2 == *other.p2) ||
           (*p1 == *other.p2 && *p2 == *other.p1);
}

bool Segment::intersects(const Segment& other) const {
    // Проверка пересечения отрезков с использованием ориентаций
    auto orientation = [](const Point2d& a, const Point2d& b, const Point2d& c) -> int {
        Real val = (b.getY() - a.getY()) * (c.getX() - b.getX()) -
                   (b.getX() - a.getX()) * (c.getY() - b.getY());
        double d = val.toDouble();
        if (std::abs(d) < 1e-9) return 0;
        return d > 0 ? 1 : -1;
    };
    
    auto onSegment = [](const Point2d& a, const Point2d& b, const Point2d& c) -> bool {
        return std::min(a.getX().toDouble(), b.getX().toDouble()) <= c.getX().toDouble() &&
               c.getX().toDouble() <= std::max(a.getX().toDouble(), b.getX().toDouble()) &&
               std::min(a.getY().toDouble(), b.getY().toDouble()) <= c.getY().toDouble() &&
               c.getY().toDouble() <= std::max(a.getY().toDouble(), b.getY().toDouble());
    };
    
    int o1 = orientation(*p1, *p2, *other.p1);
    int o2 = orientation(*p1, *p2, *other.p2);
    int o3 = orientation(*other.p1, *other.p2, *p1);
    int o4 = orientation(*other.p1, *other.p2, *p2);
    
    // Общий случай
    if (o1 != o2 && o3 != o4) {
        return true;
    }
    
    // Специальные случаи
    if (o1 == 0 && onSegment(*p1, *p2, *other.p1)) return true;
    if (o2 == 0 && onSegment(*p1, *p2, *other.p2)) return true;
    if (o3 == 0 && onSegment(*other.p1, *other.p2, *p1)) return true;
    if (o4 == 0 && onSegment(*other.p1, *other.p2, *p2)) return true;
    
    return false;
}

Real Segment::length() const {
    return p1->distanceTo(*p2);
}

std::string Segment::toString() const {
    std::stringstream ss;
    ss << "Segment(" << p1->getX().toString() << "," << p1->getY().toString() 
       << ") -> (" << p2->getX().toString() << "," << p2->getY().toString() << ")";
    return ss.str();
}
