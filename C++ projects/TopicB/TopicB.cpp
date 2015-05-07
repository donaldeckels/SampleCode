/* Donald Eckels
Topic B Project
2/17/12

This program compiles and runs with no errors.
The extra credit portion has been included in the program.

TopicB.cpp 

This program is designed to perform the following steps:
1) Ask the user for the name of an input file. If the file does not exist, it will ask for another file name.
2) The getInput function will read one line from the file into a string.
3) The HugeInteger will call the member function StringIn to check the string to see if all characters in the string are digits.
4) If there is a non-digit character in the string, it will return false to getInput. getInput will read a new line into a string.
5) If the string is all digits, the digits will be converted into integers for the HugeInteger's array.
6) The array size will be enlarged by the StringIn member function if the current array is too small.
7) the Resize member function will check the array for empty slots after the input number or leading zeroes and resize the array as necessary.
8) The HugeInteger's name, its size, and valued contained within will be displayed to the user.
9) Steps 2 through 8 will be repeated for a second HugeInteger that is referred to by its pointer.
10) The two HugeIntegers will be added and the sum placed into a third HugeInteger. The third HugeInteger is also formatted to show the correct value.
11) The third HugeInteger is displayed to the user.
12) The two HugeIntegers are checked to see if the first is larger than the second.
	a) if it is not, the user is told and subtraction is not completed.
	b) if it is, then the second HugeInteger is subtracted from the first. The difference is reformatted to show correctly.
13) The third HugeInteger is displayed to the user.
14) Comparisons are completed one the two initial HugeInteger numbers (==, !=, >, >=, <, <= in order).
15) The comparison being performed and wether it is true or false is displayed to the user.
16) Repeat steps 2 through 15 until there is no more data in the file to read.
*/

#include "hugeinteger.h"


using namespace std;

bool OpenInputFile(ifstream& infile, string& infilename);	//function prototypes that are NOT member functions of the HugeInteger class

void Pause();

bool getInput (ifstream &, HugeInteger &, HugeInteger **);


int main ()
{
	string infilename;	//string to hold the filename
	ifstream infile;	//establish the call for reading from the file

	HugeInteger hi1("hi1");	//create HugeInteger with the name hi2
	HugeInteger *hi2 = NULL;	//create a HugeInteger pointer that is currently not allocated memory from free store
	HugeInteger hi3("hi3");	//create HugeInteger with the name hi3

	bool FileInput = true;	//bool value that states if data was read from the file

	cout << "Create2 HugeInteger Objects and a HugeInteger pointer. hi1 and hi3, are direct\n";
	cout << " objects while hi1 is a pointer\n";
	cout << "hi1 and hi3 use the default constructor\n";
	cout << "Enter the file to be used as input --> ";
	
	while (!OpenInputFile(infile, infilename))	//loop opens file. if it fails, loop will ask for a new filename
	{
		cout << "Enter another file name --> ";
	}

	while (FileInput)	//attempt the next set of comparisons only if data was read from the last item
	{
		
		cout << "\nCall getInput for hi1\n";
		
		FileInput = getInput(infile, hi1, NULL);	//getInput call for hi1

		if (FileInput)
		{
			hi1.Resize();	//resize hi1

			hi1.output();	//display hi1

	 		cout << "\nCall getInput for hi2.  hi2 will be allocated in the function\n";
			FileInput = getInput(infile, *hi2, &hi2);	//getInput call for hi2

			hi2->Resize();	//resize hi2
		
			hi2->output();	//display hi2

			hi3.add(hi1, hi2);	//add hi1 and hi2 and place sum in hi3. also calls display of hi3

			hi3.subtract(hi1, hi2);	//subtract, if the result is positive, hi2 from hi1 and place the difference in hi3.
									//also calls display of hi3

			cout << "\nGo through comparisons for hi1 and hi2, always treating hi2 as a pointer\n";

			hi1.isEqualTo(hi2);	//hi1 calls the following comparisons. the results are displayed

			hi1.isNotEqualTo(hi2);

			hi1.isGreatherThan(hi2);

			hi1.isGreaterThanOrEqualTo(hi2);

			hi1.isLessThan(hi2);

			hi1.isLessThanOrEqualTo(hi2);

		}
	}
	
	cout << "\nNo more data\n";
	cout << "Program ending\n";
	
	cout << "\nPress Enter to end -->  ";
	Pause();
	
	delete hi2;
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

bool getInput (ifstream & infile, HugeInteger & HI, HugeInteger ** ptr)
{
	static const bool yay = true;				//static constant returns
	static const bool nay = false;

	static HugeInteger hiTemp;					//holder for input
	
	string strInput;							//string to take in the value to be made into a huge integer

	
	if (infile >> strInput)						//if data is successfully read from the file and placed into strInput
	{
	
		if(ptr != NULL)
		{
			cout <<"\n\nIn getInput, allocate memory for the HugeInteger pointer\n";
			delete *ptr;
			*ptr = new HugeInteger("hi2");
		}
		
		while ( !(hiTemp.stringIn(strInput)))	//put the string into the Input string integer & if it contains a non-digit value, try again
		{
			cout << strInput << " contains an invalid value\n";
			infile >> strInput;
		}

		if (ptr != NULL)						//if this is being assigned to hi2, copy hiTemp to hi2 through the pointer
			**ptr = hiTemp;
		else
			HI = hiTemp;					  //otherwise copy hiTemp to this.

		return yay;
	}
	
	else
		return nay;

}