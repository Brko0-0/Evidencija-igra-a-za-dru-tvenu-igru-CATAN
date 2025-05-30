#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evidencija.h"

 Igrac* igraci = NULL;
 int brojIgraca = 0;
 int kapacitet = 0;

void inicijalizirajIgrace() {
    kapacitet = 10;
    igraci = (Igrac*)calloc(kapacitet, sizeof(Igrac));
    if (!igraci) {
        perror("Greska pri alokaciji memorije");
        exit(EXIT_FAILURE);
    }
}

void dodajIgraca() {
    if (brojIgraca >= kapacitet) {
        kapacitet *= 2;
        igraci = (Igrac*)realloc(igraci, kapacitet * sizeof(Igrac));
        if (!igraci) {
            perror("Realloc nije uspio");
            exit(EXIT_FAILURE);
        }
    }

    Igrac novi;
    printf("Unesite ime igraca: ");
    fgets(novi.ime, MAX_IME, stdin);
    novi.ime[strcspn(novi.ime, "\n")] = '\0';
    while (1) {
        printf("Unesite broj pobjeda: ");
        if (scanf("%d", &novi.pobjede) == 1) break;

        printf("Neispravan unos! Molimo unesite cijeli broj.\n");

        // Očisti ulazni bafer
        while (getchar() != '\n');
    }
    while (1) {
        printf("Unesite broj poraza: ");
        if (scanf("%d", &novi.porazi) == 1) break;

        printf("Neispravan unos! Molimo unesite cijeli broj.\n");

        // Očisti ulazni bafer
        while (getchar() != '\n');
    }
    getchar();
    novi.omjer = (novi.pobjede + novi.porazi) > 0 ? (float)novi.pobjede / (novi.pobjede + novi.porazi) : 0.0f;

    igraci[brojIgraca++] = novi;
}

void prikaziIgrace() {
    for (int i = 0; i < brojIgraca; i++) {
        printf("%d. %s | Pobjede: %d | Porazi: %d | Omjer: %.2f\n", i + 1, igraci[i].ime, igraci[i].pobjede, igraci[i].porazi, igraci[i].omjer);
    }
}

void azurirajIgraca() {
    int index;
    prikaziIgrace();
    printf("Odaberite igraca za azuriranje (1-%d): ", brojIgraca);
    scanf("%d", &index);
    getchar();
    index--;

    if (index < 0 || index >= brojIgraca) {
        printf("Neispravan odabir.\n");
        return;
    }

    printf("Novo ime: ");
    fgets(igraci[index].ime, MAX_IME, stdin);
    igraci[index].ime[strcspn(igraci[index].ime, "\n")] = '\0';
    printf("Novi broj pobjeda: ");
    scanf("%d", &igraci[index].pobjede);
    printf("Novi broj poraza: ");
    scanf("%d", &igraci[index].porazi);
    getchar();
    igraci[index].omjer = igraci[index].pobjede + igraci[index].porazi > 0 ? (float)igraci[index].pobjede / (igraci[index].pobjede + igraci[index].porazi) : 0.0f;
}

void obrisiIgraca() {
    int index;
    prikaziIgrace();
    printf("Odaberite igraca za brisanje (1-%d): ", brojIgraca);
    scanf("%d", &index);
    getchar();
    index--;

    if (index < 0 || index >= brojIgraca) {
        printf("Neispravan odabir.\n");
        return;
    }

    for (int i = index; i < brojIgraca - 1; i++) {
        igraci[i] = igraci[i + 1];
    }
    brojIgraca--;
}

void oslobodiMemoriju() {
    free(igraci);
    igraci = NULL;
    brojIgraca = 0;
    kapacitet = 0;
}

void prikaziIzbornik() {
    printf("\n=== Evidencija igraca CATAN ===\n");
    printf("1. Dodaj igraca\n");
    printf("2. Prikazi igrace\n");
    printf("3. Azuriraj igraca\n");
    printf("4. Obrisi igraca\n");
    printf("5. Spremi u datoteku\n");
    printf("6. Ucitaj iz datoteke\n");
    printf("7. Izlaz\n");
    printf("Odabir: ");
}