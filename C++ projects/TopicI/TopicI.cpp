/*
Donald Eckels
Topic I Project
5/6/12

TopicI.cpp

This program compiles and runs with no errors.
**The extra credit requirement has been completed as well.**

1. All of the functioning portion of main is within a try block to catch any errors.
2. The file "TopicIinExtra.txt" is coded as the only file to open. If it cannot be opened, the function throws an error and the program terminates.
3. The first set of data is read from the file. If data is missing, one portion has an inconsistent format, or any type of problem is encountered with the data, the function
	throws an error and the program ends.
4. If the data set is processed correctly, the formatting data is also extracted.
5. The base data is displayed to the user.
6. The packer class is called and the data is compressed from the initial digits to one bit-packed digit per set, represented as an unsigned short integer.
7. The bit-packed data is displayed to the user.
8. The bit-packed data is written to a binary file named "TopicIBin.dat"
9. The array for holding bit-packed data is erased, the binary file is read, and the data saved in the array.
10. The bit-packed data is displayed to the user.
11. The data in the uncompressed data array is erased and the bit-packed data is extracted with a series of bit masks and bit shifts.
12. The uncompressed data is displayed to the user.
13. This process repeats until the flag states that the end of the file has been found.
14. The program ends.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include "Reader.h"
#include "Packer.h"
#include "Writer.h"

using namespace std;


int main ()
{
	ifstream infile;	//stream to read from txt file
	ofstream toBin;		//stream to write to the binary file
	ifstream fromBin;	//stream to read from the binary file
	STATE reader = NOT_READY;	//program status bit
	vector < int > values ( 1 );	//vector containing uncompressed digits
	vector < unsigned short int > bin ( 1 );	//vector containing bit packed digits
	vector < int > format ( 2 );	//vector containing formatting data

	int data_set = 1;	//counter for how many data sets have been processed
	Reader read;		//set up of reader class object to pull data from txt file
	Packer pack;		//set up of packer class that will perform bit packing / unpacking
	Writer write;		//set up of writer class that will read / write binary file

	try	//enclosed in a try block to catch any unexpected errors
	{



		reader = read.open(infile);	//open the file. File name is coded into the funciton

		
		while (reader != FILE_END)	//while loop will ensure that it will continue until all data sets are processed
		{
			reader = read.process(infile, values);	//first set of data is read from the file and stored in the values array
			
			if (reader == SET_END || reader == FILE_END)	//main body of main will only be processed if a data set was read successfully
			{
				format.resize ( read.getPer_set() + 1);	//prepare format array to hold the formatting data
	
				format[0] = read.getPer_set();	//first slot of the format array is the number of digits in each set to be encoded

				for(int i = 0; i < format[0] ; ++i)	//the remaining slots are how may bits each digit will be packed into
					format[ i + 1 ] = read.getBits_per(i);
		
				cout << "\n\nDisplay input for data set " << data_set << ":\n";	//display the data pulled from the file
				read.display(values);

				pack.compress(values, format, bin);	//perform bit packing and save in the bin array

				cout << "\nDisplay binary file input:\n";	//display bit packed data
				read.display(bin);

				write.Write(bin, toBin);	//write the binary data to the file

				write.Read(bin, fromBin);	//read the binary data from the file and store in the bin array

				cout << "\nDisplay binary file output:\n";	//display bit packed data as it was read from the file
				read.display(bin);

				pack.decompress(values, bin);	//unpack the digits and store in the values array

				cout << "\nDisplay data read from file:\n";	//display the unpacked digits
				read.display(values);

				cout << "\n\nEnd of data set " << data_set << endl << endl;	//show end of data set

				++data_set;	//incriment data set counter
			}
		}
	}


	catch (exception & error)	//catch any error thrown by program, display .what string
	{
		cout << error.what();
	}

	infile.close();	//close the stream from the .txt file. toBin and fromBin are opened and closed within the function using them

	cout << "\nProgram Ending\n\n\n";	//end program
	cout << "Press Enter key to end -->";
	cin.ignore(80, '\n');
	cout << endl;

	return 0;
}
