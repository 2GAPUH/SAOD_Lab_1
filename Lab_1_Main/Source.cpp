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

int PrintTable(studentData studentList[], int& studentCount)
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
			if (studentList[j].surname[0] > studentList[j + 1].surname[0]) 
			{
				swap(studentList, j, j + 1);
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
}

void SortSubject(studentData studentList[], int studentCount)
{
	int choice = 0;

	printf_s("Sort by: \n1 - Subject A \n2 - Subject B \n3 - Subject C \n4 - Subject D \n5 - Subject E \n0 - Return \n");
	while (true)
	{
		printf_s("Enter your choice: ");
		scanf_s("%d", &choice);

		if (choice == 0)
			return;

		else if (choice > 0 && choice <= 5)
		{
			bool swapped;

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

void FindSurname(studentData studentList[], int studentCount)
{
	printf_s("Enter surname:");
	char buffer[FIO_LENGTH];
	studentData dopStudentList[STUDENT_COUNT / 5];
	int dopStudentCount = 0;

	scanf("%s", buffer);

	for (int i = 0; i < studentCount; i++)
	{
		int surnameSearchLength = strlen(buffer);
		int surnameMasLength = strlen(studentList[i].surname);
		int j = 0;
		bool flag = true;

		while (j < surnameSearchLength && j < surnameMasLength)
		{
			if (buffer[j] != studentList[i].surname[j])
			{
				flag = false;
				break;
			}
			j++;
		}

		if (flag)
		{
			dopStudentList[dopStudentCount] = studentList[i];
			dopStudentCount++;

		}
	}

	if (dopStudentCount > 0)
	{
		PrintTable(dopStudentList, dopStudentCount);

		printf_s("Press any button to continue\n");

		while (getchar() != '\n');
		getchar();
	}
	else
		printf_s("There is no such surname.\n");
}

int main()
{
	studentData studentList[STUDENT_COUNT];
	int studentCount = -1;
	int choice = 0;

	ReadTxt("Data.txt", studentList, studentCount);

	while (true)
	{
		system("cls");

		PrintTable(studentList, studentCount);
		
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
			FindSurname(studentList, studentCount);
			break;

		default:
			printf_s("Invalid value! Try again.\n");

		}
	}


	return 0;
}