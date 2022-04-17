#include <cassert>
#include <cmath>

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

/******************************************************************************/

template <typename T1, typename T2>
std::istream& operator>>(std::istream& is, std::pair<T1, T2>& v) {
    return is >> v.first >> v.second;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (T& i: v) is >> i;
    return is;
}

template <typename X>
void in(X& x) {
    std::cin >> x;
}

template <typename X, typename Y>
void in(X& x, Y& y) {
    in(x); in(y);
}

template <typename X, typename Y, typename Z>
void in(X& x, Y& y, Z& z) {
    in(x); in(y, z);
}

/******************************************************************************/

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& v) {
    return os << v.first << ' ' << v.second;
}

template<typename T>
struct has_const_iterator {
private:
    template<typename C> static char test(typename C::const_iterator*);
    template<typename C> static int  test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

template<typename Container>
std::enable_if_t<has_const_iterator<Container>::value and not std::is_same<Container, std::string>::value, std::ostream&>
operator<<(std::ostream& os, const Container& v) {
    std::string separator;
    for (const auto& x: v) os << separator << x, separator = ' ';
    return os;
}

template <typename T>
void out(const T& H) {
    std::cout << (H);
}

template <typename T1, typename... T2>
void out(const T1& H, const T2... T) {
    std::cout << (H) << ' '; out(T...);
}

template <typename T>
void eout(const char *s, const T H) {
    std::cerr << s << '=' << H << '\n';
}

template <typename T1, typename... T2>
void eout(const char *s, const T1 H, const T2... T) {
    while (*s != ',') std::cerr << *s++;
    std::cerr << '=' << H << " | "; eout(++s, T...);
}

/******************************************************************************/
/******************************************************************************/

#define nl                std::cout << '\n'

#ifdef LOCAL
#define err(...)          eout(#__VA_ARGS__, __VA_ARGS__)
#else
#define err(...)          42
#endif

#define rep(i, n)         for (decltype(n) i = (0); i < (n); ++i)
#define per(i, n)         for (auto i = n; i--; )
#define repr(i, l, r)     for (auto i = (l); i < (r); ++i)

#define sz(v)             ((v).size())
#define all(v)            (v).begin(), (v).end()
#define lla(v)            (v).rbegin(), (v).rend()

#define no                std::cout << "No"
#define yes               std::cout << "Yes"

/******************************************************************************/

constexpr auto INF = INT32_MAX;
constexpr auto LNF = INT64_MAX;

constexpr int N  = 505050;
constexpr int MD = 1000*1000*1000 + 7;

using i64 = std::int64_t;
using vl  = std::vector<i64>;
using vi  = std::vector<int>;
using vb  = std::vector<bool>;
using ii  = std::pair<int, int>;
using iii = std::pair< ii, int>;
using vii = std::vector<ii>;

/******************************************************************************/
/******************************************************************************/

//#define TC
int solve() {
    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(nullptr);

#ifdef TC
    int t = 1; in(t); rep(tc, t)
#endif
    solve(), nl;

    return 0;
}
