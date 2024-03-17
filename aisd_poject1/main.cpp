#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include <iostream>
#include "list.h"

using namespace std;

int det_rank(char* c);
void infix_to_postfix();
void solve_step(List* onp);
void solve();

void solve_step(List* onp) {
	static int i = 0;
	char* a, *b, *op, *buff;
	do {
		i += 1;
	} while (det_rank((*onp)[i]) == 0);
	op = (*onp)[i];
	b = (*onp)[i - 1];
	a = (*onp)[i - 2];
	int res = 0;
	if (op[0] == '+') {
		res = atoi(a) + atoi(b);
	}
	else if (op[0] == '-') {
		res = atoi(a) - atoi(b);
	}
	else if (op[0] == '*') {
		res = atoi(a) * atoi(b);
	}
	else if (op[0] == '/') {
		res = atoi(a) / atoi(b);
	}
	else if (op[0] == 'N') {
		res = -atoi(b);
	}
	else if (strcmp(op, "MIN")) {
		res = atoi(a) < atoi(b) ? atoi(a) : atoi(b);
	}
	else if (strcmp(op, "MAX")) {
		res = atoi(a) > atoi(b) ? atoi(a) : atoi(b);
	}
	(*onp).remove(i);
	(*onp).remove(i - 1);
	(*onp).remove(i - 2);
	buff = new char[int(log10(res))];
	sprintf(buff, "%d", res);
	(*onp).insert(buff, i - 2);
}

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
	else if (strcmp(c, "MIN") == 0 || strcmp(c, "MAX") == 0) {
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
	
	Stack operators;
	List onp;
	Stack* min_max_count = new Stack();
	int count = 0;

	// read input
	char buffor[5];
	do {
		cin >> buffor;
		if (buffor[0] == '.') break;
		if (buffor[0] == ',') {
			char* op = operators.pop();
			if (op[0] == '(') {
				operators.append(op);
				continue;
			}
			else onp.push_back(op);
			continue;
		}
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
			if (strcmp(buffor, "MIN") == 0 || strcmp(buffor, "MAX") == 0) {
				min_max_count->append((char*)"0");
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
	cout << endl;

	delete min_max_count;
	solve_step(&onp);

	for (int i = 0; i < onp.get_size(); i++) {
		cout << onp[i] << ' ';
	}
	return 0;
}