#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "evidencija.h"
#include "sortiranje.h"

int usporediOmjer(const void* a, const void* b) {
    float o1 = ((Igrac*)a)->omjer;
    float o2 = ((Igrac*)b)->omjer;
    return (o1 < o2) - (o1 > o2);
}

void sortirajPoOmjeru() {
    qsort(igraci, brojIgraca, sizeof(Igrac), usporediOmjer);
    printf("Igraci sortirani po omjeru.\n");
}