#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "evidencija.h"
#include "sortiranje.h"

int usporediOmjer(const void* a, const void* b) {
    const Igrac* igracA = (const Igrac*)a;
    const Igrac* igracB = (const Igrac*)b;
    float o1 = igracA->omjer;
    float o2 = igracB->omjer;
    return (o1 < o2) - (o1 > o2);
}

void sortirajPoOmjeru() {
    qsort(igraci, brojIgraca, sizeof(Igrac), usporediOmjer);
    printf("Igraci sortirani po omjeru.\n");
}