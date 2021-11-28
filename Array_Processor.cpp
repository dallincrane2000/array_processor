/* -----------------------------------------------------------------------------
FILENAME:          Array_Processor.cpp
DESCRIPTION:       finds and displays the high, low, total, and average of an array
COMPILER:          MinGW  C++ compiler
NOTES:             
MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Dallin Gomez       2021-11-17         1.0 made a function that fills an array
Dallin Gomez	   2021-11-20 		  2.0 Set up the different functions needed
Dallin GOmez	   2021-11-21		  3.0 made low, high, total, and average functions
Dallin Gomez	   2021-11-26		  4.0 Made std_Dev and median functions
Dallin Gomez	   2021-11-28		  5.0 Made mode and historgram functions
----------------------------------------------------------------------------- */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

void array_fill(ifstream &fin, int &SIZE, long int numbers[]);
void points(int &count);
void low(int &SIZE, long int numbers[]);
void high(int &SIZE, long int numbers[], long int max);
void total(int &SIZE, long int numbers[], long int &total_value);
void average(int &SIZE, long int numbers[], long int &total_value, double &average);
void std_Dev(double &average, int &count, long int numbers[]);
void median(long int numbers[], int &count, long int max, long int numbers_sort[]);
void mode(long int numbers[], int &count, long int numbers_sort[]);
void histogram(long int numbers[], int &count);

const int ARRAY_SIZE = 500;

const string PROGRAMMER_NAME = "Dallin Gomez";		// Global constant

/*-----------------------------------------------------------------------------
FUNCTION:          main()
DESCRIPTION:       runs the appropriate functions and sets up the file
RETURNS:           0
NOTES:             
------------------------------------------------------------------------------- */

