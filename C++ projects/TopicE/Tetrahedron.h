/*
Donald Eckels
Topic E Project
3/29/12

Tetrahedron.h
*/

#ifndef	TETRAHEDRON_H
#define TETRAHEDRON_H

#include "ThreeDim.h"

using namespace std;

class Tetrahedron : public ThreeDim	//Tetrahedron class is a derived class of ThreeDim
{
public:
	Tetrahedron(double = 0.0, double = 0.0, double = 0.0);	//constructor with default arguments

	virtual void print() const;

	virtual double Area();

	virtual double Volume();

	virtual ~Tetrahedron();
};


#endif