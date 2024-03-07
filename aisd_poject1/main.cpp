#include "stack.h"
#include <iostream>
#include <vector>

using namespace std;

int det_rank(char* c);
void infix_to_postfix();
void solve_step();
void solve();


int det_rank(char* c) {
	if (c[0] == '+' || c[0] == '-') {
		return 1;
	}
	else if (c == "*" || c == "/") {
		return 2;
	}
	else {
		return 0;
	}
}

int main() {
	/*Stack stack;
	stack.get();
	stack.pop();
	stack.append('a');
	stack.append('b');
	stack.append('c');
	cout << stack.get() << endl;
	cout << stack.get_size() << endl;
	cout << stack.pop() << endl;
    cout << stack.get() << endl;*/
	
	Stack operators;
	vector<char*> onp;

	// read input
	char buffor[4];
	do {
		cin >> buffor;
		if (buffor[0] == '.') break;
		//cout << buffor << endl;
		if (det_rank(buffor) == 0) {
			onp.push_back(buffor);
		}
		else if (buffor == "(") {
			operators.append(buffor[0]);
		}
		else if (buffor == ")") {
			while (operators.get_size() != 0) {
				char op = operators.pop();
				if (op == '(') break;
				else onp.push_back(&op);
			}
		} 
		else {
			while (operators.get_size() != 0) {
				char op = operators.pop();
				if (op == '(' || det_rank(&op) < det_rank(buffor)) {
					operators.append(op);
					break;
				}
				onp.push_back(&op);
			}
			operators.append(buffor[0]);
		}
		for (int i = 0; i < onp.size(); i++) {
			cout << onp[i] << ' ';
		}
		cout << endl;
	} while (buffor[0] != '.');
	while (operators.get_size() > 0) {
		char a = operators.pop();
		onp.push_back(&a);
	}
	for (int i = 0; i < onp.size(); i++) {
		cout << onp[i] << ' ';
	}
	return 0;
}