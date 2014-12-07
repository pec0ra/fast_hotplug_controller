#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"


#define BUFFER_SIZE	128

#define LOAD_COMMAND_1		"adb shell \"su -c 'cat /sys/module/fast_hotplug/parameters/"
#define LOAD_COMMAND_2		"'\" 2>&1"

#define STORE_COMMAND_1		"adb shell \"su -c 'echo "
#define STORE_COMMAND_2		" > /sys/module/fast_hotplug/parameters/"
#define STORE_COMMAND_3		"'\""

unsigned int error = ~0;

unsigned int boost_duration;
unsigned int fast_hotplug_enabled;
unsigned int idle_threshold;
unsigned int max_cpu_on;
unsigned int min_cpu_on;
unsigned int screen_off_singlecore;
unsigned int threshold_to_boost;

unsigned int plug_in_core_1_threshold;
unsigned int plug_in_core_2_threshold;
unsigned int plug_in_core_3_threshold;
unsigned int plug_in_core_1_delay;
unsigned int plug_in_core_2_delay;
unsigned int plug_in_core_3_delay;

unsigned int plug_out_core_1_threshold;
unsigned int plug_out_core_2_threshold;
unsigned int plug_out_core_3_threshold;
unsigned int plug_out_core_1_delay;
unsigned int plug_out_core_3_delay;
unsigned int plug_out_core_2_delay;

static int read_value(char *file_name, unsigned int *output){
	FILE *fp;
	char path[BUFFER_SIZE];
	char command[BUFFER_SIZE];
	
	strcpy(command, LOAD_COMMAND_1);
	strcat(command, file_name);
	strcat(command, LOAD_COMMAND_2);

	/* Open the command for reading. */
	fp = popen(command, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		*output = atoi(path);
	}

	/* close */
	pclose(fp);

	return 0;
}
static int store_value(char *file_name, unsigned int input){
	char command[BUFFER_SIZE];
	char input_str[BUFFER_SIZE];
	sprintf(input_str, "%d", input);

	strcpy(command, STORE_COMMAND_1);
	strcat(command, input_str);
	strcat(command, STORE_COMMAND_2);
	strcat(command, file_name);
	strcat(command, STORE_COMMAND_3);
	system(command);

	return 0;
}

static int load_values(void){

	printf("Loading values...\n");
	read_value("boost_duration", &boost_duration);
	read_value("fast_hotplug_enabled", &fast_hotplug_enabled);
	read_value("idle_threshold", &idle_threshold);
	read_value("max_cpu_on", &max_cpu_on);
	read_value("min_cpu_on", &min_cpu_on);
	read_value("screen_off_singlecore", &screen_off_singlecore);
	read_value("threshold_to_boost", &threshold_to_boost);

	read_value("plug_in_core_1_threshold", &plug_in_core_1_threshold);
	read_value("plug_in_core_2_threshold", &plug_in_core_2_threshold);
	read_value("plug_in_core_3_threshold", &plug_in_core_3_threshold);
	read_value("plug_in_core_1_delay", &plug_in_core_1_delay);
	read_value("plug_in_core_2_delay", &plug_in_core_2_delay);
	read_value("plug_in_core_3_delay", &plug_in_core_3_delay);

	read_value("plug_out_core_1_threshold", &plug_out_core_1_threshold);
	read_value("plug_out_core_2_threshold", &plug_out_core_2_threshold);
	read_value("plug_out_core_3_threshold", &plug_out_core_3_threshold);
	read_value("plug_out_core_1_delay", &plug_out_core_1_delay);
	read_value("plug_out_core_2_delay", &plug_out_core_2_delay);
	read_value("plug_out_core_3_delay", &plug_out_core_3_delay);
	system("clear");

	return 0;
}

static void disable(void){
	if(fast_hotplug_enabled){
		char confirm;
		printf("Are you sure you want to disable fast hotplug ? (y/N) ");
		scanf(" %c", &confirm);
		if(confirm == 121 || confirm == 89){
			store_value("fast_hotplug_enabled", 0);
			fast_hotplug_enabled = 0;
		}
	} else {
			store_value("fast_hotplug_enabled", 1);
			fast_hotplug_enabled = 1;
	}
}

