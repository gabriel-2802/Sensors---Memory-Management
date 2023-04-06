//copyright Carauleanu Valentin Gabriel 311CAb
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <errno.h>
#define NMAX 100
#define DIE(assertion, call_description) do {				\
	if (assertion) {										\
		fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);	\
		perror(call_description);							\
		exit(errno);										\
	}														\
} while (0)

typedef sensor sensor_t;

typedef power_management_unit power_management_unit_t;

typedef tire_sensor tire_sensor_t;

//op_fct va fi un pointer pt o functie de tipul: void function(void *data)
typedef void (*op_fct)(void *);

/*functia utilizeaza string ul primit pentru a seta cmd la o
valoare numerica*/
void command(int *cmd, char *string);

//functia citeste de la tastura un string alocat dinamic
char *read_cmd(void);

//functia creaza si citeste un senzor
sensor_t read_sensor_data(size_t data_size, enum sensor_type type, FILE *in);

//functia printeaza datele unui senzor PMU
void print_pmu(power_management_unit_t *data);

//functia printeaza datele unui senzor TIRE
void print_ts(tire_sensor_t *data);

//functia verifica validitatea unui senzor TIRE
int valid_ts(tire_sensor_t *data);

//functia verifica validitatea unui senzor PMU
int valid_pmu(power_management_unit_t *data);

//functia verifica validitatea unui senzor
int valid_sensor(sensor_t sensor);

