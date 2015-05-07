#include <iostream>

using namespace std;

int bitFlipsNeeded(int A, int B){
	int count = 0;
	while(A !=0 || B != 0){ //continue while both are not zero
		if((A&1) != (B&1)){ //if LSB's are not equal
			++count;
		}
		A = A>>1; //right bit shift by 1
		B = B>>1;
	}
	return count;
}

int swapBitPairs(int A){
	return (((A & 0xAAAAAAAAAAAAAAAA) >> 1) | ((A & 0x5555555555555555) << 1));
}


int main(){
	int A, B, C;
	while(1){
		cout << "Enter an integer: ";
		cin >> A;
		C = swapBitPairs(A);
		cout << A << " flipped by bit pairs is " << C << endl;
		//cout << A << " and " << B << " have " << C << " bits different." << endl;
	}
}