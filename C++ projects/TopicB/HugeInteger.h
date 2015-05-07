/* Donald Eckels
Topic B Project
2/17/12

HugeInteger.h */

#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class HugeInteger
{

public:
	HugeInteger (string = "No Name"); //default constructor
	HugeInteger (const HugeInteger &);	//copy constructor
	~HugeInteger (); //default descructor
	
	void output() const;	//display function
	
	void Resize ();	//resize function
	
	bool stringIn (const string &); //set the array to a string

	void add( const HugeInteger, const HugeInteger * const );//add function

	void subtract( const HugeInteger, const HugeInteger * const );//subtract function

	void isEqualTo(const HugeInteger * const) const;	//comparison functions

	void isNotEqualTo(const HugeInteger * const) const;

	void isGreatherThan(const HugeInteger * const) const;

	void isLessThan(const HugeInteger * const) const;

	void isGreaterThanOrEqualTo(const HugeInteger * const) const;

	void isLessThanOrEqualTo(const HugeInteger * const) const;
	
	HugeInteger & operator=( const HugeInteger &);	// equivalence operator overload function



private:
	
	int *Number;	//Pointer for the array
	int Size;		//size of the array
	string Name;	//name for the HugeInteger

	
	HugeInteger operator+(const HugeInteger * const right)const; //operator overloads for HugeInteger, explicitly takes a HugeInteger pointer as the rvalue

	HugeInteger operator-(const HugeInteger * const right)const; //placed in private because they are only called by class member functions
	
	bool operator==(const HugeInteger * const) const;

	bool operator>(const HugeInteger * const) const;


	/*
	operator != (overloaded != to operator)
	Input: invoking HugeInteger object, HugeInteger pointer
	Execution: inserts inline, returns the opposite of what == would return
	Output: boolean statement
	*/
	bool operator!=(const HugeInteger * const right) const
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
	bool operator>=(const HugeInteger * const right) const
	{
		return( *this > right || *this == right);
	}


	/*
	operator<
	Input: the invoking HugeInteger object, one HugeInteger pointer
	Execution: inserts inline, function checks the >= operator and returns the opposite value
	Output: boolean statement
	*/
	bool operator<(const HugeInteger * const right) const
	{
		return ( !(*this >= right) );
	}
	

	/*
	operator <= (overloaded <= operator)
	Input: the invoking HugeInteger object and one HugeInteger pointer
	Execution: inserted inline, function checks the > operator and returns the opposite value
	Output: boolean statement
	*/
	bool operator<=(const HugeInteger * const right) const
	{
		return ( !( *this > right) );
	}

	void RoundUp();	//helper function for addition

	void RoundDown(); //helper function for subtraction
};




#endif