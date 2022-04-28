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
    unsigned a = mod, b = a - 1, c, d = b, e = 0, f = 2, g;
    if (mod_pow(n, b >> 1, mod) == 1) {
        for (; !(d & 1); ++e, d >>= 1);
        if (e == 1)
            a = mod_pow(n, (mod + 1) >> 2, mod);
        else {
            for (; b != mod_pow(f, b >> 1, mod); ++f);
            for (b = mod_pow(f, d, mod), a = mod_pow(n, (d + 1) >> 1, mod), c = mod_pow(n, d, mod), g = e; c != 1; g = d) {
                for (d = 0, e = c, --g; e != 1 && d < g; ++d)
                    e = multiplication_modulo(e, e, mod);
                for (f = b, n = g - d; n--;)
                    f = multiplication_modulo(f, f, mod);
                a = multiplication_modulo(a, f, mod);
                b = multiplication_modulo(f, f, mod);
                c = multiplication_modulo(c, b, mod);
            }
        }
    }
    return a;
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
