/*
Donald Eckels
Topic E Project
3/29/12

Shape.h
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <string>

using namespace std;


class Shape	//shape is the base class for TwoDim and ThreeDim
{
	friend ostream & operator<<(ostream &, const Shape &);	// operator overload for <<
public:
	Shape(double = 0.0, double = 0.0, double = 0.0);	//constructor with default arguments

	virtual void print() const;

	double checkVal(double &);

	void setName(string newName) {name = newName;}	//inline assignment of name

	double getSide() {return side;}

	virtual ~Shape();

private:
	double side;
	double posX;
	double posY;
	string name;
};









#endif