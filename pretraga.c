#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pretraga.h"
#include "evidencija.h"
#include "dodatno.h"

static int cmpByName(const void* a, const void* b) {
    return strcmp(((Igrac*)a)->ime, ((Igrac*)b)->ime);
}

int binarySearchRecursive(Igrac* arr, int left, int right, const char* key) {
    if (left > right) return -1;
    int mid = (left + right) / 2;
    int cmp = strcmp(arr[mid].ime, key);
    if (cmp == 0) return mid;
    else if (cmp > 0) return binarySearchRecursive(arr, left, mid - 1, key);
    else return binarySearchRecursive(arr, mid + 1, right, key);
}

void pretraziPoImenu() {
    if (brojIgraca == 0) { ispisiPoruku("Nema igraca u memoriji."); return; }
    char key[MAX_IME];
    printf("\nUnesite ime za pretragu: "); CLEAR_INPUT();
    fgets(key, MAX_IME, stdin); key[strcspn(key, "\n")] = '\0';
    qsort(igraci, brojIgraca, sizeof(Igrac), cmpByName);
    int idx = binarySearchRecursive(igraci, 0, brojIgraca - 1, key);
    if (idx != -1)
        printf("Pronadjen: %s, P:%d, Por:%d, O:%.2f\n",
            igraci[idx].ime, igraci[idx].pobjede, igraci[idx].porazi, igraci[idx].omjer);
    else
        ispisiPoruku("Igrac nije pronaden.");
}

void pretraziUFile(const char* trenutnaDatoteka) {
    FILE* f = fopen(trenutnaDatoteka, "rb"); if (!f) { perror("Greska pri otvaranju"); return; }
    char key[MAX_IME];
    printf("\nUnesite ime za pretragu u datoteci: "); CLEAR_INPUT();
    fgets(key, MAX_IME, stdin); key[strcspn(key, "\n")] = '\0';
    Igrac temp; int found = 0;
    while (fread(&temp, sizeof(Igrac), 1, f) == 1) {
        if (strcmp(temp.ime, key) == 0) {
            printf("Pronadjen u datoteci: %s, P:%d, Por:%d, O:%.2f\n",
                temp.ime, temp.pobjede, temp.porazi, temp.omjer);
            found = 1; break;
        }
        if (ferror(f)) { perror("Greska pri citanju"); break; }
        if (feof(f)) break;
    }
    if (!found) ispisiPoruku("Igrac nije pronaden u datoteci.");
    fclose(f);
}

void pretraziOpcije() {
    int pod;
    printf("\n=== Pretraga ===\n1. U memoriji\n2. U datoteci\nOdabir: ");
    if (scanf("%d", &pod) != 1) { CLEAR_INPUT(); return; }
    if (pod == 1) pretraziPoImenu();
    else if (pod == 2) pretraziUFile("igraci.bin");
    else ispisiPoruku("Nepostojeca opcija.");
}