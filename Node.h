/*
General use Node class for any type. Designed to be open ended
and usable for any project which may require nodes.

Author: Luca Ardanaz
Last Updated: 26/1/2026
*/

#include <iostream>

#ifndef NODE_H
#define NODE_H 

template <typename T> class Node {
public:
  Node() {
    left = nullptr;
    right = nullptr;
    next = nullptr;
  }

  Node(T val) {
    value = val;
    left = nullptr;
    right = nullptr;
    next = nullptr;
  }

  ~Node() {
	    left = nullptr;
	    right = nullptr;
	    next = nullptr;
    }
  }

  void setValue(T val) {
    value = val;
  }

  T getValue() {
    return value;
  }

  void setLeft(Node<T>* node) {
    left = node;
  }

  Node<T>* getLeft() {
    return left;
  }

  void setRight(Node<T>* node) {
    right = node;
  }

  Node<T>* getRight() {
    return right;
  }

  void setNext(Node<T>* node) {
    next = node;
  }

  Node<T>* getNext() {
    return next;
  }

  void printTree() {
    printTreeRecursion(this, 1);
  }

private:
  T value;
  Node<T>* left;
  Node<T>* right;
  Node<T>* next;

  void printTreeRecursion(Node<T>* node, int depth) {

    //prints everything to the right of an index first
    if (node -> getRight() != nullptr) {
      printTreeRecursion(node -> getRight(), depth + 1);
    }

    //adds appropriate spacing
    for (int i = 0; i < depth - 1; i++) {
      std::cout << "\t";
    }	

    //prints index
    std::cout << node -> getValue() << std::endl;

    //then prints everything to the left
    if (node -> getLeft() != nullptr) {
      printTreeRecursion(node -> getLeft(), depth + 1);
    }
  }
};

#endif
