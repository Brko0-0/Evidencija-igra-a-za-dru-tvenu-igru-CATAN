#define _CRT_SECURE_NO_WARNINGS
#include "sortiranje.h"
#include <stdlib.h>
static int cmp(const void* a, const void* b) {
    float oa = ((Igrac*)a)->omjer;
    float ob = ((Igrac*)b)->omjer;
    return (ob > oa) - (ob < oa);
}
void sortirajPoOmjeru() {
    qsort(igraci, brojIgraca, sizeof(Igrac), cmp);
}