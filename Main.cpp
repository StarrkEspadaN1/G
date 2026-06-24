#include <iostream>
#include "Integer.h"
#include "Rational.h"
#include "Real.h"
#include "Point2d.h"
#include "Segment.h"

int main() {
    std::cout << "=== Тестирование Integer ===" << std::endl;
    Integer a(123);
    Integer b("456");
    Integer c = a + b;
    std::cout << "a = " << a << ", b = " << b << ", a + b = " << c << std::endl;
    std::cout << "a is even? " << (a.isEven() ? "yes" : "no") << std::endl;
    std::cout << "GCD of 12 and 18 = " << Integer::gcd(Integer(12), Integer(18)) << std::endl;
    
    std::cout << "\n=== Тестирование Rational ===" << std::endl;
    Rational r1(2, 3);
    Rational r2(4, 5);
    Rational r3 = r1 + r2;
    std::cout << r1 << " + " << r2 << " = " << r3 << std::endl;
    std::cout << "r1 simplified: " << r1.simplified() << std::endl;
    std::cout << "r1 reciprocal: " << r1.reciprocal() << std::endl;
    
    std::cout << "\n=== Тестирование Real ===" << std::endl;
    Real real1(3.14);
    Real real2(2.71);
    Real real3 = real1 + real2;
    std::cout << real1 << " + " << real2 << " = " << real3 << std::endl;
    
    std::cout << "\n=== Тестирование Point2d ===" << std::endl;
    Point2d p1(Real(0), Real(0));
    Point2d p2(Real(3), Real(4));
    std::cout << "Distance between p1 and p2: " << p1.distanceTo(p2) << std::endl;
    
    std::cout << "\n=== Тестирование Segment ===" << std::endl;
    Point2d p3(Real(0), Real(0));
    Point2d p4(Real(1), Real(1));
    Point2d p5(Real(0), Real(1));
    Point2d p6(Real(1), Real(0));
    
    Segment seg1(p3, p4);
    Segment seg2(p5, p6);
    
    std::cout << "Segment 1: " << seg1.toString() << std::endl;
    std::cout << "Segment 2: " << seg2.toString() << std::endl;
    std::cout << "Segments intersect? " << (seg1.intersects(seg2) ? "yes" : "no") << std::endl;
    std::cout << "Length of segment 1: " << seg1.length() << std::endl;
    
    return 0;
}
