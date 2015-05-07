/*
Donald Eckels
Topic E Project
3/29/12

ThreeDim.h
*/

#ifndef THREEDIM_H
#define THREEDIM_H


#include"Shape.h"

using namespace std;

class ThreeDim : public Shape
{
public:
	ThreeDim(double = 0.0, double = 0.0, double = 0.0);
	
	virtual void print() const;

	void setArea(double newArea) { area = checkVal(newArea); }	//inline function verifies input double and assigns it to the area
	
	void setVolume(double newVol) { volume = checkVal(newVol); }	//inline function verifies input double and assigns it toe the volume

	virtual double Area() = 0;	//pure virtual function for returning calculated area

	virtual double Volume() = 0;	//pure virtual function for returning calculated volume
	
	virtual ~ThreeDim();

private:
	double area;
	double volume;
};




#endif