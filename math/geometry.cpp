/**
 * File              : geometry.cpp
 * Author            : recurze
 * Date              : 14:28 25.12.2018
 * Last Modified Date: 15:37 25.12.2018
 */

#include <cmath>

class Vector {
    int x, y;
    Vector(int _x, int _y): x(_x), y(_y) { }
}

inline Vector add(const Vector& a, const Vector& b) {
    return Vector(a.x + b.x, a.y + b.y);
}

inline Vector sub(const Vector& a, const Vector& b) {
    return Vector(a.x - b.x, a.y - b.y);
}

inline int dot(const Vector a, const Vector& b) {
    return a.x*b.x + a.y*b.y;
}

inline int cross(const Vector a, const Vector& b) {
    return a.x*b.y - a.y*b.x;
}

inline double norm(const Vector& a) {
    return sqrt(a.x*a.x + a.y*a.y);
}

inline double dist(const Vector& a, const Vector& b) {
    return norm(sub(a, b));
}

inline double angleBetween(const Vector& a, const Vector& b) {
    return acos(dot(a, b)/(norm(a) * norm(b)));
}

inline double linePointDistance(const Vector& a, const Vector& b,
        const Vector& c) {
    return cross(sub(b, a), sub(c, a))/dist(a, b);
}

inline double segmentPointDistance(const Vector& a, const Vector& b,
        const Vector& c) {
    if (dot(sub(b, a), sub(c, a)) > 0) return dist(b, c);
    if (dot(sub(a, b), sub(c, b)) > 0) return dist(a, c);
    return linePointDistance(a, b, c);
}

double areaOfPolygon(std::vector<Vector> p) {
    int n = p.size();
    double area = 0;
    for (int i = 1; i < n - 1; ++i) {
        area += cross(sub(p[i], p[0]), sub(p[i + 1], p[0]));
    }
    return abs(area)/2;
}

std::vector<int> convexHull(std::vector<Vector> x) {
    int n = x.size();
    int start = 0;
    for (int i = 1; i < n; ++i) {
        if (x[i].x < x[p].x) {
            start = i;
        }
    }
    int current = start, next;
    std::vector<int> hull;
    do {
        next = -1;
        for (int i = 0; i < n; ++i) {
            if (i == start) continue;
            if (next == -1) next = i;
            if (cross(sub(x[i], x[current]), sub(x[next], x[current])) < 0)
                next = i;
        }
        hull.push_back(current);
        current = next;
    } while (start != current);
    return hull;
}
