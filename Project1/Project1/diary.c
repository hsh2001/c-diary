#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>

void put_diary(int date, char[], int description);

int main(void) 
{
	return 0;
}

void put_diary(int date, char description[])
{ 
	char filename[20];

	FILE *fp;
	sprintf(filename, "%d", date);
	strcat(filename, ".txt");
	fp = fopen(filename, "w");
	fprintf(fp, "%s", description);
	fclose(fp);
}
void get_diary(int date, char description[])
{ 
	char filename[20];

	FILE *fp;
	sprintf(filename, "%d", date);
	strcat(filename, ".txt");
	fp = fopen(filename, "r");
	fgets(description, strlen(description), fp);
	fclose(fp);
}