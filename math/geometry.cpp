template <typename T>
class Vector {
public:
    Vector() { }
    Vector(const Vector& a) : x(a.x), y(a.y) { }
    Vector(const T& _x, const T& _y) : x(_x), y(_y) { }

    Vector& operator=(const Vector& b) { x = b.x; y = b.y; return *this; }

    constexpr std::pair<T, T> operator()() const { return {x, y}; }

    Vector& operator-=(const Vector& b) { x -= b.x; y -= b.y; return *this; }
    Vector& operator+=(const Vector& b) { x += b.x; y += b.y; return *this; }

    template <typename S, typename std::enable_if_t< std::is_integral_v<S>, bool> = true>
    Vector& operator*=(const S& s) { x *= s; y *= s; return *this; }

    friend double norm(const Vector<T>& a) {
        return std::sqrt(a.x*a.x + a.y*a.y);
    }

    friend Vector operator-(Vector a, const Vector& b) { return a -= b; }
    friend Vector operator+(Vector a, const Vector& b) { return a += b; }

    friend std::int64_t   dot(const Vector& a, const Vector& b) { return a.x*b.x + a.y*b.y; }
    friend std::int64_t cross(const Vector& a, const Vector& b) { return a.x*b.y - a.y*b.x; }

    friend std::ostream& operator<<(std::ostream& os, const Vector& a) { return os << a.x << ' ' << a.y; }
private:
    T x, y;
};

template <typename T>
double areaOfPolygon(const std::vector< Vector<T> >& points) {
    double area = 0;
    auto num_points = points.size();
    for (decltype(num_points) i = 1; i < num_points - 1; ++i) {
        area += cross(points[i] - points[0], points[i + 1] - points[0]);
    }
    return std::abs(area)/2;
}
