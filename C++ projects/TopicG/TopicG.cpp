/* Donald Eckels
Topic G Project
4/14/12

TopicG.cpp 

This program compiles and runs with no errors
I included my copy of the HugeInteger class for use in the Topic G project. It is the same files as created for Topic C,
except the overloaded subscript operator will now throw an out_of_range exception when an out of range subscript is called.

 1. All of the working parts of main are placed in a try block in order to catch any unexpected errors.
 2. The default file to be read is defined as "TopicGin.txt" and is attemtped to be opened.
	If the file is unable to be opened, the user is prompted for a new file name until one
	can be opened or the user specified to close the program.
 3. Two integer Array objects are instantiated (integers1 and integers2). One is set with the default
	length, while one is given a specific length. They are shown to be empty (filled with 0's), filled
	with data from the file, and again displayed to the user.
 4. The two Array objects are compared with the != operator and verified that a true response is returned.
 5. A third integer Array object is instantiated (integers3) with the copy constructor using integers1
 6. integers1 is assigned the value of integers2 with the = operator.
 7. The overloaded == operator is used with integers1 and integers2 to verify it returns a true response.
 8. Both the rvalue and lvalue overloaded subscript operators are called to show functionality. The contents of
	integers1 is displayed after use of the lvalue version to show proper assignment of a value.
 9. A subscript known to be out of range is called to show that an error is thrown when this is done. It is immediately
	caught in main, the user is promtped, and the program continues.
10. An Array object is attempted to be instantiated with a negative array length. An error is thrown by the constructor and
	immediately caught in main, the user is promtped, and the program is allowed to continue.
11. An Array of doubles is instantiated (doubleArray), filled with values from the file, and displayed to the user.
12. Two values in the doubleArray are changed with the non-const version of the overloaded subscript operator and the contents
	displayed to verify the change has occurred.
13. An Array of strings is instantiated (stringArray), filled with values from the file, and displayed to the user.
14. An Array of HugeInteger objects is instantiated (HugeIntegerArray), shown to be empty, filled with values from the file, and
	displayed a second time to the user to verify the values were stored properly.
15. Two of the HugeIntegers contained in the HugeIntegerArray are added and a third HugeInteger is overwritten with the sum. The
	HugeIntegerArray is displayed to the user to verify both operators performed correctly.
16. Two of the HugeIntegers contained in the HugeIntegerArray are subtracted and a third HugeInteger is overwritten with the difference.
	The HugeIntegerArray is displayed to the user to verify both operators performed correctly.
17. The elements of one HugeInteger are displayed one at a time to verify the HugeInteger's overloaded subscript operator will work within
	Array.
18. An element that does not exist in one HugeInteger is attempted to be displayed in order to force the HugeInteger object to throw an
	exception that will be caught in main via stack unwinding.
19. A catch block is situated just before the very end of main to catch any unexpected errors that may be generated by the program
20. The program ends.

*/

#include<iostream>
#include<fstream>
#include<string>
#include<new>
#include<cstdlib>
#include"Array.h"
#include"HugeInteger.h"

using namespace std;

//handle memory allocation failure
void memoryAllocationFailure()
{
	cerr << "\nProgram was unable to allocate memory, aborting program.\n";
	abort();
}


