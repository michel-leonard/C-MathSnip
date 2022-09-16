// return the largest number that can be used to divide the two numbers.
unsigned gcd(unsigned a, unsigned b){
    if (b) for(;(a %= b) && (b %= a););
    return a | b;
}

// Return the number that was multiplied by itself to reach N.
static inline unsigned square_root_1(unsigned n) {
    unsigned a = 0, b, c; // b = 1ULL << 62 for 64 bits
    for (b = 1 << 30; b; c = a + b, n -= c &= -(n >= c), a = (a >> 1) | (c & b), b >>= 2);
    // Variable n contains the remainder.
    return a;
}

// return the number that was multiplied by itself to reach N.
unsigned square_root_2(unsigned n){
    unsigned a = n > 0, b;
    if (n > 3) for (a = n >> 1, b = (a + n / a) >> 1; b < a; a = b, b = (a + n / a) >> 1);
    return a ;
}

unsigned initial_guess_nth_root(unsigned n, unsigned nth){
    unsigned res = 1;
    for(; n >>= 1; ++res);
    return nth ? 1 << (res + nth - 1) / nth : 0 ;
}

// return a number that, when multiplied by itself nth times, makes N.
unsigned nth_root_2(const unsigned n, const unsigned nth) {
    unsigned a = initial_guess_nth_root(n , nth), b, c, r = nth ? a + (n > 0) : n == 1 ;
    for (; a < r; b = a + (nth - 1) * r, a = b / nth)
        for (r = a, a = n, c = nth - 1; c && (a /= r); --c);
    return r;
}

#include <limits.h>

// return a number that, when multiplied by itself twice, makes N. 
unsigned cube_root(unsigned n){
    unsigned a = 0, b;
    for (int c = sizeof(unsigned) * CHAR_BIT / 3 * 3 ; c >= 0; c -= 3) {
        a <<= 1;
        b = a + (a << 1), b = b * a + b + 1 ;
        if (n >> c >= b)
            n -= b << c, ++a;
    }
    return a;
}

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
