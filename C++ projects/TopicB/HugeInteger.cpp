/* Donald Eckels
Topic B Project
2/17/12

HugeInteger.cpp */


#include "hugeinteger.h"

using namespace std;



/*
HugeInteger constructor
Input: optional string for name
Execution: It creates a HugeInteger object with the selected name, or "No Name" if one is not given.
			It sets the size for the array to 40 and creates an integer array of size 40 to hold the
			HugeInteger.
Output: One new HugeInteger object for the program.
*/
HugeInteger::HugeInteger(string NameIn)
{
	Size = 40; //Set the array size to 40
	
	Number = new int[Size];		//Create an array of integers the size of default
	
	Name = NameIn;
}


/*
HugeInteger copy constructor
Input:One HugeInteger object
Execution: when the new object is created as a copy, the name and size are copied.
			A new number array is allocated in memory for the HugeInteger
Output: The copy of a HugeInteger
*/
HugeInteger::HugeInteger( const HugeInteger &Input )
{
	Size = Input.Size;	//set new array's size to the size of the original array
	
	Number = new int [Size];	//Create the new array

	for (int i = 0; i < Size; i++) //fill the array being created with the original array values
		Number[i] = Input.Number[i];

	Name = Input.Name;
}


/*
HugeInteger destructor
Input: One HugeInteger to be destroyed
Execution:	deallocates the memory in free store that was utilized by the array before destruction
Output: nothing
*/
HugeInteger::~HugeInteger()
{
	delete [] Number;

}


/*
output
Input: The HugeInteger executing the function
Execution: Executes lines to display information about the HugeInteger
Output: Display of the HugeInteger name, size, and huge integer contained
*/
void HugeInteger::output() const
{
	cout << endl << Name << " is size " << Size << " and contains:\n";
	for (int i = 0; i < Size; i++)
		cout << Number[i];
	cout << endl;
}


/*
Resize
Input: The HugeInteger Executing the function.
Execution: It checks all values of the digits of the array. First it checks the array to find any unused slots.
			(these were specified by filling the slot with -1 in stringIn function) A temporary array is created
			and all actual values are transferred to this array, the Number array is deleted and resized to the
			correct length before being filled with the HugeInteger. Another loop is then executed to find the first non-zero digit.
			The size of the array minus the number of iterations completed gives the number of leading zeroes.
			However, if the entire array is checked and every digit is zero, the new array will be one digit.
			A new temporary array is created with the final size of the number. The huge integer without the leading zeroes is
			copied to the temporary array in order to delete the Number array, change the size to the final size, allocate the
			Number array in free store, and place the number back into the Number array. The temporary array is once again deleted.
Output: nothing
*/
void HugeInteger::Resize()
{
	int newSize = Size;	//holder for the new value of the size while it is being calculated
	int *temp;			//holder for the new array pointer
	int LeadZero;		//holds the number of leading zeroes
	
	
	for (int i = 1; i < Size ; i++) //loop to check if each digit is a negative number. if so, quit loop early and the end digits will be removed.
		if (Number[i] < 0)
		{
			newSize = i;
			i = Size;
		}

	if (newSize < Size)	//only if there are trailing digits will the array complete this resize
	{
		temp = new int[newSize];	//temp holding array
		
		for (int i = 0; i < newSize ; i ++)	//transfer actual values to the temp
			temp[i] = Number[i];
		
		delete [] Number;
		Size = newSize;
		Number = new int[Size];		//resize the number array
		
		for (int i = 0; i < Size; i++)	//move values back to number array
			Number[i] = temp[i];

		delete [] temp;
	}

	for (int i = 0; i < Size ; i++)	//loop determine number of leading zeroes newSize will hold the array size without leading zeroes
	{
			if (Number[i])	//if the number in the array isn't a 0, which will be the first digit on the left
		{
			newSize = (Size - i);	//sets the new size
			LeadZero = i;			//also declares the number of leading zeroes
			i = Size;				//terminates loop early
		}
			if ((i + 1 == Size) && (Number[i] == 0))	//if the HugeInteger == 0
				Size = 1;
	}

	if (newSize < Size)	//if the array has leading zeroes, create new array and shift the actual value to the start of the array
	{
		temp = new int[newSize];	
		
		for (int i = 0; i < newSize; i++)	//shift the digits to the left in the temp array
			temp[i] = Number[i + LeadZero];
		
		delete [] Number;
		Size = newSize;
		Number = new int[Size];		//resize the number array

		for (int i = 0; i < Size; i++)	//return the numbers back to the number array
			Number[i] = temp[i];

		delete [] temp;

		
	}


}


