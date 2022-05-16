// You can try this ~100 lines C implementation of Pollard Rho

#include <stdlib.h>
#include <stdint.h>

typedef uint_fast64_t num ;

static inline num mul_mod(num a, num b, const num mod) {
    // Return (a * b) % mod, avoiding overflow errors while doing modular multiplication.
    num res = 0, tmp;
    for (b %= mod; a; a & 1 ? b >= mod - res ? res -= mod : 0, res += b : 0, a >>= 1, (tmp = b) >= mod - b ? tmp -= mod : 0, b += tmp);
    return res % mod;
}

static inline num square_root(num n) {
    // Return the number that was multiplied by itself to reach N.
    num a = 0, b, c;
    for (b = 1ULL << 62; b; c = a + b, n -= c &= -(n >= c), a = (a >> 1) | (c & b), b >>= 2);
    // Variable n contains the remainder.
    return a;
}

static  int is_prime(const num n, size_t iterations) {
    // Perform a Miller-Rabin (strong probable prime) test.
    num a = 0, b, c, d, e, f; int h, i;
    if ((n == 1) == (n & 1)) return n == 2;
    for (b = c = n - 1, h = 0; !(b & 1); b >>= 1, ++h);
    for (; iterations--;) {
        for (size_t g = 0; g < sizeof(a); ((char*)&a)[g++] = rand()); // rand input.
        do for (d = e = 1 + a % c, f = n; (d %= f) && (f %= d););
        while (d > 1 && f > 1);
        for (d = f = 1; f <= b; f <<= 1);
        for (; f >>= 1; d = mul_mod(d, d, n), f & b && (d = mul_mod(e, d, n)));
        if (d == 1) continue;
        for (i = h; i-- && d != c; d = mul_mod(d, d, n));
        if (d != c) return 0;
    }
    return 1;
}

static inline num factor_worker_2(const num n, size_t limit) {
    // Perform a Pollard's Rho probabilistic test.
    size_t a = -1, b = 2;
    num c, d = 1 + rand(), e = 1, f = 1;
    for (c = d %= n; f == 1 && --limit; d = c, b <<= 1, a = -1) {
        for (; f |= e, f == 1 && ++a != b;) {
            c = mul_mod(c, c, n);
            ++c; c *= c != n ;
            for (e = n, f = c > d ? c - d : d - c; (f %= e) && (e %= f););
        }
    }
    return f;
}

static inline num factor_worker_1(const num n) {
    // Perform a trial divisions test on N.
    static const num list[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 1};
    size_t i;
    for (i = -1; n % list[++i];);
    return list[i];
}

num factor(const num n) {
// Basic factorization manager, detect primes, perfect squares, execute workers.
    num res;
    switch (n) {
        case 0: case 1: case 2: case 3:
            res = 1; break;
        default:
            res = factor_worker_1(n);
            if (res == 1 && !is_prime(n, 20)) {
                res = square_root(n);
                if (res * res != n)
                    for(;res = factor_worker_2(n, -1), res == 1 || res == n;);
            }
    }
    return res;
}

#include <assert.h>

int main(void){
    num N, res;

    N = 16347567015183867763U, res = factor(N);
    assert(N != res && N % res == 0);

    N = 12534228435941376119U, res = factor(N);
    assert(N != res && N % res == 0);

    N = 8019808390007354327U, res = factor(N);
    assert(res == 1 || res == N);
}
