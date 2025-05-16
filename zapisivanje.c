#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int Zapisivanje() {
	char ime[20] = { '\0' };
	char prezime[30] = { '\0' };
	int status = 0;
	int broj = 0;
	int n = 0;
	FILE* fp = NULL;
	fp = fopen("C:\\Users\\student\\source\\repos\\Project65\\studenti.txt", "w");
	if (fp == NULL) {
		printf("Datoteka se ne moze otvoriti.\n");
	}
	else {
		broj = citanjeZapisa();
		for (int i = 0; i < broj; i++)
		{
			printf("Unesite ime za %d. studenta\n", i + 1);
			scanf("%19s", ime);
			printf("Unesite prezime za %d. studenta\n", i + 1);
			scanf("%29s", prezime);
			status = fprintf(fp, "Student br: %d\t Ime:%s\t Prezime:\t %s\n", i + 1, ime, prezime);
			printf("Status je %d.\n", status);
		} fclose(fp);
	} return 0;
}