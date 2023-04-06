//copyright Carauleanu Valentin Gabriel 311CAb
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "aux_functions.h"
#include "operations.h"
#include "commands.h"

int main(int argc, char const *argv[])
{
	if (argc != 2)
		return -1;
	
	//n -> nr de senzori
	char *cmd_string = NULL;
	int cmd = 0, done = 0, n = 0;

	//citim si sortam senzorii
	sensor_t *sensors = read_sensors(argv, &n);
	sort_sensors(&sensors, n);

	//initalizam  un vector de functii
	op_fct *operations = malloc(8 * sizeof(op_fct));
	DIE (!operations, "malloc failed\n");
	//populam vectorul anterior cu operatiile senzorilor
	get_operations((void **)operations);

	while (1) {
		cmd_string = read_cmd();
		if (!cmd_string) {
			printf("Invalid command\n");
			continue;
		}
		command(&cmd, cmd_string);

		switch (cmd) {
		case 1:
			print_sensors(sensors, n);
			break;
		case 2:
			analyze(sensors, n, operations);
			break;
		case 3:
			clear(&sensors, &n);
			break;
		case 4:
			done = 1;
			free_sensors(sensors, n);
			break;
		default:
			printf("Invalid command\n");
			break;
		}

		free(cmd_string);
		if (done)
			break;
	}

	free(operations);

	return 0;
}
