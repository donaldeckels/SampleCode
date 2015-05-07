/*
Donald Eckels
Topic E Project
3/29/12

Triangle.cpp
*/

#include <iostream>
#include <cmath>

#include "Triangle.h"

using namespace std;

/*
Triangle constructor
Input: Three doubles
Execution: The three double values are passed to the TwoDim object that is created as part of the Triangle object
			The area is calculated and assigned. The name is set to "Triangle".
Output: One Triangle object
*/
Triangle::Triangle(double a, double x, double y)
	:TwoDim(a, x, y)	//initialization list to define TwoDim object
{
	setArea( Area() );	//set the area as calculated by the Area function.

	setName("Triangle");		//set name as Triangle
}

/*
print function for Triangle
Input: Nothing
Exectuion: Calls TwoDim print function. Because there are no special instructions for displaying Triangle,
			nothing else is executed
Output: Nothing
*/
void Triangle::print() const
{
	TwoDim::print();	//execute TwoDim print function
	cout << endl;
}

/*
Area
Input: One double
Execution: The area of the Triangle is calculated ( (square root of 3) / 4) * base^2 ). The value is verified to be positive and
			saved as the area of the Triangle.
Output: None
*/
double Triangle::Area()
{
	double area;

	double side( getSide() );
	
	area = ( pow(3.0, 0.5) / 4 * pow( side, 2) );	//area of an equilateral triangle is ( (square root of 3) / 4) * base^2 )

	return area;
}

/*
~Triangle (Destructor)
Input: One Triangle object to be destroyed
Execution: Body is empty because no special instructions are needed for destroying the Triangle object at the end of its scope
Output: Nothing
*/
Triangle::~Triangle()
{
}
