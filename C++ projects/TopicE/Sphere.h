/*
Donald Eckels
Topic E Project
3/29/12

Sphere.h
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "ThreeDim.h"

using namespace std;

class Sphere : public ThreeDim	//Sphere class is a derived class of ThreeDim
{
public:
	Sphere(double = 0.0, double = 0.0, double = 0.0);	//constructor with default arguments

	virtual void print() const;

	virtual double Area();

	virtual double Volume();

	virtual ~Sphere();
};









#endif