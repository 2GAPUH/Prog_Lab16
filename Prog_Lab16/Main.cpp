#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define ARRAY_SIZE 100 

struct segment
{
	double X1, Y1, X2, Y2;
};

struct storage
{
	double minLength, maxLength;
	int minPosition, maxPosition;
};

struct borders
{
	double leftBorder, rightBorder;
};

borders GetBorders()
{
	borders user;
	do {
		printf_s("Enter left border: ");
		scanf_s("%lf", &user.leftBorder);
		printf_s("Enter left border: ");
		scanf_s("%lf", &user.rightBorder);
		if (user.leftBorder < user.rightBorder) return user;
		printf_s("The right border must be greater than the left! Try again.\n");
	} while (true);

}

void GenerateRandomSegment(segment Array[], int userArraySize, borders user)
{
	int range = user.rightBorder - user.leftBorder + 1;
	for (int i = 0;i < userArraySize; i++)
	{
		Array[i].X1 = rand() % range + user.leftBorder;
		Array[i].Y1 = rand() % range + user.leftBorder;
		Array[i].X2 = rand() % range + user.leftBorder;
		Array[i].Y2 = rand() % range + user.leftBorder;
	}

	printf_s("Successful generation!\n");
}


storage GetLenghtOfSegment(segment Array[], int userArraySize)
{
	double tempF = 0, tempX, tempY;
	storage answer;
	answer.maxLength = 0;
	answer.minLength = LONG_MAX;

	for (int i = 0; i < userArraySize; i++)
	{
		tempX = Array[i].X2 - Array[i].X1;
		tempY = Array[i].Y2 - Array[i].Y1;
		tempF = sqrt(tempX * tempX + tempY * tempY);
		if (tempF < answer.minLength)
		{
			answer.minLength = tempF;
			answer.minPosition = i;
		}
		if (tempF > answer.maxLength)
		{
			answer.maxLength = tempF;
			answer.maxPosition = i;
		}

	}

	return answer;
}


int GettingArraySize()
{
	int userArraySize;

	do {
		printf_s("Enter number of segment(1 < N < %d): ", ARRAY_SIZE);
		scanf_s("%d", &userArraySize);
		if (userArraySize > 1 && userArraySize < ARRAY_SIZE) break;
		printf_s("Invalid value! Try again.\n");
	} while (true);

	return userArraySize;
}


int ManualArrayFilling(segment Array[], int UserArraySize)
{
	for (int i = 0; i < UserArraySize; i++)
	{
		printf_s("Enter X start: ");
		scanf_s("%lf", &Array[i].X1);
		printf_s("Enter Y start: ");
		scanf_s("%lf", &Array[i].Y1);
		printf_s("Enter X end: ");
		scanf_s("%lf", &Array[i].X2);
		printf_s("Enter Y end: ");
		scanf_s("%lf", &Array[i].Y2);
	}

	printf_s("Successful filling!\n");

	return 0;
}

int TextFileArrayFilling(segment Array[])
{
	FILE* FileInput;
	char FileName[40];
	int UserArraySize;

	printf_s("Enter name of the file(file.txt): ");
	while (getchar() != '\n');
	gets_s(FileName);

	if (fopen_s(&FileInput, FileName, "r") != 0) 
	{
		printf_s("Error opening file! \n");
		return 0;
	}

	fscanf_s(FileInput, "%d", &UserArraySize);

	for (int i = 0; i < UserArraySize; i++)
	{
		fscanf_s(FileInput, "%lf", &Array[i].X1);
		fscanf_s(FileInput, "%lf", &Array[i].Y1);
		fscanf_s(FileInput, "%lf", &Array[i].X2);
		fscanf_s(FileInput, "%lf", &Array[i].Y2);
	}

	printf_s("Successful filling!\n");

	fclose(FileInput);

	return UserArraySize;
}


int BinFileArrayFilling(segment Array[])
{
	FILE* FileInput;
	char FileName[40];
	int UserArraySize;

	printf_s("Enter name of the file(file.bin): ");
	while (getchar() != '\n');
	gets_s(FileName);

	if (fopen_s(&FileInput, FileName, "rb") != 0)
	{
		printf_s("Error opening file! \n");
		return 0;
	}

	fread(&UserArraySize, sizeof(int), 1, FileInput);

	fread(Array, sizeof(segment), UserArraySize, FileInput);

	printf_s("Successful filling!\n");

	fclose(FileInput);

	return UserArraySize;
}



