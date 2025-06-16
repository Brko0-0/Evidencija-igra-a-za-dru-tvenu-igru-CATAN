#define _CRT_SECURE_NO_WARNINGS
#include "datoteka.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "evidencija.h"

void spremiUDatoteku(const char* trenutnaDatoteka) {
    FILE* f = fopen(trenutnaDatoteka, "wb");
    if (!f) { perror("Greska pri otvaranju datoteke za upis"); return; }
    if (fwrite(igraci, sizeof(Igrac), brojIgraca, f) != (size_t)brojIgraca)
        perror("Greska pri pisanju");
    fclose(f);
}

void ucitajIzDatoteku(const char* trenutnaDatoteka) {
    FILE* f = fopen(trenutnaDatoteka, "rb");
    if (!f) { perror("Greska pri otvaranju datoteke za citanje"); return; }
    if (fseek(f, 0, SEEK_END) != 0) { perror("fseek"); fclose(f); return; }
    long size = ftell(f);
    if (size == -1L) { perror("ftell"); fclose(f); return; }
    rewind(f);

    int count = size / sizeof(Igrac);
    Igrac* temp = realloc(igraci, count * sizeof(Igrac));
    if (!temp) { perror("Alokacija"); fclose(f); return; }
    igraci = temp; brojIgraca = count;

    if (fread(igraci, sizeof(Igrac), brojIgraca, f) != (size_t)brojIgraca && ferror(f))
        perror("Greska pri citanju");
    fclose(f);
}

StatusKod kopirajDatoteku(const char* izvor, const char* odrediste) {
    FILE* src = fopen(izvor, "rb"); if (!src) return GRESKA_DATOTEKA;
    FILE* dst = fopen(odrediste, "wb"); if (!dst) { fclose(src); return GRESKA_DATOTEKA; }
    char buffer[1024]; size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof buffer, src)) > 0) {
        if (fwrite(buffer, 1, bytes, dst) != bytes) { fclose(src); fclose(dst); return GRESKA_DATOTEKA; }
    }
    if (ferror(src)) { fclose(src); fclose(dst); return GRESKA_DATOTEKA; }
    if (feof(src)) printf("Kraj datoteke uspjesno dostignut.\n");
    fclose(src); fclose(dst);
    return USPJEH;
}

void testDatoteke(const char* trenutnaDatoteka) {
    FILE* f = fopen(trenutnaDatoteka, "rb"); if (!f) { perror("Greska otvaranje za test"); return; }
    while (fgetc(f) != EOF);
    if (feof(f)) printf("Test: kraj datoteke uspjesno dostignut.\n");
    if (ferror(f)) perror("Greska tokom testiranja");
    fclose(f);
}

void obrisiDatoteku(const char* trenutnaDatoteka) {
    if (remove(trenutnaDatoteka) == 0) printf("Datoteka izbrisana.\n");
    else perror("Greska pri brisanju");
}

void preimenujDatoteku() {
    char novi_trenutnaDatoteka[MAX_PATH];
    printf("Unesite novi naziv datoteke (npr. nova_datoteka.bin): ");
    CLEAR_INPUT();
    if (!fgets(novi_trenutnaDatoteka, sizeof(novi_trenutnaDatoteka), stdin)) return;
    novi_trenutnaDatoteka[strcspn(novi_trenutnaDatoteka, "\r\n")] = '\0';
    if (strlen(novi_trenutnaDatoteka) == 0) {
        printf("Neispravan naziv datoteke.\n");
        return;
    }

    if (rename(trenutnaDatoteka, novi_trenutnaDatoteka) == 0) {
        printf("Datoteka je preimenovana iz '%s' u '%s'.\n",
            trenutnaDatoteka, novi_trenutnaDatoteka);
        
        strncpy(trenutnaDatoteka, novi_trenutnaDatoteka, MAX_PATH);
        sacuvajtrenutnaDatotekaDatoteke();
    }
    else {
        perror("Greska pri preimenovanju datoteke");
    }
}

void velicinaDatoteke(const char* trenutnaDatoteka) {
    FILE* f = fopen(trenutnaDatoteka, "rb"); if (!f) { perror("Greska otvaranje"); return; }
    fseek(f, 0, SEEK_END); long sz = ftell(f);
    printf("Velicina: %ld bajta\n", sz); fclose(f);
}