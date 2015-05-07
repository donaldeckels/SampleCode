/* Donald Eckels
Topic A Project
1/27/2012

TopicALibII.cpp*/

#include <iostream>
#include <string>
#include <cctype>
#include "TopicALibII.h"

using namespace std;

/* Input
Input: Two strings.
Execution: After the string is input, calls Check. If the string passes check, the string is stored as a number.
			If it fails, or if the second number is zero, new input is received until Check is passed. 
Output: None, however the doubles are retained by the pointers once the function has terminated */
void Input (double *x, double **y)
{

	string num;	//string that will be for the number
	bool check;

	do{
		cout << "Enter a number --> ";					//first number enter
		cin >> num;
		check = Check (num);
	
	}while ( check == false );					//if the input is not a number according to the Check function, the loop will continue
	

	*x = (strtod(num.c_str(), NULL));			//once the number is verified good, it is assigned to x


	do{
		cout << "Enter a non-zero number --> ";			//second number enter
		cin >> num;
		check = Check(num);

		if (check == true)	//if the second input string is a number
		{
			**y = (strtod(num.c_str(), NULL));		//assign the string to y
			if (**y == 0)							//if the number is equal to zero, advise user
			{	
				cout << num << " is zero. ";
			}
		}
	} while (check  == false || **y == 0);		//if the number is zero or not a number, the loop will repeat


}

/* 

Check
Input: Address to a string.
Execution: A character pointer passes over each character of the string. The first character can be +, -, ., or a number.
			All subsequent characters must be a number or decimal.
Output: Boolean true if the string is a real number or false if it is not

*/

bool Check (string &num)
{
	const char *pBuf;			//pointer to scan through the characters of the number
	int length = num.length();	//gets the length of num and assigns it to a variable
	
	int decimal = 0;			//count the number of decimal point characters

	pBuf = num.data();			//points the character pointer at the string

	
	for (int loop = 1; loop <= (length); loop++)	//for all characters past the first, perform the following check
	{
		if (loop == 1 && (*pBuf == '+' || *pBuf == '-'))	//Only check to see if the first character is a + or - sign. If so, move to the next character.
		{
			pBuf++;
		}
		
		else if (isdigit (*pBuf))	//if the character is a digit, increment the pointer to the next character
		{
			pBuf++;
		}
		
		else if (*pBuf == '.')	//if the character is not a digit, check if it is a decimal. if so, increment the decimal counter and move to the next character
		{	
			decimal++;
			pBuf++;
		}
		else					//if the character is not a digit or a decimal, quit the function with a false return value
		{
			cout << num << " is not a number. Re-enter\n";
			return false;
		}

		if (decimal > 1)		//if the function has counted more than one . character, quit the function with a false return value
		{
			cout << num << " is not a number. Re-enter\n";
			return false;
		}
	}
	
	return true;				//if all of the characters fit the requirements, return true value
}

/*

Divide
Input: Two pointers to doubles
Execution: The two doubles are divided.
Return: One double

*/

double Divide (double *x,double **y)
{
	return ( (*x) / (**y));	//return the value of x divided by y
}

/*

Display
Input: Three pointers to doubles
Execution: Displays the math computed in the Divide function
Output: None

*/
void Display (double *x,double **y, double ***z)
{
	cout << endl << *x << " / " << **y << " = " << ***z << endl;
}