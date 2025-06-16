#ifndef PRETRAGA_H
#define PRETRAGA_H

#include "evidencija.h"

void pretraziOpcije();
void pretraziPoImenu();
void pretraziUFile(const char* trenutnaDatoteka);
int binarySearchRecursive(Igrac* arr, int left, int right, const char* key);

#endif 