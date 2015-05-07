/*
Donald Eckels
Topic I Project
5/6/12

Writer.h

*/

#ifndef WRITER_H
#define WRITER_H

#include <vector>
#include <fstream>

using namespace std;


class Writer
{
public:
	Writer(void);
	~Writer(void);

	void Write(vector <unsigned short int> &, ofstream &);

	void Read(vector <unsigned short int> &, ifstream &);
};

#endif