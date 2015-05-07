/*
Donald Eckels
Topic E Project
3/29/12

TwoDim.h
*/

#ifndef TWODIM_H
#define TWODIM_H


#include"Shape.h"

using namespace std;

class TwoDim : public Shape //TwoDim class is a derrived class of Shape
{
public:
	TwoDim(double = 0.0, double = 0.0, double = 0.0); //construtor with default arguments
	
	virtual void print() const;

	void setArea(double newArea) {area = checkVal(newArea);} //inline function takes input double, checks validity, and assigns to area

	virtual double Area() = 0;	//pure virtual for Area

	virtual ~TwoDim();

private:
	double area;
};


#endif