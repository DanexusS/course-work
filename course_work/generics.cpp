#include <iostream>

#include "generics.h"

int CmpStr(const char* first, const char* second){
	while (*first == *second && *first != '\0' && *second != '\0') {
		first++;
		second++;
	}

	int difference = *first - *second;

	if (difference < -1)
		return -1;
	if (difference > 1)
		return 1;
	return 0;
}

bool CheckFolderLocation(const char* folder_location) {
	char* long_temp = new char[LONG_INPUT_BUFFER];
	strcpy(long_temp, folder_location);
	strcat(long_temp, "temp.txt");

	FILE* file = fopen(long_temp, "w");

	if (file != 0) {
		fclose(file);
		remove(long_temp);
		delete[] long_temp;
		return 0;
	}
	delete[] long_temp;
	return 1;
}

bool CheckFileLocation(const char* file_location) {
	FILE* file = fopen(file_location, "r");

	if (file != 0) {
		fclose(file);
		return 0;
	}
	return 1;
}
