#include "stack.h"
#include <iostream>

using namespace std;

int main() {
	Stack stack;
	stack.get();
	stack.pop();
	stack.append('a');
	stack.append('b');
	stack.append('c');
	cout << stack.get() << endl;
	cout << stack.get_size() << endl;
	cout << stack.pop() << endl;
    cout << stack.get() << endl;
	return 0;
}