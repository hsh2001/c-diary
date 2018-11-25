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
			//일기 쓰기 시작
			scan_description(description);
			date = get_date_file_name();
			put_diary(date, description);
			system("cls");
			printf("\n\n~~![%d.txt] 일기 작성 성공!~~\n\n", date);
			break;
		case 2: 
			//일기 보기 시작
			printf("확인하고 싶은 날짜를 입력해주세요 (YYYY.MM.DD): ");
			scanf("%d.%d.%d", &year, &month, &day);
			system("cls");
			date = (year * 10000 + month * 100 + day);

			if (get_diary(date, description))
				printf("\n\n%d.txt의 정보:\n%s\n\n(그만 보려면 아무 키나 누르세요.)\n", date, description);
			else
				puts("그 날에는 일기를 작성하지 않았습니다.\n(아무 키나 눌러 메인화면으로 돌아가기.)\n");
			
			getchar();
			getchar();
			system("cls");
			break;
		case 3:
			//프로그램 종료
			return 0;
		default:
			//잘못된 번호 입력
			system("cls");
			puts("잘못된 번호를 입력하셨습니다. 다시 입력해주세요.\n");
			break;
		}
	}
	return 0;
}


//오늘의 날짜를 파일 이름으로 사용하기 위해
//정수형으로 변경해 리턴합니다.
//예시: 20181124 (int)
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
	printf("일기장\n");
	for (i = 0; i < 30; i++)
		printf("*");
	puts("\n");

	puts("원하는 기능의 번호를 입력 후 엔터를 눌러주십시오.");
	puts("1. 일기 쓰기");
	puts("2. 일기 보기");
	puts("3. 프로그램 종료");
}

void scan_description(char description[])
{
	int ch;
	unsigned int index = 0;
	char guide[] = "오늘의 일기를 입력하십시오(종료하려면 ctrl + Z를 누르고 enter.)";

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
			puts("\n글자 제한을 초과하여 작성을 종료하고 저장합니다.");
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