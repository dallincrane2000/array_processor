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
Dallin Gomez	   2021-11-28		  5.0 Made mode and histogram functions
Dallin Gomez	   2021-12-01		  6.0 made mode work using vectors
Dallin Gomez	   2021-12-02		  7.0 fixed histogram error
----------------------------------------------------------------------------- */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

void array_fill(ifstream &fin, int &SIZE, long int numbers[]);
long int points(int &count);
long int low(int &SIZE, long int numbers[]);
long int high(int &SIZE, long int numbers[], long int max);
long int total(int &SIZE, long int numbers[], long int &total_value);
double average(int &SIZE, long int numbers[], long int &total_value, double &average);
double std_Dev(double &average, int &count, long int numbers[]);
void sorting(long int numbers[], int &count, long int numbers_sort[], long int max);
double median(int &count, long int numbers_sort[]);
long int mode(int &count, long int numbers_sort[], ostream &out);
void histogram(long int numbers[], int &count, ostream &out);
void output_file(long int points_return, long int low_return, long int high_return, long int total_return, double average_return, double std_Dev_return, double median_return, ostream &out);
void file_setup(ofstream &fout);

// Global constant
const int ARRAY_SIZE = 500;
const string PROGRAMMER_NAME = "Dallin Gomez";

/*-----------------------------------------------------------------------------
FUNCTION:          main()
DESCRIPTION:       runs the appropriate functions and sets up the file
RETURNS:           0
NOTES:             
------------------------------------------------------------------------------- */

