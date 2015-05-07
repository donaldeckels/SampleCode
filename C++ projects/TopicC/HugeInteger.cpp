/* Donald Eckels
Topic C Project
3/1/12

HugeInteger.cpp */


#include "hugeinteger.h"

using namespace std;



/*
HugeInteger constructor
Input: optional string for name
Execution: It creates a HugeInteger object.
			It sets the size for the array to 40 and creates an integer array of size 40 to hold the
			HugeInteger.
Output: One new HugeInteger object for the program.
*/
HugeInteger::HugeInteger()
{
	Size = 40; //Set the array size to 40
	
	Number = new int[Size];		//Create an array of integers the size of default

	Zero();

}


/*
HugeInteger copy constructor
Input:One HugeInteger object
Execution: when the new object is created as a copy, the size is copied.
			A new number array is allocated in memory for the HugeInteger
Output: The copy of a HugeInteger
*/
HugeInteger::HugeInteger( const HugeInteger &Input )
{
	Size = Input.Size;	//set new array's size to the size of the original array
	
	Number = new int [Size];	//Create the new array

	for (int i = 0; i < Size; i++) //fill the array being created with the original array values
		Number[i] = Input.Number[i];

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
Resize
Input: The HugeInteger Executing the function.
Execution: It checks all values of the digits of the array. A loop is executed to find the first non-zero digit.
			The size of the array minus the number of iterations completed gives the number of leading zeroes.
			However, if the entire array is checked and every digit is zero, the new array will be one digit.
			A new temporary array is created with the final size of the number. The huge integer without the leading zeroes is
			copied to the temporary array in order to delete the Number array, change the size to the final size, allocate the
			Number array in free store, and place the number back into the Number array. The temporary array is deleted.
Output: nothing
*/
void HugeInteger::Resize()
{
	int newSize = Size;	//holder for the new value of the size while it is being calculated
	int *temp;			//holder for the new array pointer
	int LeadZero;		//holds the number of leading zeroes
	
	
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
Execution: The array is first resized to be the same size as the string and all digits set to zero. Each character in
			the string is then evaluated. If it is not a digit, the return value is flagged as false. If it is a digit,
			it is translated from the character of that digit to the same integer. HugeInteger is then resized to
			eliminate any leading zeroes contained within the input
Output: boolean value stating if the string was good or not, Number array filled with values from the string
*/
bool HugeInteger::stringIn (const string & strInput)
{
	bool check = true;	//keep track if the input values are numbers or not
	unsigned i = 0;		//number to track slots filled through both loops

	delete [] Number;
	Size = strInput.size();
	Number = new int [Size];
	Zero();

	for (; i < strInput.size() ; i++)
	{
		if ( !(isdigit (strInput[i]) ) )	//first check to see if it is a digit
			check = false;					//if not, notify invoking function
		else 	//if it is, convert digit character to single integer
			Number[i] = (strInput[i] - '0');
	}

	Resize();

	return check;
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
HugeInteger HugeInteger::operator+(const HugeInteger & right) const
{
	HugeInteger sum;									//HugeInteger to hold the sum
	
	if (Size >= sum.Size || right.Size >= sum.Size)	//If the sum HugeInteger is the same size or smaller than either array. make it one digit larger than the larger array
	{
		delete [] sum.Number;
		sum.Size = ((Size >= right.Size) ? (Size + 1) : (right.Size + 1));
		sum.Number = new int[sum.Size];
	}
	
	for (int i = 0; i < sum.Size; i ++)					//Fill sum array with zeroes
		sum.Number[i] = 0;
	
	int s = 1;											//value to use for both loops

	for (; s <= Size && s <= right.Size ; s++)			//add each Number array value from right to left (smallest to largest) as long as both array have a value for that digit
		sum.Number[sum.Size - s] = Number[Size - s] + right.Number[(right.Size) - s];
	
	if (Size > right.Size)								//if the invoking HugeInteger is larger, move the rest of the values to the sum
		for (; s <= Size ; s++)
			sum.Number[sum.Size - s] = Number[Size - s];
	
	else if (Size < right.Size)						//if the right HugeInteger is larger, move the rest of the vlues to the sum
		for (; s <= right.Size; s++)
			sum.Number[sum.Size - s] = right.Number[right.Size - s];


	
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
HugeInteger HugeInteger::operator-(const HugeInteger & right) const
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

	for (; s <= Size && s <= right.Size ; s++)			//subtract each Number array value from right to left (smallest to largest) as long as both array have a value for that digit
		sum.Number[sum.Size - s] = Number[Size - s] - right.Number[(right.Size) - s];
	
	if (Size > right.Size)								//if the invoking HugeInteger is larger, move the rest of the values to the sum
		for (; s <= Size ; s++)
			sum.Number[sum.Size - s] = Number[Size - s];


	sum.RoundDown();	//function call to get all digits back to a single positive digit

	sum.Resize();	//resize sum's Number array is too large
	
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
bool HugeInteger::operator==(const HugeInteger & right) const
{
	bool result = true;

	if (Size != right.Size)	//the numbers are different sizes, they are not equal
		result = false;
	else
		for (int i = 0; i < Size; i++)	//if any digits are not the same, they are not equal
			if (Number[i] != right.Number[i])
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
bool HugeInteger::operator>(const HugeInteger & right) const
{
	bool result = true;	//boolean value of the statement, assumed true

	if (Size < right.Size)	//if the invoking object has less digits than the pointer's object
		result = false;		//the statement isn't true
	
	else if (Size == right.Size)	//if they are the same number of digits, run a loop
		for (int i = 0; i < Size; i++)
		{
			if (Number[i] > right.Number[i])	//if the invoking object's digit is larger, end the loop early
				i = Size;
			
			else if (Number[i] < right.Number[i])	//otherwise if the invoking object's digit is smaller, flag false
				result = false;
			
			else if ( (i + 1) == Size )			//If the loops runs long enough to actually check all digits, the
				result = false;					//HugeInteger must be less than or equal to the pointer's object, flagging the operator false
		}


	return result;
	}

/*
operator() (overloaded () for integer input)
Input: the invoking HugeIntegerObject and one integer
Execution: The number placed in the parentheses is treated as the new desired number
			for the HugeInteger. The input is evaluated one digit at a time. First, the
			modulus of the input by a given power of 10, starting at 10^1, is taken to 
			remove all leading digits from the currently desired digit and saved into a
			holding variable. Second, the holding variable is divided by one lower power of
			10 than before, which results in a single digit. The isolated digit is placed in
			the corresponding index of the HugeInteger. This process starts with the ones
			digit and continue until the final digit of the input is being read. If the input
			number has more digits than the HugeInteger can currently hold, it is resized to be
			10 digits larger and all current digits are moved to the new array.
			 
Output: None
*/

void HugeInteger::operator()(const int input)
{
	int inDigit = 10;		//for isolating digits
	int hDigit = (Size - 1);	//location digit is being placed into the array
	int slot;				//holder for digit
	bool end = false;			//check to continue the loop

	Zero();					//clear the current value held with the HugeInteger

	while(!end)
	{
		if (hDigit < 0)		//check to verify the next digit has a space in the array, if not
		{
			int *temp;		//create a temporary integer array that is larget than the current array
			temp = new int[Size + 10];
			
			for (int i = 0; i < 10; ++i)	//fill all new slots with zeroes
				temp[i] = 0;
			
			for (int i = 0; i < Size; ++i)	//copy all existing slots to the new array
				temp[i + 10] = Number[i];
			
			delete [] Number;		//delete the original Number array
			Number = temp;			//pass the address of the temp array to the Number array
			
			Size += 10;				//increase Size to match the size of the now adjusted array
		}
		
		slot = input % inDigit;		//Save into slot the modulus (remainder) of dividing the input
									//by the given power of 10. (eg: 123 % 100 = 23)

		if (slot == input)			//when the digit holder is equivalent to the input at this point, the
			end = true;				//final digit is being transferred and another loop will be unnecessary
					
		slot /= (inDigit / 10);		//remove all lower digits from the currently desired value
									//(eg: 23 / (100 / 10) = 2
		Number[hDigit] = slot;		//assign the digit to the slot currently being filled
		
		inDigit *= 10;				//increment the input digit locaiton
		--hDigit;					//decrement the Number array index to move to the corresponding digit
	}

	Resize();
}


/*
operator () (overloaded () for string input)
Input: The invoking HugeInteger Object and one string
Execution:	The string placed in the praretheses is treated as the new desired number
			for the HugeInteger. A copy of the HugeInteger is array is made and stored.
			The function sends the string through the stringIn member function to
			verify it does consist of only digits. If the input was good, the value is
			kept. However, if the input was invalid, the original number held by HugeInteger
			is restored and the user is notified of the error.
Output: none
*/
void HugeInteger::operator()(const string input)
{
	bool check = false;	//bool flag for input checking

	int * hold;			//create holding array for current value of the HugeInteger
	int holdSize;
	
	hold = new int[Size];
	holdSize = Size;

	for (int i = 0; i < Size; ++i)
		hold[i] = Number[i];

	check = stringIn(input);	//put the string into the HugeInteger and change to show if the input was valid

	if (!check)					//if input was invalid
	{
		cout << input << " is an invalid input. Value not stored\n\n";	//tell the user
		delete [] Number;												//restore the previous value of the HugeInteger
		Number = hold;
		Size = holdSize;
	}
	else
		delete [] hold;	//if the input was valid, delete the previous value
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

/*
Zero
Input:The invoking HugeInteger object
Execution: Every digit in the HugeInteger array is set to zero
Output: none
*/
void HugeInteger::Zero()
{
	for (int i = 0; i < Size; ++i)
		Number[i] = 0;
}




/*
operator << (out stream operator overload)
Input: the specified ostream (lvalue), one HugeInteger object (rvalue)
Execution: A loop sends each digit of the HugeInteger to the ostream for
			processing. Once all values have been passed, a new line
			is started to ensure readability of the HugeInteger
Output: the specified ostream (for chaining to the ostream)
*/
ostream & operator<<(ostream & out, const HugeInteger & HI)
{
	for (int i = 0; i < HI.Size; ++i)
		out << HI[i];
	out << endl;

	return out;
}