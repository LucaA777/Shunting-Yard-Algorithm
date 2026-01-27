#ifndef NODE_H
#define NODE_H 

template <typename T> class Node {
public:
  Node();
  Node(T val);
  ~Node();

  void setValue(T val);
  T getValue();

  void setLeft(Node<T>* &node);
  Node<T>* &getLeft();

  void setRight(Node<T>* &node);
  Node<T>* &getRight();

  void setNext(Node<T>* &node);
  Node<T>* &getNext();

private:
  T value;
  Node<T>* left;
  Node<T>* right;
  Node<T>* next;
};

#endif
