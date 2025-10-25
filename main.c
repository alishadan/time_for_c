#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h" //this library is for sounds
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <windows.h>
void config(void) {
	//this function reset file.txt 
	FILE* file = fopen("file.txt", "w"); //open or create file.txt for write in that
	char arr[] = "start_music:start.mp3\n"
		"duration_work:5 minute // only number and minimum is one minute;\n"
		"break_music :stop.mp3\n"
		"duration_break :1 minute 1 minute // only number and minimum is one minute;\n";
	fprintf(file, arr);  //write arr on file.txt
	fclose(file); //close file.txt
	
	// if user remove file.txt
	//create a new file.txt or replaced with file.txt
}
void read_file(char arr2[4][100]) {
	//this function read file.txt and saved their data in arr2
	FILE* file = fopen("file.txt", "r"); // open file.txt and pointer to that with name file
	char arr[4][100]; //  array for save data from file.txt 
	//arr[0] is name of start sound, arr[1] is work time, arr[2] is name of stop sound and arr[3] is break time
	if (file != NULL) {   //if do not error occured in open file.txt
		for (int i = 0; i < 4; i++) { //this for loop is for full arr
			if (fgets(arr[i], 100, file) != NULL) {  //read data from file.txt and saved in arr[i]
				char* temp; temp = strchr(arr[i], '\n'); *temp = '\0'; //ENTER is last element of arr[i], we removed that
				char* p = strstr(arr[i], ":"); // in file.txt in each line is amount:value, we need to value
				if (p == NULL) {
					printf("p is null\n");
					printf("file.txt encountered with erorr\nthis file repair automitically\n"
						"file.txt set to default values\n"
						"please do not remove ':' in file.txt\n\n");
					config(); // repair file.txt


				}
				else {

					strcpy_s(arr2[i], sizeof(arr2[i]), p + 1); //we full arr2[i] with value only, p point to : in arr[i]
				}
			}
		}
		fclose(file);
	}
	else {
		printf("Error reading input.");
	}
	
	
}
void run(int w_time, int b_time) {
	//this function run time_for_c program
	char arr2[4][100]; //array for save data saved in fil.txt,sounds
	read_file(arr2); //function for read file.txt and save data in array with name arr2
	int duration_work = w_time * 60000;  //convert minute to miliseconds
	int duration_break = b_time * 60000; //convert minute to miliseconds

	// initialization miniaudio library
	ma_engine engine; //defined in miniaudio.h 
	ma_result result; //defined in miniaudio.h
	result = ma_engine_init(NULL, &engine); //we initialize miniaudio
	if (result != MA_SUCCESS) { //if initialization occured with error
		printf("Failed to initialize audio engine.");
		return;
	}
	// start program
	printf("please enter a key and ENTER than program run \n");
	int a = getchar(); //we use of getchar function to give control to user for run the program
	printf("for exite the program, enter 'ctrl+c' \n");
	while (1) {
		char quite=getchar();
		if (quite == "q") break;
		//work time
		printf("work time is started for %i minutes\n", w_time);
		if (strcmp(arr2[0], "start.mp3") == 0) {
			ma_engine_play_sound(&engine, arr2[0], NULL); // this function play sound, arr2[0] is contain name of the sound
			Sleep(duration_work); //sleep accept data to miliseconds, we convert minutes in miliseconds before
			printf("work time is finised\n");
		}
		else {
			return;

		}
		if (strcmp(arr2[2], "stop.mp3") == 0) {//break time
			printf("break time is started for %i minutes \n", b_time);
			ma_engine_play_sound(&engine, arr2[2], NULL);
			Sleep(duration_break); //sleep accept data to miliseconds, we convert minutes in miliseconds before
			printf("break time is finised\n");
		}
		else {
			return;
		}
	}


}
int check_requirements(void) {
	// this function check requirement for run program
	//check exiting start.mp3 and stop.mp3 file
	LPCSTR file_name = "start.mp3";	//we confirm be start.mp3 file
	LPCSTR file_name2 = "stop.mp3";	//we confirm be start.mp3 file
	HANDLE file_handle;				// in this variable value of findfirestfileA function saved
	WIN32_FIND_DATAA file_data;		// information about start.mp3 or stop.mp3 saved
	file_handle = FindFirstFileA(file_name, &file_data);	//search for finding start.mp3
	if (file_handle == INVALID_HANDLE_VALUE) {		//if dont exist start.mp3
		printf("start.mp3 file does not have, please provide that");
		return -1 ;
	}
	file_handle = FindFirstFileA(file_name2, &file_data); //search for finding stop.mp3
	if (file_handle == INVALID_HANDLE_VALUE) { //if dont exist start.mp3
		printf("stop.mp3 file does not have, please provide that");
		return -1;
	}
	return 1; // every thing is good
	//check for file.txt and content of that

}
int main(int argc, char* argv[]) {
	check_requirements(); //check requirement for run the program
	char arr2[4][100];  //array for save data saved in fil.txt, times and sounds
	read_file(arr2); //function for read file.txt and save data in array with name arr2
	
	int w_time = atoi(arr2[1]);  // provided with file.txt //time for work time
	int b_time = atoi(arr2[3]); //provided with file.txt /time for break time

	if (argc == 1) {
		run(w_time, b_time);
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
		if (strcmp(argv[1], "-w") == 0) {  //compare argv[1] and -w, Do user enter -w
			w_time = atoi(argv[2]); //work time is equal with value that user enter
			if (w_time == 0) {
				printf("please enter how many work you want work\n");
				return -1;
			}
			run(w_time, b_time); //run function to rest of program
		}
		else {
			printf("please enter right format\n");
			printf("enter -h for helps\n");
		}
	}
	if (argc == 4) {
		if (strcmp(argv[1], "-w") == 0) { //compare argv[1] and -w, Do user enter -w

			if (strcmp(argv[3], "-b") == 0) {  //compare argv[1] and -w, Do user enter -w
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
		if (strcmp(argv[1], "-w") == 0) {  //compare argv[1] and -w, Do user enter -w
			w_time = atoi(argv[2]); //work time is equal with value that user enter
			if (w_time == 0) {
				printf("please enter how many work you want work\n");
				return -1;
			}
			if (strcmp(argv[3], "-b") == 0) { //compare argv[3] and -w, Do user enter -b
				b_time = atoi(argv[4]); //break time is equal with value that user enter
				if (b_time == 0) {
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
		else {
			printf("please enter right format\n");
			printf("enter -h for helps\n");
			return -1;
		}
	}
	system("pause");
	return 0;
}
