#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"
#include <stdio.h>
#include <windows.h>
#include<string.h>
void read_file(char arr2[4][100]) {
	FILE* file = fopen("file.txt", "r");
	char arr[4][100];
	if (file != NULL) {
		for (int i = 0; i < 4; i++) {
			if (fgets(arr[i], 100, file) != NULL) {
				char* temp; temp = strchr(arr[i], '\n'); *temp = '\0';
				char* p = strstr(arr[i], ":");
				if (p == NULL) {
					printf("p is null");
					
				}
				else {
					
					strcpy_s(arr2[i], sizeof(arr2[i]), p + 1);
				}
			}
			else {
				printf("Error reading input.");
			}
		}
	}
}
void run(int w_time, int b_time) {
	char arr2[4][100];
	read_file(arr2);
	char* temp2; temp2 = strchr(arr2[1], ' '); *temp2 = '\0';
	temp2 = strchr(arr2[3], ' '); *temp2 = '\0';
	int duration_work = w_time * 60000;
	int duration_break = b_time * 60000;

	// initialization miniaudio library
	ma_engine engine;
	ma_result result;
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS) {
		printf("Failed to initialize audio engine.");
		return;
	}
	// start program
	printf("please enter a key and ENTER than program run \n");
	int a = getchar();
	//work time

	while (1) {
		printf("work time is started for %i minutes\n", w_time);
		ma_engine_play_sound(&engine, arr2[0], NULL);
		Sleep(duration_work);
		printf("work time is finised\n");
		//break time
		printf("break time is started for %i seconds \n", b_time);
		ma_engine_play_sound(&engine, arr2[2], NULL);
		Sleep(duration_break);
		printf("break time is finised\n");
	}


}
int main(int argc, char* argv[]) {
	int b_time = 0.5; int w_time = 4;
	if (argc == 1) {
		char arr2[4][100];
		read_file(arr2);
		char* temp2; temp2 = strchr(arr2[1], ' '); *temp2 = '\0';
		temp2 = strchr(arr2[3], ' '); *temp2 = '\0';
		int duration_work = atoi(arr2[1]) * 60000;
		int duration_break = atoi(arr2[3]) * 1000;
		run(duration_work, duration_break);

	}
	if (argc == 2) {
		if (strcmp(argv[1], "-h") == 0) {
			printf("okay , you entered in the help \n"
			"time is setted in minute\n"
			"-w for assign work time\n"
			"-w number , number shoud have a number for example -w 10\n"
			"-b for assign rest time\n"
			"-w number -b number , that number should have a number\n"
			"-w 4 -b 1 , it is a example\n"
			);
		}
		else if (strcmp(argv[1], "-w") == 0) {
			printf("please enter how many work time is \n");
			printf("enter -h for find helps");
			return -1;
		}
		else {
			printf("please enter how many work time is \n");
			printf("enter -h for find helps");
			return -1;
		}
	}
	if (argc == 3) {
		if (strcmp(argv[1], "-w") == 0) {
			w_time = atoi(argv[2]);
			if (w_time == 0) {
				printf("please enter how many work you want work\n");
				return -1;
			}
			run(w_time, b_time);
		}
		else {
			printf("please enter right format\n");
			printf("enter -h for helps\n");
		}
	}
	if (argc == 4) {
		if (strcmp(argv[1], "-w") == 0){
			w_time = atoi(argv[2]);
			if (w_time == 0) {
				printf("please enter how many work you want work\n");
				return -1;
			}
			if (strcmp(argv[3], "-b") == 0) {
				printf("please enter how many time you want rest\n");
				printf("for help, enter -h");
				return -1;
			}
			else {
				printf("please enter right format\n");
				printf("for helps enter -h");
				return -1;
			}
		
		}
		else {
			printf("please enter right format \n");
			printf("for helps enter -h\n");
			return -1;
		}
	}
	if (argc == 5) {
		if (strcmp(argv[1], "-w") == 0) {
			w_time = atoi(argv[2]);
			if (w_time == 0) {
				printf("please enter how many work you want work\n");
				return -1;
			}
		}
		else {
			printf("please enter right format\n");
			printf("enter -h for helps\n");
			return -1;
		}
		if (strcmp(argv[3], "-b") == 0) {
			b_time = atoi(argv[4]);
			if (w_time == 0) {
				printf("please enter how many work you want work\n");
				return -1;
			}
			run(w_time, b_time);
		}
		else {
			printf("please enter right format\n");
			printf("enter -h for helps\n");
			return -1;
		}
	}
	system("pause");
	return 0;

}