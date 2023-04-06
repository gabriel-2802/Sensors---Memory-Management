//copyright Carauleanu Valentin Gabriel 311CAb
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "aux_functions.h"
#include "operations.h"

/*functia citeste din fisierul dat ca prim argument in linia
de comanda senzorii*/
sensor_t *read_sensors(char const *argv[], int *n);

/*functia sorteaza vectorul de senzori astfel incat senzorii PMU
sa fie la inceputul vectorului*/
void sort_sensors(sensor_t **sensors, int n);

/*functia citeste de la tastatura un index si printeaza datele
senzorului*/
void print_sensors(sensor_t *sensors, int n);

/*functia citeste de la tastatura un index si aplica operatiile din
vectorul operations asupra senzorului cerut*/
void analyze(sensor_t *sensors, int n, op_fct *operations);

//functia indeparteaza senzorii invalizi din vector
void clear(sensor_t **sensors, int *n);

//functia elibereaza memoria utlizata de vectorul primit
void free_sensors(sensor_t *sensors, int n);

