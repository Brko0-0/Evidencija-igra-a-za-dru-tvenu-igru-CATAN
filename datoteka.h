#ifndef DATOTEKA_H
#define DATOTEKA_H

#include "evidencija.h"

void spremiUDatoteku(const char* trenutnaDatoteka);
void ucitajIzDatoteku(const char* trenutnaDatoteka);
StatusKod kopirajDatoteku(const char* izvor, const char* odrediste);
void testDatoteke(const char* trenutnaDatoteka);
void obrisiDatoteku(const char* trenutnaDatoteka);
void preimenujDatoteku(const char* s, const char* d);
void velicinaDatoteke(const char* trenutnaDatoteka);

#endif 
