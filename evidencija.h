#ifndef EVIDENCIJA_H
#define EVIDENCIJA_H

#include <stdio.h>

#define MAX_IME 50

typedef struct {
    char ime[MAX_IME];
    int pobjede;
    int porazi;
    float omjer;
} Igrac;

typedef enum {
    DODAJ = 1, PRIKAZI, AZURIRAJ, BRISI, SPREMI, UCITAJ, IZLAZ
} Izbornik;

void inicijalizirajIgrace();
void dodajIgraca();
void prikaziIgrace();
void azurirajIgraca();
void obrisiIgraca();
void oslobodiMemoriju();
void prikaziIzbornik();

#endif
