// return the largest number that can be used to divide the two numbers.
unsigned gcd(unsigned a, unsigned b){
    if (b) for(;(a %= b) && (b %= a););
    return a | b;
}
