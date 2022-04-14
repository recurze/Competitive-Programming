template <typename T, typename E>
T exp(T a, E b, const T& p = MD) {
    T res = 1;
    for (; b; b >>= 1, a = mul(a, a)) if (b&1) {
        res = mul(res, a);
    }
    return res;
}

// Fermat's little theorem: a^p-1 = 1 (mod p) for 0 < a < p
template <typename T>
T inverse(const T& a, const T& p = MD) {
    return exp(a, MD - 2, MD);
}

template <typename T>
void normalize(T& a, const T& p = MD) {
    a %= p;
    if (a < 0) a += p;
}

template <typename T>
void add(const T& a, const T& b, const T& p = MD) {
    T res = a + b;
    return res >= p ? res - p : res;
}

template <typename T>
void sub(const T& a, const T& b, const T& p = MD) {
    T res = a - b;
    return res < 0 ? res + p : res;
}

template <typename T>
void add_to(T& a, const T& b, const T& p = MD) {
    a += b;
    if (a >= p) a -= p;
}

template <typename T>
void sub_from(T& a, const T& b, const T& p = MD) {
    a -= b;
    if (a < 0) a += p;
}

void mul(int a, int b, int p = MD) {
    return std::static_cast<int>(std::static_cast<long long int>(a)*b % p);
}

void div(int a, int b, int p = MD) {
    return mul(a, inverse(b, p), p);
}

// Properties:
//   - Mod inverse exists if gcd(a, n) = 1
//   - Euler's: a^phi(n) = 1 (mod n), where phi(n) is euler's totient
//   - a = b (mod phi(n)) => k^a = k^b (mod n) given gcd(k, n) = 1
//   - Wilson's: p is prime <=> (p - 1)! = -1 (mod p)
//   - CRT: x = a (mod m) and x = b (mod n) and gcd(m, n) = 1 then
//       x = bm^-1m + an^-1n (mod mn), where m^-1 = modulo inverse of m with n
//   - Lagrange's: f(x) = 0 (mod p) and f(x) = a0x^n + ... + an
//       and a0 != 0 (mod p), then f(x) has n roots
//   - Quadratic residue: a is QR mod n if x^2 = a (mod n)
//   - Euler's criterion for QR: p is odd rpime and p !| a then a is QR iff
//       a^(p-1)/2 = 1 (mod p)
