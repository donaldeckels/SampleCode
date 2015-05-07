#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

class Stack{
	private:
		int top; //index for top
		int *base;
		int maxIndex; //restricts from out of bounds
	public:
		Stack(int *base, int size){
			top = -1;
			this->base = base;
			maxIndex = (size-1);
		}
		int push(int put){
			if(top<maxIndex){
				base[++top] = put;
				return put;
			}
			return -1;
		}
		int pop(){
			if(top == -1){
				return -1;
			}
			int ret = base[top--];
			return ret;
		}
		int peek(){return base[top];}
		~Stack(){}
};

int main(){
	int stuff[30];
	Stack stackA(stuff,10);
	Stack stackB(stuff+10,10);
	Stack stackC(stuff+20,10);
	srand(time(NULL));
	int input;
	for(int i=0; i<11;i++){
		input = rand()%100;
		cout << "Pushing " << input << " to stackA" << endl;
		input = stackA.push(input);
		if(input == -1){
			cout << "value wasn't accepted!" << endl;
		}
	}
	for(int i=0; i<11;i++){
		input = rand()%100;
		cout << "Pushing " << input << " to stackB" << endl;
		input = stackB.push(input);
		if(input == -1){
			cout << "value wasn't accepted!" << endl;
		}
	}
	for(int i=0; i<11;i++){
		input = rand()%100;
		cout << "Pushing " << input << " to stackC" << endl;
		input = stackC.push(input);
		if(input == -1){
			cout << "value wasn't accepted!" << endl;
		}
	}
	printf("Time to pull out values!\n");
	for(int i=0; i<11; i++){
		input = stackA.pop();
		if(input == -1){
			cout << "Nothing left in stackA!" << endl;
		}
		else{
			cout << "Pulled " << input << " from stackA" << endl;
		}
	}
	for(int i=0; i<11; i++){
		input = stackB.pop();
		if(input == -1){
			cout << "Nothing left in stackB!" << endl;
		}
		else{
			cout << "Pulled " << input << " from stackB" << endl;
		}
	}
	for(int i=0; i<11; i++){
		input = stackC.pop();
		if(input == -1){
			cout << "Nothing left in stackC!" << endl;
		}
		else{
			cout << "Pulled " << input << " from stackC" << endl;
		}
	}
	cin >> input;
}