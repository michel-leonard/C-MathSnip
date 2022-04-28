// return the largest number that can be used to divide the two numbers.
unsigned gcd(unsigned a, unsigned b){
    if (a && b) for(;(a %= b) && (b %= a););
    return a | b;
}

// return the number that was multiplied by itself to reach N.
unsigned square_root(unsigned n){
    unsigned a = n > 0, b;
    if (n > 1) for (a = n >> 1, b = (a + n / a) >> 1; b < a; a = b, b = (a + n / a) >> 1);
    return a ;
}

#include <limits.h>
// return the distance from zero of N.
unsigned int absolute(int n){
    const int mask = n >> (sizeof(int) * CHAR_BIT - 1);
    return (n + mask) ^ mask;
}

#include <stdlib.h>
unsigned short random(){
    unsigned short n = 0 ;
    for (size_t i = 0; i < sizeof(n); ((char*)&n)[i++] = rand());
    return n ;
}
