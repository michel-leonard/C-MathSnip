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
