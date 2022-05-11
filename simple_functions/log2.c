//  returns the binary logarithm (base 2) of N, and -1 if the result goes to negative infinity.
static double log_2(const unsigned n) {
    static const double constant = 1.4426950408889634074;
    unsigned a = 0, d;
    double b, c, e = (double) n, f;
    if (e) {
        for (c = e; (c /= constant) > 1; ++a);
        c = 1 / (c * constant - 1), c = c + c + 1, f = c * c, b = 0;
        for (d = 1, c /= 2; e = b, b += 1 / (d * c), b - e > 0.000001;)
            d += 2, c *= f;
    } else b = -1;
    return a + b;
}