int main()
{
	ifstream fin;
	ofstream fout;
	string filename;
	long int total_value = 0;
	int count;
	long int numbers[ARRAY_SIZE], max, numbers_sort[ARRAY_SIZE];
	double mean;
	long int points_return, low_return, high_return, total_return, modes_return;
	double median_return, std_Dev_return, average_return;

	// Asks what the files name is and opens a file with that name
	cout << "input file: ";
	cin >> filename;
	cout << endl;
	fin.open(filename);

	// if the file exists it runs this if not it displays file not found
	if (fin){
		array_fill(fin, count, numbers);
		points_return = points(count);
		low_return = low(count, numbers);
		high_return = high(count, numbers, max);
		total_return = total(count, numbers, total_value);
		average_return = average(count, numbers, total_value, mean);
		std_Dev_return = std_Dev(mean, count, numbers);
		sorting(numbers, count, numbers_sort, max);
		median_return = median(count, numbers_sort);
		mode(count, numbers_sort, cout);
		histogram(numbers, count, cout);
		file_setup(fout);
		output_file(points_return, low_return, high_return, total_return, average_return, std_Dev_return, median_return, fout);
		mode(count, numbers_sort, fout);
		histogram(numbers, count, fout);
	} else {
		cout << "File not found" << endl;
	}

	// closes the .txt file
	fin.close();
	fout.close();

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
NOTES:             got help from http://www.cplusplus.com/forum/beginner/115599/
c++ from control structures through objects by Tony Gaddis page: 283.
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
RETURNS:           long int
NOTES:             
------------------------------------------------------------------------------- */
long int points(int &count)
{
	cout << "No. points: " << count << endl;

	return count;
}

/*-----------------------------------------------------------------------------
FUNCTION:          low()
DESCRIPTION:       finds the lowest value in an array and displays it
RETURNS:           long int
NOTES:             
------------------------------------------------------------------------------- */
long int low(int &count, long int numbers[])
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

	return min;
}
/*-----------------------------------------------------------------------------
FUNCTION:          high()
DESCRIPTION:       finds the highest value in an array and displays it
RETURNS:           long int
NOTES:             
------------------------------------------------------------------------------- */
long int high(int &count, long int numbers[], long int max)
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

	return max;
}
/*-----------------------------------------------------------------------------
FUNCTION:          total()
DESCRIPTION:       finds the total and displays it
RETURNS:           long int
NOTES:            
------------------------------------------------------------------------------- */
long int total(int &count, long int numbers[], long int &total_value)
{
	// Adds each number to the total_value 
	for (int i = 0; i < count; i++){
		total_value += numbers[i];
	}

	// Displays the total
	cout << "Sum  Total: " << total_value << endl;

	return total_value;
}
/*-----------------------------------------------------------------------------
FUNCTION:          average()
DESCRIPTION:       finds the average and displays it
RETURNS:           double
NOTES:             
------------------------------------------------------------------------------- */
double average(int &count, long int numbers[], long int &total_value, double &mean)
{
	double average;

	// divides the total value by the array size and sets that equal to average
	average = ((double)total_value/(double)count);

	// Displays the average
	cout << "The Avg is: " << average << endl;

	return average;

	mean = average;
}
/*-----------------------------------------------------------------------------
FUNCTION:          std_Dev()
DESCRIPTION:       finds the average and displays it
RETURNS:           double
NOTES:             
------------------------------------------------------------------------------- */
double std_Dev(double &mean, int &count, long int numbers[])
{
	double dev = 0;

	for(int i = 0; i < count; i++) {
        dev += pow((numbers[i] - mean), 2);
    }

	dev = sqrt(dev/count);

	cout << "Std Dev is: " << dev << endl;

	return dev;
}
/*-----------------------------------------------------------------------------
FUNCTION:          sorting()
DESCRIPTION:       bubble sorts the code
RETURNS:           void
NOTES:             bubble search from 
c++ from control structures through objects by Tony Gaddis page: 477.
------------------------------------------------------------------------------- */
void sorting(long int numbers[], int &count, long int numbers_sort[], long int max)
{
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
}
/*-----------------------------------------------------------------------------
FUNCTION:          median()
DESCRIPTION:       finds the median and displays it
RETURNS:           double
NOTES:             
------------------------------------------------------------------------------- */
double median(int &count, long int numbers_sort[])
{
	double median;

	// Calculates median from the sorted data
	if((count/2) % 2 == 0){
		//even
		median = (double)(numbers_sort[(count - 1) / 2] + numbers_sort[count / 2]) / 2.0;
	} else {
		//odd
		median = (double)numbers_sort[count / 2];
	}
	
	// Displays median
	cout << "Median  is: " << median << endl;

	return median;
}
/*-----------------------------------------------------------------------------
FUNCTION:          mode()
DESCRIPTION:       finds the mode and displays it
RETURNS:           long int
NOTES:             max_element from https://www.cplusplus.com/reference/algorithm/max_element/
unique from https://www.cplusplus.com/reference/algorithm/unique/?kw=unique
------------------------------------------------------------------------------- */
long int mode(int &count, long int numbers_sort[], ostream &out)
{
	// Just store the modes in the vector using pushback
	vector<long int>modes;
	vector<long int>modes_results;
	int freq = 0;
	long int modes_high = 0;
	
	// goes through every value in the array
	for (int i = 0; i < count; i++)
	{
		// secondary goes through every value in the array
		for (int n = 0; n < count; n++)
		{
			// compares every value in the array to each other
			if (numbers_sort[i] == numbers_sort[n])
			{
				freq++;
				modes.insert(modes.begin() + i, freq);
			}
		}
		// Clears freq for next number to compare
		freq = 0;
	}
	
	// Finds the highest value in the vector and sets it to modes_high
	modes_high = *max_element(modes.begin(), modes.end());

	// fills a vector with the values that match the locations of the modes
	for (int x = 0; x < count; x++)
	{
		if (modes.at(x) == modes_high)
		{
			modes_results.push_back (numbers_sort[x]);
		}
	}
	
	// Deletes duplicates
	modes_results.erase( unique( modes_results.begin(), modes_results.end() ), modes_results.end() );

	out << "modes  are: ";

	// Prints
	for (int b = 0; b < modes_results.size(); b++)
	{
		out << modes_results.at(b) << " ";
	}

	out << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          histogram()
DESCRIPTION:       finds the mode and displays it
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void histogram(long int numbers[], int &count, ostream &out)
{
	int star = 0;
	out << endl << "Histogram: " << endl << endl;
	
	// counts up 100 for each of the categories
	for (int i = 1; i < 1000; i = (i+100))
	{
		// Counts up until it reaches the end of the array
		for (int n = 0; n < count; n++)
		{
			// if the value of numbers is greater than i which is the category and is less than i+100 which is the next category then it adds a star
			if (numbers[n] >= i && numbers[n] < (i+100))
			{
				star++;
			}
		}
		
		if (i == 901){
			out << setw(3) << i << "- " << (i+99) << ": " << setfill ('*') << setw(star+1) << " " << endl;
			out << setfill(' ');
		} else {
			out << setw(4) << i << "- " << (i+100) << ": " << setfill ('*') << setw(star+1) << " " << endl;
			out << setfill(' ');
		}
		star = 0;
	}
}
/*-----------------------------------------------------------------------------
FUNCTION:          output_file()
DESCRIPTION:       sends data to the output file
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void output_file(long int points_return, long int low_return, long int high_return, long int total_return, double average_return, double std_Dev_return, double median_return, ostream &out)
{
	out << "No. points: " << points_return << endl;
	out << "The Min is: " << low_return << endl;
	out << "The Max is: " << high_return << endl;
	out << "Sum  Total: " << total_return << endl;
	out << "The Avg is: " << average_return << endl;
	out << "Std Dev is: " << std_Dev_return << endl;
	out << "Median  is: " << median_return << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          file_setup()
DESCRIPTION:       configures the output file
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void file_setup(ofstream &fout)
{
	string out_filename;

	cout << endl << "Output filename: ";
	cin >> out_filename;
	cout << endl;
	fout.open(out_filename);
}
