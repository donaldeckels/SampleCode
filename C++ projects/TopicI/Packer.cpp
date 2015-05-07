/*
Donald Eckels
Topic I Project
5/6/12

Packer.cpp

*/

#include "Packer.h"

using namespace std;

/*
Packer constructor
input: none
execution: none
output: one Packer class object
*/
Packer::Packer(void)
{
}


/*
Packer destructor
input: none
execution: none, the bits_per vector destruction is handled by the vector descrutor that is implicitly called
output: none
*/
Packer::~Packer(void)
{
}

/*
compress member function
input: two integer vectors (raw data and format data), one unsigned short int vector (compressed data). all by reference
execution: The format data is extracted to variables that are easier to remember and work with. The vector that will contain the bitpacked data is resized to the appropriate number of
	values and any data that may be in the indecies is cleared. The digit to be packed is added to the appropriate compressed data slot by a bit mask in order to truncate the number of bits
	stored for the given value if it exceeds how many bits are allowed for that digit. All but the last value to be stored in the digit are bitwise shifted left in order to store the next digit.
	Once the appropriate number of digits are packed into a single value, the process is repeated until all data is processed.
output: none
*/
void Packer::compress( vector <int> & numbers, vector <int> & format, vector <unsigned short int> & out)
{
	int binSize;
	per_set = format[0];	//get digits per set into the compressor
	int mask = 0;	//create mask


	bits_per.resize(per_set);

	for (int i = 0; i < per_set; ++i)	//get the number of bits needed per each digit.
		bits_per[i] = format[i+1];

	binSize = (numbers.size() / per_set);	//determine the number of slots needed to save the compressed numbers

	out.resize(binSize, 0);	//resize the output array to the correct size

	for (int i = 0; i < binSize; ++i)	//verify all slots in the output are empty
		out[i] = 0;

	for( int i = 0 ; i < binSize ; ++i)	//outer loop shifts to the next consecutive compressed digit
	{

		for (int j = 0; j < (per_set); ++j)	//inner loop puts each digit into the compressed value
		{
			mask = ( static_cast<unsigned short int> (pow(2.0, (bits_per[j] ) ) - 1 ) );	//set mask to be the "maximum" value stored by the number of bits that are being used to store the given number
			
			out[i] += ( numbers[(i * per_set) + j] & mask );//place the number in the binary digit
			
			if (j != (per_set - 1) )	//left shift the digit the appropriate number of spaces if its not the last digit
				out[i] <<= bits_per[j + 1];
		}	
	}
}

/*
decompress member function
input:  one integer vector (raw data ), one unsigned short int vector (compressed data). both by reference
execution: The values packed in each are extracted in reverse order. A mask is created for the appropriate number of bits used to store the final number.
	This mask is used to then extract the final number and it is saved in the first index of the raw data vector for the last digit. The compressed data is then
	shifted right the appropriate number of bits and the process is repeated until the first number is extracted and saved in the first index. This process is completed until
	the final bit packed data is processed.
output: none
*/
void Packer::decompress( vector <int> & numbers, vector <unsigned short int> & in)
{
	for (unsigned i = 0; i < numbers.size() ; ++i) //scrub the unpacked numbers array of any data
		numbers[i] = 0;

	int mask = 0;	//create mask

	for (unsigned i = 0; i < in.size() ; ++i)	//outer loop handles which bit packed number is being processed
	{

		for (int j = (per_set - 1); j >= 0 ; --j)	//inner loop works from the final digit in the bit packed number to the first
		{
			mask = ( static_cast<unsigned short int> (pow(2.0, (bits_per[j] ) ) - 1 ) );	//the mask is set to have a all 1's for the number of bits used to store the number currently being extracted.
			
			numbers[(i * per_set) + j] = mask & in[i];										//the uncompressed number is extracted
			
			in[i] >>= bits_per[j];															//the compressed number is shifted right by the number of bits that were just extracted
		}
	}
}