#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include <stdio.h>

void prikaziGlavniMeni() {
    int izbor;
    do {
        printf("\n===================================\n");
        printf("         >>> Glavni Meni Igraca <<<        \n");
        printf("===================================\n");
        printf("1. Meni igraca\n");
        printf("0. Izlaz iz programa\n");
        printf("-----------------------------------\n");
        printf("Unesite izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            prikaziMeniIgraca();
            break;
        case 0:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Pogresan unos.\n");
        }
    } while (izbor != 0);
}