int TextFileArraySave(segment Array[], int UserArraySize)
{
	FILE* FileOutput;
	char FileName[40];

	printf_s("Enter name of the file(file.txt): ");
	while (getchar() != '\n');
	gets_s(FileName);

	if (fopen_s(&FileOutput, FileName, "w") != 0)
	{
		printf_s("Error opening file! \n");
		return 0;
	}

	fprintf_s(FileOutput, "%d\n", UserArraySize);

	for (int i = 0; i < UserArraySize; i++)
	{
		fprintf_s(FileOutput, "%lf ", Array[i].X1);
		fprintf_s(FileOutput, "%lf ", Array[i].Y1);
		fprintf_s(FileOutput, "%lf ", Array[i].X2);
		fprintf_s(FileOutput, "%lf ", Array[i].Y2);
	}

	printf_s("Successful array saving!\n");

	fclose(FileOutput);

	return 0;
}


int BinFileArraySave(segment Array[], int UserArraySize)
{
	FILE* FileOutput;
	char FileName[40];

	printf_s("Enter name of the file(file.bin): ");
	while (getchar() != '\n');
	gets_s(FileName);

	if (fopen_s(&FileOutput, FileName, "wb") != 0)
	{
		printf_s("Error opening file! \n");
		return 0;
	}

	fwrite(&UserArraySize, sizeof(int), 1, FileOutput);

	fwrite(Array, sizeof(segment), UserArraySize, FileOutput);

	printf_s("Successful array saving!\n");

	fclose(FileOutput);

	return 0;
}


void ArrayPrinting(segment Array[], int UserArraySize)
{
	for (int i = 0; i < UserArraySize; i++)
	{
		printf_s("Segment X start = %lf\n", Array[i].X1);
		printf_s("Segment Y start = %lf\n", Array[i].Y1);
		printf_s("Segment X end = %lf\n", Array[i].X2);
		printf_s("Segment Y end = %lf\n", Array[i].Y2);
	}
}


int main()
{
	int TypeOfFilling, TypeOfOutputing;
	segment Array[ARRAY_SIZE] = {};
	int UserArraySize;
	storage answer;
	int seed;
	borders user;
	srand(seed = time(NULL));



	printf_s("0 - Continue \n1 - Text file Array filling \n2 - Bin file Array filling \n3 - Manual Array filling \n4 - Random Array Filling \n");
	do {
		printf_s("Enter type of filling Array: ");
		scanf_s("%d", &TypeOfFilling);
		switch (TypeOfFilling)
		{
		case 0: 
			break;
		case 1:
			UserArraySize = TextFileArrayFilling(Array); break;
		case 2:
			UserArraySize = BinFileArrayFilling(Array); break;
		case 3:
			UserArraySize = GettingArraySize(); 
			ManualArrayFilling(Array, UserArraySize); break;
		case 4:
			UserArraySize = GettingArraySize();
			user = GetBorders(); 
			GenerateRandomSegment(Array, UserArraySize, user); break;

		default: 
			printf_s("Invalid value! Try again.\n");
		}
	
	} while (TypeOfFilling != 0);

	answer = GetLenghtOfSegment(Array, UserArraySize);

	printf_s("Min length of segment: %lf\n", answer.minLength);
	printf_s("It's position: X1:%lf Y1:%lf X2:%lf Y2:%lf\n", Array[answer.minPosition].X1, Array[answer.minPosition].Y1, Array[answer.minPosition].X2, Array[answer.minPosition].Y2);
	printf_s("Max length of segment: %lf\n", answer.maxLength);
	printf_s("It's position: X1:%lf Y1:%lf X2:%lf Y2:%lf\n", Array[answer.maxPosition].X1, Array[answer.maxPosition].Y1, Array[answer.maxPosition].X2, Array[answer.maxPosition].Y2);


	printf_s("0 - Finish program \n1 - Array printing \n2 - Text file Array save \n3 - Bin file Array save\n");
	do {

		printf_s("Enter type of outputing: ");
		scanf_s("%d", &TypeOfOutputing);
		switch (TypeOfOutputing)
		{
		case 0: break;
		case 1:ArrayPrinting(Array, UserArraySize);  break;
		case 2:TextFileArraySave(Array, UserArraySize);  break;
		case 3:BinFileArraySave(Array, UserArraySize);  break;

		default:printf_s("Invalid calue!Try again.\n");break;
		}
	} while (TypeOfOutputing != 0);
		
	return 0;
}