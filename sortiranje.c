#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "sortiranje.h"
#include "evidencija.h"

static int cmpDesc(const void* a, const void* b) {
    float oa = ((Igrac*)a)->omjer;
    float ob = ((Igrac*)b)->omjer;
    return (ob > oa) - (ob < oa);
}
static int cmpAsc(const void* a, const void* b) {
    float oa = ((Igrac*)a)->omjer;
    float ob = ((Igrac*)b)->omjer;
    return (oa > ob) - (oa < ob);
}

void sortirajPoOmjeru() {
    int odabir;
    printf("\n=== Sortiranje ===\n1. Silazno\n2. Uzlazno\nOdabir: ");
    if (scanf("%d", &odabir) != 1) { CLEAR_INPUT(); return; }
    if (odabir == 1)
        qsort(igraci, brojIgraca, sizeof(Igrac), cmpDesc);
    else if (odabir == 2)
        qsort(igraci, brojIgraca, sizeof(Igrac), cmpAsc);
    else
        printf("Nepostojeca opcija za sortiranje.\n");
}