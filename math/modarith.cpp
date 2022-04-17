#include <ostream>
#include <type_traits>
#include <cstdint>
constexpr int MD = 10;
template <typename T, typename std::enable_if_t< std::is_signed_v<T>, bool> = true>
class Mod {
public:
    Mod() : value(0), m(MD) {}
    Mod(const Mod& a) : value(a.value), m(a.m) {}

    template <typename U, typename std::enable_if_t< std::is_integral_v<U>, bool> = true>
    Mod(const U& n, const T& _m = MD) : value(normalize(n, _m)), m(_m) {}

    Mod& operator=(const Mod& b) { value = b.value; return *this; }

    constexpr T operator()() const { return value; }

    Mod& operator-=(const Mod& b) { if ((value -= b.value) <   0) value += m; return *this; }
    Mod& operator+=(const Mod& b) { if ((value += b.value) >= m) value -= m; return *this; }
    Mod& operator/=(const Mod& b) { return *this *= inverse(b); }
    Mod& operator*=(const Mod& b) {
        // assuming m*m fits in int64_t
        value = static_cast<T>(static_cast<std::int64_t>(value)*b.value % m);
        return *this;
    }

    template <typename U, typename std::enable_if_t< std::is_integral_v<U>, bool> = true>
    Mod& operator-=(const U& b) { return *this -= Mod(b); }

    template <typename U, typename std::enable_if_t< std::is_integral_v<U>, bool> = true>
    Mod& operator+=(const U& b) { return *this += Mod(b); }

    template <typename U, typename std::enable_if_t< std::is_integral_v<U>, bool> = true>
    Mod& operator*=(const U& b) { return *this *= Mod(b); }

    template <typename U, typename std::enable_if_t< std::is_integral_v<U>, bool> = true>
    Mod& operator/=(const U& b) { return *this /= Mod(b); }

    template <typename U, typename std::enable_if_t< std::is_integral_v<U>, bool> = true>
    static T normalize(U n, const T& m) {
        if (n < 0 or n >= m) n %= m;
        if (n < 0) n += m;
        return static_cast<T>(n);
    }

    friend Mod operator-(Mod a, const Mod& b) { return a -= b; }
    friend Mod operator+(Mod a, const Mod& b) { return a += b; }
    friend Mod operator*(Mod a, const Mod& b) { return a *= b; }
    friend Mod operator/(Mod a, const Mod& b) { return a /= b; }

    template <typename U, typename std::enable_if_t< std::is_integral_v<U>, bool> = true>
    friend Mod pow(Mod a, U b) {
        assert(b >= 0);
        Mod res(1);
        for (; b; b >>= 1, a *= a) {
            if (b&1) {
                res *= a;
            }
        }
        return res;
    }

    // assuming m is prime; otherwise use extended_gcd
    friend Mod inverse(Mod a) { return pow(a, a.m - 2); }

    friend std::ostream& operator<<(std::ostream& os, const Mod& a) { return os << a(); }
private:
    T value;
    T m;

    // Properties:
    //   - Mod inverse exists if gcd(a, n) = 1
    //   - Euler's: a^phi(n) = 1 (mod n), where phi(n) is euler's totient
    //   - a = b (mod phi(n)) => k^a = k^b (mod n) given gcd(k, n) = 1
    //   - Wilson's: p is prime <=> (p - 1)! = -1 (mod p)
    //   - CRT: x = a (mod m) and x = b (mod n) and gcd(m, n) = 1 then
    //       x = bm^-1m + an^-1n (mod mn), where m^-1 = modulo inverse of m wrt n
    //   - Lagrange's: f(x) = 0 (mod p) and f(x) = a0x^n + ... + an
    //       and a0 != 0 (mod p), then f(x) has n roots
    //   - Quadratic residue: a is QR mod n if x^2 = a (mod n)
    //   - Euler's criterion for QR: p is odd prime and p !| a then a is QR iff
    //       a^(p-1)/2 = 1 (mod p)
};
