#define _CRT_SECURE_NO_WARNINGS
#include "evidencija.h"
#include "dodatno.h"

Igrac* igraci = NULL;
int brojIgraca = 0;
int kapacitet = 0;

void inicijalizirajIgrace() {
    kapacitet = 10;
    brojIgraca = 0;
    igraci = malloc(kapacitet * sizeof(Igrac));
}

void dodajIgraca() {
    if (brojIgraca >= kapacitet) {
        int noviKap = kapacitet * 2;
        Igrac* temp = realloc(igraci, noviKap * sizeof(Igrac));
        if (!temp) { perror("Alokacija memorije pri dodavanju igraca"); return; }
        igraci = temp;
        kapacitet = noviKap;
    }

    Igrac novi;
    printf("Unesite ime: ");
    CLEAR_INPUT();
    if (!fgets(novi.ime, MAX_IME, stdin)) {
        ispisiPoruku("Greska pri unosu imena.");
        return;
    }
    novi.ime[strcspn(novi.ime, "\n")] = '\0';

    printf("Unesite pobjede: ");
    if (scanf("%d", &novi.pobjede) != 1) {
        ispisiPoruku("Pogresan unos pobjeda!");
        CLEAR_INPUT();
        return;                
    }

    printf("Unesite poraze: ");
    if (scanf("%d", &novi.porazi) != 1) {
        ispisiPoruku("Pogresan unos poraza!");
        CLEAR_INPUT();
        return;                
    }

   
    novi.omjer = (novi.porazi == 0)
        ? (float)novi.pobjede
        : (float)novi.pobjede / novi.porazi;

    igraci[brojIgraca++] = novi;
    ispisiPoruku("Igrac uspjesno dodan.");
}

void prikaziIgrace() {
    if (brojIgraca == 0) { ispisiPoruku("Nema igraca za prikaz."); return; }
    for (int i = 0; i < brojIgraca; i++)
        printf("%d) %s - Pobjede:%d, Porazi:%d, Omjer:%.2f\n",
            i + 1, igraci[i].ime, igraci[i].pobjede, igraci[i].porazi, igraci[i].omjer);
}

void azurirajIgraca() {
    if (brojIgraca == 0) { ispisiPoruku("Nema igraca za azuriranje."); return; }
    int idx; prikaziIgrace(); printf("Odaberite igraca po broju: "); scanf("%d", &idx);
    if (idx < 1 || idx > brojIgraca) { ispisiPoruku("Pogresan unos indeksa."); return; }
    idx--;
    printf("Odaberite polje za azuriranje:\n1. Ime\n2. Pobjede\n3. Porazi\n4. Prosijek\nIzbor: ");
    int pol; scanf("%d", &pol); Vrijednost v; Polje p = pol;
    switch (p) {
    case POLJE_IME:
        CLEAR_INPUT(); printf("Unesite novo ime: ");
        fgets(v.ime, MAX_IME, stdin); v.ime[strcspn(v.ime, "\n")] = '\0';
        strcpy(igraci[idx].ime, v.ime); break;
    case POLJE_POBJEDA:
        scanf("%d", &v.i); igraci[idx].pobjede = v.i; break;
    case POLJE_PORAZ:
        scanf("%d", &v.i); igraci[idx].porazi = v.i; break;
    case POLJE_OMJER:
        scanf("%f", &v.f); igraci[idx].omjer = v.f; break;
    default:
        ispisiPoruku("Nepostojeca opcija."); return;
    }
    ispisiPoruku("Igrac azuriran.");
}

void obrisiIgraca() {
    if (brojIgraca == 0) { ispisiPoruku("Nema igraca za brisanje."); return; }
    int idx; prikaziIgrace(); printf("Odaberite igraca za brisanje: "); scanf("%d", &idx);
    if (idx < 1 || idx > brojIgraca) { ispisiPoruku("Pogresan unos indeksa."); return; }
    idx--;
    for (int i = idx; i < brojIgraca - 1; i++)
        igraci[i] = igraci[i + 1];
    brojIgraca--;
    ispisiPoruku("Igrac obrisan.");
}

void oslobodiMemoriju() {
    if (igraci) {
        for (int i = 0; i < brojIgraca; i++)
            memset(igraci[i].ime, 0, MAX_IME);
        free(igraci);
        igraci = NULL; brojIgraca = kapacitet = 0;
    }
}

void prikaziIzbornik() {
    printf("\n=== Glavni Izbornik ===\n"
        "1. Dodaj igraca\n"
        "2. Prikazi igrace\n"
        "3. Azuriraj igraca\n"
        "4. Obrisi igraca\n"
        "5. Spremi u datoteku\n"
        "6. Ucitaj iz datoteke\n"
        "7. Sortiraj igrcae\n"
        "8. Pretrazi igrace\n"
        "9. Kopiraj datoteku\n"
        "10. Test datoteke\n"
        "11. Obrisi datoteku\n"
        "12. Preimenuj datoteku\n"
        "13. Velicina datoteke\n"
        "14. Izlaz\n"
        "Odabir: ");
}

const char* dohvatiStatusPoruku(StatusKod kod) {
    switch (kod) {
    case USPJEH: return "Uspjeh";
    case GRESKA_ALOKACIJE: return "Greska alokacije";
    case GRESKA_DATOTEKA: return "Greska datoteke";
    case NE_POSTOJI: return "Ne postoji";
    case POGRESAN_UNOS: return "Pogresan unos";
    default: return "Nepoznati kod";
    }
}

char trenutnaDatoteka[MAX_PATH] = "igraci.bin";  

void ucitajNazivDatoteke() {
    FILE* f = fopen(CONFIG_FILE, "r");
    if (!f) {
      
        return;
    }
    if (fgets(trenutnaDatoteka, MAX_PATH, f)) {
     
        trenutnaDatoteka[strcspn(trenutnaDatoteka, "\r\n")] = '\0';
    }
    fclose(f);
}

void sacuvajtrenutnaDatotekaDatoteke() {
    FILE* f = fopen(CONFIG_FILE, "w");
    if (!f) {
        perror("Ne mogu otvoriti config za pisanje");
        return;
    }
    fprintf(f, "%s\n", trenutnaDatoteka);
    fclose(f);
}