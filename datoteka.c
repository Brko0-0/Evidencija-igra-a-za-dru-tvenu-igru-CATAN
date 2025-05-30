#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evidencija.h"
#include "datoteka.h"

extern Igrac* igraci;
extern int brojIgraca;
extern int kapacitet;

void spremiUDatoteku(const char* naziv) {
    FILE* fp = fopen("C:\\Users\\Administrator\\source\\repos\\Project2\\igraci.txt", "wb");
    if (!fp) {
        perror("Greska pri otvaranju datoteke za pisanje");
        return;
    }

    fwrite(&brojIgraca, sizeof(int), 1, fp);
    fwrite(igraci, sizeof(Igrac), brojIgraca, fp);

    fclose(fp);
}

void ucitajIzDatoteke(const char* naziv) {
    FILE* fp = fopen("C:\\Users\\Administrator\\source\\repos\\Project2\\igraci.txt", "rb");
    if (!fp) {
        perror("Greska pri otvaranju datoteke za citanje");
        return;
    }

    fread(&brojIgraca, sizeof(int), 1, fp);
    kapacitet = brojIgraca > 10 ? brojIgraca : 10;
    igraci = (Igrac*)realloc(igraci, kapacitet * sizeof(Igrac));

    fread(igraci, sizeof(Igrac), brojIgraca, fp);
    fclose(fp);
}