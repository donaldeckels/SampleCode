/*
Donald Eckels
Topic I Project
5/6/12

Packer.h

*/

#ifndef PACKER_H
#define PACKER_H

#include <vector>
#include <cmath>
using namespace std;


class Packer
{
public:
	Packer(void);
	~Packer(void);

	void compress( vector <int> &, vector <int> &, vector <unsigned short int> &);
	void decompress( vector <int> &, vector <unsigned short int> &);

private:
	int per_set;	//holds how many nubmers are in each set
	vector <int> bits_per;	//array holds the number of bits required to store each number

};

#endif