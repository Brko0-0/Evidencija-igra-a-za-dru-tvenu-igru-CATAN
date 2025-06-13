#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "evidencija.h"
#include "datoteka.h"
#include "sortiranje.h"
#include "pretraga.h"

int main() {
    int izbor;
    inicijalizirajIgrace();

    do {
        prikaziIzbornik();
        scanf("%d", &izbor);
        getchar();

        switch ((Izbornik)izbor) {
        case DODAJ:
            dodajIgraca();
            break;
        case PRIKAZI:
            prikaziIgrace();
            break;
        case AZURIRAJ:
            azurirajIgraca();
            break;
        case BRISI:
            obrisiIgraca();
            break;
        case SPREMI:
            spremiUDatoteku("igraci.bin");
            break;
        case UCITAJ:
            ucitajIzDatoteke("igraci.bin");
            break;
        case SORTIRAJ:
            sortirajPoOmjeru();
            break;
        case PRETRAZI:
            pretraziPoImenu();
            break;
        case PRETRAZI_DAT:
            pretraziUFile("igraci.bin");
            break;
        case KOPIRAJ: {
            StatusKod status = kopirajDatoteku("igraci.bin", "igraci_kopija.bin");
            if (status == USPJEH) {
                printf("Datoteka uspje�no kopirana.\n");
            }
            else {
                printf("Gre�ka pri kopiranju: %s\n", dohvatiStatusPoruku(status));
            }
            break;
        }
        case TEST:
            testDatoteke("igraci.bin");
            break;
        case IZLAZ:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Opcija ne postoji!\n");
            break;
        }
    } while (izbor != IZLAZ);

    oslobodiMemoriju();
    return 0;
}