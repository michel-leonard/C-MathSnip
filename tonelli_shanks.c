// return (lhs * rhs) % mod
static unsigned multiplication_modulo(unsigned a, unsigned b, const unsigned mod) {
    unsigned res = 0, tmp;
    for (b %= mod; a; a & 1 ? b >= mod - res ? res -= mod : 0, res += b : 0, a >>= 1, (tmp = b) >= mod - b ? tmp -= mod : 0, b += tmp);
    return res % mod;
}

// return (n ^ exp) % mod
static unsigned mod_pow(unsigned n, unsigned exp, const unsigned mod) {
    unsigned res = 1;
    for (n %= mod; exp; exp >>= 1) {
        if (exp & 1)
            res = multiplication_modulo(res, n, mod);
        n = multiplication_modulo(n, n, mod);
    }
    return res;
}

// return root such that (root * root) % mod congruent to n % mod.
// return mod if n is a quadratic non-residue modulo mod, no solution to the congruence exists.
static unsigned tonelli_shanks(unsigned n, const unsigned mod) {
    unsigned a = mod - 1, b = a, c = 0, d = 2, e, f, r = mod;
    if (mod_pow(n, b >> 1, mod) == 1) {
        for (; !(a & 1); ++c, a >>= 1);
        if (c == 1)
            r = mod_pow(n, (mod + 1) >> 2, mod);
        else {
            for (; b != mod_pow(d, b >> 1, mod); ++d);
            for (b = mod_pow(d, a, mod), r = mod_pow(n, (a + 1) >> 1, mod), e = mod_pow(n, a, mod), f = c; e != 1; f = a) {
                for (a = 0, c = e, --f; c != 1 && a < f; ++a)
                    c = multiplication_modulo(c, c, mod);
                for (d = b, n = f - a; n--;)
                    d = multiplication_modulo(d, d, mod);
                r = multiplication_modulo(r, d, mod);
                b = multiplication_modulo(d, d, mod);
                e = multiplication_modulo(e, b, mod);
            }
        }
    }
    return r;
}

#include <assert.h>
int main() {
    unsigned n, mod, root ; /* root_2 = mod - root */

    n = 27875, mod = 26371, root = tonelli_shanks(n, mod);
    assert(root == 14320); // 14320 * 14320  mod  26371 = 1504     and   1504 =    27875 mod 26371

    n = 1111111111, mod = 1111111121, root = tonelli_shanks(n, mod);
    assert(root == 88664850);

    n = 5258, mod = 3851, root = tonelli_shanks(n, mod);
    assert(root == 3851); // no solution to the congruence exists.
}

// A is assumed prime, the algorithm requires O(log A + r * r) multiplications modulo A, where r is the power of 2 dividing A − 1.
