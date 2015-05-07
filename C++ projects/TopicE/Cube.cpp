/*
Donald Eckels
Topic E Project
3/29/12

Cube.cpp
*/
#include <iostream>

#include "Cube.h"

using namespace std;

/*
Cube constructor
Input: Three doubles
Execution: The three double values are passed to the TwoDim object that is created as part of the Cube object
			The area is calculated, verified to be positive, and assigned.
			The volume is calculated, verified to be positive, and assigned. The name is set to "Cube".
Output: One Cube object
*/
Cube::Cube(double a, double x, double y)
	:ThreeDim( a, x, y)	//initialization list to define ThreeDim object
{

	setArea( Area() );	//set area

	setVolume( Volume() ); //set volume
	
	setName("Cube");		//set name as Cube
}

/*
print function for Cube
Input: Nothing
Exectuion: Calls TwoDim print function. Because there are no special instructions for displaying Cube,
			nothing else is executed
Output: Nothing
*/
void Cube::print() const
{
	ThreeDim::print();	//execute ThreeDim print function
	cout << endl;
}

/*
Area
Input: One double
Execution: The area of the Cube is calculated (side squared times six). The value is verified to be positive and
			returned.
Output: one double
*/
double Cube::Area()
{
	double area;

	double side( getSide() );

	area = (side * side * 6);	//area of sphere is pi*rad^2

	checkVal(area);

	return area;
}

/*
Area
Input: One double
Execution: The volume of the Cube is calculated (side cubed). The value is verified to be positive and
			returned.
Output: one double
*/
double Cube::Volume()
{
	double volume;

	double side( getSide() );

	volume = (side * side * side);	//area of cube is x^3

	checkVal( volume );

	return volume;
}

/*
~Cube (Destructor)
Input: One Cube object to be destroyed
Execution: Body is empty because no special instructions are needed for destroying the Cube object at the end of its scope
Output: Nothing
*/
Cube::~Cube()
{
}