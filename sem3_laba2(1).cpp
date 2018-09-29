// sem3_laba2(1).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "string.h"
#include <iostream>

#pragma warning(disable:4996)

int convert(int dec)
{
	if (dec == 0)
	{
		return 0;
	}
	else
	{
		return (dec % 2 + 10 * convert(dec / 2));
	}
}

int main()
{
	FILE *inFile;
	inFile = fopen("file_out.bin", "r");

	char buffer[256];			//баффер
	unsigned int lines;			//количество строк
	int size;					//размер файла
	int line_size;				//длина строки
	int number_buffer;
	int number;

	fseek(inFile, 0, SEEK_END);
	size = ftell(inFile);
	rewind(inFile);

	fread(buffer, sizeof(int), 1, inFile);

	lines = static_cast<unsigned int>(static_cast<unsigned char>(buffer[0]));
	lines = lines + static_cast<unsigned int>(static_cast<unsigned char>(buffer[1])) *256;
	lines = lines + static_cast<unsigned int>(static_cast<unsigned char>(buffer[2])) * 65536;
	lines = lines + static_cast<unsigned int>(static_cast<unsigned char>(buffer[3])) * 16777216;

	line_size = (size - 4) / lines;
	
	std::cout << "File size: " << size << std::endl;

	std::cout << "File:" << std::endl;

	std::cout << line_size << std::endl;

	while (fread(buffer, sizeof(char), line_size, inFile) != NULL)
	{
		//buffer[line_size] = '\0';
		//std::cout << buffer;
		
		for (int i = 0; i < line_size; i++)
		{
			number_buffer = static_cast<unsigned int>(static_cast<unsigned char>(buffer[i]));
			std::cout << convert(number_buffer) << " ";

			//std::cout << static_cast<unsigned int>(static_cast<unsigned char>(buffer[i])) << " ";
		}

		std::cout << std::endl;

	}


		std::cout << std::endl;

	fclose(inFile);
	system("pause");
	return 0;
}
