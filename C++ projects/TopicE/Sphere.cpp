/*
Donald Eckels
Topic E Project
3/29/12

Sphere.cpp
*/

#include <iostream>

#include "Sphere.h"

using namespace std;


/*
Sphere constructor
Input: Three doubles
Execution: The three double values are passed to the TwoDim object that is created as part of the Sphere object
			The area is calculated, verified to be positive, and assigned.
			The volume is calculated, verified to be positive, and assigned. The name is set to "Sphere".
Output: One Sphere object
*/
Sphere::Sphere(double a, double x, double y)
	:ThreeDim( a, x, y)	//initialization list to definte ThreeDim object
{
	setArea( Area() );		//set area

	setVolume( Volume() );	//set volume

	setName("Sphere");				//set name as Sphere
}

/*
print function for Sphere
Input: Nothing
Exectuion: Calls TwoDim print function. Because there are no special instructions for displaying Sphere,
			nothing else is executed
Output: Nothing
*/
void Sphere::print() const
{
	ThreeDim::print();	//execute ThreeDim print function
	cout << endl;
}

/*
Area
Input: One double
Execution: The area of the Sphere is calculated (4 times pi times the radius squared). The value is verified to be positive and
			returned.
Output: one double
*/
double Sphere::Area()
{
	double area;

	double rad( getSide() );

	area = (4 * 3.14159 * rad * rad);	//surface area of a sphere is pi * 4 * rad^2

	checkVal( area );

	return area;
}

/*
Area
Input: One double
Execution: The volume of the Sphere is calculated (side cubed). The value is verified to be positive and
			returned.
Output: one double
*/
double Sphere::Volume()
{
	double volume;

	double rad( getSide() );

	volume = ( (4.0/3) * 3.14159 * rad * rad * rad);	//volume of a sphere is 4/3 * pi * rad^3

	checkVal( volume );

	return volume;
}

/*
~Sphere (Destructor)
Input: One Sphere object to be destroyed
Execution: Body is empty because no special instructions are needed for destroying the Sphere object at the end of its scope
Output: Nothing
*/
Sphere::~Sphere()
{
}