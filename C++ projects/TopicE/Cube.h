/*
Donald Eckels
Topic E Project
3/29/12

Cube.h
*/

#ifndef CUBE_H
#define CUBE_H

#include "ThreeDim.h"

using namespace std;

class Cube : public ThreeDim	//Cube class is a derived class of ThreeDim
{
public:
	Cube(double = 0.0, double = 0.0, double = 0.0);	//constructor with default arguments

	virtual void print() const;

	virtual double Area();

	virtual double Volume();

	virtual ~Cube();
};


#endif