/*
Donald Eckels
Topic E Project
3/29/12

Triangle.h
*/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "TwoDim.h"

using namespace std;

class Triangle : public TwoDim	//Triangle class is a derrived class of TwoDim
{
public:
	Triangle(double = 0.0, double = 0.0, double = 0.0); //constructo with default arguments

	virtual void print() const;

	virtual double Area();

	virtual ~Triangle();
};


#endif