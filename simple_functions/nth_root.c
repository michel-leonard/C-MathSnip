// return a number that, when multiplied by itself nth times, makes N.
unsigned nth_root(const unsigned n, const unsigned nth) {
    unsigned a = n, b, c, r = nth ? n + (n > 1) : n == 1 ;
    for (; a < r; b = a + (nth - 1) * r, a = b / nth)
        for (r = a, a = n, c = nth - 1; c && (a /= r); --c);
    return r;
}

unsigned initial_guess_nth_root(unsigned n, unsigned nth){
    unsigned res = 1;
    for(; n >>= 1; ++res);
    return nth ? 1 << (res + nth - 1) / nth : 0 ;
}

// return a number that, when multiplied by itself nth times, makes N.
unsigned nth_root_2(const unsigned n, const unsigned nth) {
    unsigned a = initial_guess_nth_root(n , nth), b, c, r = nth ? a + (n > 0) : n == 1 ;
    for (; a < r; b = a + (nth - 1) * r, a = b / nth)
        for (r = a, a = n, c = nth - 1; c && (a /= r); --c);
    return r;
}
