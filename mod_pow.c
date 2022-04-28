// return (n ^ exp) % mod
unsigned mod_pow(unsigned n, unsigned exp, const unsigned mod) {
    unsigned a, b, res = 1;
    for (n %= mod; exp; exp >>= 1) {
            if (exp & 1)
                for (a = res, b = n, res = 0; b; b & 1 ? res = (res + a) % mod : 0, a = a << 1 % mod, b >>= 1); // res = (res * x) % n ;
            for (a = n, b = n, n = 0; b; b & 1 ? n = (n + a) % mod : 0, a = a << 1 % mod, b >>= 1); // x = (x * x) % n ;
        }
    return res;
}

#include <stdio.h>
int main(void){
    // res = (a ^ b) mod c
    unsigned a = 4, b = 13, c = 497, res = mod_pow(a, b, c) ;
    printf("(%d ^ %d) mod %d = %d\n", a, b , c, res);
}
