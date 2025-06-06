#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "evidencija.h"
#include "datoteka.h"

StatusKod kopirajDatoteku(const char* izvor, const char* odrediste) {
    FILE* izvorFile = fopen(izvor, "rb");
    if (!izvorFile) {
        return GRESKA_DATOTEKE;
    }

    FILE* odredisteFile = fopen(odrediste, "wb");
    if (!odredisteFile) {
        fclose(izvorFile);
        return GRESKA_DATOTEKE;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), izvorFile)) > 0) {
        if (fwrite(buffer, 1, bytesRead, odredisteFile) != bytesRead) {
            fclose(izvorFile);
            fclose(odredisteFile);
            return GRESKA_DATOTEKE;
        }
    }

    if (ferror(izvorFile)) {
        fclose(izvorFile);
        fclose(odredisteFile);
        return GRESKA_DATOTEKE;
    }

    fclose(izvorFile);
    fclose(odredisteFile);
    return USPJEH;
}

void spremiUDatoteku(const char* naziv) {
    FILE* fp = fopen(naziv, "wb");
    if (!fp) {
        printf("%s: %s\n", dohvatiStatusPoruku(GRESKA_DATOTEKE), strerror(errno));
        return;
    }

    if (fwrite(&brojIgraca, sizeof(int), 1, fp) != 1) {
        printf("%s: %s\n", dohvatiStatusPoruku(GRESKA_DATOTEKE), strerror(errno));
        fclose(fp);
        return;
    }

    if (fwrite(igraci, sizeof(Igrac), brojIgraca, fp) != brojIgraca) {
        printf("%s: %s\n", dohvatiStatusPoruku(GRESKA_DATOTEKE), strerror(errno));
        fclose(fp);
        return;
    }

    if (fclose(fp) == EOF) {
        printf("%s: %s\n", dohvatiStatusPoruku(GRESKA_DATOTEKE), strerror(errno));
        return;
    }

    printf("%s\n", dohvatiStatusPoruku(USPJEH));
}

void ucitajIzDatoteke(const char* naziv) {
    FILE* fp = fopen(naziv, "rb");
    if (!fp) {
        printf("%s: %s\n", dohvatiStatusPoruku(GRESKA_DATOTEKE), strerror(errno));
        return;
    }

    int broj;
    if (fread(&broj, sizeof(int), 1, fp) != 1) {
        printf("%s: %s\n", dohvatiStatusPoruku(GRESKA_DATOTEKE), strerror(errno));
        fclose(fp);
        return;
    }

    kapacitet = broj > 10 ? broj : 10;
    Igrac* temp = (Igrac*)realloc(igraci, kapacitet * sizeof(Igrac));
    if (!temp) {
        printf("%s\n", dohvatiStatusPoruku(GRESKA_ALOKACIJE));
        fclose(fp);
        return;
    }
    igraci = temp;

    if (fread(igraci, sizeof(Igrac), broj, fp) != broj) {
        printf("%s: %s\n", dohvatiStatusPoruku(GRESKA_DATOTEKE), strerror(errno));
        fclose(fp);
        brojIgraca = 0;
        return;
    }

    brojIgraca = broj;

    if (fclose(fp) == EOF) {
        printf("%s: %s\n", dohvatiStatusPoruku(GRESKA_DATOTEKE), strerror(errno));
        return;
    }

    printf("%s\n", dohvatiStatusPoruku(USPJEH));
}

void testDatoteke(const char* naziv) {
    FILE* fp = fopen(naziv, "rb");
    if (fp) {
        printf("Datoteka '%s' postoji.\n", naziv);
        fclose(fp);
    }
    else {
        printf("Datoteka '%s' ne postoji: %s\n", naziv, strerror(errno));
    }
}