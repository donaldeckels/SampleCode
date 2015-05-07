/*
Donald Eckels
Topic E Project
3/29/12

ThreeDim.cpp
*/

#include <iostream>
#include <iomanip>

#include "ThreeDim.h"

using namespace std;

/*
ThreeDim constructor
Input: Three doubles
Execution: The three double values are passed to the Shape object that is created as part of the ThreeDim
			The name is set to "3D shape", but should be overwritten because a ThreeDim object will never be
			instantiated by the user.
Output: One ThreeDim object
*/
ThreeDim::ThreeDim(double a, double x, double y)
	:Shape(a, x, y)	//instantiation of Shape object contained by ThreeDim object
{
	setName("3D shape");	//set name
}

/*
print function for ThreeDim
Input: Nothing
Execution: The ancestor's (Shape) print function is invoked, followed by displaying the area and volume 
			information that is part of the ThreeDim object.
Output: Display information to user
*/
void ThreeDim::print() const
{
	Shape::print();	//execute Shape print function
	cout << " area of " << area << "; volume of " << volume << endl;	//add ThreeDim information
}

/*
~ThreeDim (Destructor)
Input: One ThreeDim object to be destroyed
Execution: Body is empty because no special instructions are needed for destroying the ThreeDim object at the end of its scope
Output: Nothing
*/
ThreeDim::~ThreeDim()
{
}