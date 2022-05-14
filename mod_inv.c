// return a modular multiplicative inverse of n with respect to the modulus.
// return 0 if the linear congruence has no solutions.
unsigned mod_inv(unsigned ra, unsigned rb) {
    unsigned rc, sa = 1, sb = 0, sc, i = 0;
    if (rb > 1) do {
            rc = ra % rb;
            sc = sa - (ra / rb) * sb;
            sa = sb, sb = sc;
            ra = rb, rb = rc;
        } while (++i, rc);
    sa *= (i *= ra == 1) != 0;
    sa += (i & 1) * sb;
    return sa;
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
