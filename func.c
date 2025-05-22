#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ucitajIgraca(Zapis igraci[], int max) {
    FILE* fp = fopen(DATOTEKA, "rb");
    if (!fp) return 0;

    int count = 0;
    while (fread(&igraci[count], sizeof(igraci), 1, fp) == 1 && count < max) {
        count++;
    }

    fclose(fp);
    return count;
}

void dodajIgraca() {
    Zapis igraci[MAX_IGRAC];
    int count = ucitajIgraca(igraci, MAX_IGRAC);

    Zapis novi;
    novi.id = count + 1;
    getchar();

    printf("Unesite naziv: ");
    fgets(novi.nazivIgraca, MAX_NAZIV, stdin);
    novi.nazivIgraca[strcspn(novi.nazivIgraca, "\n")] = '\0';

    printf("Unesite ime igraca: ");
    fgets(novi.imeIgraca, MAX_IME, stdin);
    novi.imeIgraca[strcspn(novi.imeIgraca, "\n")] = '\0';

    printf("Unesite prezime: ");
    fgets(novi.prezimeIgraca, MAX_PREZIME, stdin);
    novi.prezimeIgraca[strcspn(novi.prezimeIgraca, "\n")] = '\0';

    printf("Unesite koliko godina ima igrac: ");
    scanf("%d", &novi.godina);

    printf("Unesite koliko dugo igrac igra: ");
    scanf("%f", &novi.kolikoDanaIgra);

    FILE* fp = fopen(DATOTEKA, "ab");
    if (!fp) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    fwrite(&novi, sizeof(Zapis), 1, fp);
    fclose(fp);

    printf("Igrac uspjesno dodan.\n");
}

void prikazIgraca() {
    Zapis z;
    FILE* fp = fopen(DATOTEKA, "rb");
    if (!fp) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    while (fread(&z, sizeof(Zapis), 1, fp) == 1) {
        printf("\nID: %d | Naziv: %s | Ime: %s | Prezime: %s | Godina: %d | KolikoDugoIgra: %.2f min\n",
            z.id, z.nazivIgraca, z.imeIgraca, z.prezimeIgraca, z.godina, z.kolikoDanaIgra);
    }

    void urediStanjeIgraca() {
        Igrac igraci[MAX_IGRAC];
        int count = ucitajIgrace(igraci, MAX_IGRAC);

        int id;
        printf("Unesite ID igraca za uredjivanje: ");
        scanf("%d", &id);
        getchar();
        
        int found = 0;
        for (int i = 0; i < count; i++) {
            if (igraci[i].id == id) {
                found = 1;
                printf("Uredjivanje igraca ID %d:\n", id);

                printf("Trenutni naziv: %s\nNovi naziv: ", igraci[i].naziv);
                fgets(igraci[i].naziv, MAX_NAZIV, stdin);
                igraci[i].igrac[strcspn(igraci[i].naziv, "\n")] = '\0';

                printf("Trenutno ime igraca: %s\nNovo ime igraca: ", igraci[i].ime);
                fgets(zapisi[i].ime, MAX_IME, stdin);
                igraci[i].ime[strcspn(igraci[i].ime, "\n")] = '\0';

                printf("Trenutno prezime igraca: %s\nNovo prezime igraca: ", igraci[i].prezime);
                fgets(igraci[i].prezime, MAX_PREZIME, stdin);
                igraci[i].prezime[strcspn(igraci[i].prezime, "\n")] = '\0';

                printf("Koliko godina ima igrac: %d\nNova godina: ", igraci[i].godina);
                scanf("%d", &igraci[i].godina);

                printf("Koliko dugo igrac igra: %.2f\nNovi datum: ", igraci[i].kolikoDanaIgra);
                scanf("%f", &igraci[i].kolikoDanaIgra);
                getchar();
                break;
            }
        }

        if (!found) {
            printf("Igrac s ID %d nije pronadjen.\n", id);
            return;
        }

        FILE* fp = fopen(DATOTEKA, "wb");
        for (int i = 0; i < count; i++) {
            fwrite(&igraci[i], sizeof(Igrac), 1, fp);
        }
        fclose(fp);

        printf("Igrac uspjesno azuriran.\n");
    }

    void izbrisiIgraca() {
        Igrac igraci[MAX_IGRAC];
        int count = ucitajIgraca(igrac, MAX_IGRAC);

        int id;
        printf("Unesite ID igraca za brisanje: ");
        scanf("%d", &id);

        int noviIndex = 0;
        for (int i = 0; i < count; i++) {
            if (igrac[i].id != id) {
                igrac[noviIndex++] = igrac[i];
            }
        }

        for (int i = 0; i < noviIndex; i++) {
            igrac[i].id = i + 1;
        }

        FILE* fp = fopen(DATOTEKA, "wb");
        for (int i = 0; i < noviIndex; i++) {
            fwrite(&igrac[i], sizeof(igrac), 1, fp);
        }
        fclose(fp);

        printf("igrac izbrisan i ID-evi azurirani.\n");
    }