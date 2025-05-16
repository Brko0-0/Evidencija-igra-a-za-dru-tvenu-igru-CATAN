#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int citanjeZapisa() {
	int broj;
	int status = 0;
	FILE* fp = NULL;
	fp = fopen("C:\\Users\\student\\source\\repos\\Project65\\dat.txt", "r");
	if (fp == NULL) {
		printf("Datoteka se ne moze otvoriti.\n");
		exit(EXIT_FAILURE);
	}
	else {
		while ((status = fscanf(fp, "%d", &broj)) != EOF)
		{
			printf("Status je %d.\n", status);
			printf("Upisani broj je %d.\n", broj);
		}

		fclose(fp);
	}
	return broj;
}