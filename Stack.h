/*
General purpose stack implementation using a singly linked list.

Author: Luca Ardanaz
Last Updated: 27/1/2026
*/

#include "Node.h"
#include <iostream>

#ifndef Stack_H 
#define Stack_H 

template <typename T> class Stack {
public:
  Stack() {
    head = nullptr;
  }

  Stack(T value) {
    head = new Node<T>(value);
  }

  void push(T value) {
    //empty stack case
    if (head == nullptr) {
      head = new Node<T>(value);
      return;
    }

    Node<T>* current = head;

    //find the end of the linked list
    while (current -> getNext() != nullptr) {
      current = current -> getNext();
    }

    //connect the new node to the end
    current -> setNext(new Node<T>(value));
  }

  T pop() {
    //empty stack case
    if (head == nullptr) {
      T value;
      return value;
    }

    Node<T>* current = head;
    Node<T>* previous = nullptr;

    //find the end of the linked list 
    while (current -> getNext() != nullptr) {
      previous = current;
      current = current -> getNext();
    }

    T value = current -> getValue();

    //if there is only one element in the stack, set the head to null
    if (previous == nullptr) {
      head = nullptr;
      delete current;
      return value;
    }
    
    //remove the node from the stack and return it
    previous -> setNext(nullptr);
    delete current;
    return value;
    
  }
  
  T peek() {
    //empty stack case 
    if (head == nullptr) {
      T value;
      return value;
    }

    Node<T>* current = head;

    //find the end of the linked list
    while (current -> getNext() != nullptr) {
      current = current -> getNext();  
    }

    //returns the last element in the linked list, the top of the stack
    return current -> getValue();
  }

  bool isEmpty() {
	  return head == nullptr;
  }

  void print() {
    Node<T>* current = head;

    //go through each element and print it 
    while (current != nullptr) {
      std::cout << current -> getValue() << " ";
      current = current -> getNext();
    }
  }

private:
  Node<T>* head;
};

#endif
