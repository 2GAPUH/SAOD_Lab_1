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
	char surname[FIO_LENGTH];
	char patronymic[FIO_LENGTH];

	int bookNumber;

	int markList[SUBJECTS_COUNT];
};

void AddSpace(char array[])
{
	int tmp = strlen(array);
	while (tmp < FIO_LENGTH)
	{
		array[tmp] = ' ';
		tmp++;
	}
	array[FIO_LENGTH - 1] = 0;
}

int ReadTxt(const char fileName[], studentData studentList[], int &studentCount)
{
	FILE* f = 0;

	if (fopen_s(&f, fileName, "r") != 0)
		return -1;


	while (feof(f) == 0)
	{
		studentCount++;

		fscanf_s(f, "%d", &studentList[studentCount].sequenceNumber);

		fscanf(f, "%s", studentList[studentCount].surname);
		AddSpace(studentList[studentCount].surname);

		fscanf(f, "%s", studentList[studentCount].name);
		AddSpace(studentList[studentCount].name);

		fscanf(f, "%s", studentList[studentCount].patronymic);
		AddSpace(studentList[studentCount].patronymic);


		fscanf_s(f, "%d", &studentList[studentCount].bookNumber);

		for (int i = 0; i < SUBJECTS_COUNT; i++)
			fscanf_s(f, "%d", &studentList[studentCount].markList[i]);
	}

	studentCount++;

	fclose(f);

	return 0;
}

int PrintTable(studentData studentList[], int& studentCount, bool flag, char buffer[])
{
	char head[] = "ID | Surname        Name           Patronymic     | Book ID |";
	int headLen = strlen(head) + 4 * SUBJECTS_COUNT;

	printf_s("%s", head);

	for (int i = 0; i < SUBJECTS_COUNT; i++)
		printf_s(" %c |", 'A' + i);
	
	printf_s("\n");

	for(int i = 0; i < headLen; i++)
		printf_s("-");

	printf_s("\n");

	for (int i = 0; i < studentCount; i++)
	{
		if(studentList[i].sequenceNumber < 10)
			printf_s("0%d | ", studentList[i].sequenceNumber);
		else
			printf_s("%d | ", studentList[i].sequenceNumber);

		if (flag)
		{
			char* tmp1 = strstr(studentList[i].surname, buffer);
			int tmp = (tmp1 - studentList[i].surname) / sizeof(char);
			int stringLen = strlen(buffer);

			for (int j = 0; j < tmp; j++)
				printf_s("%c", studentList[i].surname[j]);

			printf_s("\033[33m");
			for (int j = tmp; j < stringLen + tmp; j++)
				printf_s("%c", studentList[i].surname[j]);
			printf("\033[0m");

			for (int j = stringLen + tmp; j < FIO_LENGTH; j++)
				printf_s("%c", studentList[i].surname[j]);

			printf_s(" ");
		}
		else
			printf_s("%s ", studentList[i].surname);
		
		printf_s("%s ", studentList[i].name);
		printf_s("%s ", studentList[i].patronymic);

		printf_s("|  %d   | ", studentList[i].bookNumber);

		for (int j = 0; j < SUBJECTS_COUNT; j++)
		{
			printf_s("%d ", studentList[i].markList[j]);
			printf_s("| ");
		}

		printf_s("\n");
	}

	for (int i = 0; i < headLen; i++)
		printf_s("-");

	printf_s("\n");

	return 0;
}

void swap(studentData studentList[], int i, int j)
{
	studentData temp = studentList[i];
	studentList[i] = studentList[j];
	studentList[j] = temp;
}

void SortSurname(studentData studentList[], int studentCount) 
{
	bool swapped;

	for (int i = 0; i < studentCount - 1; i++) 
	{
		swapped = false;
		for (int j = 0; j < studentCount - i - 1; j++)
		{
			for (int k = 0; studentList[j].surname[k] != ' '; k++)
			{
				if (studentList[j].surname[k] > studentList[j + 1].surname[k])
				{
					swap(studentList, j, j + 1);
					swapped = true;
					break;
				}
				else if(studentList[j].surname[k] != studentList[j + 1].surname[k])
					break;
			}
		}
		if (swapped == false)
			break;
	}
}

void SortSubject(studentData studentList[], int studentCount)
{
	int choice = 0;

	printf_s("Sort by: \n0 - Return");

	for (int i = 0; i < SUBJECTS_COUNT; i++)
		printf_s("\n%d - Subject %c", i + 1, 'A' + i);

	printf_s("\n");

	while (true)
	{
		printf_s("Enter your choice: ");
		scanf_s("%d", &choice);

		if (choice == 0)
			return;

		else if (choice > 0 && choice <= SUBJECTS_COUNT)
		{
			bool swapped = false;

			for (int i = 0; i < studentCount - 1; i++)
			{
				swapped = false;

				for (int j = 0; j < studentCount - i - 1; j++)
				{
					if (studentList[j].markList[choice - 1] < studentList[j + 1].markList[choice - 1])
					{
						swap(studentList, j, j + 1);
						swapped = true;
					}
				}

				if (swapped == false)
					break;
			}
			
			return;
		}

		else
			printf_s("Invalid value!Try again.\n");
	}
}

void FindSurname(studentData studentList[], int studentCount, char buffer[])
{
	studentData dopStudentList[STUDENT_COUNT / 5];
	int dopStudentCount = 0;

	for (int i = 0; i < studentCount; i++)
		if (strstr(studentList[i].surname, buffer))
			dopStudentList[dopStudentCount++] = studentList[i];
		
	if (dopStudentCount > 0)
		PrintTable(dopStudentList, dopStudentCount, 1, buffer);

	else
		printf_s("There is no such surname.\n");
	
	system("pause");
}

void GetSurname(char buffer[])
{
	printf_s("Enter surname: ");

	scanf("%s", buffer);
}

int main()
{
	studentData studentList[STUDENT_COUNT];
	int studentCount = -1;
	int choice = 0;
	char buffer[FIO_LENGTH] = { 0 };

	if (ReadTxt("Data.txt", studentList, studentCount) == -1)
	{
		printf_s("Error opening file!\n");
		return -1;
	}

	while (true)
	{
		system("cls");

		PrintTable(studentList, studentCount, 0, buffer);
		
		printf_s("Sort by:\n");
		printf_s("1 - surname\n");
		printf_s("2 - mark\n");
		printf_s("3 - Find surname\n");
		printf_s("0 - exit\n");
		printf_s("Enter your choice: ");

		scanf_s("%d", &choice);

		switch (choice)
		{
		case 0:
			return 0;

		case 1:
			SortSurname(studentList, studentCount);
			break;
		
		case 2:
			SortSurname(studentList, studentCount);
			SortSubject(studentList, studentCount);
			break;
		
		case 3:
			GetSurname(buffer);
			FindSurname(studentList, studentCount, buffer);
			break;

		default:
			printf_s("Invalid value! Try again.\n");

		}
	}


	return 0;
}