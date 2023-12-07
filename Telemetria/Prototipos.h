#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int comprobar_endianidad(void);
int Escribir_fecha(FILE *,FILE *,long int );
int Escribir_volt(FILE *,FILE *, long int );
int cambiar_puntoXcoma();


#endif // PROTOTIPOS_H_INCLUDED
