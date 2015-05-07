/*
Donald Eckels
Topic E Project
3/29/12

TwoDim.cpp
*/
#include <iostream>
#include <iomanip>

#include "TwoDim.h"

using namespace std;

/*
TwoDim constructor
Input: Three doubles
Execution: The three double values are passed to the Shape object that is created as part of the TwoDim
			The name is set to "2D shape", but should be overwritten because a TwoDim object will never be
			instantiated by the user.
Output: One TwoDim object
*/

TwoDim::TwoDim(double a, double x, double y)
	:Shape(a, x, y)	//initialization list to define Shape object
{
	setName("2D shape");	//set name
}

/*
print function for TwoDim
Input: Nothing
Execution: The ancestor's (Shape) print function is invoked, followed by displaying the area information that
			is part of the TwoDim object.
Output: Display information to user
*/

void TwoDim::print() const
{
	Shape::print();		//Print the Shape information
	cout << " area of " << area << endl;	//Print area information

}


/*
~TwoDim (Destructor)
Input: One TwoDim object to be destroyed
Execution: Body is empty because no special instructions are needed for destroying the TwoDim object at the end of its scope
Output: Nothing
*/
TwoDim::~TwoDim()
{
}