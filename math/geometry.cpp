#include <cmath>

template <typename T>
struct Vector {
    T x, y;
    Vector() { }
};

template <typename T>
Vector<T> add(const Vector<T>& a, const Vector<T>& b) {
    return Vector<T>{ .x = a.x + b.x, .y = a.y + b.y };
}

template <typename T>
Vector<T> sub(const Vector<T>& a, const Vector<T>& b) {
    return Vector<T>{ .x = a.x - b.x, .y = a.y - b.y };
}

template <typename T>
void add_to(Vector<T>& a, const Vector<T>& b) {
    a.x += b.x;
    a.y += b.y;
}

template <typename T>
void sub_from(Vector<T>& a, const Vector<T>& b) {
    a.x -= b.x;
    a.y -= b.y;
}

template <typename T, typename S>
void scale(Vector<T>& a, const S& s) {
    a.x *= s;
    a.y *= s;
}

template <typename T>
double norm(const Vector<T>& a) {
    return std::sqrt(x*x + y*y);
}

template <typename T>
T dot(const Vector<T>& a, const Vector<T>& b) {
    return a.x*b.x + a.y*b.y;
}

template <typename T>
T cross(const Vector<T>& a, const Vector<T>& b) {
    return a.x*b.y - a.y*b.x;
}

template <typename T>
double areaOfPolygon(const std::vector< Vector<T> >& points) {
    double area = 0;
    for (std::size_t i = 1; i < points.size() - 1; ++i) {
        area += cross(sub(points[i], points[0]), sub(points[i + 1], points[0]));
    }
    return std::abs(area)/2;
}
