/*
Donald Eckels
Topic I Project
5/6/12

Reader.h

*/

#ifndef READER_H
#define READER_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>
#include <cstring>

using namespace std;

enum STATE { NOT_READY, READY, READ, SET_END, FILE_END, NO_FILE, BAD_DATA, INCORRECT_FORMAT };	//flag for state of reading data from original txt file

/*
Class FileFail
Input: STATE value
Execution: a FileFail class object is created as a decendant of the invalid_argument class. It is thrown to signify when the file cannot be read.
Output: none
*/

class FileFail : public invalid_argument
{
public:
		FileFail(STATE why)
		: invalid_argument( "TopicIinExtra.txt cannot be opened\n" ), why( why )	//set the invalid_argument.why() to the FileFail text
	{}
		STATE why;	//include the state for verification purposes
};

/*
Class FormatFail
Input: STATE value
Execution: a FormatFail class object is created as a decendant of the invalid_argument class. It is thrown to signify that the leading data detailing the format of data to be compressed has an error.
Output: none
*/
class FormatFail : public invalid_argument
{
public:
	FormatFail(STATE why)
		: invalid_argument( "The data is incorrect / corrupted.\n" ), why( why )
	{}
	STATE why;
};

/*
Class EndOfFile
Input: none
Execution: an EndOfFile class object is created as a decendant of the length_error class. It is thrown to signify the end of the file has been reached
Output: none
*/
class EndOfFile : public length_error
{
public:
	EndOfFile()
		: length_error("\nEnd of file data\n"), why( FILE_END )
	{}
	STATE why;
};



class Reader
{
public:
	Reader(void);
	~Reader(void);
	STATE open(ifstream &);
	STATE process(ifstream &, vector <int> &);


	int getPer_set() {return per_set;}	//inline function to return the per_set value
	int getBits_per(int);
	void display(vector <int> &);
	void display(vector <unsigned short int> &);

private:
	
	STATE prep_set(ifstream &);
	
	STATE status;	//enum STATE used as a flag of the reading & processing status
	int per_set;	//holds the value signifying how many digits are in each set
	vector <int> bits_per;	//each vector element holds how many bits are utilized in the bit-packed data to hold the digit of the corresponding location

};

#endif