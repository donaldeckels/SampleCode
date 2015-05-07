/* Donald Eckels
Topic G Project
4/14/12

Array.h */

#include <iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
#include"HugeInteger.h"

using namespace std;

//negativeArraySize objects should be thrown if an attempt to
//initialize an Array object with a size of less than zero
class negativeArraySize : public invalid_argument
{

public:
	//constructor specifies error message
	negativeArraySize()
		: invalid_argument ( "Array size must be greater than 0" )
	{}
};

//InvalidSlot objects should be thrown if an attempt is made to
//utilize an Array subscript that does not exist
class InvalidSlot : public out_of_range
{
public:
	//constructor specifies error message
	InvalidSlot()
		: out_of_range ( "This subcript does not exist" )
	{}
};


template < typename T >
class Array
{
	template < typename T > friend ostream &operator<<( ostream &, const Array< T > &);
	template < typename T > friend istream &operator>>( istream &, Array< T > &);

public:
	explicit Array ( int = 10 ); //default constructor
	
	Array ( const Array< T > & ); //copy constructor
	~Array(); //destructor
	
	int getSize() const;

	const Array &operator=( const Array< T > & ); //assignment operator
	bool operator==( const Array< T > & ) const; //equality operator

	// inequality operator; returns opposite of == operator
	bool operator!=( const Array< T > &right ) const
	{
		return ! ( *this == right );	//invokes Array::operator==
	} //end function operator!=

	//subscript operator for non-const objects returns modifiable lvalue
	T &operator[]( int );

	//subscript operator for const objects returns rvalue
	T operator[]( int ) const;

private:
	int size;	//pointer based array size
	T *ptr;	//pointer to first element of pointer-based array
};


/*defaut INT constructor for class Array (default size is 10)
Input: (optional) one integer
Execution: If an Array with the template type of int is created, this
constructor will be called. The length of the desired array is first tested.
If it is less than or equal to zero, a negativeArraySize exception is thrown.
Otherwise, an Array object of integers is created and all values are set to 0.
Output: one Array object
*/
template<>
Array< int >::Array( int arraySize )
{
	//validate arraySize
	if ( arraySize > 0)
		size = arraySize;
	else
		throw negativeArraySize();

	ptr = new int[size]; //create space for pointer-based array

	for ( int i = 0; i < size; ++i)
		ptr[ i ] = 0;	//set pointer-based array element
}


/*defaut DOUBLE constructor for class Array (default size is 10)
Works the same as the previous Array constructor, except the Array
object consists of doubles and all values are set to 0.0
*/
template<>
Array< double >::Array( int arraySize )
{
	//validate arraySize
	if ( arraySize > 0)
		size = arraySize;
	else
		throw negativeArraySize();

	ptr = new double[size]; //create space for pointer-based array

	for ( int i = 0; i < size; ++i)
		ptr[ i ] = 0.0;	//set pointer-based array element
}

/*defaut STRING constructor for class Array (default size is 10)
Works the same as the previous Array constructor, except the Array
object consists of strings and all values are set to "Blank"
*/
template<>
Array< string >::Array( int arraySize )
{
	//validate arraySize
	if ( arraySize > 0)
		size = arraySize;
	else
		throw negativeArraySize();

	ptr = new string[size]; //create space for pointer-based array

	for ( int i = 0; i < size; ++i)
		ptr[ i ] = "Blank";	//set pointer-based array element
}

/*defaut constructor for class Array (default size is 10)
Works the same as the previous Array constructor, except no type
is specified for the template. Used to construct an Array object for
any type not specified above
*/
template< typename T >
Array< T >::Array( int arraySize )
{
	//validate arraySize
	if ( arraySize > 0)
		size = arraySize;
	else
		throw negativeArraySize();

	ptr = new T[size]; //create space for pointer-based array
	
}


/*copy constructor for class Array
Input: one Array object to be copied
Execution: The new Array object is set to have the same size as
			the Array object to be copied. Memory is allocated
			for the new array. Finally, each element of the original
			Array is copied into the new Array.
Output: one new Array object with the same contents as the original
*/
template< typename T >
Array< T >::Array( const Array &arrayToCopy)
	: size (arrayToCopy.size)
{
	ptr = new T[size]; //create space for pointer-based array

	for ( int i = 0; i < size; ++i)
		ptr[ i ] = arrayToCopy.ptr[ i ]; //copy into object
}



//Array desctuctor - the allocated memory is released when the Array object
//					is destroyed.
template< typename T >
Array< T >::~Array()
{
	delete [] ptr; //release pinter-based array space
}

