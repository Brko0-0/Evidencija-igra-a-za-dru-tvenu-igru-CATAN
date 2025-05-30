#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evidencija.h"
#include "pretraga.h"

int usporediIme(const void* a, const void* b) {
    return strcmp(((Igrac*)a)->ime, ((Igrac*)b)->ime);
}

void pretraziPoImenu() {
    qsort(igraci, brojIgraca, sizeof(Igrac), usporediIme);

    char trazeno[MAX_IME];
    printf("Unesite ime za pretragu: ");
    fgets(trazeno, MAX_IME, stdin);
    trazeno[strcspn(trazeno, "\n")] = '\0';

    Igrac kljuc;
    strcpy(kljuc.ime, trazeno);
    Igrac* rezultat = (Igrac*)bsearch(&kljuc, igraci, brojIgraca, sizeof(Igrac), usporediIme);

    if (rezultat) {
        printf("Pronaden: %s | Pobjede: %d | Porazi: %d | Omjer: %.2f\n", rezultat->ime, rezultat->pobjede, rezultat->porazi, rezultat->omjer);
    }
    else {
        printf("Igrac nije pronaden.\n");
    }
}