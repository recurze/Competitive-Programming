/**
 * File              : modarith.cpp
 * Author            : recurze
 * Date              : 13:34 25.12.2018
 * Last Modified Date: 17:05 25.12.2018
 */

inline void add(int& a, int b, int p = MD) { a += b; a -= (a >= p)*p; }
inline void sub(int& a, int b, int p = MD) { a -= b; a -= (a <  0)*p; }

inline int mul(int a, int b, int p = MD) { return (int) (1L*a*b)%p; }
inline int div(int a, int b, int p = MD) { return mul(a, inverse(b, p), p); }

int exp(int a, long long b, int p = MD) {
    int res = 1;
    while (b) {
        if (b&1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

// Fermat's little theorem: a^p-1 = 1 (mod p) for 0 < a < p
int inverse(int a, int p = MD) {
    return exp(a, MD - 2, MD);
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
