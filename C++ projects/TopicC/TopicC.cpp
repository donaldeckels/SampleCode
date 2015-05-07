/* Donald Eckels
Topic C Project
3/1/12

This program compiles and runs with no errors.

TopicC.cpp 

This program is designed to perform the following steps:
1) The first HugeInteger and the pointer for the second HugeInteger are created.
2) The first HugeInteger is filled with a test number and the third HugeInteger is created with the same values as
	the first HugeInteger. The values stored by the first and third HugeIntegers are displayed.
3)Ask the user for the name of an input file. If the file does not exist, it will ask for another file name.
4) The getInput function will read one line from the file into a string.
5) The HugeInteger will call the member function StringIn to check the string to see if all characters in the string are digits.
6) If there is a non-digit character in the string, it will return false to getInput. getInput will read a new line into a string.
7) If the string is all digits, the digits will be converted into integers for the HugeInteger's array.
8) The array size will be enlarged by the StringIn member function if the current array is too small.
9) the Resize member function will check the array for empty slots after the input number or leading zeroes and resize the array as necessary.
10) The HugeInteger's name, its size, and valued contained within will be displayed to the user.
11) Steps 2 through 8 will be repeated for a second HugeInteger that is referred to by its pointer.
12) The two HugeIntegers will be added and the sum placed into a third HugeInteger.
13) The third HugeInteger is displayed to the user.
14) The two HugeIntegers are checked to see if the first is larger than the second.
	a) if it is not, the user is told and subtraction is not completed.
	b) if it is, then the second HugeInteger is subtracted from the first and saved in the third HugeInteger
15) The third HugeInteger is displayed to the user.
16) Comparisons are completed on the two initial HugeInteger numbers (==, !=, >, >=, <, <= in order).
	a) The comparison being performed and wether it is true or false is displayed to the user.
17) Repeat steps 2 through 15 until there is no more data in the file to read.
*/

#include "hugeinteger.h"


using namespace std;

bool OpenInputFile(ifstream& infile, string& infilename);	//function prototypes that are NOT member functions of the HugeInteger class

void Pause();

bool getInput (ifstream &, HugeInteger &);	//overloaded getInput function prototypes
bool getInput (ifstream &, HugeInteger * &);

int main ()
{
	string infilename;	//string to hold the filename
	ifstream infile;	//establish the call for reading from the file


	HugeInteger *hi2 = NULL;	//create a HugeInteger pointer that is currently not allocated memory from free store
	
	bool FileInput = true;	//bool value that states if data was read from the file

	cout << "Create one HugeInteger Object and a HugeInteger pointer. hi1 is a direct object\n";
	cout << " while hi2 is a pointer\n";
	cout << "hi1 uses the default constructor\n";

	HugeInteger hi1;	//create HugeInteger hi1

	cout << "\nPut some test data in hi1\n\n";
	
	hi1(123);		//input 123 with the overloaded () operator

	cout << "Create hi3 as a copy of hi1\n\n";

	HugeInteger hi3 = hi1;	//copy constructor called to build hi3

	cout << "hi1 is " << hi1 << endl;

	cout << "hi3 is " << hi3 << endl << endl;

	cout << "Enter the file to be used as input --> ";
	
	while (!OpenInputFile(infile, infilename))	//loop opens file. if it fails, loop will ask for a new filename
	{
		cout << "Enter another file name --> ";
	}

	while (FileInput)	//attempt the next set of comparisons only if data was read from the last item
	{
		
		cout << "\nCall getInput for hi1\n";
		
		FileInput = getInput(infile, hi1);	//getInput call for hi1

		if (FileInput)
		{

			cout << endl << "hi1 is size " << hi1.getSize() << " and contains:\n" << hi1;

	 		cout << "\nCall getInput for hi2.  hi2 will be allocated in the function\n";
			FileInput = getInput(infile, hi2);	//getInput call for hi2
		
			cout << endl << "hi2 is size " << hi2->getSize() << " and contains:\n" << *hi2;

			cout << endl << "Add hi3 = hi1 + hi2" << endl;
			
			hi3 = hi1 + *hi2;	//hi1 and *hi2 are added and the sum is save in hi3

			cout << endl << "hi3 is size " << hi3.getSize() << " and contains:\n" << hi3;

			cout << endl << "Subtract hi3 = hi1 - hi2" << endl;

			if (hi1 >= *hi2)	//if the hi1 is greater or equal to *hi2
			{
				
				hi3 = hi1 - *hi2;	//subtract *hi2 from hi1 and save the difference in hi3

				cout << endl << "hi3 is size " << hi3.getSize() << " and contains:\n" << hi3;
			}

			else			//otherwise, the subtraction is not completed
				cout << endl << "hi1 - hi2 would result in a negative value. Subtraction not done\n";

			cout << "\nGo through comparisons for hi1 and hi2\n";

			
			//comparisons of hi1 and *hi2 are completed. An if statement is used by the truth to display the truth of the
			//comparison to the user.


			cout << "hi1 == hi2" << endl;
			cout << "hi1 is ";
	
			if (hi1 == *hi2)
				cout << "";
			else
				cout << "NOT ";
	
			cout << "equal to hi2" << endl << endl;

			
			
			cout << "hi1 != hi2" << endl;
			cout << "hi1";
			if (hi1 != *hi2)
				cout << " is not ";
			else
				cout << " IS ";
			cout << "equal to hi2" << endl << endl;

			
			
			
			cout << "hi1 > hi2" << endl;
			cout << "hi1";
			if (hi1 > *hi2)
				cout << " is ";
			else
				cout << " NOT ";
			cout << "> hi2" << endl << endl;

			
			
			cout << "hi1 >= hi2" << endl;
			cout << "hi1";
			if (hi1 >= *hi2)
				cout << " is ";
			else
				cout << " NOT ";
			cout << ">= hi2" << endl << endl;

			
			
			cout << "hi1 < hi2" << endl;
			cout << "hi1";
			if (hi1 < *hi2)
				cout << " is ";
			else
				cout << " NOT ";
			cout << "< hi2" << endl << endl;



			cout << "hi1 <= hi2" << endl;
			cout << "hi1";
			if (hi1 <= *hi2)
				cout << " is ";
			else
				cout << " NOT ";
			cout << "<= hi2" << endl << endl;

			//end comparisons

			delete hi2;	//delete hi2 in perparation for next run or possible termination
			hi2 = NULL;

		}
	}
	
	cout << "\nNo more data\n";
	cout << "Program ending\n";
	
	cout << "\nPress Enter to end -->  ";
	Pause();

	infile.close();
	
	return 0;
}

