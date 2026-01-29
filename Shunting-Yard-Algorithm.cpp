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
bool isNumber(string input);
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
  string previousSubstring = "";
  string previousElement = "";

  for (char c : input) {

    //if a space is reached, ignore it
    if (c == ' ') {
      continue;
    }

    //add character to substring
    previousSubstring = substring;
    substring += c;

    //if the previous output was a number and the current character is a '-', output it. 
    if (previousElement != "" && isNumber(previousElement) && substring == "-") {
      output -> enqueue(substring);
      previousElement = substring;
      substring = "";
      continue;
    }

    //if the substring is currently a number, there may be more digits, don't enqueue yet 
    //if the substring isn't a number, but the previous one is, then we must add the previous substring.

    if (!isNumber(substring) && isNumber(previousSubstring)) {
      output -> enqueue(previousSubstring);
      previousElement = substring;
      //set the current substring to be the current char 
      substring = c;
    }

    //check if the new substring is also valid and not a number  
    if (validString(substring) && !isNumber(substring)) {
      output -> enqueue(substring);
      previousElement = substring;
      substring = "";
    }
  }

  //add last substring to the output if its not empty
  if (substring == "") {
    return output;
  }
  else if (validString(substring)) {
    output -> enqueue(substring);
    return output;
  }
  else {
    return new Queue<string>();
  }
}

bool validString(string input) {
  //check if the string is a number, if so it is an operand and thus valid.
  if (isNumber(input)) {
    return true;
  }

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

bool isNumber(string input) {
  /*
    Conditions to be a number: 
      - A negative sign can only be the first character
      - There can only be one decimal point
      - Everything else must be a number
      - Can't be empty
  */

  if (input == "") {
    return false;
  }

  bool decimalFound = false;

  for (int i = 0; i < input.length(); i++) {

    //invalid negative placement check  
    if (input[i] == '.' && i != 0) {
      return false;
    }

    //decimal point check 
    if (input[i] == '.' && decimalFound) {
      return false;
    }

    //update decimal boolean
    if (input[i] == '.') {
      decimalFound = true;
    }


    //check whether the character is not in the valid set 
    if (input[i] != '0' &&
      input[i] != '1' &&
      input[i] != '2' &&
      input[i] != '3' &&
      input[i] != '4' &&
      input[i] != '5' &&
      input[i] != '6' &&
      input[i] != '7' &&
      input[i] != '8' &&
      input[i] != '9' &&
      input[i] != '-' &&
      input[i] != '.')
    {
      return false;
    }
  }

  //if nothing was wrong, return true 
  return true;

}

Queue<string>* infixToPostfix(Queue<string>* infix) {
  Queue<string>* output = new Queue<string>();
  Stack<string>* stack = new Stack<string>();

  //go through the infix and process the strings
  while (!infix -> isEmpty()) {
    string element = infix -> dequeue();

    //if the element is a number, push it to the output
    if (isNumber(element)) {
      output -> enqueue(element);
      continue;
    }

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
    if (isNumber(element)) {
      //if so, push to the stack 
      treeStack -> push(new Node<string>(element));
      continue;
    }

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
