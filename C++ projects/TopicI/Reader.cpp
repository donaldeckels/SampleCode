/*
Donald Eckels
Topic I Project
5/6/12

Reader.cpp

*/

#include "Reader.h"

using namespace std;


/*
Class Reader constructor
Input: none
Execution: The status flag of the Reader object is set to NOT_READY (because it is not ready to read data yet).
Output: one Reader class object
*/

Reader::Reader(void)
{
	status = NOT_READY;	//flag initialized to NOT_READY
}

/*
Reader class destructor
input: nothing
execution: nothing, destruction of bits_per vector is handled by the vector destructor and is implicitly called.
output: nothing.
*/
Reader::~Reader(void)
{
}


/*
open member function
Input: ifstream object by reference
Execution: The file titled "TopicIinExtra.txt" is attempted to be opened. If it is inaccessible, a FileFail exception
	is thrown. otherwise, a signal that the file is READY to be processed is returned.
Output: READY for the STATE or a FileFail exception
*/
STATE Reader::open ( ifstream & infile)
{
	
	infile.open( "TopicIinExtra.txt" );
	if (infile.fail())
		throw FileFail(NO_FILE);

	return READY;
}

/*
prep_set member function (used only by Reader)
Input: ifstream object by reference
Execution: The status of the process is set to NOT_READY. The first value is read from the file. If 
Output: READY as the STATE or a FormatFail exception
*/
STATE Reader::prep_set( ifstream & infile )
{
	string holder;
	int length;
	STATE ready = NOT_READY;

	infile >> per_set;	//declare how many numbers per line
	
	if (infile.eof())	//verify data was read from the file
		throw EndOfFile();	//if not, throw exception

	else if (infile.fail())	//if the data was not processed correctly
		throw FormatFail(BAD_DATA);	//throw exception

	
	if (per_set == 0)	//verify the data if it was read properly
		throw FormatFail(INCORRECT_FORMAT);	//throw exception if it was not
	
	
	
	infile >> holder;	//hold the number of bits per number in a string

	length = holder.length();	//set length of the bit counter to length

	if ( holder.length() != per_set)	//if the string holding the bits per number is longer or shorter than the number of digits per line, we have a problem
		throw FormatFail(INCORRECT_FORMAT);



	bits_per.resize(per_set);	//prep the bits_per array for being filled

	string::const_iterator digit = holder.begin();	//iterator to pull each digit

	int x = 0;
	while (digit != holder.end() )	//loop changes each of the single digits to an actual digit in the bits_per array
	{
		bits_per[x] = (*digit - 48);
		++digit;
		++x;
		
	}


	ready = READY;	//set flag to READY if an exception has not been thrown by now
	
	return ready;	//end function
}


/*
process member function
Input: ifstream object by reference, vector for holding read digits
Execution: The STATE is set to NOT_READY. The prep_set member function is called. If the prep_set returns a STATE of READY, the function can continue.
	Each line is read until a line containing a single asterisk "*" is processed. When this occurrs, the STATE flag is changed to SET_END.
	Until this, a "/" character is appended to the number for format purposes. An iterator and loop is uses to count the number of / characters in the holder since one should follow each number.
	If the number of /'s does not correspond to how many digits are supposed to be in a set, an exception is thrown. While this occurrs, the / are changed to spaces. This string of data is then
	appended to the ostringstream object. Once all data for the set has been read and verified to be correctly formatted, it is then placed into an istringstream object. The individual values
	are read one at a time into a vector that has been sized to the number of digits processed. If this has been completed successfully, then a STATE of SET_END is returned.
Output: STATE flag showing a full set of digits have been processed or a FormatFail exception
*/
STATE Reader::process(ifstream & infile, vector <int> & digits)
{

	ostringstream outString;
	
	string holder;	//holder for current string being processed
	int singleChar;	//used for going through the strings to find characters
	int holdCtr = 0;			//counts the number of digits in holder
	int allCtr = 0;				//counts the number of digits in total
	STATE state = NOT_READY;

	state = prep_set(infile);	//read format data & return a flag of its validity

	if (state == READY)	//as long as the format data was good, change state to show it's ok to continue
		state = READ;

	while (state == READ)	//while there is more lines of data to read, continue loop.
	{
		holdCtr = 0;	//will count the number of digits contained in a line

		infile >> holder;	//read in one line/set of digits

		if( holder == "*" )	//if the line just read signifies the end of a set, do not read any more data.1
			state = SET_END;
		
		
		else
		{
			holder += "/";	//add a slash to the end of the set for fomatting purposes

			singleChar = holder.find("/");	//find the first slash
			
			while (singleChar != string::npos )	//count each / to indicate another number has been read and replace with a space
			{
				++holdCtr;
				holder.replace( singleChar, 1, " " );	
				singleChar = holder.find( "/", singleChar + 1);
			}
		
			
			
			if (holdCtr != per_set)		//if the number of digits counted in a single set is incorrect, the set is bad
				throw FormatFail(BAD_DATA);

			else						//otherwise it's ok to continue
			{
				outString << holder;	//store the digits in the outstring
				allCtr += per_set;		//indicates there are X more digits on the total string.
			}

		}

	}

	
	
	if ( state == SET_END) //as long as all read data for a set is properly formatted, continue to process the data
	{
		istringstream inString (outString.str() );

		digits.resize(allCtr, 0);	//resize the vector to hold all of the numbers

		for (int i = 0; i < allCtr; ++i)	//read each of the numbers into the vector
			inString >> digits[i];

	}
	
	return state;
}


/*
getBits_per member function
Input: integer for the digit desired.
Execution: The index given is first verified. Once it shows Ok, the integer that corresponds to the requested number is returned. index 0 is the first digit, 1 is the second, etc.
Output: integer stating the number of bits that will be used to store the corresponding digit
*/
int Reader::getBits_per(int slot)
{
	if(slot >= per_set)
		throw out_of_range( "Reader::getBits_per() was given an invalid argument.\n");
	
	return bits_per[slot];
}

/*
display member function (overload for regular integers)
Input: vector of integers by reference
Execution: a loop sends each number in the array to the display on a single line.
Output: display of all vaues in the vector to the user
*/
void Reader::display(vector <int> & data)
{
	for (unsigned i = 0; i < data.size() ; ++i)
		cout << data[i] << endl;
}


/*
display member function (overload for unsigned short integers)
Input: vector of integers by reference
Execution: a loop sends each number in the array to the display on a single line.
Output: display of all vaues in the vector to the user
*/
void Reader::display(vector <unsigned short int> & data)
{
	for (unsigned i = 0; i < data.size() ; ++i)
		cout << data[i] << endl;
}