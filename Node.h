/*
General use Node class for any type. Designed to be open ended
and usable for any project which may require nodes.

Author: Luca Ardanaz
Last Updated: 26/1/2026
*/

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

private:
  T value;
  Node<T>* left;
  Node<T>* right;
  Node<T>* next;
};

#endif
