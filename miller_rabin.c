typedef unsigned long long int ulong;

ulong mul_mod(ulong a, ulong b, const ulong mod) {
	ulong res = 0, c; // return (a * b) % mod, avoiding overflow errors while doing modular multiplication.
	for (b %= mod; a; a & 1 ? b >= mod - res ? res -= mod : 0, res += b : 0, a >>= 1, (c = b) >= mod - b ? c -= mod : 0, b += c);
	return res % mod;
}

ulong pow_mod(ulong n, ulong exp, const ulong mod) {
	ulong res = 1; // return (n ^ exp) % mod
	for (n %= mod; exp; exp & 1 ? res = mul_mod(res, n, mod) : 0, n = mul_mod(n, n, mod), exp >>= 1);
	return res;
}

ulong mul_mod(ulong a, ulong b, const ulong mod) {
	ulong res = 0, c; // return (a * b) % mod, avoiding overflow errors while doing modular multiplication.
	for (b %= mod; a; a & 1 ? b >= mod - res ? res -= mod : 0, res += b : 0, a >>= 1, (c = b) >= mod - b ? c -= mod : 0, b += c);
	return res % mod;
}

ulong pow_mod(ulong n, ulong exp, const ulong mod) {
	ulong res = 1; // return (n ^ exp) % mod.
	for (n %= mod; exp; exp & 1 ? res = mul_mod(res, n, mod) : 0, n = mul_mod(n, n, mod), exp >>= 1);
	return res;
}

int is_prime(ulong n) {
	// Perform a Miller-Rabin test, it should be a deterministic version.
	static const ulong bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	static const int n_bases = (int) sizeof(*bases);
	for (int i = 0; i < n_bases; ++i)
		if (n % bases[i] == 0)
			return n == bases[i];
	if (n < bases[n_bases - 1] * bases[n_bases - 1])
		return 1 < n;
	// Depending on the size of the number, we don't need to test all the bases.
	int lim = n < 2152302898747 ? n < 25326001 ? n < 2047 ? 1 : n < 1373653 ? 2 : 3 : n < 3215031751 ? 4 :
		5 : n < 341550071728321 ? n < 3474749660383 ? 6 : 7 : n < 3825123056546413051 ? 9 : 12, res = 1, a = 0;
	ulong b, c;
	for (b = n - 1; ~b & 1; b >>= 1, ++a);
	for (int i = 0; i < lim && res; ++i)
		if (c = pow_mod(bases[i], b, n), c != 1) {
			for (int d = a; d-- && (res = c + 1 != n);)
				c = mul_mod(c, c, n);
			res = !res;
		}
	return res;
}

int main(void){
	return is_prime(8193145868754512737);
}
