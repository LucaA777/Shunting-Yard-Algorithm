/*
General purpose queue implementation using a singly linked list.

Author: Luca Ardanaz
Last Updated: 27/1/2026
*/

#include "Node.h"

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

private:
  Node<T>* head;
};

#endif
