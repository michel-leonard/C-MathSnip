#include <stdlib.h>

// return a random unsigned number.
unsigned random(){
    unsigned n = 0 ;
    for (size_t i = 0; i < sizeof(n); ((char*)&n)[i++] = rand());
    return n ;
}
