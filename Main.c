#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "evidencija.h"
#include "datoteka.h"
#include "sortiranje.h"
#include "pretraga.h"
#include "dodatno.h"

int main() {
    int izbor;
    inicijalizirajIgrace();
    ucitajNazivDatoteke();

    do {
        prikaziIzbornik();
        if (scanf("%d", &izbor) != 1) {
            ispisiPoruku("Pogresan unos!");
            CLEAR_INPUT();
            continue;
        }
        switch (izbor) {
        case DODAJ: dodajIgraca(); break;
        case PRIKAZI: prikaziIgrace(); break;
        case AZURIRAJ: azurirajIgraca(); break;
        case OBRISI: obrisiIgraca(); break;
        case SPREMI_DAT: spremiUDatoteku("igraci.bin"); break;
        case UCITAJ_DAT: ucitajIzDatoteku("igraci.bin"); break;
        case SORTIRAJ: sortirajPoOmjeru(); break;
        case PRETRAZI: pretraziOpcije(); break;
        case KOPIRAJ_DAT: {
            StatusKod kod = kopirajDatoteku("igraci.bin", "igraci_kopija.bin");
            if (kod != USPJEH)
                ispisiPoruku(dohvatiStatusPoruku(kod));
            else
                ispisiPoruku("Datoteka uspjesno kopirana.");
        } break;
        case TEST: testDatoteke("igraci.bin"); break;
        case OBRISI_DAT: obrisiDatoteku("igraci.bin"); break;
        case PREIMENUJ_DAT: preimenujDatoteku("igraci.bin", "igraci_novo.bin"); break;
        case VELICINA_DAT: velicinaDatoteke("igraci.bin"); break;
        case IZLAZ: ispisiPoruku("Izlaz iz programa."); break;
        default: ispisiPoruku("Nepostojeca opcija!"); break;
        }
    } while (izbor != IZLAZ);

    oslobodiMemoriju();
    return 0;
}