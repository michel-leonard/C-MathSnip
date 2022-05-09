#include <stdlib.h>
unsigned random(){
    unsigned n = 0 ;
    for (size_t i = 0; i < sizeof(n); ((char*)&n)[i++] = rand());
    return n ;
}