/*
stringIn
Input: The invoking HugeInteger object and one string
Execution: If the length of the string to be evaluated is longer than the Number array, the Number array is resized
			to fit the entire string. Each character in the string is then evaluated. If it is not a digit, the 
			return value is flagged as false. If it is a digit, it is translated from the character of that digit to
			the same integer. Any unused offsets in the array are set to -1 for future deletion in the Resize function.
Output: boolean value stating if the string was good or not, Number array filled with values from the string
*/
bool HugeInteger::stringIn (const string & strInput)
{
	bool check = true;	//keep track if the input values are numbers or not
	unsigned i = 0;		//number to track slots filled through both loops

	if (strInput.size() > static_cast<unsigned>(Size))	//If the accepted string is longer than the current array size, make the array large enough to hold the value
	{
		delete [] Number;
		Size = strInput.size();
		Number = new int [Size];
	}
	
	for (; i < strInput.size() ; i++)
	{
		if ( !(isdigit (strInput[i]) ) )	//first check to see if it is a digit
			check = false;					//if not, notify invoking function
		else if (strInput[i] == '0')	//if it is, convert digit character to single integer
			Number[i] = 0;
		else if (strInput[i] == '1')
			Number[i] = 1;
		else if (strInput[i] == '2')
			Number[i] = 2;
		else if (strInput[i] == '3')
			Number[i] = 3;
		else if (strInput[i] == '4')
			Number[i] = 4;
		else if (strInput[i] == '5')
			Number[i] = 5;
		else if (strInput[i] == '6')
			Number[i] = 6;
		else if (strInput[i] == '7')
			Number[i] = 7;
		else if (strInput[i] == '8')
			Number[i] = 8;
		else if (strInput[i] == '9')
			Number[i] = 9;
		}
	for (; i < static_cast<unsigned>(Size) ; i++)	//fill unused array values, if any, with -1
		Number[i] = -1;

	return check;
}


/*
add
Input: The invoking HugeInteger object, one other HugeInteger and one HugeInteger pointer
Execution: The function displays which HugeIntegers are being added and which will store the sum.
			It then calls the overloaded + operator to add and the two HugeIntegers. The returned
			sum is copied to the invoking object by the overloaded = operator
Output: display of the math being completed, the sum of the two HugeIntegers to the invoking object,
		and display of the resulting object
*/
void HugeInteger::add( HugeInteger const left, const HugeInteger * const right )
{
	
	cout << endl << "Add " << Name << " = " << left.Name << " + " << right->Name << endl << endl;


	*this = left + right;

	output();

}


/*
subtract
Input: The invoking HugeInteger object, one other HugeInteger and one HugeInteger pointer
Execution: The function displays which HugeIntegers are being subtracted and which will store the
			difference. It then calls the overloaded - operator to subtract and the two HugeIntegers.
			The returned difference is copied to the invoking object by the overloaded = operator
Output: display of the math being completed, the difference of the two HugeIntegers to the invoking object,
		and display of the resulting object
*/
void HugeInteger::subtract( HugeInteger const left, const HugeInteger * const right )
{
	cout << endl << "Subtract " << Name << " = " <<left.Name << " - " << right->Name << endl << endl;
	
	if ( left >= right)
	{
		*this = left - right;

		output();
	}
	

	else
		cout << endl << left.Name << " - " << right->Name << " would result in a negative value. Subtraction not done\n";
}


