//copyright Carauleanu Valentin Gabriel 311CAb
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "aux_functions.h"
#include "operations.h"

sensor_t *read_sensors(char const *argv[], int *n)
{
	FILE *in = fopen(argv[1], "rb");
	DIE(!in, "failed to open file\n");

	//citim nr de senzori si alocam memoria necesara
	fread(n, 1, sizeof(int), in);
	sensor_t *sensors = malloc(*n * sizeof(sensor_t));
	DIE(!sensors, "malloc failed\n");

	//citim fiecare senzor in functie de tipul acestuia: PMU sau TIRE
	for (int i = 0; i  < *n; ++i) {
		enum sensor_type type;
		fread(&type, 1, sizeof(enum sensor_type), in);

		if (type == TIRE)
			sensors[i] = read_sensor_data(sizeof(tire_sensor_t), type, in);
		else 
			sensors[i] = read_sensor_data(sizeof(power_management_unit_t), type, in);
		
		fread(&sensors[i].nr_operations, 1, sizeof(int), in);
		sensors[i].operations_idxs = malloc(sensors[i].nr_operations * sizeof(int));
		DIE(!sensors[i].operations_idxs, "malloc failed");

		//fiind un fisier binar, citim intregul vector
		fread(sensors[i].operations_idxs, sensors[i].nr_operations, sizeof(int), in);
	}

	fclose(in);
	return sensors;
}

void sort_sensors(sensor_t **sensors, int n)
{
	/*Vom folosi un vector auxiliar pe care il vom completa
	inital cu toti senzorii PMU*/
	sensor_t *sorted  = malloc(n * sizeof(sensor_t));
	DIE(!sorted, "malloc failed\n");
	int index = 0;

	for (int i = 0; i < n; ++i)
		if ((*sensors)[i].sensor_type == PMU)
			sorted[index++] = (*sensors)[i];

	/*mai parcurgem o data vectorul original si completam
	vectorul auxiliar cu senzorii TIRE*/
	for (int i = 0; i < n; ++i)
		if ((*sensors)[i].sensor_type == TIRE)
			sorted[index++] = (*sensors)[i];
	
	free(*sensors);
	*sensors = sorted;
}

void print_sensors(sensor_t *sensors, int n)
{
	int index;
	scanf("%d", &index);

	if (index < 0 || index >= n) {
		printf("Index not in range!\n");
		return;
	}

	if (sensors[index].sensor_type == TIRE)
		print_ts(sensors[index].sensor_data);
	else
		print_pmu(sensors[index].sensor_data);
}

void analyze(sensor_t *sensors, int n, op_fct *operations)
{
	int idx;
	scanf("%d", &idx);

	if (idx < 0 || idx > n) {
		printf("Index not in range!\n");
		return;
	}

	//aplicam toate operatiile reprezentate de vectorul operations_idxs
	for (int i = 0; i < sensors[idx].nr_operations; ++i)
		operations[sensors[idx].operations_idxs[i]](sensors[idx].sensor_data);
}

void clear(sensor_t **sensors, int *n)
{
	int inital_n = *n;
	/*parcurgem intreg vectorul, iar daca un element este invalid, eliberam
	memoria aferenta acestuia si shiftam intreg vectorul cu o pozitie
	la stanga*/
	for (int i = 0 ; i < *n; ++i) {
		if (!valid_sensor((*sensors)[i])) {
			free((*sensors)[i].sensor_data);
			free((*sensors)[i].operations_idxs);

			for (int j = i; j < *n - 1; ++j)
				(*sensors)[j] = (*sensors)[j + 1];
			
			(*n)--;
			i--;
		}
	}

	//daca nu avem elemente in vector, returnam NULL
	if (!(*n)) {
		free(*sensors);
		*sensors = NULL;
	}

	//daca au existat elemente invalide, realocam vectorul
	if (*n != inital_n) {
		sensor_t *aux = realloc(*sensors, *n * sizeof(sensor_t));
		DIE(!aux, "realloc failed\n");
		*sensors = aux;
	}
}

void free_sensors(sensor_t *sensors, int n)
{
	if (!sensors)
        return;
    
	//eliberam inreaga memorie utilizata
    for (int i = 0; i < n; ++i) {
		free(sensors[i].sensor_data);
		free(sensors[i].operations_idxs);
	}

	free(sensors);
}