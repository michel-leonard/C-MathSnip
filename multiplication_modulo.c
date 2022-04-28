// return (a * b) % mod, avoiding overflow errors while doing modular multiplication.
static unsigned multiplication_modulo(unsigned a, unsigned b, const unsigned mod) {
    unsigned res = 0, tmp;
    for (b %= mod; a; a & 1 ? b >= mod - res ? res -= mod : 0, res += b : 0, a >>= 1, (tmp = b) >= mod - b ? tmp -= mod : 0, b += tmp);
    return res % mod;
}

#include <assert.h>
int main(void){
    unsigned a = 4294967291 ;
    unsigned b = 4294967279 ;
    unsigned mod = 4294967231 ;
    assert(multiplication_modulo(a, b, mod) == 2880);
    assert(multiplication_modulo(-1, -1, -5) == 16);
}