/*
isEqualTo
Input: The invoking HugeInteger object, one HugeInteger pointer
Execution: Displays to the user that the == comparison is going to be made.
		An if/else statement uses the truth of the overloaded operator to
		display wether the comparison is correct or incorrect
Output: The comparison being completed and its truth to the display
*/
void HugeInteger::isEqualTo(const HugeInteger * const right) const
{
	cout << Name << " == " << right->Name << endl;
	cout << Name << " is ";
	
	if (*this == right)
		cout << "";
	else
		cout << "NOT ";
	
	cout << "equal to " << right->Name << endl << endl;
}


/*
isNotEqualTo
Input: The invoking HugeInteger object, one HugeInteger pointer
Execution: Displays to the user that the != comparison is going to be made.
		An if/else statement uses the truth of the overloaded operator to
		display wether the comparison is correct or incorrect
Output: The comparison being completed and its truth to the display
*/
void HugeInteger::isNotEqualTo(const HugeInteger * const right) const
{
	cout << Name << " != " << right->Name << endl;
	cout << Name;
	if (*this != right)
		cout << " is not ";
	else
		cout << " IS ";
	cout << "equal to "  << right->Name << endl << endl;
}


/*
isGreaterThan
Input: The invoking HugeInteger object, one HugeInteger pointer
Execution: Displays to the user that the > comparison is going to be made.
		An if/else statement uses the truth of the overloaded operator to
		display wether the comparison is correct or incorrect
Output: The comparison being completed and its truth to the display
*/
void HugeInteger::isGreatherThan(const HugeInteger * const right) const
{
	cout << Name << " > " << right->Name << endl;
	cout << Name;
	if (*this > right)
		cout << " is ";
	else
		cout << " NOT ";
	cout << "> "  << right->Name << endl << endl;
}


/*
isLessThan
Input: The invoking HugeInteger object, one HugeInteger pointer
Execution: Displays to the user that the < comparison is going to be made.
		An if/else statement uses the truth of the overloaded operator to
		display wether the comparison is correct or incorrect
Output: The comparison being completed and its truth to the display
*/
void HugeInteger::isLessThan(const HugeInteger * const right) const
{
	cout << Name << " < " << right->Name << endl;
	cout << Name;
	if (*this < right)
		cout << " is ";
	else
		cout << " NOT ";
	cout << "< " << right->Name << endl << endl;
}


/*
isGreaterThanOrEqualTo
Input: The invoking HugeInteger object, one HugeInteger pointer
Execution: Displays to the user that the >= comparison is going to be made.
		An if/else statement uses the truth of the overloaded operator to
		display wether the comparison is correct or incorrect
Output: The comparison being completed and its truth to the display
*/
void HugeInteger::isGreaterThanOrEqualTo(const HugeInteger * const right) const
{
	cout << Name << " >= " << right->Name << endl;
	cout << Name;
	if (*this >= right)
		cout << " is ";
	else
		cout << " NOT ";
	cout << ">= " << right->Name << endl << endl;
}


/*
isLessThanOrEqualTo
Input: The invoking HugeInteger object, one HugeInteger pointer
Execution: Displays to the user that the <= comparison is going to be made.
		An if/else statement uses the truth of the overloaded operator to
		display wether the comparison is correct or incorrect
Output: The comparison being completed and its truth to the display
*/
void HugeInteger::isLessThanOrEqualTo(const HugeInteger * const right) const
{
	cout << Name << " <= " << right->Name << endl;
	cout << Name;
	if (*this <= right)
		cout << " is ";
	else
		cout << " NOT ";
	cout << "<= " << right->Name << endl << endl;
}


/*
operator= (overloaded assignment operator)
Input: the invoking HugeInteger (lvalue) and the HugeInteger number to be assigned to the invoking HugeInteger (rvalue)
Execution: The function checks for self assignment by verifying the addressed. If they are not the same, the size of
			the rvalue array is given to the lvalue array, the lvalue array is resized by delete/new, and all array
			items are copied one by one from the rvalue to lvalue array.
Output: the invoking HugeInteger
*/
HugeInteger & HugeInteger::operator=( const HugeInteger & right)
{
	if (this == &right)						//check for self assignment, then move all rvalues to the correspoding lvalues
		return *this;

	Size = right.Size;
	delete [] Number;
	Number = new int[Size];
	for (int i = 0; i < Size; i++)
		Number[i] = right.Number[i];
	
	return *this;
}


