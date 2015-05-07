/*
Donald Eckels
Topic E Project
3/29/12

Square.h
*/

#ifndef SUQARE_H
#define SQUARE_H

#include "TwoDim.h"

using namespace std;

class Square : public TwoDim //Square class is a derived class of TwoDim
{
public:
	Square(double = 0.0, double = 0.0, double = 0.0); //constructor with default arguments

	virtual void print() const;

	virtual double Area();

	virtual ~Square();
};









#endif