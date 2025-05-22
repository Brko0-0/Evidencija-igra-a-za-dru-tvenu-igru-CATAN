#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include <stdio.h>

void prikaziMeniIgraca() {
    int izbor;
    do {
        printf("\n===================================\n");
        printf("      [>>> Meni Igraca <<<]       \n");
        printf("===================================\n");
        printf("1. Dodaj novog igraca\n");
        printf("2. Prikazi sve igrace\n");
        printf("3. Uredi stanje igraca\n");
        printf("4. Izbrisi igraca\n");
        printf("0. Povratak na glavni meni\n");
        printf("-----------------------------------\n");
        printf("\nUnesite izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            dodajIgraca();
            break;
        case 2:
            printf("\n|+==============================+|\n");
            printf("|--> Trenutno stanje igraca:  <--|\n");
            printf("|+==============================+|\n");
            prikaziSveIgrace();
            break;
        case 3:
            urediStanjeIgraca();
            break;
        case 4:
            izbrisiIgraca();
            break;
        case 0:
            break;
        default:
            printf("Pogresan unos.\n");
        }
    } while (izbor != 0);
}