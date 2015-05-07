/*
Donald Eckels
Topic E Project
3/29/12

Shape.cpp
*/

#include "Shape.h"

#include <iostream>
#include <iomanip>


using namespace std;

/*
Shape constructor
Input: Three doubles
Execution: The number input for the side value is checked to verify that it is positive. If not, it is made positive.
			The values are then placed into the corresponding variables. If a value was not passed,
			the default value (0.0) is saved. The shape is also given the name "Unnamed shape". However,
			since a Shape object will never be instantiated on its own, this value will be overwritten.
Output: One new shape object
*/

Shape::Shape(double a, double x, double y)
{
	checkVal(a);	//make sure side length / radius is positive
	side = a;		//assign all values
	posX = x;
	posY = y;
	name = "Unnamed shape";	//declare name
}

/*
Print function for Shape
Input: None
Execution: Displays the dimensional and location information for the Shape to the user.
Output: Display information
*/

void Shape::print() const
{
	cout << fixed << setprecision(2);	//set precision to 2 decimal places and keep it that way
	cout << name << " with";
	if (name == "Sphere" || name == "Circle")	//if statement will change "side length" to "radius" if the shape is a circle or sphere
		cout << " radius ";
	else
		cout << " side length ";
	cout << side << "; center at (" << posX << ", " << posY << ");\n";	//display location
}

/*
checkVal
Input: One double by reference
Execution: If the input value is negative, change it to a positive with the same value.
Output: Display notification to user if executed, referenced value
*/

double Shape::checkVal(double &val)
{
	if(val < 0.0)	//only flip the sign of the value if it is negative & notify user
	{
		cout << "Shapes cannot have negative dimensions. " << val << "will be treated as positive.\n";
		val *= (-1);
	}
	
	return val;
}


/*
~Shape (destructor)
Input: One Shape to be destroyed
Execution: Body is empty because no special instructions are needed for destroying the Shape object at the end of its scope
Output: Nothing
*/
Shape::~Shape()
{
}

/*
operator<< (outstream operator overload)
Input: The specified stream (invoking object), one Shape object or derived class object
Execution: runs the requested object's print function.
Output: The specified ostream
*/
ostream & operator<<(ostream & out, const Shape & obj)
{

	obj.print();
	return out;
}