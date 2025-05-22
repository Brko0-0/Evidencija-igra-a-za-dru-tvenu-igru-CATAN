#ifndef FUNCTION_H
#define FUNCTION_H

#define MAX_NAZIV 100
#define MAX_IME 100
#define MAX_PREZIME 50
#define MAX_IGRAC 100
#define DATOTEKA "datoteka.bin"

typedef struct {
    int id;
    char nazivIgraca[MAX_NAZIV];
    char imeIgraca[MAX_IME];
    char prezimeIgraca[MAX_PREZIME];
    int godina;
    float kolikoDanaIgra;
} Zapis;

void prikaziGlavniMeni();
void prikaziMeniIgraca();
void dodajIgraca();
void prikaziIgrace();
void urediStanjeIgraca();
void izbrisiIgraca();
int ucitajIgraca(Igrac Igraci[], int max);

#endif
