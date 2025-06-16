#define _CRT_SECURE_NO_WARNINGS
#include "datoteka.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

void spremiUDatoteku(const char* naziv) {
    FILE* f = fopen(naziv, "wb");
    if (!f) return;
    fwrite(&brojIgraca, sizeof(int), 1, f);
    fwrite(igraci, sizeof(Igrac), brojIgraca, f);
    fclose(f);
}

void ucitajIzDatoteke(const char* naziv) {
    FILE* f = fopen(naziv, "rb");
    if (!f) return;
    fread(&brojIgraca, sizeof(int), 1, f);
    igraci = realloc(igraci, brojIgraca * sizeof(Igrac));
    fread(igraci, sizeof(Igrac), brojIgraca, f);
    fclose(f);
}

StatusKod kopirajDatoteku(const char* izvor, const char* odrediste) {
    FILE* f1 = fopen(izvor, "rb");
    FILE* f2 = fopen(odrediste, "wb");
    if (!f1 || !f2) return GRESKA_DATOTEKE;
    char buf[1024]; size_t b;
    while ((b = fread(buf, 1, 1024, f1)) > 0)
        fwrite(buf, 1, b, f2);
    fclose(f1); fclose(f2);
    return USPJEH;
}

void testDatoteke(const char* naziv) {
    FILE* f = fopen(naziv, "rb");
    if (f) { printf("Postoji: %s\n", naziv); fclose(f); }
    else printf("Ne postoji: %s\n", naziv);
}

void obrisiDatoteku(const char* naziv) {
    if (remove(naziv) == 0) printf("Obrisano: %s\n", naziv);
    else printf("Greska: %s\n", strerror(errno));
}

void preimenujDatoteku(const char* s, const char* d) {
    if (rename(s, d) == 0) printf("Preimenovano\n");
    else printf("Greska\n");
}

void velicinaDatoteke(const char* naziv) {
    struct stat s;
    if (stat(naziv, &s) == 0)
        printf("Velicina %s: %ld bajta\n", naziv, s.st_size);
    else
        printf("Neuspjeh\n");
}