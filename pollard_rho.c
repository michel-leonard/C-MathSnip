// Integer factorization in C language.
// Integer factorization is the decomposition of a composite number into a product of smaller integers.

unsigned long long pollard_rho(const unsigned long long N) {
	// Require : N is a composite number, not a square.
	// Ensure : gcd is a non-trivial factor of N.
	// Option : change the timeout, change the rand function.
	static const int timeout = 18;
	static unsigned long long rand_val = 2994439072U;
	rand_val = (rand_val * 1025416097U + 286824428U) % 4294967291LLU;
	unsigned long long gcd = 1, a, b, c, i = 0, j = 1, x = 1, y = 1 + rand_val % (N - 1);
	for (; gcd == 1; ++i) {
		if (i == j) {
			if (j >> timeout)
				break;
			j <<= 1;
			x = y; // "x" takes the previous value of "y" when "i" is a power of 2.
		}
		a = y, b = y; // computes y = f(y)
		for (y = 0; a; a & 1 ? b >= N - y ? y -= N : 0, y += b : 0, a >>= 1, (c = b) >= N - b ? c -= N : 0, b += c);
		y = (1 + y) % N; // function f performed f(y) = (y * y + 1) % N
		for (a = y > x ? y - x : x - y, b = N; (a %= b) && (b %= a););
		gcd = a | b; // the GCD(abs(y - x), N) was computed, continue until it's a non-trivial divisor of N.
	}
	return gcd;
}

#include <stdio.h>

int main(void){
	printf("a factor of %llu is %llu\n", 2466907995401943941, pollard_rho(2466907995401943941));
	//
	printf("a factor of %llu is %llu\n", 9203098392289663399, pollard_rho(9203098392289663399));
}
