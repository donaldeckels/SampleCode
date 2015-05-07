/* Donald Eckels
Topic A Project
1/27/2012

This program compiles and runs with no errors.
Extra credit 1 and 2 have also been added to the program.

TopicAII.cpp

This program is designed to perform the following steps:
1) Ask the user to input a number. Any real value will be accepted.
2) The value input by the user is checked to verify it is a number.
3) If it is not a number, the user is notified that their input is invalid and will be asked to input a number again. This will repeat as necessary.
4) The user is asked for a second number. When this number is verified, it is also checked to verify it is not zero.
5) The first number is divided into the second number and the result is stored.
6) The division and result are displayed.
7) the user is asked if they would like to repeat the program.*/

#include <iostream>
#include <iomanip>
#include <string>
#include "TopicALibII.h"

using namespace std;


int main()
{
	double *x;		//create x, which is a pointer to a double
	x = new double;	//allocate a double in the heap to x

	double **y;		//create y, which is a pointer to a pointer to a double
	y = new double*;	//allocate a pointer to a double in the heap for y
	*y = new double;	//allocate a double in the heap to the pointer that y points to

	double *q;		//create q, which is a pointer to a double
	q = new double;	//allocate a double in the heap to q

	double ***z;	//create z, which is a pointer to a pointer to a pointer to a double
	z = new double**;	//allocate a pointer to a pointer to a double in the heap
	*z = &q;		//give the pointer that z points towards the address of q.

	char repeat; 
	
	do{
		Input(x, y);	//input function called to fill x and y
		
		***z = Divide (x, y);	//divide function is called and value is assigned to ***z

		Display (x, y, z);		//display the values

		cout << "Repeat (y/n) -->  ";	//ask for and receive input for wether or not the user will want to repeat
		
		cin >> repeat;
		
	}while( repeat == 'Y' || repeat == 'y'); //only quit the loop if the user specified they do not want to repeat

	delete x;	//deallocate dynamic memory
	delete *y;
	delete y;
	delete q;
	delete z;

	return 0; //end main
}