#include "assert.h"
#include "stdio.h"
#include "types.h"
#include "math.h"
#include "Windows.h"

#include "help.h"

#include "day6.cpp"

int main(int args, char** argv)
{
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;

	printf("------- Advent of code 2022 -------\n");
	QueryPerformanceFrequency(&Frequency); 
	QueryPerformanceCounter(&StartingTime);

	run(args, argv);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	printf("-----------------------------------\n");
	printf("Finished in %llds %lldms %lldus", ElapsedMicroseconds.QuadPart / 1000000,
											  ElapsedMicroseconds.QuadPart % 1000000 / 1000,
											  ElapsedMicroseconds.QuadPart % 1000000 % 1000);
	return 0;
};