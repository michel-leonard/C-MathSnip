// return (lhs * rhs) % mod
static unsigned multiplication_modulo(unsigned lhs, unsigned rhs, const unsigned mod) {
    unsigned res = 0;
    for (lhs %= mod, rhs%= mod; rhs; (rhs & 1) ? (res = (res + lhs) % mod) : 0, lhs = (lhs << 1) % mod, rhs >>= 1);
    return res;
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

#include <stdio.h>
int main(void){
    // res = (a ^ b) mod c
    unsigned a = 4, b = 13, c = 497, res = mod_pow(a, b, c) ;
    printf("(%d ^ %d) mod %d = %d\n", a, b , c, res);
}
