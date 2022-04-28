// return a modular multiplicative inverse of n with respect to the modulus.
// return 0 if the linear congruence has no solutions.
unsigned mod_inv(unsigned n, const unsigned mod) {
    unsigned b = mod, c = b, d = 0, e = 0, f = 1, g, h;
    for (n *= b > 1; n > 1 && (n *= b > 0); f = h, d = (d & 3) | (d & 1) << 2) {
        h = e, e *= n / (g = b);
        b = n % b, n = g;
        d = (d & 6) | (d & 2) >> 1;
        g = d > 1 && d < 6 ;
        d = (d & 5) | (g || f > e ? (d & 4) >> 1 : ~d & 2);
        e = g ? e + f : f > e ? f - e : e - f;
    }
    return n ? d & 4 ? c - f : f : 0;
}

#include <assert.h>
int main(void){
    unsigned n, mod, res ;

    n = 57, mod = 107 ;
    res = mod_inv(n, mod); assert(res == 92); //  92 is a solution of the linear congruence.

    n = 66, mod = 123 ;
    res = mod_inv(n, mod); assert(res == 0); // 66 does note have an inverse modulo 123.
}

/*
    n =        3 and mod = 13       then res = 9        so 1 ==        9 % 13
    n =       14 and mod = 11       then res = 4        so 1 ==        4 % 11
    n =       29 and mod = 54       then res = 41       so 1 ==       41 % 54
    n =       57 and mod = 107      then res = 92       so 1 ==       92 % 107
    n =      222 and mod = 41       then res = 29       so 1 ==       29 % 41
    n =      502 and mod = 57       then res = 31       so 1 ==       31 % 57
    n =       77 and mod = 254      then res = 33       so 1 ==       33 % 254
    n =     1283 and mod = 787      then res = 668      so 1 ==      668 % 787
    n =     2794 and mod = 1503     then res = 475      so 1 ==      475 % 1503

    n = 3834279218 and mod = 4026303609 then res = 2564349128 so 1 == 2564349128 % 4026303609
*/