int main()
{
	ifstream fin;
	string filename;
	bool tf = true;
	long int total_value = 0;
	int count;
	long int numbers[ARRAY_SIZE], max, numbers_sort[ARRAY_SIZE];
	double mean;

	// Loop that ends if tf == false for file validation
	while (tf == true){
		// Asks what the files name is and opens a file with that name
		cout << "input file: ";
		cin >> filename;
		fin.open(filename);

		// if the file exists it runs this if not it displays file not found
		if (fin){
			array_fill(fin, count, numbers);
			points(count);
			low(count, numbers);
			high(count, numbers, max);
			total(count, numbers, total_value);
			average(count, numbers, total_value, mean);
			std_Dev(mean, count, numbers);
			median(numbers, count, max, numbers_sort);
			mode(numbers, count, numbers_sort);
			histogram(numbers, count);
			tf = false;
		} else {
			cout << "File not found";
		}
	}

	// closes the .txt file
	fin.close();

	cout << "Programmed by: " << PROGRAMMER_NAME << " -- ";
	cout << __DATE__ << "  " __TIME__ << endl;
	cout << endl;

	system("pause");

	return 0;
}
/*-----------------------------------------------------------------------------
FUNCTION:          array_fill()
DESCRIPTION:       fills the array with the values in the .txt file
RETURNS:           void
NOTES:             got help from http://www.cplusplus.com/forum/beginner/115599/ & the book pg. 283
------------------------------------------------------------------------------- */
void array_fill(ifstream &fin, int &count, long int numbers[])
{
	// Sets size to zero
	count = 0;

	/* Adds one value to SIZE for every line in the .txt file
	   Also adds every line into an array*/
	while (count < ARRAY_SIZE && fin >> numbers[count]){
		count++;
	}
}
/*-----------------------------------------------------------------------------
FUNCTION:          points()
DESCRIPTION:       finds the lowest value in an array and displays it
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void points(int &count)
{
	cout << "No. points: " << count << endl;
}

/*-----------------------------------------------------------------------------
FUNCTION:          low()
DESCRIPTION:       finds the lowest value in an array and displays it
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void low(int &count, long int numbers[])
{
	long int min;

	// sets min to the first number of the array
	min = numbers[0];

	// Checks if the value in min is greater than any value in the array
	for (int n = 1; n < count; n++){
		if (min > numbers[n]){
			min = numbers[n];
		}
	}

	// Displays the min
	cout << "The Min is: " << min << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          high()
DESCRIPTION:       finds the highest value in an array and displays it
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void high(int &count, long int numbers[], long int max)
{
	// sets max to the first number of the array
	max = numbers[0];

	// Checks if the value in max is less than any value in the array
	for (int n = 1; n < count; n++){
		if (max < numbers[n]){
			max = numbers[n];
		}
	}
	cout << "The Max is: " << max << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          total()
DESCRIPTION:       finds the total and displays it
RETURNS:           void
NOTES:            
------------------------------------------------------------------------------- */
void total(int &count, long int numbers[], long int &total_value)
{
	// Adds each number to the total_value 
	for (int i = 0; i < count; i++){
		total_value = total_value + numbers[i];
	}

	// Displays the total
	cout << "Sum  Total: " << total_value << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          average()
DESCRIPTION:       finds the average and displays it
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void average(int &count, long int numbers[], long int &total_value, double &mean)
{
	double average;

	// divides the total value by the array size and sets that equal to average
	average = ((double)total_value/(double)count);

	// Displays the average
	cout << "The Avg is: " << average << endl;

	mean = average;
}
/*-----------------------------------------------------------------------------
FUNCTION:          std_Dev()
DESCRIPTION:       finds the average and displays it
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void std_Dev(double &mean, int &count, long int numbers[])
{
	double dev = 0;

	for(int i = 0; i < count; i++) {
        dev += pow((numbers[i] - mean), 2);
    }

	dev = sqrt(dev/count);

	cout << "Std Dev is: " << dev << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          median()
DESCRIPTION:       finds the median and displays it
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void median(long int numbers[], int &count, long int max, long int numbers_sort[])
{
	// sort from smallest to largest
	// median is the central number in the sorted list
	double median;

	// Makes numbers_sort equal to numbers
	for (int i = 0; i < count; i++)
	{
		numbers_sort[i] = numbers[i];
	}
	
	// Bubble search
	for (max = count - 1; max > 0; max--)
	{
		for (int index = 0; index < max; index++)
		{
			if (numbers_sort[index] > numbers_sort[index + 1])
			{
				swap(numbers_sort[index], numbers_sort[index+1]);
			}
		}
	}

	// Calculates median from the sorted data
	if((count/2) % 2 == 0){
		//even
		median = (double)(numbers_sort[(count - 1) / 2] + numbers_sort[count / 2]) / 2.0;
	} else {
		//odd
		median = (double)numbers_sort[count / 2];
	}
	
	// Displays median
	cout << "Median is: " << median << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          mode()
DESCRIPTION:       finds the mode and displays it
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void mode(long int numbers[], int &count, long int numbers_sort[])
{
	long int modes;
	long int modes_max;

	for (int i = 0; i < count; i++)
	{
		int mode_count = 1;
		// runs while i is less tan count - 1 & numbers_sort is the same as the next number in the array
		while (i < count - 1 && numbers_sort[i] == numbers_sort[i+1])
		{
			mode_count++;
			i++;

			// If the count is greater than the highest number than it sets that number as the mode
			if (mode_count > modes_max)
			{
				modes_max = mode_count;
				modes = numbers_sort[i];
			}
			
		}
	}
	
	cout << "Modes  are: " << modes << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          histogram()
DESCRIPTION:       finds the mode and displays it
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void histogram(long int numbers[], int &count)
{
	cout << endl << "Histogram: " << endl << endl;
	

	for (int i = 1; i < 1000; i = (i+100))
	{
		if (i == 901){
			cout << setw(3) << i << "- " << (i+99) << ": " << endl;
		} else {
			cout << setw(4) << i << "- " << (i+100) << ": " << endl;
		}
	}
	
}