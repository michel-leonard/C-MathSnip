#include <stdlib.h>
#include <string.h>

static char *base_convert(const char * str, const int base_in, const int base_out) {
    static const char *alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    size_t a, b, c = 1, d;
    char *s = malloc(c + 1);
    strcpy(s, "0");
    for (; *str; ++str) {
        for (a = (char*)memchr(alphabet, *str, base_out) - alphabet, b = c; b;) {
            d = ((char *) memchr(alphabet, s[--b], base_out) - alphabet) * base_in + a;
            s[b] = alphabet[d % base_out];
            a = d / base_out;
        }
        for (; a; s = realloc(s, ++c + 1), memmove(s + 1, s, c), *s = alphabet[a % base_out], a /= base_out);
    }
    return s;
}

#include <assert.h>
int main(void){
    char * str = base_convert("10439845206726871283263044911246204010983490699597806179", 10, 62);
    assert(strcmp(str, "HendrikLenstraFactorization1987") == 0);
    free(str); // memory must be freed after usage.
}