//return number of elements in Array - takes no input and simply returns the
//integer value stored as the Array object's size
template< typename T >
int Array< T >::getSize() const
{
	return size; //number of elements in Array
}

/*overload assignment operator;
Input: 2 Array objects (invoking and to be copied)
Execution: To prevent self-assignment, the entire execution is
		contained within an if statement that checkes the address
		of the lvalue and rvalue. The size of the Arrays are checked.
		If the size of the invoking is not the same as the right, the
		Array is deleted, the size set to equal the right's, and a
		new array is allocated. Each element of the right array is copied
		to the same element of the invoking array.
Output: invoking object (to allow chained operators)
*/
template< typename T >
const Array< T > &Array< T >::operator=( const Array & right )
{
	if ( &right != this)	//avoids self-assignment
	{
		//for Arrays of different sizes, deallocate original
		//left-side array, then allocate new left-size array
		if (size != right.size)
		{
			delete [] ptr;	//release psace
			size = right.size; //resize this object
			ptr = new T[ size ]; //create space for array copy
		}	//end inner if

		for ( int i = 0; i < size; ++i)
			ptr[ i ] = right.ptr[ i ];	//copy array into object
	}	//end outer if

	return *this; //enables x = y = z, for example
}	//end function operator=

/*overload equivalence operator
Input: 2 Array objects (invoking and to be compared)
Execution: First the size of both Array objects are checked. If
			they are not the same, false is returned. If both
			are of equal length, the individual values stored
			in Array are checked. When a value is found to not match,
			fales is returned. If both the size and total contents match,
			the Array objects are equal and true is returned.
Output: bool
*/
template< typename T >
bool Array< T >::operator==( const Array &right ) const
{
	
	if( size != right.size)
		return false; //arrays of different number of elements

	for ( int i = 0; i <size; ++i)
		if ( ptr[ i ] != right.ptr[ i ] )
			return false; //Array contents are not equal

	return true; //array contents are equal
} //end operator==

/*overloaded subscript operator for non-const Arrays
Input: Array object with an integer within the subscript operator
Execution: If the integer specified in the subscript operator
			is a number that does not correspond to an actual
			offset in the array, an exception is thrown.
			Otherwise, the lvalue version of the value is returned.
Output: One Array element that is modifiable
*/
template< typename T >
T &Array< T >::operator[]( int subscript )
{
	//check for subscript out-of-range error
		if ( subscript < 0 || subscript >= size)
			throw InvalidSlot();

		return ptr[ subscript ]; //reference return
} //end function operator[]

/*overloaded subscript operator for const Arrays
Input: Array object with an integer within the subscript operator
Execution: If the integer specified in the subscript operator
			is a number that does not correspond to an actual
			offset in the array, an exception is thrown.
			Otherwise, the rvalue version of the value is returned.
Output: One Array element that is modifiable
*/
template< typename T >
T Array< T >::operator[]( int subscript ) const
{
	//check for subscript out-of-range error
	if ( subscript < 0 || subscript >= size)
			throw InvalidSlot();

		return ptr[ subscript ]; //returns copy of this element
} //end function operator[]

/*overlaod input operator for class Array;
Input: one input stream (lvalue), one Array (rvalue)
Execution: until all elements of the Array object are filled,
			one input value is stored in one element of the Array
			object.
Output: input stream (for input chaining)
*/
template< typename T >
istream &operator>>( istream &input, Array< T > &a)
{
	for ( int i = 0; i < a.size; ++i )
		input >> a.ptr[ i ];

	return input; //enables cin >> x >> y;
} //end function

/*overload output operator for class Array
Input: one output stream (lvalue), one Array (rvalue)
Execution: Each element of the Array is sent to the output stream.
			Each element is given a width of 12 to separate each value.
			Four elements are given for each line sent to the output stream
			before a new line is started. Once all values are displayed, one
			last new line is started in order to not have any future data on the same line
			(Not executed if the last item to be displayed was also the end of its line,
			this prevents inconsistent line spacing)
Output: output stream (for output chaining)
*/
template< typename T >
ostream &operator<<( ostream &output, const Array< T > &a)
{
	int i;

	//output private ptr-based array
	for ( i = 0; i < a.size ; ++i )
	{
		output << setw( 12 ) << a.ptr[ i ];

		if ( ( i + 1 ) % 4 == 0 ) //4 numbers per row of output
			output << endl;
	}//end for

	if ( i % 4 != 0) //end last line of output
		output << endl;

	return output; //enables cout << x << y;
} //end function operator <<
