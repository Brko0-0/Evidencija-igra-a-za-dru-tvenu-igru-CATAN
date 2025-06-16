#ifndef DATOTEKA_H
#define DATOTEKA_H
#include "evidencija.h"
void spremiUDatoteku(const char* naziv);
void ucitajIzDatoteke(const char* naziv);
StatusKod kopirajDatoteku(const char* izvor, const char* odrediste);
void testDatoteke(const char* naziv);
void obrisiDatoteku(const char* naziv);
void preimenujDatoteku(const char* s, const char* d);
void velicinaDatoteke(const char* naziv);
#endif

