//copyright Carauleanu Valentin Gabriel 311CAb
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "structs.h"
#include "aux_functions.h"

void command(int *cmd, char *string)
{
	/*pentru un meniu mai eye-candy vom transforma comanda primita
	in valori numerice */

	if (!strcmp(string, "print"))
		*cmd = 1;
	else if (!strcmp(string, "analyze"))
		*cmd = 2;
	else if (!strcmp(string, "clear"))
		*cmd = 3;
	else if (!strcmp(string, "exit"))
		*cmd = 4;
	else
		*cmd = -1;
}

char *read_cmd(void)
{
	// citim comanda primita
	char command[NMAX];
	scanf("%s", command);

	// eliminam \n de la finalul string ului citit
	int len = strlen(command);
	if (command[len - 1] == '\n') {
		command[len - 1] = '\0';
		len--;
	}
	// crestem len pentru a copia si \0
	len++;

	char *cmd = malloc(len * sizeof(char));
	if (!cmd)
		return NULL;

	strcpy(cmd, command);
	return cmd;
}

sensor_t read_sensor_data(size_t data_size, enum sensor_type type, FILE *in)
{	
	sensor_t sensor;
	sensor.sensor_type = type;

	//alocam sensor_data si citim intreaga structura din fisier
	sensor.sensor_data = malloc(data_size);
	DIE(!sensor.sensor_data, "malloc failed\n");
	fread(sensor.sensor_data, 1, data_size, in);

	return sensor;
}

void print_pmu(power_management_unit_t *data)
{
	printf("Power Management Unit\n");
	printf("Voltage: %.2f\nCurrent: %.2f\nPower Consumption: %.2f\n",
			data->voltage, data->current, data->power_consumption);
	printf("Energy Regen: %d%%\nEnergy Storage: %d%%\n",
			data->energy_regen, data->energy_storage);
}

void print_ts(tire_sensor_t *data)
{
	printf("Tire Sensor\n");
	printf("Pressure: %.2f\nTemperature: %.2f\nWear Level: %d%%\n",
			data->pressure, data->temperature, data->wear_level);
	if (!data->performace_score)
		printf("Performance Score: Not Calculated\n");
	else
		printf("Performance Score: %d\n", data->performace_score);
}

int valid_ts(tire_sensor_t *data)
{
	/*verificam daca datele unui senzor TIRE se incadreaza
	in limitele valide*/
	if (data->pressure < 19 || data->pressure > 29)
		return 0;
	
	if (data->temperature < 0 || data->temperature > 120)
		return 0;
	
	if (data->wear_level < 0 || data->wear_level > 100)
		return 0;
	
	return 1;
}

int valid_pmu(power_management_unit_t *data)
{	
	/*verificam daca datele unui senzor PMU se incadreaza
	in limitele valide*/
	if (data->voltage < 10 || data->voltage > 20)
		return 0;
	
	if (data->current < -100 || data->current > 100)
		return 0;
	
	if (data->power_consumption < 0 || data->power_consumption > 1000)
		return 0;
	
	if (data->energy_regen < 0 || data->energy_regen > 100)
		return 0;
	
	if (data->energy_storage < 0 || data->energy_storage > 100)
		return 0;
	
	return 1;
}

int valid_sensor(sensor_t sensor)
{
	if (sensor.sensor_type == TIRE)
		if (!valid_ts(sensor.sensor_data))
			return 0;
	
	if (sensor.sensor_type == PMU)
		if (!valid_pmu(sensor.sensor_data))
			return 0;
	
	return 1;
}