/*
OpenInputFile
Input: the infile stream call and empty string
Execution: The user types in the name of the file to be opened.
	The program attempts to open a file in the same folder.
	If it succeeds, the function changes the bool value to reflect.
Output: bool value stating wether a file was opened or not.
		if file is opened, the file as the focus of the file stream.
*/

bool OpenInputFile(ifstream& infile, string& infilename)
{
	
	bool fileChk = false;

	//Prompt the user for the name of the file to open for input.
	cin >> infilename;
	cout << endl;

	// Open the input file and verify that it opened
	infile.open(infilename.c_str());

	if (infile.fail())
	{
		cout << "Problem with the file\n";

	}
	else
		fileChk = true;


	return fileChk;		//signal success to the function caller.
}


/*
Pause
Input: one return stroke from user
Execution: it takes in one line of input from the user. It will ignore all data
			except the return stroke
Output: nothing
*/
void Pause()
	  //Pause function
{
	
	cin.ignore(80, '\n');
	cin.get();
	cout << endl;
}


/*
getInput (HugeInteger by reference overload)
Input: The current input stream, One HugeInteger by reference
Execution: If a line is able to be extracted from the file, the stringIn member function of
			HugeInteger is called to handle translating the string into the HugeInteger number
			array and it returns a bool status flag stating if the input line was good or not.
			If the input line is bad, the bad line is displayed to the user and another line
			is extracted. Once a good line is read, the function returns a true status flag to the
			calling function. If a line was unable to be extracted from the file, a false status
			flag is returned to the calling function.
Output: boolean statement stating if the input was valid
*/
bool getInput (ifstream & in, HugeInteger & HI)
{
	static const bool yay = true;				//static constant returns
	static const bool nay = false;

	string strInput;							//string to take in the value to be made into a huge integer

	
	if (in >> strInput)						//if data is successfully read from the file and placed into strInput
	{
	
		
		while ( !(HI.stringIn(strInput)))	//put the string into the Input string integer & if it contains a non-digit value, try again
		{
			cout << strInput << " contains an invalid value\n";
			in >> strInput;
		}

		return yay;
	}
	
	else
		return nay;

}

/*
getInput (HugeInteger by pointer reference overload)
Input: The current input stream, One HugeInteger by reference
Execution:  If a line is able to be extracted from the file, the pointer is first allocated new
			memory before the stringIn member function of HugeInteger is called to handle translating the
			string into the HugeInteger number array. The stringIn function returns a bool status flag
			stating if the input line was good or not.
			If the input line is bad, the bad line is displayed to the user and another line
			is extracted. Once a good line is read, the function returns a true status flag to the
			calling function. If a line was unable to be extracted from the file, a false status
			flag is returned to the calling function.
Output: boolean statement stating if the input was valid
*/
bool getInput (ifstream & in, HugeInteger * & HI)
{
	static const bool yay = true;				//static constant returns
	static const bool nay = false;

	static HugeInteger hiTemp;					//holder for input
	
	string strInput;							//string to take in the value to be made into a huge integer

	
	if (in >> strInput)						//if data is successfully read from the file and placed into strInput
	{

		cout <<"\n\nIn getInput, allocate memory for the HugeInteger pointer\n";
		if (HI)						//check to verify pointer has been deleted and set to null. if not, release the currently allocated memory
			delete HI;

		HI = new HugeInteger();		//allocate memory for the HugeInteger
				
		while ( !(HI->stringIn(strInput)))	//put the string into the Input string integer & if it contains a non-digit value, try again
		{
			cout << strInput << " contains an invalid value\n";
			in >> strInput;
		}

		return yay;
	}
	
	else
		return nay;

}