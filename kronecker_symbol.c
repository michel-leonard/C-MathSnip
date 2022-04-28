//  This function returns the Kronecker symbol of A and B.
int kronecker(unsigned a, unsigned b) {
    static const int s[8] = {0, 1, 0, -1, 0, -1, 0, 1};
    unsigned c;
    int res = (int) (a | b);
    if (a && b)
        if (res & 1) {
            for (c = 0; !(b & 1); ++c, b >>= 1);
            // When b is odd Jacobi and Kronecker symbols are identical, in factorization algorithms b is often the prime.
            // When b is an odd prime, Jacobi symbol is equal to the Legendre symbol. 
            for (res = c & 1 ? s[a & 7] : 1; a; c & 1 ? res *= s[b & 7] : 0, a & b & 2 ? res = -res : 0, c = b % a, b = a, a = c)
                for (c = 0; !(a & 1); ++c, a >>= 1);
            res = b == 1 ? res : 0;
        } else res = 0;
    else res = res == 1;
    return res;
}


#include <assert.h>
int main() {
    assert(kronecker(0, 0) == 0);
    assert(kronecker(2, 0) == 0);
    assert(kronecker(3, 0) == 0);
    assert(kronecker(0, 1) == 1);
    assert(kronecker(1, 1) == 1);
    assert(kronecker(2, 1) == 1);
    assert(kronecker(2, 3) == -1);
    assert(kronecker(3, 5) == -1);
    assert(kronecker(5, 2) == -1);

    assert(kronecker(900, 900) == 0);
    assert(kronecker(902, 902) == 0);
    assert(kronecker(903, 903) == 0);
    assert(kronecker(901, 902) == 1);
    assert(kronecker(902, 907) == 1);
    assert(kronecker(903, 908) == 1);
    assert(kronecker(901, 903) == -1);
    assert(kronecker(902, 903) == -1);
    assert(kronecker(903, 907) == -1);
}
