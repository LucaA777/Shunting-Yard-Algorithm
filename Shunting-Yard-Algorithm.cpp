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
#include <cmath>

using namespace std;

Queue<string>* createInfixFromString(string input);
bool validString(string input);
bool isNumber(string input);
Queue<string>* infixToPostfix(Queue<string>* infix);
bool shouldPopStack(string newOperator, string stackOperator);
bool shoudlOpenParenthesis(string currentOperator, string previousOperator);
Node<string>* postfixToTree(Queue<string>* postfix);
string toLower(string str);
void treeToPostfix(Stack<string>* &postfix, Node<string>* node);
void treeToPrefix(Queue<string>* &prefix, Node<string>* node);
void treeToInfix(Queue<string>* &infix, Node<string>* node, string nextOperator);
double solveFromTree(Node<string>* node);
void deleteTree(Node<string>* node);

int main() {

  Queue<string>* infix = nullptr;
  Node<string>* tree = nullptr;
  string input = "";
  //input loop 
  do {
    cout << endl << endl;
    cout << "Enter an expression or a command (TREE, INFIX, PREFIX, POSTFIX, SOLVE, QUIT): " << endl;
    getline(cin, input);
    input = toLower(input);

    if (input == "tree") {
      //check if the infix has been defined
      if (tree == nullptr) {
        cout << "You must enter an expression first." << endl;
        continue;
      }

      //otherwise, make the tree 
      cout << "Equation tree: " << endl;
      tree -> printTree();
      cout << endl;
      continue;
    }

    if (input == "postfix") {
      Stack<string>* postfix = new Stack<string>();
      treeToPostfix(postfix, tree);
      cout << "Postfix: " << endl;

      while (!postfix -> isEmpty()) {
        cout << postfix -> pop() << " ";
      }

      cout << endl;
      delete postfix;
      continue; 
    }

    if (input == "prefix") {
      Queue<string>* prefix = new Queue<string>();
      treeToPrefix(prefix, tree);
      cout << "Prefix: " << endl;

      while (!prefix -> isEmpty()) {
        cout << prefix -> dequeue() << " ";
      }

      cout << endl;
      delete prefix;
      continue;
    }

    if (input == "infix") {
      Queue<string>* nInfix = new Queue<string>();
      treeToInfix(nInfix, tree, "+");
      cout << "Infix: " << endl;

      while (!nInfix -> isEmpty()) {
        cout << nInfix -> dequeue() << " ";
      }
      cout << endl;
      delete nInfix;
      continue;
    }

    if (input == "solve") {
      cout << " = " << solveFromTree(tree) << endl;
      continue;
    }

    if (input == "quit") {
      continue;
    }	

    //if the input doesn't match a command, try converting it into an expression
    if (createInfixFromString(input) == nullptr) {
      cout << "That is not a valid expression." << endl;
      continue;
    }


    //if it is valid, then set it as our infix
    infix = createInfixFromString(input);
    Queue<string>* postfix = infixToPostfix(createInfixFromString(input) -> clone());
    tree = postfixToTree(postfix);
    infix -> print();
    cout << endl;


  } while (input != "quit");

  delete infix;
  infix = nullptr;
  deleteTree(tree);
  tree = nullptr;

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

    //if the previous element was not an operator and the current substring is a minus sign, enqueue it
    if (isNumber(previousElement) && previousElement != "-" && previousSubstring == "-") {
      output -> enqueue(previousSubstring);
      substring = c;
      previousElement = previousSubstring;
      continue;
    }


    //if the previous substring is a number but the current isn't, it enqueue the number 
    if (isNumber(previousSubstring) && !isNumber(substring)) {
      output -> enqueue(previousSubstring);
      substring = c;
      previousElement = previousSubstring;
      continue;
    }

    //if the previous substring is valid but the current isn't, enqueue it 
    if (validString(previousSubstring) && !validString(substring)) {
      output -> enqueue(previousSubstring);
      substring = c;
      previousElement = previousSubstring;
      continue;
    }


  }

  //add last substring to the output if its not empty and a number
  if (substring == "") {
    return output;
  }

  if ((isNumber(substring) && substring != "-" && substring != ".") || substring == ")") {
    output -> enqueue(substring);
    return output;
  }

  return nullptr;
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
  return false;
}