int main()
{
	
	ifstream infile;							//set identifier for the in file stream

	//entire functioning portion of main placed in try block in order to catch any unexpected errors
	try
	{
	
		ifstream infile;							//set identifier for the in file stream
		string fileName("TopicGin.txt");			//create a string to hold the file name

		infile.open( fileName );					//attempt to open the file specified
	
		while ( infile.fail() )						//as long as the requested file does not exist
		{											//prompt the user for a new file name
			cout << "The default file could not be opened.\n";
			cout << "Specify another file to open or type QUIT to quit\n";
			cout << "\nFile: ";
			cin >> fileName;						//set new file name
			cout << endl << endl;
			
			if ( fileName == "QUIT" )
			{
				cout << "Program terminating...\n";
			
				infile.close();
	
				return 0;
			}
	
			infile.clear();							//clear the error bit stating file could not be opened
			infile.open( fileName );				//attempt to open new file
		}

	
		cout << "Create two arrays, integers1 - 7 elements, integers2 - default size\n";

		Array< int > integers1( 7 ); //seven-element Array
		Array< int > integers2; // 10-element Array by default

			// print integers1 size and contents
		cout << "\nSize of Array integers1 is "
			<< integers1.getSize()
			<< "\nArray after initialization:\n" << integers1;

			// print integers2 size and contents
		cout << "\nSize of Array integers2 is "
			<< integers2.getSize()
			<< "\nArray after initialization:\n" << integers2;


			//data is read for the file and placed into integers1 and integers2
		cout << "\nReading 17 integers from file " << fileName << ":\n";
		infile >> integers1 >> integers2;

			//print integers1 and integers2 contents
		cout << "\nAfter input, the Arrays contain:\n";
		cout << "integers1:\n" << integers1;
		cout << "integers2:\n" << integers2;
	
			// overloaded inequivalence operator is checked to verify for proper true/false return
		cout << "\nEvaluating: integers1 != integers2\n";
		cout << "integers1 and integers2 ";
		if( integers1 != integers2)
			cout << "are not equal\n";
		else
			cout << "ARE equal\n";
	
			//copy constructor is used to create integers3 from integers1
		cout << "\nCreate Array integers3 from integers1\n";
		Array< int > integers3(integers1);

		//display integers3 size and contents
		cout << "\n\nSize of Array integers3 is " << integers3.getSize() << endl;
		cout << "Array after initialization:\n" << integers3;

			//overloaded assignment operator is utilized to set integers1 to the same values as integers2
		cout << "\nAssigning integers2 to integers1 (integers1 = integers2):\n";
		integers1 = integers2;

			//integers1 and integers2 contents displayed
		cout << "integers1:\n" << integers1 << "integers2:\n" << integers2;

			//overloaded equivalence operator used to verify proper true/false return
		cout << "\nEvaluating: integers1 == integers2\n";
		cout << "\nintegers1 and integers2 ";
		if (integers1 == integers2)
			cout << "are equal\n";
		else
			cout << "are NOT equal\n";

			//overloaded subscript operator for const return (rvalue) is verified to work
		cout << "\n\nintegers1[5] is " << integers1[5] << endl;
	
			//overloaded subscript operator for non-const return (lvalue) is verified to work
			//by setting a value in the Array
		cout << "\nAssigning 1000 to integers1[5]\n";
		integers1[5] = 1000;
	
			//integers1 displayed to verify change
		cout << "integers1:\n" << integers1;

			//overloaded subscript operator for non-const return is called on purpose with an out of range
			//value to verify that it throws an exception
		cout << "\nAttempt to assign 1000 to integers1[15]\n";
		try	//in try block for error processing
		{
			integers1[15] = 1000;
		}
	
			//catch block placed here in order to catch the error thrown by the overloaded subscript operator
		catch( InvalidSlot )
		{
			cout << "15 is beyond the end of the array and thefefore invalid as a subscript\n";
		}

			//Array object is attempted to be instantiated with a negative array size on purpose in order
			//to verify the constructor throws an exception
		cout << "\nAttempt to create array with a negative length\n";
		try	//in try block for error processing
		{
			Array< int > negativeArray( -7 );
		}
	
			//catch block placed here in order to catch the error thrown by the default int constructor
		catch( negativeArraySize )
		{
			cout << "\n-7 is an illegal length for an array\n";
		}

			//create a default size Array of doubles labeled doubleArray
		cout << "\n\nCreate doubleArray with defalut length\n";
		Array< double > doubleArray;

			//fill the array with 10 values in the file
		cout << "Reading 10 numbers from file TopicGin.txt:\n";
		infile >> doubleArray;

			//display the contents of doubleArray
		cout << "\nDisplay doubleArray:\n" << doubleArray;

			//utilize the non-const version of the overloaded subscript operator to set the first two values
		cout << "set the first two elements to 2.7 and 3.4\n";
		doubleArray[0] = 2.7;
		doubleArray[1] = 3.4;

			//display the contents of doubleArray to verify change
		cout << "\n\n Display doubleArray:\n" << doubleArray;

			//create a string Array with a size of 5
		cout << "\nCreate stringArray of length 5\n";
		Array< string > stringArray(5);

			//fill the array with 5 words contained by the file
		cout << "Reading 5 words from file TopicGin.txt:\n";
		infile >> stringArray;

			//display the contents of the stringArray
		cout << "\nDisplay string array\n" << stringArray;

			//create an Array object of 6 HugeInteger objects, in order to show it can work even with user defined types
		cout << "\nCreate an array of 6 default HugeInteger objects\n";
		Array < HugeInteger > HugeIntegerArray(6);

			//display the contents of HugeIntegerArray to show successful creation
		cout << "\nDisplay HugeInteger array:\n" << HugeIntegerArray << endl;
	
			//read in six numbers from the file to fill the HugeInteger arrays
		cout << "Read in values from the file\n";
		infile >> HugeIntegerArray;

			//display the HugeIntegerArray
		cout << "Display HugeInteger array:\n" << HugeIntegerArray << endl;

			//utilize the overloaded + and = operators. Shows that overloaded operators for user defined types held by the Array
			//will function as definted
		cout << "Add first and second elements and assign the result to third element\n";
		HugeIntegerArray[2] = HugeIntegerArray[0] + HugeIntegerArray[1];

			//display the contents of HugeIntegerArray to verify addition
		cout << "\nDisplay HugeInteger array:\n" << HugeIntegerArray << endl;

			//utilized the - and = overloaded operators to subtract two HugeIntegers and save the result in a third
		cout << "Subtract fourth element from third element and store in fifth element\n";
		HugeIntegerArray[4] = HugeIntegerArray[2] - HugeIntegerArray[3];

			//display the contents of the HugeIntegerArray to verify subtraction
		cout << "\nDisplay HugeInteger array:\n" << HugeIntegerArray << endl;

			//display each element of one HugeInteger object in the HugeIntegerArray at a time. shows the HugeInteger's overloaded subscript
			//will function properly
		cout << "Display each element of the HugeInteger in the 6th element of the array using the HugeArray subscript operator:\n";
		for (int i = 0; i < HugeIntegerArray[5].getSize() ; ++i)
			cout << HugeIntegerArray[5][i] << endl;

			//attempt to display an element of a HugeInteger that does not exist. shows that the stack will unwind from in the HugeInteger's
			//overloaded subscript operator to the catch block here in main
		cout << "\nDisplay the 1000th element of the HugeInteger in the 6th element of the array:\n";
		try	//in try block
		{
			cout << HugeIntegerArray[5][1000];
		}

			//catch block immediately following to catch error thrown by HugeInteger subscript operator
		catch( out_of_range &error)
		{
			cout << error.what();
		}
	}

	//catch block for all unexpected exceptions
	catch ( exception & error)
	{
		cerr << "\nAn unexpected exception has occurred and the function will now end.\n";
		cerr << "Exception: " << error.what() << endl;
	}

	cout << endl << endl;

		//end program
	cout << "\nPress Enter to end";
	cin.ignore(80, '\n');
	cout << endl;

	infile.close();

	return 0;

}