/*
Donald Eckels
Topic E Project
3/29/12

Tetrahedron.cpp
*/

#include <iostream>
#include <cmath>

#include "Tetrahedron.h"

using namespace std;

/*
Tetrahedron constructor
Input: Three doubles
Execution: The three double values are passed to the TwoDim object that is created as part of the Tetrahedron object
			The area is calculated, verified to be positive, and assigned.
			The volume is calculated, verified to be positive, and assigned. The name is set to "Tetrahedron".
Output: One Tetrahedron object
*/
Tetrahedron::Tetrahedron(double a, double x, double y)
	:ThreeDim( a, x, y)	//initialization list to define ThreeDim object
{
	
	setArea( Area() );		//set area

	setVolume( Volume() );	//set volume

	setName("Tetrahedron");			//set name as Tetrahedron
}

/*
print function for Tetrahedron
Input: Nothing
Exectuion: Calls TwoDim print function. Because there are no special instructions for displaying Tetrahedron,
			nothing else is executed
Output: Nothing
*/
void Tetrahedron::print() const
{
	ThreeDim::print();	//execute ThreeDim print function
	cout << endl;
}

/*
Area
Input: One double
Execution: The area of the Tetrahedron is calculated (square root of three times side squared). The value is verified to be positive and
			returned.
Output: one double
*/
double Tetrahedron::Area()
{
	double area;

	double side( getSide() );

	area = ( pow(3.0, 0.5) * side * side );	//surface area of a tetrahedron is equal to four triangles, or (square root of 3) * x^2

	checkVal(area);

	return area;
}

/*
Area
Input: One double
Execution: The volume of the Tetrahedron is calculated (suqare root of two divided by twelve times side cubed). The value is verified to be positive and
			returned.
Output: one double
*/
double Tetrahedron::Volume()
{
	double volume;

	double side( getSide() );

	volume = ( pow(2.0, 0.5) / 12 * side * side * side );	//volume of a tetrahedron is ( (square root of 2)/ 12 ) * x^3

	checkVal( volume );

	return volume;
}

/*
~Tetrahedron (Destructor)
Input: One Tetrahedron object to be destroyed
Execution: Body is empty because no special instructions are needed for destroying the Tetrahedron object at the end of its scope
Output: Nothing
*/
Tetrahedron::~Tetrahedron()
{
}