/*
Donald Eckels
Topic E Project
3/29/12

Square.cpp
*/

#include <iostream>

#include "Square.h"

using namespace std;

/*
Square constructor
Input: Three doubles
Execution: The three double values are passed to the TwoDim object that is created as part of the Square object
			The area is calculated, verified to be positive, and assigned. The name is set to "Square".
Output: One Square object
*/
Square::Square(double a, double x, double y)
	:TwoDim(a, x, y)	//initialization list to define TwoDim object
{
	setArea(Area());

	setName("Square");		//set name as Square
}

/*
print function for Square
Input: Nothing
Exectuion: Calls TwoDim print function. Because there are no special instructions for displaying Square,
			nothing else is executed
Output: Nothing
*/
void Square::print() const
{
	TwoDim::print();	//execute TwoDim print function
	cout << endl;
}

/*
Area
Input: One double
Execution: The area of the Square is calculated (side squared). The value is verified to be positive and
			returned.
Output: None
*/
double Square::Area()
{
	double area;

	double side( getSide() );
	
	area = (side * side);	//area of sphere is pi*rad^2

	checkVal(area);

	return area;
}

/*
~Square (Destructor)
Input: One Square object to be destroyed
Execution: Body is empty because no special instructions are needed for destroying the Square object at the end of its scope
Output: Nothing
*/
Square::~Square()
{
}