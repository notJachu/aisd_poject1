#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include <iostream>
#include "list.h"

using namespace std;

int det_rank(char* c);
void infix_to_postfix();
void solve_step();
void solve();


int det_rank(char* c) {
	if (c[0] == '+' || c[0] == '-') {
		return 1;
	}
	else if (c[0] == '*' || c[0] == '/') {
		return 2;
	}
	else if (c[0] == 'N') {
		return 3;
	}
	else if (strcmp(c, "MIN") || strcmp(c, "MAX")) {
		return 4;
	}
	else if (c[0] == ')' || c[0] == '(') {
		return 5;
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
	List onp;

	// read input
	char buffor[4];
	do {
		cin >> buffor;
		if (buffor[0] == '.') break;
		if (buffor[0] == ',') continue;
		//cout << buffor << endl;
		if (det_rank(buffor) == 0) {
			onp.push_back(buffor);
		}
		else if (buffor[0] == '(') {
			operators.append(buffor);
		}
		else if (buffor[0] == ')') {
			while (operators.get_size() != 0) {
				char* op = operators.pop();
				if (op[0] == '(') break;
				else onp.push_back(op);
			}
		} 
		else {
			while (operators.get_size() != 0) {
				char* op = operators.pop();
				if (op[0] == '(' || det_rank(op) < det_rank(buffor)) {
					operators.append(op);
					break;
				}
				onp.push_back(op);
			}
			operators.append(buffor);
		}
		for (int i = 0; i < onp.get_size(); i++) {
			cout << onp[i] << ' ';
		}
		cout << endl;
	} while (buffor[0] != '.');
	while (operators.get_size() > 0) {
		char* a = operators.pop();
		onp.push_back(a);
	}
	for (int i = 0; i < onp.get_size(); i++) {
		cout << onp[i] << ' ';
	}
	return 0;
}