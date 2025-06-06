#ifndef DATOTEKA_H
#define DATOTEKA_H

void spremiUDatoteku(const char* naziv);
void ucitajIzDatoteke(const char* naziv);
StatusKod kopirajDatoteku(const char* izvor, const char* odrediste);
void testDatoteke(const char* naziv);

#endif