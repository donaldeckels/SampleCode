/*
Donald Eckels
Topic E Project
3/29/12

Circle.cpp
*/

#include <iostream>

#include "Circle.h"

using namespace std;


/*
Circle constructor
Input: Three doubles
Execution: The three double values are passed to the TwoDim object that is created as part of the Circle object
			The area is defined and the name is set to "Circle".
Output: One Circle object
*/
Circle::Circle(double a, double x, double y)
	:TwoDim( a, x, y)	//initialization list to define TwoDim object
{
	setArea(Area());
	
	setName("Circle");			//set name as Circle
}

/*
print function for Circle
Input: Nothing
Exectuion: Calls TwoDim print function. Because there are no special instructions for displaying Circle,
			nothing else is executed
Output: Nothing
*/
void Circle::print() const
{
	TwoDim::print(); //execute TwoDim print function
	cout << endl;
}

/*
Area
Input: One double
Execution: The area of the Circle is calculated (pi times the square of the radius). The value is verified to be positive and
			returned.
Output: one double
*/
double Circle::Area()
{
	double area;

	double rad( getSide() );

	area = (3.14159 * rad * rad);	//area of sphere is pi*rad^2

	checkVal(area);

	return area;
}


/*
~Circle (Destructor)
Input: One Circle object to be destroyed
Execution: Body is empty because no special instructions are needed for destroying the Circle object at the end of its scope
Output: Nothing
*/
Circle::~Circle()
{
}