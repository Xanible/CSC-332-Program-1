#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

void randomizeArray(int array[][3]) {	
	// Seed random number generator. 
	srand((unsigned)time(NULL));

	// A random number in the range of 1 to 100,000 is assigned.
	for(int i=0;i < 100;i++) {
		array[i][0] = rand() % 100000 + 1;
		array[i][1] = rand() % 100000 + 1;
	}
}

int euclids(int a, int b) {
	// Preprocessing to verify a and b
	if(a < 0) {
		a = a * -1;
	}
	if(b < 0) {
		b = b * -1;
	}
	
	int remainder, quotient;
	remainder = 1;
	
	// While loop for the algorithm
	while(remainder != 0) {
		quotient = a/b;
		remainder = a%b;
		a =b;
		b = remainder;
	}
	
	return a;
}

int improved_euclids(int a, int b) {
	// Preprocessing for a and b
	if(b < 0) {
		b = b * -1;
	}
	
	if(a < b) {
		int temp = a;
		a = b;
		b = temp;
	}
	
	int remainder, quotient;
	remainder = 1;
	
	// The loop and if statements to perform the algorithm
	while(remainder != 0) {
		remainder = a -b;
			
		if (remainder > b) {
			remainder = remainder - b;
			
			if (remainder > b) {
				remainder = remainder - b;
					
				if (remainder > b) {
					remainder = a - b * (a/b);
				}
			}
		}
			
		a =b;
		b = remainder;
	}
	
	return a;	
}

// This function creates a text file for creating the .xls files
void output_results(ofstream &output,int pairs[][3], double times[]) {
	output << "Number 1\tNumber 2\tTheir GCD\tTime Spent(Millieconds) \n";
	for(int i = 0; i<100;i++) {
		output << pairs[i][0] << "\t\t" << pairs[i][1] << "\t\t" << pairs[i][2] << "\t\t" << times[i] << "\n";
	}
}

// This function creates a text file for creating the .xls files
void output_stats(ofstream &output, double times[]) {
	double max, min, avg, median;
	
	// the time values are sorted highest to lowest
	for(int i = 0; i < 99; i++) {
		for(int j=i+1; j < 100; j++) {
			if(times[i] < times[j]) {
				double temp = times[i];
				times[i] = times[j];
				times[j] = temp;
			}
		}
	}
	
	// Assign max and min
	max = times[0];
	min = times[99];
	
	// Calculate median
	median = (times[49] + times[50])/2;
	
	// Calculate average
	avg = 0;
	for(int i = 0; i < 100; i++) {
		avg += times[i];
	}
	avg = avg/100;
	
	output << "Statistics\tMilliseconds\n";
	output << "Maximium\t" << max << "\nMinimum\t\t" << min << "\nAverage\t\t" << avg << "\nMedian\t\t" << median;
	
}

void generate_conclusions(double etimes[], double itimes[]) {
	string junk = "Conclusions.txt";
	ofstream conclusions(junk.c_str());
	int wins = 0;
	double avg = 0;
	
	// Compare times between the two algorithms
	for(int i = 0;i < 100;i++) {
		if(etimes[i] > itimes[i]) {
			// If improved time is lower, add to wins and use it for the avg
			wins++;
			avg += (etimes[i] - itimes[i]);	
		}
	}
	
	// Finish calculating average
	avg = avg/wins;
	
	conclusions << "Out of 100 pairs of integers, the improved(?)"
		<<" Euclid's algorithm outperformed the original one in " 
		<< wins << " pairs; and the average saved/wasted time for"
		<< " one pair of integers was " << avg << " milliseconds.";

	conclusions.close();
}

int main(int argc, char** argv) {
	// Initialize the arrays and other variables
	int pairs[100][3] = {};
	double etimes[100] = {};
	double itimes[100] = {};
	string euclidsResults = "Original_Euclids_Results.txt";
	string euclidsStats = "Original_Euclids_Statistics.txt";
	string impStats = "Improved_Euclids_Statistics.txt";
	string impResults = "Improved_Euclids_Results.txt";
	
	// Open output files
	ofstream eRfile (euclidsResults.c_str());
	ofstream iSfile (impStats.c_str());
	ofstream eSfile (euclidsStats.c_str());
	ofstream iRfile (impResults.c_str());
	
	// Randomize values in array.
	randomizeArray(pairs);

	// Euclids Algrotihm 
	for(int i = 0; i<100;i++) {
		// start chrono timer
		auto start = std::chrono::high_resolution_clock::now();
		
		pairs[i][2] = euclids(pairs[i][0],pairs[i][1]);
		
		// stop chrono timer
		auto finish = std::chrono::high_resolution_clock::now();
		
		// make sure enough time has passed for the timer to have registered change
		while(finish == start) {
			finish = std::chrono::high_resolution_clock::now();
		}
		
		// calculate elapsed time and add to array
		std::chrono::duration<double, std::milli> elapsed = finish - start;
		etimes[i] = elapsed.count();
		
	}
	
	
	// Improved Euclids Algorithm
	for(int i = 0; i<100;i++) {
		// start timer
		auto start = std::chrono::high_resolution_clock::now();
		
		pairs[i][2] = improved_euclids(pairs[i][0],pairs[i][1]);
		
		// stop timer
		auto finish = std::chrono::high_resolution_clock::now();
		
		// make sure enough time has passed and timer has changed
		while(finish == start) {
			finish = std::chrono::high_resolution_clock::now();
		}
		
		// calculate elapsed and add to array
		std::chrono::duration<double, std::milli> elapsed = finish - start;
		itimes[i] = elapsed.count();
	}
	
	// Generate Conclusions
	generate_conclusions(etimes, itimes);
	
	// Output results into text file for viewing
	output_results(iRfile,pairs,itimes);
	output_stats(iSfile,itimes);
	output_results(eRfile,pairs,etimes);
	output_stats(eSfile,etimes);
	
	// close files
	eSfile.close();
	eRfile.close();
	iSfile.close();
	iRfile.close();
	
	return 0;
}
