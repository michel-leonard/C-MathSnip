// return the number that was multiplied by itself to reach N.
unsigned square_root_1(const unsigned num) {
    unsigned a = 0, b = num, c, d;
    for (c = 1 << 30 ; c; c >>= 2) {
        d = a + c;
        a >>= 1;
        if (b >= d)
            b -= d, a += c;
    }
    // la variable b contient le reste.
    return a;
}


// return the number that was multiplied by itself to reach N.
unsigned square_root_2(unsigned n){
    unsigned a = n > 0, b;
    if (n > 3) for (a = n >> 1, b = (a + n / a) >> 1; b < a; a = b, b = (a + n / a) >> 1);
    return a ;
}
