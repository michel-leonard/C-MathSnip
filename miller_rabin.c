#include <stdlib.h>

typedef unsigned long long int positive_number;

static positive_number multiplication_modulo(positive_number a, positive_number b, const positive_number mod) {
    positive_number res = 0, tmp;
    for (b %= mod; a; a & 1 ? b >= mod - res ? res -= mod : 0, res += b : 0, a >>= 1, (tmp = b) >= mod - b ? tmp -= mod : 0, b += tmp);
    return res % mod;
}

static int is_prime(positive_number n, int k) {
    positive_number a = 0, b, c, d, e, f, g; int h, i;
    if ((n == 1) == (n & 1)) return n == 2;
    for (b = c = n - 1, h = 0; !(b & 1); b >>= 1, ++h);
    for (; k--;) {
        for (g = 0; g < sizeof(positive_number); ((char*)&a)[g++] = rand()); // random number.
        do for (d = e = 1 + a % c, f = n; (d %= f) && (f %= d););
        while (d > 1 && f > 1);
        for (d = f = 1; f <= b; f <<= 1);
        for (; f >>= 1; d = multiplication_modulo(d, d, n), f & b && (d = multiplication_modulo(e, d, n)));
        if (d == 1) continue;
        for (i = h; i-- && d != c; d = multiplication_modulo(d, d, n));
        if (d != c) return 0;
    }
    return 1;
}

int main(void){
    return is_prime(5722419224120611, 20);
}
