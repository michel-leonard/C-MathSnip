// return the largest number that can be used to divide the two numbers.
unsigned gcd(unsigned a, unsigned b){
    if (b) for(;(a %= b) && (b %= a););
    return a | b;
}

// return the number that was multiplied by itself to reach N.
unsigned square_root(unsigned n){
    unsigned a = n > 0, b;
    if (n > 3) for (a = n >> 1, b = (a + n / a) >> 1; b < a; a = b, b = (a + n / a) >> 1);
    return a ;
}

// return a number that, when multiplied by itself nth times, makes N.
unsigned nth_root(const unsigned n, const unsigned nth) {
    unsigned a = n, b, c, r = nth ? n + (n > 1) : n == 1 ;
    for (; a < r; b = a + (nth - 1) * r, a = b / nth)
        for (r = a, a = n, c = nth - 1; c && (a /= r); --c);
    return r;
}

#include <limits.h>
// return the distance from zero of N.
unsigned int absolute(int n){
    const int mask = n >> (sizeof(int) * CHAR_BIT - 1);
    return (n + mask) ^ mask;
}

#include <stdlib.h>
unsigned random(){
    unsigned n = 0 ;
    for (size_t i = 0; i < sizeof(n); ((char*)&n)[i++] = rand());
    return n ;
}
