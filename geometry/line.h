//
// Created by Shuangquan Li on 20/09/2018.
//

#ifndef __GEOMETRY_LINE_H__
#define __GEOMETRY_LINE_H__

#include <cmath>
#include <functional>
#include <iostream>

#include "point.h"

namespace cil {


template<
        typename T,
        typename Point = point<T>
>
class __line_base {

public:
    typedef Point point_type;

public:
    virtual T A() const = 0;

    virtual T B() const = 0;

    virtual T C() const = 0;

    /// whether a point lies on this line.
    bool on_line(const point_type &p, double eps = 1e-9) const {
        return on_line(p.x(), p.y());
    }

    template<typename U>
    bool on_line(U x, U y, double eps = 1e-9) const {
        return std::abs(A() * x + B() * y + C()) <= eps;
    }

    T solve_x_with_y(T y) const {
        return (-C() - B() * y) / A();
    }

    T solve_y_with_x(T x) const {
        return (-C() - A() * x) / B();
    }
};


/// line_abc: A * x + B * y + C = 0
template<
        typename T,
        typename Point = point<T>
>
class line_abc : public __line_base<T, Point> {

public:
    typedef Point point_type;

private:
    T __a, __b, __c;

public:
    line_abc(T a, T b, T c) : __a(a), __b(b), __c(c) {}

    T A() const { return __a; }

    T B() const { return __b; }

    T C() const { return __c; }

};

template<
        typename T,
        typename Point = point<T>
>
std::ostream& operator<<(std::ostream& os, const line_abc<T, Point>& l) {
    os << "line_abc( " << l.A() << " * x + " << l.B() << " * y + " << l.C() << " = 0 )" << std::flush;
    return os;
};


/// line_kv: y = k * x + b
template<
        typename T,
        typename Point = point<T>
>
class line_kb : public __line_base<T, Point> {

public:
    typedef Point point_type;

private:
    T __k, __b;

public:

    line_kb(T k, T b): __k(k), __b(b) {}

    T A() const { return __k; }

    T B() const { return static_cast<T>(-1); }

    T C() const { return __b; }

    T k() const { return __k; }

    T b() const { return __b; }

};

template<
        typename T,
        typename Point = point<T>
>
std::ostream& operator<<(std::ostream& os, const line_kb<T, Point>& l) {
    os << "line_kb( y = " << l.k() << " * x + " << l.b()<< " )" << std::flush;
    return os;
};


/// line_2p: line with 2 point (x1, y1), (x2, y2)
template<
        typename T,
        typename Point = point<T>
>
class line_2p : public __line_base<T, Point> {

public:
    typedef Point point_type;

private:
    point_type __pa, __pb;

public:

    line_2p(const point_type& Pa, const point_type& Pb): __pa(Pa), __pb(Pb) {}

    line_2p(T x1, T y1, T x2, T y2) : __pa(x1, y1), __pb(x2, y2) {}

    T A() const { return __pb.y() - __pa.y(); }

    T B() const { return __pa.x() - __pb.x(); }

    T C() const { return __pb.x() * __pa.y() - __pa.x() * __pb.y(); }

    point_type Pa() const { return __pa; }

    point_type Pb() const { return __pb; }

    /// whether a point lies on the segment between Pa and Pb.
    bool on_segment(const point_type& p) const {
        return on_segment(p.x(), p.y());
    }

    template<typename U>
    bool on_segment(U x, U y) const {
        if (!this->on_line(x, y)) return false;
        bool x_on = (__pa.x() <= x && x <= __pb.x()) || (__pa.x() >= x && x >= __pb.x());
        bool y_on = (__pa.y() <= y && y <= __pb.y()) || (__pa.y() >= y && y >= __pb.y());
        return x_on && y_on;
    }
};

template<
        typename T,
        typename Point = point<T>
>
std::ostream& operator<<(std::ostream& os, const line_2p<T, Point>& l) {
    os << "line_2p( " << l.Pa() << ", " << l.Pb() << " )" << std::flush;
    return os;
};


/////////////////// utils ///////////////////


/// whether two lines are parallel.
template<
        typename T,
        typename Point = point<T>
>
bool are_parallel(const line_2p<T, Point>& l1, const line_2p<T, Point>& l2, double eps = 1e-9) {
    return std::abs(l1.A() * l2.B() - l1.B() * l2.A()) <= eps;
}


/// whether two lines have and only have one intersection point.
/// if true, return the coordinate on reference parameters "x" and "y".
template<
        typename T,
        typename Point = point<T>,
        typename IntersectionType = double
>
bool intersection(const line_2p<T, Point>& l1, const line_2p<T, Point>& l2,
                  IntersectionType& x, IntersectionType& y, double eps=1e-9) {
    if (are_parallel(l1, l2, eps)) return false;
    if (l1.B() == 0) {
        x = IntersectionType(-l1.C()) / IntersectionType(l1.A());
        y = IntersectionType(-l2.C() - l2.A() * x) / IntersectionType(l2.B());
        return true;
    }
    if (l2.B() == 0) {
        x = IntersectionType(-l2.C()) / l2.A();
        y = IntersectionType(-l1.C() - l1.A() * x) / IntersectionType(l1.B());
        return true;
    }
    x = IntersectionType(l1.B() * l2.C() - l2.B() * l1.C()) / IntersectionType(l1.A() * l2.B() - l2.A() * l1.B());
    y = IntersectionType(-x * l1.A() - l1.C()) / IntersectionType(l1.B());
    return true;
}


} // namespace cil

#endif // __GEOMETRY_LINE_H__
