#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*Пусть задано N отрезков с помощью координат их концов.
Определить длины наибольшего и наименьшего из них, также
вывести их координаты.*/


//Структура с координатами отрезка
struct segmentCoordinates
{
	int xStart, yStart, xFinal, yFinal;
};


//Cтруктура позиции в массиве и координат
struct desiredSegment
{
	int position;
	double length;
};


//Нахождение длины отрезка
double lengthOfSegment(int i, segmentCoordinates array[])
{
	double lengthOfSegment;

	lengthOfSegment = sqrt(pow(array[i].xStart - array[i].xFinal, 2) + pow(array[i].yStart - array[i].yFinal, 2));

	return lengthOfSegment;
}


//Вывод массива координат
void arrayPrinting(int userArraySize, segmentCoordinates arrayOfSegmentPosition[])
{
	for (int i = 0; i < userArraySize; i++)
	{
		printf("arrayOfSegmentCoordinates[%d]  ", i);
		printf("xStart = %d  ", arrayOfSegmentPosition[i].xStart);
		printf("yStart = %d  ", arrayOfSegmentPosition[i].yStart);
		printf("xFinal = %d  ", arrayOfSegmentPosition[i].xFinal);
		printf("yFinal = %d  \n", arrayOfSegmentPosition[i].yFinal);
	}
}


//Ручной ввод координат отрезков
int manualArrayFilling(int fixedSizeOfArray, segmentCoordinates arrayOfSegmentPosition[])
{
	int userArraySize;

	//Запрос количества отрезков
	do {
		printf("Enter how many segments(<100): "); scanf("%d", &userArraySize);
		if (fixedSizeOfArray < userArraySize && userArraySize < 1) printf("Invalid number!Try again. \n");
	} while (fixedSizeOfArray < userArraySize && userArraySize < 1);

	//Запрос координат отрезков
	for(int i = 0; i < userArraySize ; i++)
	{ 
		printf("Enter %d segment start coordinates: \n", i);
		printf("x = "); scanf("%d", &arrayOfSegmentPosition[i].xStart);
		printf("y = "); scanf("%d", &arrayOfSegmentPosition[i].yStart);
		printf("Enter %d segment final coordinates: \n", i);
		printf("x = "); scanf("%d", &arrayOfSegmentPosition[i].xFinal);
		printf("x = "); scanf("%d", &arrayOfSegmentPosition[i].yFinal);
	}

	//Возврат размера массива
	return userArraySize;
}


//Заполнение массива из текстового файла
int textArrayFilling(int fixedSizeOfArray, segmentCoordinates arrayOfSegmentPosition[])
{
	int userArraySize;
	FILE* userFileInput;
	char fileName[25];

	printf("Enter the name of the processed file: ");
	while (getchar() != '\n');
	gets_s(fileName);

	if (fopen_s(&userFileInput, fileName, "r") != 0)
	{
		printf("Error oppening file!");
		exit(1);
	}

	fscanf_s(userFileInput, "%d", &userArraySize);

	for (int i = 0;i < userArraySize; i++)
	{
		fscanf_s(userFileInput, "%d", &arrayOfSegmentPosition[i].xStart);
		fscanf_s(userFileInput, "%d", &arrayOfSegmentPosition[i].yStart);
		fscanf_s(userFileInput, "%d", &arrayOfSegmentPosition[i].xFinal);
		fscanf_s(userFileInput, "%d", &arrayOfSegmentPosition[i].yFinal);
	}

	fclose(userFileInput);

	return userArraySize;
}


//Заполнение массива из бинарных файлов
int binArrayFilling(int sizeOfArray)
{
	

	return sizeOfArray;
}





//Запись массива в бинарный файл
void binFileWriting()
{



}





//Обработка данных массива
int arrayProcessing(segmentCoordinates arrayOfSegmentPosition[], int userArraySize, desiredSegment answer[])
{
	double tek = 0;

	for (int i = 0; i < userArraySize; i++)
	{
		tek = lengthOfSegment(i, arrayOfSegmentPosition);

		if (tek > answer[0].length)
		{
			answer[0].position = i;
			answer[0].length = tek;
		}

		if (tek < answer[1].length)
		{
			answer[1].position = i;
			answer[1].length = tek;
		}
	}


	return 0;
}



int main()
{
	system("chcp 1251");

	const int fixedSizeOfArray = 100;
	int typeOfFilling, userArraySize;
	segmentCoordinates arrayOfSegmentPosition[fixedSizeOfArray];
	desiredSegment answer[2] = { {0, 0}, {0 , INT_MAX} };
	
	do {
		printf("Enter type of filling: \n1-From text file \n2-Manual filling \n"); scanf("%d", &typeOfFilling);
		if (typeOfFilling > 2 || typeOfFilling < 1) printf("Invalid value! Try again \n");
	} while (typeOfFilling > 2 || typeOfFilling < 1);

	switch (typeOfFilling)
	{
	case 1:userArraySize = textArrayFilling(fixedSizeOfArray, arrayOfSegmentPosition); break;
	case 2:userArraySize = manualArrayFilling(fixedSizeOfArray, arrayOfSegmentPosition); break;
	}

	arrayProcessing(arrayOfSegmentPosition, userArraySize, answer);

	printf("Maxium segment length = %lf \n", answer[0].length);
	printf("Its coordinates: \nxStart = %d \nyStart = %d \nxFinal = %d \nyFinal = %d \n", arrayOfSegmentPosition[answer[0].position].xStart,
		arrayOfSegmentPosition[answer[0].position].yStart, arrayOfSegmentPosition[answer[0].position].xFinal, arrayOfSegmentPosition[answer[0].position].yFinal);

	printf("Minium segment length = %lf \n", answer[1].length);
	printf("Its coordinates: \nxStart = %d \nyStart = %d \nxFinal = %d \nyFinal = %d \n", arrayOfSegmentPosition[answer[1].position].xStart,
		arrayOfSegmentPosition[answer[1].position].yStart, arrayOfSegmentPosition[answer[1].position].xFinal, arrayOfSegmentPosition[answer[1].position].yFinal);

	return 0;
}