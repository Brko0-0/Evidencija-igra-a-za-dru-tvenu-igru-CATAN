#ifndef EVIDENCIJA_H
#define EVIDENCIJA_H

#define MAX_IME 50

typedef struct {
    char ime[MAX_IME];
    int pobjede;
    int porazi;
    float omjer;
} Igrac;

typedef enum {
    DODAJ = 1, PRIKAZI, AZURIRAJ, BRISI, SPREMI, UCITAJ, SORTIRAJ, PRETRAZI, PRETRAZI_DAT, KOPIRAJ, TEST, IZLAZ
} Izbornik;

typedef enum {
    USPJEH = 0,
    GRESKA_ALOKACIJE,
    GRESKA_DATOTEKE,
    NE_POSTOJI,
    POGRESAN_UNOS
} StatusKod;

void inicijalizirajIgrace();
void dodajIgraca();
void prikaziIgrace();
void azurirajIgraca();
void obrisiIgraca();
void oslobodiMemoriju();
void prikaziIzbornik();
const char* dohvatiStatusPoruku(StatusKod kod);

extern Igrac* igraci;
extern int brojIgraca;
extern int kapacitet;

#endif