static void min_max(void){

	unsigned int new_min = error, new_max = error;

	printf("Enter two numbers :\n<min_cpu_on> <max_cpu_on>\n");
	scanf("%d %d", &new_min, &new_max);
	if(new_min <= 8 && new_min >= 1){
		store_value("min_cpu_on", new_min);
		min_cpu_on = new_min;
	}
	if(new_max <= 8 && new_max >= 1){
		store_value("max_cpu_on", new_max);
		max_cpu_on = new_max;
	}
}

static void boost(void){
	unsigned int new_duration = error, new_threshold = error;

	printf("Enter two numbers :\n<boost_duration> <threshold_to_boost>\n");
	scanf("%d %d", &new_duration, &new_threshold);

	store_value("boost_duration", new_duration);
	boost_duration = new_duration;
	store_value("threshold_to_boost", new_threshold);
	threshold_to_boost = new_threshold;
}

static void plug_in(void){
	unsigned int new_1_t = error, new_2_t = error, new_3_t = error;
	unsigned int new_1_d = error, new_2_d = error, new_3_d = error;

	printf("Enter three thresholds :\n<plug_in_core_1_threshold> <plug_in_core_2_threshold> <plug_in_core_3_threshold>\n");
	scanf("%d %d %d", &new_1_t, &new_2_t, &new_3_t);

	store_value("plug_in_core_1_threshold", new_1_t);
	plug_in_core_1_threshold = new_1_t;
	store_value("plug_in_core_2_threshold", new_2_t);
	plug_in_core_2_threshold = new_2_t;
	store_value("plug_in_core_3_threshold", new_3_t);
	plug_in_core_3_threshold = new_3_t;

	printf("Enter three delays :\n<plug_in_core_1_delay> <plug_in_core_2_delay> <plug_in_core_3_delay>\n");
	scanf("%d %d %d", &new_1_t, &new_2_t, &new_3_t);

	store_value("plug_in_core_1_delay", new_1_t);
	plug_in_core_1_delay = new_1_t;
	store_value("plug_in_core_2_delay", new_2_t);
	plug_in_core_2_delay = new_2_t;
	store_value("plug_in_core_3_delay", new_3_t);
	plug_in_core_3_delay = new_3_t;
}

static void plug_out(void){
	unsigned int new_1_t = error, new_2_t = error, new_3_t = error;
	unsigned int new_1_d = error, new_2_d = error, new_3_d = error;

	printf("Enter three thresholds :\n<plug_out_core_1_threshold> <plug_out_core_2_threshold> <plug_out_core_3_threshold>\n");
	scanf("%d %d %d", &new_1_t, &new_2_t, &new_3_t);

	store_value("plug_out_core_1_threshold", new_1_t);
	plug_out_core_1_threshold = new_1_t;
	store_value("plug_out_core_2_threshold", new_2_t);
	plug_out_core_2_threshold = new_2_t;
	store_value("plug_out_core_3_threshold", new_3_t);
	plug_out_core_3_threshold = new_3_t;

	printf("Enter three delays :\n<plug_out_core_1_delay> <plug_out_core_2_delay> <plug_out_core_3_delay>\n");
	scanf("%d %d %d", &new_1_t, &new_2_t, &new_3_t);

	store_value("plug_out_core_1_delay", new_1_t);
	plug_out_core_1_delay = new_1_t;
	store_value("plug_out_core_2_delay", new_2_t);
	plug_out_core_2_delay = new_2_t;
	store_value("plug_out_core_3_delay", new_3_t);
	plug_out_core_3_delay = new_3_t;
}

static void idle(void){
	unsigned int new_idle = error;

	printf("Enter one number :\n<idle_threshold>\n");
	scanf("%d", &new_idle);
	store_value("idle_threshold", new_idle);
	idle_threshold = new_idle;
}

static void singlecore(void){
	unsigned int new_single = error;

	printf("Enter 0 or 1 :\n<screen_off_singlecore>\n");
	scanf("%d", &new_single);
	if(new_single == 0 || new_single == 1){
		store_value("screen_off_singlecore", new_single);
		screen_off_singlecore = new_single;
	}
}
int main(int argc, char **argv){
	int option;
	load_values();
start:
	print_menu();
	scanf("%d", &option);
	switch(option){
		case 0:
			disable();
			break;
		case 1:
			min_max();
			break;
		case 2:
			boost();
		case 3:
			plug_in();
			break;
		case 4:
			plug_out();
			break;
		case 5:
			idle();
			break;
		case 6:
			singlecore();
			break;
		case 7:
			load_values();
			break;
		case 8:
			return 0;
			break;
		default:
			break;
	}
	goto start;
	return 0;
}
