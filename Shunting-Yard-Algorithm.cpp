/*
   Implementation of the shunting yard algorithm using stacks and queues implemented
   with linked lists.

Author: Luca Ardanaz
Last Updated: 27/1/2026
*/

#include "Stack.h"
#include "Queue.h"
#include "Node.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

Queue<string>* createInfixFromString(string input);
bool validString(string input);
Queue<string>* infixToPostfix(Queue<string>* infix);
bool shouldPopStack(string newOperator, string stackOperator);
Node<string>* postfixToTree(Queue<string>* postfix);

int main() {

	//basic tester to see if the infix creation works

	cout << "Enter an expression (space seperated): " << endl;
	string input;
	getline(cin, input);

	Queue<string>* infix = createInfixFromString(input);

	Queue<string>* postfix = infixToPostfix(infix -> clone());

  cout << "Infix: ";
  infix -> print();
  cout << endl;
  

  cout << "Postfix: ";
  postfix -> print();
  cout << endl;

  Node<string>* equationTree = postfixToTree(postfix -> clone());
  cout << "Equation tree: " << endl;
  equationTree -> printTree();
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
		double num = stod(input);
		return true;
	}
	catch(...) {}

	//check if the string is in the valid set of operators.
	if (input == "+" ||
			input == "-" ||
			input == "*" ||
			input == "/" ||
			input == "(" ||
			input == ")" ||
			input == "^") 
	{
		return true;  
	}
	cout << "INVALID INPUT" << endl;
	return false;
}

Queue<string>* infixToPostfix(Queue<string>* infix) {
	Queue<string>* output = new Queue<string>();
	Stack<string>* stack = new Stack<string>();

	//go through the infix and process the strings
	while (!infix -> isEmpty()) {
		string element = infix -> dequeue();

		//if the element is a number, push it to the output
		try {
			double num = stod(element);
			output -> enqueue(element);
			continue;
		}
		catch (...) {}

		//if the element is an operator, process it
		
		//always push open parenthesis
		if (element == "(") {
			stack -> push(element);
		}

		//when closing parenthesis, pop until matching open
		else if (element == ")") {
			string stackOperator;
			do {
				stackOperator = stack -> pop();

				if (stackOperator != "(") {
					output -> enqueue(stackOperator);
				}

			} while (stackOperator != "(");
		}

		//for other operators, check if the stack should be popped
		//pop until it reaches a point it doesn't need to
		else {
			while (shouldPopStack(element, stack -> peek())) {
				output -> enqueue(stack -> pop());
			}
			stack -> push(element);
		}

	}
  
  //end by pushing the stack into the queue
  while (!stack -> isEmpty()) {
    output -> enqueue(stack -> pop());
  }

	return output;

}

bool shouldPopStack(string newOperator, string stackOperator) {
	//define precedence for all the operators
	map<string, int> precedence = {
		{"^", 4},
		{"*", 3},
		{"/", 3},
		{"+", 2},
		{"-", 2}
	};	
	
	//if new has higher precedence, it should be added to the stack
	if (precedence[newOperator] > precedence[stackOperator]) {
		return false;
	}

	//since ^ is right-evaluated, don't pop consecutive
	if (newOperator == "^" && stackOperator == "^") {
		return false;
	}

	//otherwise, the stack should be popped
	return true;


}

Node<string>* postfixToTree(Queue<string>* postfix) {
  Stack<Node<string>*>* treeStack = new Stack<Node<string>*>();

  //go through all of the elements and arrange them into a tree 
  while (!postfix -> isEmpty()) {
    //store queue element 
    string element = postfix -> dequeue();

    //check to see if it's an operand
    try {
		  double num = stod(element);
		  
      //if so, push to the stack
      treeStack -> push(new Node<string>(element));
      continue;
	  }
	  catch(...) {}

    //otherwise, it must be an operator
    //take the last two branches of the tree, and unite them as children of the operator
    Node<string>* right = treeStack -> pop();
    Node<string>* left = treeStack -> pop();
    
    Node<string>* parent = new Node<string>(element);
    parent -> setRight(right);
    parent -> setLeft(left);

    //add this new tree to the stack again
    treeStack -> push(parent);
  }

  //this assumes that a valid postfix equation was entered
  return treeStack -> pop();
}
