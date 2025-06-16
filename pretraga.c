#define _CRT_SECURE_NO_WARNINGS
#include "pretraga.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void pretraziPoImenu() {
    char ime[MAX_IME];
    printf("Ime za pretragu: ");
    fgets(ime, MAX_IME, stdin);
    ime[strcspn(ime, "\n")] = 0;
    for (int i = 0; i < brojIgraca; i++)
        if (strcmp(igraci[i].ime, ime) == 0)
            printf("Igrac pronadjen: %s - %.2f\n", igraci[i].ime, igraci[i].omjer);
}

void pretraziUFile(const char* naziv) {
    FILE* f = fopen(naziv, "rb");
    if (!f) return;
    int br; fread(&br, sizeof(int), 1, f);
    Igrac tmp;
    char ime[MAX_IME];
    printf("Ime za pretragu: "); fgets(ime, MAX_IME, stdin);
    ime[strcspn(ime, "\n")] = 0;
    for (int i = 0; i < br; i++) {
        fread(&tmp, sizeof(Igrac), 1, f);
        if (strcmp(tmp.ime, ime) == 0) {
            printf("Pronadjeno: %s - %.2f\n", tmp.ime, tmp.omjer);
            break;
        }
    }
    fclose(f);
}