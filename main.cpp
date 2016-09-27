#include <iostream>
#include <time.h>

void randomizeArray(int array[], int length)
{
	srand((unsigned)time(NULL));			// Seed random number generator. 

	int i = 0;
	do
	{
		array[i] = rand() % 100000 + 1;		// A random number in the range of 1 to 100,000 is assigned.
		i++;
	} while (i < length);
}

int main(int argc, char** argv) {
	clock_t startTime, endTime;
	// Randomize values in array.
	randomizeArray(array, length);

	// Time array sort.
	startTime = clock();			// Get starting time.
	selectionSort(array, length);	// Sort array.
	endTime = clock();				// Get ending time.
	return 0;
}
