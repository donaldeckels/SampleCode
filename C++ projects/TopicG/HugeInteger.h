/* Donald Eckels
Topic G Project
4/14/12

HugeInteger.h 

Unmodified from Topic C Project
*/

#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class HugeInteger
{
	
	friend ostream & operator<<(ostream &, const HugeInteger &);	// output operator overload prototype
	friend istream & operator>>(istream &, HugeInteger &);			// input operator overload prototype
	
public:
	HugeInteger (); //default constructor
	HugeInteger (const HugeInteger &);	//copy constructor
	~HugeInteger (); //default descructor

	void Resize ();	//resize function
	
	bool stringIn (const string &); //set the array to a string


	int getSize() {return Size;}	//inline function that returns the Size integer of the invoking HugeInteger
	
	HugeInteger & operator=( const HugeInteger &);	// assignment operator overload prototype

	HugeInteger operator+(const HugeInteger &) const;	//addition operator overload prototype

	HugeInteger operator-(const HugeInteger &) const;	//subtraction operator overload	prototype
	
	bool operator==(const HugeInteger &) const;			//is equal to operator overload	prototype

	bool operator>(const HugeInteger &) const;			//greater than operator overload prototype


	/*
	operator != (overloaded != to operator)
	Input: invoking HugeInteger object, HugeInteger pointer
	Execution: inserts inline, returns the opposite of what == would return
	Output: boolean statement
	*/
	bool operator!=(const HugeInteger & right) const
	{
		return ( !(*this == right) );
	}


	/*
	operator >= (overloaded >= operator)
	Input: invoking HugeInteger object, HugeInteger pointer
	Execution: inserts inline, checks both the > and == operators. If either
				is true, the function returns true, otherwise returns false
	Output: boolean statement
	*/
	bool operator>=(const HugeInteger & right) const
	{
		return( *this > right || *this == right);
	}


	/*
	operator<
	Input: the invoking HugeInteger object, one HugeInteger pointer
	Execution: inserts inline, function checks the >= operator and returns the opposite value
	Output: boolean statement
	*/
	bool operator<(const HugeInteger & right) const
	{
		return ( !(*this >= right) );
	}
	

	/*
	operator <= (overloaded <= operator)
	Input: the invoking HugeInteger object and one HugeInteger pointer
	Execution: inserted inline, function checks the > operator and returns the opposite value
	Output: boolean statement
	*/
	bool operator<=(const HugeInteger & right) const
	{
		return ( !( *this > right) );
	}

	/*
	operator[] (overloaded [] operator)
	Input: The invoking HugeInteger Object, one integer
	Execution: The function is placed inline and returns the digit stored in the
				HugeInteger with the index that corresponds to the input integer.
	Output: one integer from the HugeInteger array
	*/
	int operator[](const int) const;

	void operator()(const int);	//prototypes for parentheses operator overload

	void operator()(const string);

private:
	
	int *Number;	//Pointer for the array
	int Size;		//size of the array

	
	void RoundUp();	//helper function for addition

	void RoundDown(); //helper function for subtraction

	void Zero();	//helper function for blanking the array
};




#endif