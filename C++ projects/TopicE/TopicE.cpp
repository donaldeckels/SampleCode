/*
Donald Eckels
Topic E Project
3/29/12

The extra credit assignment of creating a vector of two Shape pointer arrays was completed.
This program compiles and runs with no errors.

This program does the following steps
1) Instantiates one each of the specified shapes - circle, square, sphere, cube, triangle, and tertahedron
2) Each shape as it uses its class constructor sets a name for its shape along with calculating and saving
	its area or surface area and volume.
3) A vector array is created with two pointers to pointers to shape (base class) objects.
4) Each of the pointers is assigned an array of six pointers to shape (base class) objects.
5) The addresses of the six shapes are given to the two arrays of pointers in the speficied orders.
6) All of the shapes have their information displayed.
7) The pointer arrays are deleted from the heap
8) Program end.
TopicE.cpp
*/

#include <iostream>
#include <vector>


using namespace std;

//include files for each shape
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Cube.h"
#include "Tetrahedron.h"

int main()
{
	Circle cir(3.5, 6, 9);	//shapes created as specified in "Topic E Project CS M10BS12.doc"
	Square sqr(12, 2, 2);
	Sphere sph(5, 1.5, 4.5);
	Cube cub(2.2);
	Triangle tri(3, 1);
	Tetrahedron tet(10, 15, 7);


	vector < Shape** > Shapes(2);	//create vector of two pointer to pointer to shape items

	Shapes[0] = new Shape*[6];	//give first pointer an array of 6 pointers
	Shapes[1] = new Shape*[6];	//give second pointer an array of 6 pointers

	Shapes[0][0] = &cir;	//assign the 6 shapes to the first array of pointers in the vector in the specified order
	Shapes[0][1] = &sqr;
	Shapes[0][2] = &sph;
	Shapes[0][3] = &cub;
	Shapes[0][4] = &tri;
	Shapes[0][5] = &tet;

	Shapes[1][0] = &sqr;	//assign the 6 shapes to the second array of pointers in the vector in the specified order
	Shapes[1][1] = &sph;
	Shapes[1][2] = &cir;
	Shapes[1][3] = &tri;
	Shapes[1][4] = &tet;
	Shapes[1][5] = &cub;

	for (unsigned int j = 0; j < Shapes.size() ; ++j) //loop to display all shapes info
	{
		for (int i = 0; i < 6; ++i)
		{
			if (i == 0)
				cout << "For set " << (j + 1) << " shapes are:\n";
			cout << *Shapes[j][i];
		}

		cout << endl << endl;
	}

	delete [] Shapes[0];	//delete pointer arrays
	delete [] Shapes[1];

	cout << endl << "Press Enter key to end --> ";
	cin.get();
	cout << endl;
	return 0;
}