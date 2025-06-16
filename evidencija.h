#ifndef EVIDENCIJA_H
#define EVIDENCIJA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME 50
#define CLEAR_INPUT() while (getchar()!='\n')
#define CONFIG_FILE "config.txt"
#define MAX_PATH 256

extern char trenutnaDatoteka[MAX_PATH];

void ucitajtrenutnaDatotekaDatoteke();
void sacuvajtrenutnaDatotekaDatoteke();

// Podaci o igracu
typedef struct {
    char ime[MAX_IME];
    int pobjede;
    int porazi;
    float omjer;
} Igrac;

// Union za azuriranje vrijednosti
typedef union {
    char ime[MAX_IME];
    int i;
    float f;
} Vrijednost;

// Polja za azuriranje
typedef enum {
    POLJE_IME = 1,
    POLJE_POBJEDA,
    POLJE_PORAZ,
    POLJE_OMJER
} Polje;

// Statusni kodovi
typedef enum {
    USPJEH = 0,
    GRESKA_ALOKACIJE,
    GRESKA_DATOTEKA,
    NE_POSTOJI,
    POGRESAN_UNOS
} StatusKod;

// Glavni izbornik
typedef enum {
    DODAJ = 1,
    PRIKAZI,
    AZURIRAJ,
    OBRISI,
    SPREMI_DAT,
    UCITAJ_DAT,
    SORTIRAJ,
    PRETRAZI,
    KOPIRAJ_DAT,
    TEST,
    OBRISI_DAT,
    PREIMENUJ_DAT,
    VELICINA_DAT,
    IZLAZ
} Izbornik;

extern Igrac* igraci;
extern int brojIgraca;
extern int kapacitet;

void inicijalizirajIgrace();
void dodajIgraca();
void prikaziIgrace();
void azurirajIgraca();
void obrisiIgraca();
void oslobodiMemoriju();
void prikaziIzbornik();
const char* dohvatiStatusPoruku(StatusKod kod);

#endif 