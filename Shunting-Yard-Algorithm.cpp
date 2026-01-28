/*
   Implementation of the shunting yard algorithm using stacks and queues implemented
   with linked lists.

Author: Luca Ardanaz
Last Updated: 27/1/2026
*/

#include "Stack.h"
#include "Queue.h"

#include <iostream>
#include <string>

using namespace std;

bool validString(string input);
Queue<string>* createInfixFromString(string input);

int main() {

	//basic tester to see if the infix creation works

	cout << "Enter an expression (space seperated): " << endl;
	string input;
	getline(cin, input);

	Queue<string>* infix = createInfixFromString(input);
	string out;
	while (!infix -> isEmpty()) {
		cout << infix -> dequeue() << " ";
	}
	cout << endl;

	return 0;
}

Queue<string>* createInfixFromString(string input) {
	Queue<string>* output = new Queue<string>();
	string substring = "";
	for (char c : input) {

		//if a space is reached, check if the substring is valid.
		if (c == ' ') {

			//if it is valid, add to output
			if (validString(substring)) {
				output -> enqueue(substring);
				substring = "";
			}
			//otherwise, abort.
			else {
				return new Queue<string>();
			}
		}

		//if not a space, add it to the substring
		else {
			substring += c;
		}
	}

	//add last substring to the output if its valid
	if (validString(substring)) {
		output -> enqueue(substring);
		substring = "";
	}
	else {
		return new Queue<string>();
	}


	return output;
}

bool validString(string input) {
	//check if the string is a number, if so it is an operand and thus valid.
	try {
		double num = stoi(input);
		return true;
	}
	catch(...) {}

	//check if the string is in the valid set of operators.
	if (input == "+" ||
			input == "-" ||
			input == "*" ||
			input == "/" ||
			input == "(" ||
			input == ")") 
	{
		return true;  
	}
	cout << "INVALID INPUT" << endl;
	return false;
}

