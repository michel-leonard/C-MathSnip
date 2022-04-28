unsigned mod_pow(unsigned n, unsigned exp, const unsigned mod) {
    unsigned a, b, res = 1;
    if (mod) for (n %= mod; exp; exp >>= 1) {
        if (exp & 1)
            for (a = res, b = n, res = 0; b; b & 1 ? res = (res + a) % mod : 0, a = a << 1 % mod, b >>= 1);
        for (a = n, b = n, n = 0; b; b & 1 ? n = (n + a) % mod : 0, a = a << 1 % mod, b >>= 1);
    }
    return res;
}

// without using numbers larger than 32 bits.
// return root such that (root * root) % mod congruent to n % mod.
// return mod if n is a quadratic non-residue modulo mod, no solution to the congruence exists.
unsigned tonelli_shanks(unsigned n, const unsigned mod) {
    unsigned a = mod - 1, b = a, c = 0, d = 2, e, f, r = mod;
    if (mod_pow(n, b >> 1, mod) == 1) {
        for (; !(a & 1); ++c, a >>= 1);
        if (c == 1)
            r = mod_pow(n, (mod + 1) >> 2, mod);
        else {
            for (; b != mod_pow(d, b >> 1, mod); ++d);
            for (b = mod_pow(d, a, mod), r = mod_pow(n, (a + 1) >> 1, mod), e = mod_pow(n, a, mod), f = c; e != 1; f = a){
                for(a = 0, c = e, --f; c != 1 && a < f; ++a)
                    for (d = c, n = c, c = 0; n; n & 1 ? c = (c + d) % mod : 0, d = d << 1 % mod, n >>= 1); // c = (c * c) % mod ;
                for(d = b, n = f - a; n--;)
                    for (c = d, f = d, d = 0; f; f & 1 ? d = (d + c) % mod : 0, c = c << 1 % mod, f >>= 1); // d = (d * d) % mod ;
                for (c = r, f = d, r = 0; f; f & 1 ? r = (r + c) % mod : 0, c = c << 1 % mod, f >>= 1); // r = (r * d) % mod ;
                for (c = d, f = d, b = 0; f; f & 1 ? b = (b + c) % mod : 0, c = c << 1 % mod, f >>= 1); // b = (d * d) % mod ;
                for (c = e, f = b, e = 0; f; f & 1 ? e = (e + c) % mod : 0, c = c << 1 % mod, f >>= 1); // e = (e * b) % mod ;
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

    n = 2675, mod = 7757, root = tonelli_shanks(n, mod);
    assert(root == 2034); // 2034 * 2034   mod   7757 = 2675     and   2675 =     2675 mod 7757

    n = 5258, mod = 3851, root = tonelli_shanks(n, mod);
    assert(root == 3851); // no solution to the congruence exists.
}
