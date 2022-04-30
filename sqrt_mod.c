// return (a * b) % mod, avoiding overflow errors while doing modular multiplication.
static unsigned multiplication_modulo(unsigned a, unsigned b, const unsigned mod) {
    unsigned res = 0, tmp;
    for (b %= mod; a; a & 1 ? b >= mod - res ? res -= mod : 0, res += b : 0, a >>= 1, (tmp = b) >= mod - b ? tmp -= mod : 0, b += tmp);
    return res % mod;
}

// return (n ^ exp) % mod
static unsigned mod_pow(unsigned n, unsigned exp, const unsigned mod) {
    unsigned res = 1;
    for (n %= mod; exp; exp & 1 ? res = multiplication_modulo(res, n, mod) : 0, n = multiplication_modulo(n, n, mod), exp >>= 1);
    return res;
}

//  This function returns the Kronecker symbol of A and B.
int kronecker(unsigned a, unsigned b) {
    static const int s[8] = {0, 1, 0, -1, 0, -1, 0, 1};
    unsigned c;
    int res = (int) (a | b);
    if (a && b)
        if (res & 1) {
            for (c = 0; !(b & 1); ++c, b >>= 1);
            // When b is odd Jacobi and Kronecker symbols are identical, in factorization algorithms b is often the prime.
            // When b is an odd prime, Jacobi symbol is equal to the Legendre symbol.
            for (res = c & 1 ? s[a & 7] : 1; a; c & 1 ? res *= s[b & 7] : 0, a & b & 2 ? res = -res : 0, c = b % a, b = a, a = c)
                for (c = 0; !(a & 1); ++c, a >>= 1);
            res = b == 1 ? res : 0;
        } else res = 0;
    else res = res == 1;
    return res;
}

#include <stdlib.h>

// With "kronecker" it's on average faster than the "tonelli_shanks" implementation.
// Average complexity is O(log(mod) ** 3).
static unsigned sqrt_mod(unsigned n, const unsigned mod) {
    unsigned a = 0, b, c, d, e;
    if (kronecker(n, mod) != -1) {
        for(; kronecker(b = rand(), mod) != -1;);
        for(c = (e = mod - 1) >> 1, d = 0; !(c & 1); c >>= 1, d >>= 1, multiplication_modulo(mod_pow(n, c, mod), mod_pow(b, d, mod), mod) == e ?  d += e >> 1 : 0);
        a = multiplication_modulo(mod_pow(n, (c + 1) >> 1, mod), mod_pow(b, d >> 1, mod), mod);
    }
    return a ;
}


#include <assert.h>
int main() {
    unsigned n, mod, root ; /* root_2 = mod - root */

    n = 9964, mod = 57649, root = sqrt_mod(n, mod);
    assert(root == 6745); // 6745 * 6745  mod  9964 = 1504     and   9964 =    9964 mod 57649

    n = 1111111111, mod = 1111111121, root = sqrt_mod(n, mod);
    assert(root == 88664850);

    n = 5258, mod = 3851, root = sqrt_mod(n, mod);
    assert(root == 0); // no solution to the congruence exists.
}
