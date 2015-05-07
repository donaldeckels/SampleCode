/*
Donald Eckels
Topic I Project
5/6/12

Writer.cpp

*/

#include "Writer.h"

using namespace std;

/*
Writer constructor
input: none
execution: none
output: one Writer class object
*/
Writer::Writer(void)
{
}

/*
Writer destructor
input: none
execution: none
output: none
*/
Writer::~Writer(void)
{
}

/*
write member function
input: one vector of unsigned short integers and one ofstream object.
execution: The file "TopicIBin.dat" is opened (or created if it does not exist) and it is specified that it is going to be written to as a binary file. If it cannot be opened, an exception is thrown
	Reinterpret cast is utilized to create a character pointer to the specified bit-packed value and the data starting at that location and the number of bits that are in the size of
	one unsigned short integer are written to the file. This is repeated until all data is written to the file and is then closed.
output: none
*/
void Writer::Write(vector <unsigned short int> & data, ofstream & toBin)
{
	toBin.open("TopicIBin.dat",ios::binary);	//open file as a binary file

	if (toBin.fail())							//verify it was opened ok
		throw invalid_argument("TopicIBin.dat could not be opened.\n");

	for(unsigned i = 0; i < data.size() ; ++i)	//write each value bitwise to the file
		toBin.write(reinterpret_cast<char *>(&data[i]), sizeof(unsigned short int));

	toBin.close();	//close the file
}

/*
write member function
input: one vector of unsigned short integers and one ofstream object.
execution: The array for the bit-packed values is cleared. The file "TopicIBin.dat" is opened and it is specified that it is going to be read from as a binary file.
	If it cannot be opened, an exception is thrown. Reinterpret cast is utilized to create a character pointer to the specified bit-packed value and the the number
	of bits contained by one unsigned short int are read from the file and stored in the specified bit-packed value. The ifstream object is then closed.
output: nothing
*/
void Writer::Read(vector <unsigned short int> & data, ifstream & fromBin)
{
	for( unsigned i = 0; i < data.size(); ++i)	//cleanse the array
		data[i] = 0;
	
	fromBin.open("TopicIBin.dat",ios::binary);	//open the file as a binary file

	if (fromBin.fail())							//verify the file could be opened
		throw invalid_argument("TopicIBin.dat could not be opened.\n");


	for(unsigned i = 0; i < data.size(); ++i)	//read the specified number of bits from the file and store them consecutively in the vector indecies
		fromBin.read(reinterpret_cast<char *>(&data[i]), sizeof(unsigned short int));


	fromBin.close();	//close the file

}
