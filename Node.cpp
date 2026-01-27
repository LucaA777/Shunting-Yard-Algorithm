#include "Node.h"

template<typename T> 
Node<T>::Node() {
  left = nullptr;
  right = nullptr;
  next = nullptr;
}

template<typename T>
Node<T>::Node(T val) {
  value = val;
  left = nullptr;
  right = nullptr;
  next = nullptr;
}

template<typename T>
void Node<T>::setValue(T val) {
  value = val;
}

template<typename T>
T Node<T>::getValue() {
  return value;
}

template<typename T>
void Node<T>::setLeft(Node<T>* &node) {
  left = node;
}

template<typename T>
Node<T>* &Node<T>::getLeft() {
  return left;
}

template<typename T>
void Node<T>::setRight(Node<T>* &node) {
  right = node;
}

template<typename T>
Node<T>* &Node<T>::getRight() {
  return right;
}

template<typename T>
void Node<T>::setNext(Node<T>* &node) {
  next = node;
}

template<typename T>
Node<T>* &Node<T>::getNext() {
  return next;
}

template class Node<int>;

