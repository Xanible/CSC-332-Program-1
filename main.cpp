#include <iostream>
#include <time.h>


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
