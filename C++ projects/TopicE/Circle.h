/*
Donald Eckels
Topic E Project
3/29/12

Circle.h
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "TwoDim.h"

using namespace std;

class Circle : public TwoDim //Circle class is a derived class of TwoDim
{
public:
	Circle(double = 0.0, double = 0.0, double = 0.0); //construtcor with default arguments

	virtual void print() const;

	virtual double Area();

	virtual ~Circle();
};


#endif