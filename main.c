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
int main() {
	char arr2[4][100];
	read_file(arr2);
	char* temp2; temp2 = strchr(arr2[1], ' '); *temp2 = '\0';
	temp2 = strchr(arr2[3], ' '); *temp2 = '\0';
	int duration_work = atoi(arr2[1]) * 60000;
	int duration_break = atoi(arr2[3]) * 1000;

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
		printf("work time is started for 4 minutes\n");
		ma_engine_play_sound(&engine, arr2[0], NULL);
		Sleep(duration_work);
		printf("work time is finised\n");
		//break time
		printf("break time is started for 30 seconds \n");
		ma_engine_play_sound(&engine, arr2[2], NULL);
		Sleep(duration_break);
		printf("break time is finised\n");
	}
	system("pause");
	return 0;

}