/*
operator + (overloaded addition operator)
Input: The invoking HugeInteger (lvalue) and pointer to a HugeInteger object (rvalue)
Execution: The function checks to see if either input HugeInteger's Size is as large orlarger than the sum's Size (40).
			If it is the Sum array is resized to be one digit larger to accomodate the sum (e.g.: 999 + 1 = 1000). 
			The sum array is filled with zeroes to overrite any garbage in the slots. The "ones" digit of each array
			(the value contained in the last slot) are added and saved in the "ones" digit of the sum array. This is
			is repeated for each digit (tens, hundreds, thousands, etc.) until one of the input arrays is out of digits.
			The second loops takes over and moves all of the digits from the array with a larget Size to the sum.
			The function then calls the RoundUp function to fix any digits that are over 9. The resize function is then
			called to clear off the leading zero if it was not used.
Output: one HugeInteger containing the sum
*/
HugeInteger HugeInteger::operator+(const HugeInteger * const right) const
{
	HugeInteger sum;									//HugeInteger to hold the sum
	
	if (Size >= sum.Size || right->Size >= sum.Size)	//If the sum HugeInteger is the same size or smaller than either array. make it one digit larger than the larger array
	{
		delete [] sum.Number;
		sum.Size = ((Size >= right->Size) ? (Size + 1) : (right->Size + 1));
		sum.Number = new int[sum.Size];
	}
	
	for (int i = 0; i < sum.Size; i ++)					//Fill sum array with zeroes
		sum.Number[i] = 0;
	
	int s = 1;											//value to use for both loops

	for (; s <= Size && s <= right->Size ; s++)			//add each Number array value from right to left (smallest to largest) as long as both array have a value for that digit
		sum.Number[sum.Size - s] = Number[Size - s] + right->Number[(right->Size) - s];
	
	if (Size > right->Size)								//if the invoking HugeInteger is larger, move the rest of the values to the sum
		for (; s <= Size ; s++)
			sum.Number[sum.Size - s] = Number[Size - s];
	
	else if (Size < right->Size)						//if the right HugeInteger is larger, move the rest of the vlues to the sum
		for (; s <= right->Size; s++)
			sum.Number[sum.Size - s] = right->Number[right->Size - s];


	
	sum.RoundUp();	//function call to get all digits back to a single digit

	sum.Resize();	//resize sum's Number array is too large
	
	return sum;
	
}


/*
operator- (overloaded subtraction)
Input: The invoking HugeInteger (lvalue), and a pointer to a HugeInteger
Execution: If the invoking HugeInteger object has a larger Size than the sum array, the sum array is resized.
			The sum array is then filled with zeroes. An if statement checks to see if the value for the HugeInteger
			pointer is larger than the invoking object. If it is, no subtraction is performed. Otherwise, each single digit subtraction is completed.
			A helper function is called to fix any negative digits before the HugeInteger is resized.
Output: One HugeInteger object containing the difference
*/
HugeInteger HugeInteger::operator-(const HugeInteger * const right) const
{
	HugeInteger sum;
	
	if (Size >= sum.Size)	//If the sum HugeInteger is the same size or smaller than either array. make it the size of than the larger array
	{
		delete [] sum.Number;
		sum.Size = Size;
		sum.Number = new int[sum.Size];
	}

	for (int i = 0; i < sum.Size; i ++)					//Fill sum array with zeroes
		sum.Number[i] = 0;
	
	if ( *this < right)									//verifies that subtraction will not result in a negative value. if it does, then 0 is returned
		return sum;
	
	int s = 1;											//value to use for both loops

	for (; s <= Size && s <= right->Size ; s++)			//subtract each Number array value from right to left (smallest to largest) as long as both array have a value for that digit
		sum.Number[sum.Size - s] = Number[Size - s] - right->Number[(right->Size) - s];
	
	if (Size > right->Size)								//if the invoking HugeInteger is larger, move the rest of the values to the sum
		for (; s <= Size ; s++)
			sum.Number[sum.Size - s] = Number[Size - s];


	sum.RoundDown();	//function call to get all digits back to a single positive digit

	sum.Resize();	//resize sum's Number array is too large
	
	return sum;

	
	return sum;
}


