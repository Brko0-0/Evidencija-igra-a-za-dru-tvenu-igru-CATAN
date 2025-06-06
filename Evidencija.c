#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evidencija.h"

Igrac* igraci = NULL;
int brojIgraca = 0;
int kapacitet = 0;

const char* statusPoruke[] = {
    "Operacija uspješno izvrsena",
    "Greska pri alokaciji memorije",
    "Greska pri radu s datotekom",
    "Trazeni podatak ne postoji",
    "Pogresan unos podataka"
};

const char* dohvatiStatusPoruku(StatusKod kod) {
    return statusPoruke[kod];
}

void inicijalizirajIgrace() {
    kapacitet = 10;
    igraci = (Igrac*)calloc(kapacitet, sizeof(Igrac));
    if (!igraci) {
        perror(dohvatiStatusPoruku(GRESKA_ALOKACIJE));
        exit(EXIT_FAILURE);
    }
}

void dodajIgraca() {
    if (brojIgraca >= kapacitet) {
        kapacitet *= 2;
        Igrac* temp = (Igrac*)realloc(igraci, kapacitet * sizeof(Igrac));
        if (!temp) {
            perror(dohvatiStatusPoruku(GRESKA_ALOKACIJE));
            return;
        }
        igraci = temp;
    }

    Igrac novi;
    printf("Unesite ime igraca: ");
    fgets(novi.ime, MAX_IME, stdin);
    novi.ime[strcspn(novi.ime, "\n")] = '\0';

    printf("Unesite broj pobjeda: ");
    if (scanf("%d", &novi.pobjede) != 1) {
        printf("%s\n", dohvatiStatusPoruku(POGRESAN_UNOS));
        getchar();
        return;
    }
    printf("Unesite broj poraza: ");
    if (scanf("%d", &novi.porazi) != 1) {
        printf("%s\n", dohvatiStatusPoruku(POGRESAN_UNOS));
        getchar();
        return;
    }
    getchar();

    novi.omjer = (novi.pobjede + novi.porazi) > 0 ? (float)novi.pobjede / (novi.pobjede + novi.porazi) : 0.0f;

    igraci[brojIgraca++] = novi;
    printf("%s\n", dohvatiStatusPoruku(USPJEH));
}

void prikaziIgrace() {
    if (brojIgraca == 0) {
        printf("%s\n", dohvatiStatusPoruku(NE_POSTOJI));
        return;
    }

    for (int i = 0; i < brojIgraca; i++) {
        printf("%d. %s | Pobjede: %d | Porazi: %d | Omjer: %.2f\n",
            i + 1, igraci[i].ime, igraci[i].pobjede, igraci[i].porazi, igraci[i].omjer);
    }
}

void azurirajIgraca() {
    if (brojIgraca == 0) {
        printf("%s\n", dohvatiStatusPoruku(NE_POSTOJI));
        return;
    }

    prikaziIgrace();
    printf("Odaberite igraca za azuriranje (1-%d): ", brojIgraca);

    int index;
    if (scanf("%d", &index) != 1) {
        printf("%s\n", dohvatiStatusPoruku(POGRESAN_UNOS));
        getchar();
        return;
    }
    getchar();
    index--;

    if (index < 0 || index >= brojIgraca) {
        printf("%s\n", dohvatiStatusPoruku(POGRESAN_UNOS));
        return;
    }

    printf("Novo ime: ");
    fgets(igraci[index].ime, MAX_IME, stdin);
    igraci[index].ime[strcspn(igraci[index].ime, "\n")] = '\0';

    printf("Novi broj pobjeda: ");
    if (scanf("%d", &igraci[index].pobjede) != 1) {
        printf("%s\n", dohvatiStatusPoruku(POGRESAN_UNOS));
        getchar();
        return;
    }

    printf("Novi broj poraza: ");
    if (scanf("%d", &igraci[index].porazi) != 1) {
        printf("%s\n", dohvatiStatusPoruku(POGRESAN_UNOS));
        getchar();
        return;
    }
    getchar();

    igraci[index].omjer = igraci[index].pobjede + igraci[index].porazi > 0
        ? (float)igraci[index].pobjede / (igraci[index].pobjede + igraci[index].porazi)
        : 0.0f;

    printf("%s\n", dohvatiStatusPoruku(USPJEH));
}

void obrisiIgraca() {
    if (brojIgraca == 0) {
        printf("%s\n", dohvatiStatusPoruku(NE_POSTOJI));
        return;
    }

    prikaziIgrace();
    printf("Odaberite igraca za brisanje (1-%d): ", brojIgraca);

    int index;
    if (scanf("%d", &index) != 1) {
        printf("%s\n", dohvatiStatusPoruku(POGRESAN_UNOS));
        getchar();
        return;
    }
    getchar();
    index--;

    if (index < 0 || index >= brojIgraca) {
        printf("%s\n", dohvatiStatusPoruku(POGRESAN_UNOS));
        return;
    }

    for (int i = index; i < brojIgraca - 1; i++) {
        igraci[i] = igraci[i + 1];
    }
    brojIgraca--;

    printf("%s\n", dohvatiStatusPoruku(USPJEH));
}

void oslobodiMemoriju() {
    if (igraci != NULL) {
        free(igraci);
        igraci = NULL;
    }
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
    printf("7. Sortiraj po omjeru\n");
    printf("8. Pretrazi po imenu\n");
    printf("9. Pretrazi ime u datoteci\n");
    printf("10. Kopiraj datoteku\n");
    printf("11. Test postojanja datoteke\n");
    printf("12. Izlaz\n");
    printf("Odabir: ");
}