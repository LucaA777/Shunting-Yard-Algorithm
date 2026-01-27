#include <iostream>

#include "Node.h"

using namespace std;

int main() {
  
  Node<int>* node;
  node = new Node<int>(5);
  cout << "Node value: " << node -> getValue() << endl;

  node -> setValue(15);
  cout << "Node value: " << node -> getValue() << endl;

  return 0;
}
