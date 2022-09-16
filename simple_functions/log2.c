static double native_log_computation(const double n) {
    // Basic logarithm computation.
    static const double euler = 2.7182818284590452354 ;
    unsigned a = 0, d;
    double b, c, e, f;
    if (n > 0) {
        for (c = n < 1 ? 1 / n : n; (c /= euler) > 1; ++a);
        c = 1 / (c * euler - 1), c = c + c + 1, f = c * c, b = 0;
        for (d = 1, c /= 2; e = b, b += 1 / (d * c), b - e /* > 0.0000001 */ ;)
            d += 2, c *= f;
    } else b = (n == 0) / 0.;
    return n < 1 ? -(a + b) : a + b;
}

static inline double native_ln(const double n) {
    //  Returns the natural logarithm (base e) of N.
    return native_log_computation(n) ;
}

static inline double native_log_base(const double n, const double base) {
    //  Returns the logarithm (base b) of N. Right hand side can be precomputed.
    return native_log_computation(n) / native_log_computation(base) ;
}
