#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_DIARY_LENGTH 1000

void print_title(void);
int get_date_file_name(void);
void scan_description(char[]);
void put_diary(int, char[]);
int get_diary(int, char[]);

int main(void) 
{
	int menu, date, year, month, day;
	char description[MAX_DIARY_LENGTH] = "";

	while (1) 
	{
		description[0] = '\0';
		print_title();
		scanf("%d", &menu);
		system("cls");
		switch (menu)
		{
		case 1: 
			//�ϱ� ���� ����
			scan_description(description);
			date = get_date_file_name();
			put_diary(date, description);
			system("cls");
			printf("\n\n~~![%d.txt] �ϱ� �ۼ� ����!~~\n\n", date);
			break;
		case 2: 
			//�ϱ� ���� ����
			printf("Ȯ���ϰ� ���� ��¥�� �Է����ּ��� (YYYY.MM.DD): ");
			scanf("%d.%d.%d", &year, &month, &day);
			system("cls");
			date = (year * 10000 + month * 100 + day);

			if (get_diary(date, description))
				printf("\n\n%d.txt�� ����:\n%s\n\n(�׸� ������ �ƹ� Ű�� ��������.)\n", date, description);
			else
				puts("�� ������ �ϱ⸦ �ۼ����� �ʾҽ��ϴ�.\n(�ƹ� Ű�� ���� ����ȭ������ ���ư���.)\n");
			
			getchar();
			getchar();
			system("cls");
			break;
		case 3:
			//���α׷� ����
			return 0;
		default:
			//�߸��� ��ȣ �Է�
			system("cls");
			puts("�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n");
			break;
		}
	}
	return 0;
}


//������ ��¥�� ���� �̸����� ����ϱ� ����
//���������� ������ �����մϴ�.
//����: 20181124 (int)
int get_date_file_name(void) 
{
	int year, month, day;
	struct tm *t;
	time_t timer;

	timer = time(NULL);
	t = localtime(&timer);

	year = t->tm_year + 1900;
	month = t->tm_mon + 1;
	day = t->tm_mday;

	return (year * 10000 + month * 100 + day);
}

void print_title(void) 
{
	int i;

	for (i = 0; i < 30; i++)
		printf("*");
	puts("");
	for (i = 0; i < 10; i++)
		printf(" ");
	printf("�ϱ���\n");
	for (i = 0; i < 30; i++)
		printf("*");
	puts("\n");

	puts("���ϴ� ����� ��ȣ�� �Է� �� ���͸� �����ֽʽÿ�.");
	puts("1. �ϱ� ����");
	puts("2. �ϱ� ����");
	puts("3. ���α׷� ����");
}

void scan_description(char description[])
{
	int ch;
	unsigned int index = 0;
	char guide[] = "������ �ϱ⸦ �Է��Ͻʽÿ�(�����Ϸ��� ctrl + Z�� ������ enter.)";

	getchar();
	printf("%s(0/%d)\n", guide, MAX_DIARY_LENGTH - 1);

	while ((ch = getchar()) != EOF)
	{
		description[index] = ch;
		index = strlen(description);
		
		system("cls");
		printf(
			"%s(%d/%d):\n%s", 
			guide,
			index,
			MAX_DIARY_LENGTH - 1,
			description
		);

		if (index + 1 == MAX_DIARY_LENGTH - 1)
		{
			puts("\n���� ������ �ʰ��Ͽ� �ۼ��� �����ϰ� �����մϴ�.");
			break;
		}
	}

	description[index + 1] = '\0';
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

int get_diary(int date, char description[])
{ 
	char filename[20];
	FILE *fp;

	sprintf(filename, "%d", date);
	strcat(filename, ".txt");
	fp = fopen(filename, "r");

	if (fp == NULL)
		return 0;

	fgets(description, MAX_DIARY_LENGTH, fp);
	fclose(fp);
	return 1;
}