bool isNumber(string input) {
  /*
     Conditions to be a number: 
     - There can only be one decimal point
     - Everything else must be a number
     - Negative sign can only be in front
     - Can't be empty
     - Can't be just a valid symbol
     */

  if (input == "") {
    return false;
  }

  if (input == "-") {
    return false;
  }

  if (input == ".") {
    return false;
  }

  bool decimalFound = false;

  for (int i = 0; i < input.length(); i++) {

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
      input[i] != '.' &&
      input[i] != '-')
    {
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

    //negative sign check
    if (input[i] == '-' && i != 0) {
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

  delete stack;
  delete infix;

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

bool shoudlOpenParenthesis(string currentOperator, string previousOperator) {
  map<string, int> precedence = {
    {"^", 4},
    {"*", 3},
    {"/", 3},
    {"+", 2},
    {"-", 2}
  };
  
  //if the current operator is of lower precedence, then we must add parenthesis
  if (precedence[currentOperator] < precedence[previousOperator]) {
    return true;
  }

  return false;
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

    //if there aren't numbers yet, the equation is invalid
    if (treeStack -> isEmpty()) {
      delete treeStack;
      delete postfix;
      return nullptr;
    }

    Node<string>* right = treeStack -> pop();

    //if there was only one number, the equation is invalid
    if (treeStack -> isEmpty()) {
      delete treeStack;
      delete postfix;
      return nullptr;
    }

    Node<string>* left = treeStack -> pop();

    Node<string>* parent = new Node<string>(element);
    parent -> setRight(right);
    parent -> setLeft(left);

    //add this new tree to the stack again
    treeStack -> push(parent);
  }

  delete postfix;
  return treeStack -> pop();
}

string toLower(string str) {
  for (char& c : str) {
    c = (char)tolower(c);
  }

  return str;
}

void treeToPostfix(Stack<string>* &postfix, Node<string>* node) {

  //go down the right branches until reaching the end, then start going left
  postfix -> push(node -> getValue());

  if (node -> getRight() != nullptr) {
    treeToPostfix(postfix, node -> getRight());
  }

  if (node -> getLeft() != nullptr) {
    treeToPostfix(postfix, node -> getLeft());
  }
}

void treeToPrefix(Queue<string>* &prefix, Node<string>* node) {
  //go down the left branches until reaching the end, then start going right
  prefix -> enqueue(node -> getValue());

  if (node -> getLeft() != nullptr) {
    treeToPrefix(prefix, node -> getLeft());
  }

  if (node -> getRight() != nullptr) {
    treeToPrefix(prefix, node -> getRight());
  }
}

void treeToInfix(Queue<string>* &infix, Node<string>* node, string nextOperator) {
  //go all the way to the left, then start adding elements before going to the right

  bool isOperator = !isNumber(node -> getValue());
  cout << "At: " << node -> getValue() << endl;
  cout << "Parent operator: " << nextOperator << endl;

  if (isOperator && shoudlOpenParenthesis(node -> getValue(), nextOperator)) {
    infix -> enqueue("(");    
    cout << "Opening parenthesis..." << endl;
  }


  if (node -> getLeft() != nullptr) {
    cout << "Going left..." << endl;
    treeToInfix(infix, node -> getLeft(), isOperator ? node -> getValue() : nextOperator);
  }

  cout << "Adding element: " << node -> getValue() << " parent operator: "<< (isOperator ? nextOperator : "n/a") << endl;
  infix -> enqueue(node -> getValue());

  if (node -> getRight() != nullptr) {
    cout << "Going right..." << endl;
    treeToInfix(infix, node -> getRight(), isOperator ? node -> getValue() : nextOperator);
  }

  
  if (isOperator && shoudlOpenParenthesis(node -> getValue(), nextOperator)) {
    cout << "Closing parenthesis." << endl;
    infix -> enqueue(")");
  }

}

double solveFromTree(Node<string>* node) {
  string value = node -> getValue();

  //if it is an operator, go get the children to use as operands
  if (!isNumber(value) && validString(value)) {
    double first = 0;
    double second = 0;

    if (node -> getLeft() != nullptr) {
      first = solveFromTree(node -> getLeft());
    }

    if (node -> getRight() != nullptr) {
      second = solveFromTree(node -> getRight());
    }


    //perform the actual operator 
    if (value == "+") {
      return first + second;
    }
    if (value == "-") {
      return first - second;
    }
    if (value == "*") {
      return first * second;
    }
    if (value == "/") {
      return first / second;
    }
    if (value == "^") {
      return pow(first, second);
    }
  }

  //must be a number, so return it for the operators further down
  try {
    return stod(node -> getValue());
  }
  catch (...) {
    cout << "Fatal error." << endl;
  }
  return 0.0;
}

void deleteTree(Node<string>* node) {
  //skip if the node is null for any reason
  if (node == nullptr) {
    return;
  }

  //delete all of the children before deleting self
  if (node -> getLeft() != nullptr) {
    deleteTree(node -> getLeft());
  }
  if (node -> getRight() != nullptr) {
    deleteTree(node -> getRight());
  }
  delete node;
}
