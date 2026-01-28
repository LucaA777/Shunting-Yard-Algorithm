#include <iostream>

#include "Node.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

int main() {
  
  Node<int>* node1 = new Node<int>(5);
  cout << "Node 1 value: " << node1 -> getValue() << endl;

  Node<int>* node2 = new Node<int>(15);
  cout << "Node 2 value: " << node2 -> getValue() << endl;

  Stack<int>* stack = new Stack<int>();
  cout << "Empty stack peek: " << stack -> peek() << endl;

  stack -> push(22);
  cout << "Stack top 22 peek: " << stack -> peek() << endl;

  stack -> push(47);
  cout << "Stack push 47 pop: " << stack -> pop() << endl;
  cout << "Stack post-pop: " << stack -> peek() << endl;

  Queue<char>* queue = new Queue<char>('a');

  queue -> enqueue('b');
  queue -> enqueue('c');

  cout << "Alphabet queue dequeue 1: " << queue -> dequeue() << endl;
  cout << "Aplhabet queue dequeue 2: " << queue -> dequeue() << endl;
  cout << "Alphabet queue dequeue 3: " << queue -> dequeue() << endl;

  return 0;
}
