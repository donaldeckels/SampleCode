#include <iostream>
#include <string>
#include <list>
#include <iterator>

using namespace std;

string encode(list<string> input){
	string output;
	list<string>::iterator inputPos = input.begin();
	short int len;
	for(inputPos = input.begin();inputPos != input.end();inputPos++){
		if( inputPos->size() >= 65536){
			return NULL;
		}
		len = inputPos->size();
		char a, b;
		a = len/256;
		b = len%256;
		output += a;
		output += b;
		output += *inputPos;
	}
	return output;
}

list<string> decode (string input){
	list<string> output;
	string buffer;
	short int len;
	bool more = true;
	for(int i=0; i<input.length();){
		len = (input.at(i++)<<8) + input.at(i++);
		for(int j=i;(j<(i+len))&&(j<=input.length());j++){
			buffer += input.at(j);
		}
		output.push_back(buffer);
		buffer.clear();
		i += len;
	}
	return output;
}

int main(){
	list<string> input;
	input.push_back("abcdefghijklmnopqrstuvwxyz");
	input.push_back("def");
	input.push_back("ggg");
	string output = encode(input);
	cout << output << endl;
	input.clear();
    input = decode(output);
	cout << "Decoded strings:" << endl;
	list<string>::iterator inputPos = input.begin();
	for(inputPos = input.begin();inputPos != input.end();inputPos++){
		cout << *inputPos << endl;
	}
	cout << "That's all folks!" << endl;
	cin >> output;

	return 0;
}