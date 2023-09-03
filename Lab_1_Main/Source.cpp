#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define STUDENT_COUNT 50
#define FIO_LENGTH 15
#define SUBJECTS_COUNT 5

struct studentData
{
	int sequenceNumber;

	char name[FIO_LENGTH];
	char surname[FIO_LENGTH] = {0};
	char patronymic[FIO_LENGTH];

	int bookNumber;

	int markList[SUBJECTS_COUNT];
};

int ReadTxt(const char fileName[], studentData studentList[], int &studentCount)
{
	int tmp = 0;

	FILE* f = 0;


	if (fopen_s(&f, fileName, "r") != 0)
	{
		printf_s("Error opening file!\n");
		return -1;
	}

	while (feof(f) == 0)
	{
		studentCount++;

		fscanf_s(f, "%d", &studentList[studentCount].sequenceNumber);

		fscanf(f, "%s", studentList[studentCount].surname);
		fscanf(f, "%s", studentList[studentCount].name);
		fscanf(f, "%s", studentList[studentCount].patronymic);

		fscanf_s(f, "%d", &studentList[studentCount].bookNumber);

		for (int i = 0; i < SUBJECTS_COUNT; i++)
			fscanf_s(f, "%d", &studentList[studentCount].markList[i]);
	}

	studentCount++;

	fclose(f);

	return 0;
}

int PrintTxt(studentData studentList[], int& studentCount)
{
	char head[] = "ID | FIO                                             | Book ID | A | B | C | D | E |";
	int headLen = strlen(head);

	printf_s("%s\n", head);
	
	for(int i = 0; i < headLen; i++)
		printf_s("-");

	printf_s("\n");

	for (int i = 0; i < studentCount; i++)
	{
		if(studentList[i].sequenceNumber < 10)
			printf_s("0%d ", studentList[i].sequenceNumber);
		else
			printf_s("%d ", studentList[i].sequenceNumber);

		printf_s("| ");

		printf_s("%s ", studentList[i].surname);
		printf_s("%s ", studentList[i].name);
		printf_s("%s ", studentList[i].patronymic);

		int stringLen = strlen(studentList[i].surname) + strlen(studentList[i].name) + strlen(studentList[i].patronymic);
		while (stringLen++ < FIO_LENGTH * 3)
		{
			printf_s(" ");
		}

		printf_s("| ");

		printf_s("%d    ", studentList[i].bookNumber);

		printf_s("| ");

		for (int j = 0; j < SUBJECTS_COUNT; j++)
		{
			printf_s("%d ", studentList[i].markList[j]);
			printf_s("| ");
		}

		printf_s("\n");
	}

	for (int i = 0; i < headLen; i++)
		printf_s("-");

	return 0;
}

int main()
{
	studentData studentList[STUDENT_COUNT];
	int studentCount = - 1;

	ReadTxt("Data.txt", studentList, studentCount);

	PrintTxt(studentList, studentCount);

	return 0;
}