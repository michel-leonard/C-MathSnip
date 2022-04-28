// return a modular multiplicative inverse of n with respect to the modulus.
// return 0 if the linear congruence has no solutions.
unsigned mod_inv(unsigned n, const unsigned mod) {
    unsigned a = mod, b = a, c = 0, d = 0, e = 1, f, g;
    for (n *= a > 1; n > 1 && (n *= a > 0); e = g, c = (c & 3) | (c & 1) << 2) {
        g = d, d *= n / (f = a);
        a = n % a, n = f;
        c = (c & 6) | (c & 2) >> 1;
        f = c > 1 && c < 6;
        c = (c & 5) | (f || e > d ? (c & 4) >> 1 : ~c & 2);
        d = f ? d + e : e > d ? e - d : d - e;
    }
    return n ? c & 4 ? b - e : e : 0;
}

#include <assert.h>

int main(void) {
    unsigned n, mod, res;

    n = 52, mod = 107;
    res = mod_inv(n, mod);
    assert(res == 35); //  35 is a solution of the linear congruence.

    n = 66, mod = 123;
    res = mod_inv(n, mod);
    assert(res == 0); // 66 does note have an inverse modulo 123.

}

/*
	n =     7 and mod = 45    then res = 13    so 1 == (   13 * 7    ) % 45   
	n =    52 and mod = 107   then res = 35    so 1 == (   35 * 52   ) % 107  
	n =   213 and mod = 155   then res = 147   so 1 == (  147 * 213  ) % 155  
	n =   392 and mod = 45    then res = 38    so 1 == (   38 * 392  ) % 45   
	n =   687 and mod = 662   then res = 53    so 1 == (   53 * 687  ) % 662  
	n =   451 and mod = 799   then res = 512   so 1 == (  512 * 451  ) % 799  
	n =  1630 and mod = 259   then res = 167   so 1 == (  167 * 1630 ) % 259  
	n =  4277 and mod = 4722  then res = 191   so 1 == (  191 * 4277 ) % 4722
	
	n = 4135054603 and mod = 3212775958 then res = 1220502011 so 1 == (1220502011 * 4135054603) % 3212775958
*/
