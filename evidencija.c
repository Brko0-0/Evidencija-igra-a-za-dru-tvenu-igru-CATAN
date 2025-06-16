#define _CRT_SECURE_NO_WARNINGS
#include "evidencija.h"

Igrac* igraci = NULL;
int brojIgraca = 0;
int kapacitet = 0;

static const char* statusPoruke[] = {
    "Operacija uspjesno izvrsena",
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
    igraci = calloc(kapacitet, sizeof(Igrac));
    if (!igraci) {
        perror(dohvatiStatusPoruku(GRESKA_ALOKACIJE));
        exit(EXIT_FAILURE);
    }
}

void dodajIgraca() {
    if (brojIgraca >= kapacitet) {
        int noviKap = kapacitet * 2;
        Igrac* tmp = realloc(igraci, noviKap * sizeof(Igrac));
        if (!tmp) {
            perror(dohvatiStatusPoruku(GRESKA_ALOKACIJE));
            return;
        }
        igraci = tmp;
        kapacitet = noviKap;
    }

    Igrac novi;
    printf("Unesite ime igraca: ");
    fgets(novi.ime, MAX_IME, stdin);
    novi.ime[strcspn(novi.ime, "\n")] = '\0';

    while (1) {
        printf("Unesite broj pobjeda: ");
        if (scanf("%d", &novi.pobjede) == 1) {
            while (getchar() != '\n');
            break;
        }
        else {
            printf("Pogrešan unos! Molimo unesite cijeli broj.\n");
            while (getchar() != '\n');
        }
    }

    while (1) {
        printf("Unesite broj poraza: ");
        if (scanf("%d", &novi.porazi) == 1) {
            while (getchar() != '\n');
            break;
        }
        else {
            printf("Pogrešan unos! Molimo unesite cijeli broj.\n");
            while (getchar() != '\n');
        }
    }

    int tot = novi.pobjede + novi.porazi;
    novi.omjer = (tot > 0) ? (float)novi.pobjede / tot : 0.0f;

    igraci[brojIgraca++] = novi;
    printf("%s\n", dohvatiStatusPoruku(USPJEH));
}

void prikaziIgrace() {
    if (brojIgraca == 0) {
        printf("%s\n", dohvatiStatusPoruku(NE_POSTOJI));
        return;
    }
    for (int i = 0; i < brojIgraca; i++) {
        printf("%d. %s | Pobijede:%d | Porazi:%d | Omjer: %.2f\n",
            i + 1, igraci[i].ime,
            igraci[i].pobjede, igraci[i].porazi,
            igraci[i].omjer);
    }
}

void azurirajIgraca() {
    if (brojIgraca == 0) {
        printf("%s\n", dohvatiStatusPoruku(NE_POSTOJI));
        return;
    }
    prikaziIgrace();
    printf("Odaberite broj za azuriranje: ");
    int i;
    if (scanf("%d", &i) != 1) { getchar(); return; }
    getchar();
    i--;
    if (i < 0 || i >= brojIgraca) {
        printf("%s\n", dohvatiStatusPoruku(POGRESAN_UNOS)); return;
    }

    printf("Novo ime: ");
    fgets(igraci[i].ime, MAX_IME, stdin);
    igraci[i].ime[strcspn(igraci[i].ime, "\n")] = '\0';
    printf("Nove pobjede i porazi: ");
    scanf("%d%d", &igraci[i].pobjede, &igraci[i].porazi);
    getchar();
    int tot = igraci[i].pobjede + igraci[i].porazi;
    igraci[i].omjer = (tot > 0) ? (float)igraci[i].pobjede / tot : 0.0f;
    printf("%s\n", dohvatiStatusPoruku(USPJEH));
}

void obrisiIgraca() {
    if (brojIgraca == 0) {
        printf("%s\n", dohvatiStatusPoruku(NE_POSTOJI)); return;
    }
    prikaziIgrace();
    printf("Odaberite broj za brisanje: ");
    int i;
    if (scanf("%d", &i) != 1) { getchar(); return; }
    getchar();
    i--;
    if (i < 0 || i >= brojIgraca) { printf("%s\n", dohvatiStatusPoruku(POGRESAN_UNOS)); return; }
    for (int j = i; j < brojIgraca - 1; j++) igraci[j] = igraci[j + 1];
    brojIgraca--;
    printf("%s\n", dohvatiStatusPoruku(USPJEH));
}

void oslobodiMemoriju() {
    if (igraci) {
        for (int i = 0; i < brojIgraca; i++) memset(igraci[i].ime, 0, MAX_IME);
        free(igraci); igraci = NULL;
    }
    brojIgraca = kapacitet = 0;
}

void prikaziIzbornik() {
    printf("\n=== CATAN Evidencija ===\n"
        "1. Dodaj\n2. Prikazi\n3. Azuriraj\n4. Obrisi\n"
        "5. Spremi datoteku\n6. Ucitaj datoteku\n"
        "7. Sortiraj po omjeru\n8. Pretrazi ime\n9. Pretrazi datoteku\n"
        "10. Kopiraj datoteku\n11. Test datoteke\n12. Obrisi datoteku\n"
        "13. Preimenuj datoteku\n14. Velicina datoteke\n15. Izlaz\n"
        "Odabir: ");
}