/*
operator == (equivalence operator overload)
Input: The invoking HugeInteger object and a pointer to a HugeInteger
Execution: The values are assumed to be identical. An if/else statement first checks to see if the Size values are not equal. If they are not, the operator is flagged as false.
			If they are, each digit is checked to see if they are equivalent. If any are found to not be equal, the operator is flagged as false.
			The result is then returned.
Output: boolean statement
*/
bool HugeInteger::operator==(const HugeInteger * const right) const
{
	bool result = true;

	if (Size != right->Size)	//the numbers are different sizes, they are not equal
		result = false;
	else
		for (int i = 0; i < Size; i++)	//if any digits are not the same, they are not equal
			if (Number[i] != right->Number[i])
				result = false;

	return result;
}

/*
operator> (greater than operator overload)
Input: The invoking HugeInteger object and a pointer to a HugeInteger
Execution:	The invoking object is assumed to be greater than the pointed to HugeInteger. An if/else if statement first checks if the right object
			has a larger Size. if it does, then the operator is flagged as false. Otherwise, if the two have the same size, for loop is run to check
			each digit starting with the left side of the number (if 200, 2. if 5368789, 5. etc.) with an if/else if statement.If a digit in the invoking object is greater than
			the digit in the pointer's object, the loop is terminated early. If it is not, the digit is checked to see invoking object's digit is less than the pointer's digit.
			if it is, the statment is flagged as false. If all digits are checked and not found to have terminated the loop early by a digit being greater than the pointer's
			digit, then every digit must be less than or equal to the pointer's digits and the operator is flagged false.
Output: boolean statement
*/
bool HugeInteger::operator>(const HugeInteger * const right) const
{
	bool result = true;	//boolean value of the statement, assumed true

	if (Size < right->Size)	//if the invoking object has less digits than the pointer's object
		result = false;		//the statement isn't true
	
	else if (Size == right->Size)	//if they are the same number of digits, run a loop
		for (int i = 0; i < Size; i++)
		{
			if (Number[i] > right->Number[i])	//if the invoking object's digit is larger, end the loop early
				i = Size;
			
			else if (Number[i] < right->Number[i])	//otherwise if the invoking object's digit is smaller, flag false
				result = false;
			
			else if ( (i + 1) == Size )			//If the loops runs long enough to actually check all digits, the
				result = false;					//HugeInteger must be less than or equal to the pointer's object, flagging the operator false
		}


	return result;
	}

/*
RoundUp
Input: the invoking HugeInteger object
Execution: the for loop checks each digit of the HugeInteger starting with the "ones" digit. If the digit is over 10 (due to addition), 10 is subtracted and 
			one is added to the next higher digit.
Output: nothing
*/
void HugeInteger::RoundUp()
{
	for (int i = (Size - 1); i >= 0 ; i--)	//starting from the right (ones) digit...
	{
		if (Number[i] > 9)					//if the number in the array is 10 or above
		{
			Number[i] -= 10;				//bring it down to just the single digit (eg: 12 becomes 2)
			Number[i - 1]++;				//and add one to the next higher digit
		}
	}

}


/*
RoundDown
Input: The invoking HugeInteger object
Execution: the for loop starts at the far end of the HugeInteger number array (the "ones" digit). if it is less than
			zero, it "borrows" one from the next higher to make the digit positive
Output: nothing
*/
void HugeInteger::RoundDown()
{

	for (int i = (Size - 1); i >= 0 ; i--)	//starting from the right (ones) digit...
	{
		if (Number[i] < 0 && i != 0)				//if the number in the array is less than 0 and not 
		{
			Number[i] += 10;				//add that 10 to the digit (eg: -2 becomes 8)
			Number[i - 1]--;				//subtract one to the next higher digit
		}					//eg: 10 - 2 results in 1-2 in the subtraction operator. these two steps make it 08
	}

}



