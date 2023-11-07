#pragma once
#include <cstdio>
#include <iostream>
#include "files.h"

#define DATA_LOCATION "data/"

static void scan(char* input)
{
	scanf("%[^\n]s\n", input);
}

static void get_files_data(Files* files)
{
	unsigned int files_size = 0;
	FILE* files_data = fopen("data/files_data.txt", "r");
	char buffer[1000];
	char* book_location = buffer;

	printf("Gathering Files information from ./data folder.\n\n\n");

	fscanf(files_data, "%d\n", &files_size);

	files->size = files_size;

	for (int i = 0; i < files_size; i++)
	{
		fscanf(files_data, "%[^\n]s\n", book_location);


		


		//printf("Opening ./data/%s and reading information", book_location);
		//FILE* book = fopen(DATA_LOCATION + book_location, "r");
		//printf(strcat(book_location, "data/"));

		fgets(buffer, 2, files_data);
	}

	fclose(files_data);
}
