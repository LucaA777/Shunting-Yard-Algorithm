/*
General purpose queue implementation using a singly linked list.

Author: Luca Ardanaz
Last Updated: 27/1/2026
*/

#include "Node.h"
#include <iostream>

#ifndef QUEUE_H 
#define QUEUE_H 

template <typename T> class Queue {
public:
  Queue() {
    head = nullptr;
  }

  Queue(T value) {
    head = new Node<T>(value);
  }

  ~Queue() {
	Node<T>* current = head;
	Node<T>* previous = nullptr;

	//go and delete all of the nodes
	while (current != nullptr) {
		previous = current;
		current = current -> getNext();
		delete previous;	
	}
  }

  void enqueue(T value) {
    //empty queue case 
    if (head == nullptr) {
      head = new Node<T>(value);
      return;
    }
    
    Node<T>* current = head;

    //find the end of the linked list 
    while (current -> getNext() != nullptr) {
      current = current -> getNext();
    }

    //add a new node to the end 
    current -> setNext(new Node<T>(value));
  }

  T dequeue() {
    //empty queue case 
    if (head == nullptr) {
      T value;
      return value;
    }
    
    //single element queue case
    if (head -> getNext() == nullptr) {
      T value = head -> getValue();
      delete head;
      head = nullptr;
      return value;
    }

    //regular case, detach head.
    T value = head -> getValue();
    Node<T>* newHead = head -> getNext();
    delete head;
    head = newHead;
    return value;
  }

  bool isEmpty() {
    return head == nullptr;
  }

  void print() {
    Node<T>* current = head;
    
    //go through each element and print it.
    while (current != nullptr) {
      std::cout << current -> getValue() << " ";
      current = current -> getNext();
    }
  }

  Queue<T>* clone() {
    Queue<T>* newQueue = new Queue<T>();

    //for each element in the queue, make a copy of it and reconstruct the queue 
    Node<T>* current = head;
    while (current != nullptr) {
      newQueue -> enqueue(current -> getValue());
      current = current -> getNext();
    }

    return newQueue;
  }

private:
  Node<T>* head;
};

#endif
