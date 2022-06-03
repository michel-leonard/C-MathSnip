#include <stdlib.h>

typedef unsigned long long int positive_number;

static positive_number multiplication_modulo(positive_number a, positive_number b, const positive_number mod) {
    positive_number res = 0, tmp;
    for (b %= mod; a; a & 1 ? b >= mod - res ? res -= mod : 0, res += b : 0, a >>= 1, (tmp = b) >= mod - b ? tmp -= mod : 0, b += tmp);
    return res % mod;
}

static int is_prime_1062961(const positive_number n) {
    // Simply faster for small primes...
	return (n > 1) & ((n < 6) * 42 + 0x208A2882) >> n % 30 && (n < 49 || (n % 7 && n % 11 && n % 13 && n % 17 && n % 19 && n % 23 && n % 29 && (n < 961 || (n % 31 && n % 37 && n % 41 && n % 43 && n % 47 && n % 53 && n % 59 && n % 61 && n % 67 && (n < 5041 || (n % 71 && n % 73 && n % 79 && n % 83 && n % 89 && n % 97 && n % 101 && n % 103 && n % 107 && (n < 11881 || (n % 109 && n % 113 && n % 127 && n % 131 && n % 137 && n % 139 && n % 149 && n % 151 && n % 157 && (n < 26569 || (n % 163 && n % 167 && n % 173 && n % 179 && n % 181 && n % 191 && n % 193 && n % 197 && n % 199 && (n < 44521 || (n % 211 && n % 223 && n % 227 && n % 229 && n % 233 && n % 239 && n % 241 && n % 251 && n % 257 && (n < 69169 || (n % 263 && n % 269 && n % 271 && n % 277 && n % 281 && n % 283 && n % 293 && n % 307 && n % 311 && (n < 97969 || (n % 313 && n % 317 && n % 331 && n % 337 && n % 347 && n % 349 && n % 353 && n % 359 && n % 367 && (n < 139129 || (n % 373 && n % 379 && n % 383 && n % 389 && n % 397 && n % 401 && n % 409 && n % 419 && n % 421 && (n < 185761 || (n % 431 && n % 433 && n % 439 && n % 443 && n % 449 && n % 457 && n % 461 && n % 463 && n % 467 && (n < 229441 || (n % 479 && n % 487 && n % 491 && n % 499 && n % 503 && n % 509 && n % 521 && n % 523 && n % 541 && (n < 299209 || (n % 547 && n % 557 && n % 563 && n % 569 && n % 571 && n % 577 && n % 587 && n % 593 && n % 599 && (n < 361201 || (n % 601 && n % 607 && n % 613 && n % 617 && n % 619 && n % 631 && n % 641 && n % 643 && n % 647 && (n < 426409 || (n % 653 && n % 659 && n % 661 && n % 673 && n % 677 && n % 683 && n % 691 && n % 701 && n % 709 && (n < 516961 || (n % 719 && n % 727 && n % 733 && n % 739 && n % 743 && n % 751 && n % 757 && n % 761 && n % 769 && (n < 597529 || (n % 773 && n % 787 && n % 797 && n % 809 && n % 811 && n % 821 && n % 823 && n % 827 && n % 829 && (n < 703921 || (n % 839 && n % 853 && n % 857 && n % 859 && n % 863 && n % 877 && n % 881 && n % 883 && n % 887 && (n < 822649 || (n % 907 && n % 911 && n % 919 && n % 929 && n % 937 && n % 941 && n % 947 && n % 953 && n % 967 && (n < 942841 || (n % 971 && n % 977 && n % 983 && n % 991 && n % 997 && n % 1009 && n % 1013 && n % 1019 && n % 1021))))))))))))))))))))))))))))))))))))));
}

static int rabin_miller(const positive_number n, int iterations) {
	// Perform a Miller-Rabin test.
	positive_number a, b, c, d, e, f, h, i;
	if ((n == 1) == (n & 1)) { return n == 1 || n == 2; }
	if (n < 1062961) return is_prime_1062961(n);
	for (b = c = n - 1, h = 0; !(b & 1); b >>= 1, ++h);
	for (; iterations--;) {
		a = rand(); // random initialization.
		e = 1 + a % c;
		for (d = f = 1; f <= b; f <<= 1);
		for (; f >>= 1; d = multiplication_modulo(d, d, n), f & b && (d = multiplication_modulo(e, d, n)));
		if (d == 1) continue;
		for (i = h; i-- && d != c; d = multiplication_modulo(d, d, n));
		if (d != c) return 0;
	}
	return 1;
}

int main(void){
    return rabin_miller(5722419224120611, 20);
}
