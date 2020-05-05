/**
    CS 460 Final Project MCmain.cpp
    Purpose: Approximate Pi using Leibniz' Formula

    @author Marcus Corbin
    @version 1.0 01/04/2020 
*/

// Includes
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

// Standard Namespace
using namespace std;

// Global Variables
long double sum1, newSum;

/**
    Creates a thread and uses Leibniz' Formula to calculate sum.

    @param params Passed in array from main
    @return sum of the calculated formula
*/
void *threadFunc(void *params)
{
	// Thread Variables
	long double sum;
	int n;
	
	// Bring in the values from main
	int *value = (int *)params; 

	//cout << "N value: "       << value[0] << endl; // N value
	//cout << "Total Threads: " << value[1] << endl; // Thread numbers
	cout << "Thread #: "      << value[2] << endl; // Thread #

	
	
	// For Loop to calculate Leibniz' Formula
	for (n = 0; n < value[0]/value[1]; n++)
	{
		sum = pow(-1, n) * (1.0 / (2.0*n + 1.0));
		sum1 += sum;
	}
	
	newSum = 4.0*(sum1 / value[1]); // Multiply by 4 to get Pi Sum

	cout << "The sum is: " << newSum << endl << endl; // Output current Sum
	
	pthread_exit(NULL); // End Thread
	
}

/**
    Main code that get's user input

    @param argc Contains number of arguments passed into program.
    @param argv Array of argument strings
    @return Approximation of Pi using values from user.
*/
int main( int argc, char *argv[] )
{
  int i;
  int val[3];
  
  // Let user know what the program is
  cout << "Pi Approximation using Leibniz's formula" << endl;
  cout << "----------------------------------------" << endl;
  
  cout.precision(17); // Set the precision so more decimal places are shown
  
  // Ask user for value of n
  cout << "How many (n) iterations to check?: ";
  cin  >> val[0];
  cout << endl;
  
  // Ask user how many threads to create
  cout << "How many threads to create? : ";
  cin  >> val[1];
  cout << endl;
  
  // Thread definition
  pthread_t tid[val[1]];
  
  // For loop used to create number of threads per user's input
  for (i = 0; i < val[1]; i++)
  {
	val[2] = i; // This will be used for the Thread number
	pthread_create(&tid[i], NULL, threadFunc, (void *)val); // Create a thread
	pthread_join(tid[i], NULL); // Wait till thread finishes

  }
  // Last line of terminal
  cout << endl << "Pi Approx: " << newSum << endl << endl;
  
  // End Code
  pthread_exit(NULL);
}
