#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evidencija.h"
#include "pretraga.h"

int usporediIme(const void* a, const void* b) {
    const Igrac* igracA = (const Igrac*)a;
    const Igrac* igracB = (const Igrac*)b;
    return strcmp(igracA->ime, igracB->ime);
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
        printf("Pronaden: %s | Pobjede: %d | Porazi: %d | Omjer: %.2f\n",
            rezultat->ime, rezultat->pobjede, rezultat->porazi, rezultat->omjer);
    }
    else {
        printf("%s\n", dohvatiStatusPoruku(NE_POSTOJI));
    }
}

void pretraziUFile(const char* naziv) {
    FILE* fp = fopen(naziv, "rb");
    if (!fp) {
        perror(dohvatiStatusPoruku(GRESKA_DATOTEKE));
        return;
    }

    int broj;
    if (fread(&broj, sizeof(int), 1, fp) != 1) {
        printf("%s\n", dohvatiStatusPoruku(GRESKA_DATOTEKE));
        fclose(fp);
        return;
    }

    Igrac temp;
    char trazeno[MAX_IME];
    printf("Unesite ime za pretragu u datoteci: ");
    fgets(trazeno, MAX_IME, stdin);
    trazeno[strcspn(trazeno, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < broj; i++) {
        if (fread(&temp, sizeof(Igrac), 1, fp) != 1) {
            printf("%s\n", dohvatiStatusPoruku(GRESKA_DATOTEKE));
            break;
        }
        if (strcmp(temp.ime, trazeno) == 0) {
            printf("Pronaden u datoteci: %s | Pobjede: %d | Porazi: %d | Omjer: %.2f\n",
                temp.ime, temp.pobjede, temp.porazi, temp.omjer);
            found = 1;
            break;
        }
    }
    if (!found) printf("%s\n", dohvatiStatusPoruku(NE_POSTOJI));
    fclose(fp);
}