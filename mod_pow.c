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

#include <stdio.h>
int main(void){
    // res = (a ^ b) mod c
    unsigned a = 4, b = 13, c = 497, res = mod_pow(a, b, c) ;
    printf("(%d ^ %d) mod %d = %d\n", a, b , c, res);
}
