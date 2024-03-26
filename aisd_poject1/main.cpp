#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include <iostream>
#include "list.h"
#include <cmath>
#include <cstring>
#include <time.h>

using namespace std;


int det_rank(char* c);
void infix_to_postfix(List& onp);
void solve_step(List& onp, bool& err);
void solve(List& onp);

void solve_step(List& onp, bool& err) {
	int i = 0;
	int rank;
	int res = 0;
	int removed = 0;
	do {
		rank = det_rank(onp[i]);
		if (rank == 0) {
			i++;
		}
	}
	while (rank == 0);
	cout << onp[i] << ' ';
	for (int j = i - 1; j >= 0; j--) {
		cout << onp[j] << ' ';
	}
	cout << endl;

	if (rank == 1) {
		if (onp[i][0] == 'N') {
			int a = atoi(onp[i - 1]);
			res = a * (-1);
			onp.remove(i);
			onp.remove(i - 1);
			removed = 1;
		}
		else {

		int a = atoi(onp[i - 2]);
		int b = atoi(onp[i - 1]);
		if (onp[i][0] == '+') {
			res = a + b;
		}
		else {
			res = a - b;
		}
		onp.remove(i);
		onp.remove(i - 1);
		onp.remove(i - 2);
		removed = 2;
		}
	}
	else if (rank == 2) {
		if (onp[i][0] == 'N') {
			int a = atoi(onp[i - 1]);
			res = a * (-1);
			onp.remove(i);
			onp.remove(i - 1);
			removed = 1;
		}
		else {
			int a = atoi(onp[i - 2]);
			int b = atoi(onp[i - 1]);
			if (onp[i][0] == '*') {
				res = a * b;
			}
			else {
				if (b == 0) {
					err = true;
					return;
				}
				res = a / b;
			}
			onp.remove(i);
			onp.remove(i - 1);
			onp.remove(i - 2);
			removed = 2;
		}
	}
	else if (rank == 3) {
		if (onp[i][0] == 'N') {
			int a = atoi(onp[i - 1]);
			res = a * (-1);
			onp.remove(i);
			onp.remove(i - 1);
			removed = 1;
		}
		else {
			int c = atoi(onp[i - 1]);
			int b = atoi(onp[i - 2]);
			int a = atoi(onp[i - 3]);
			if (a > 0) {
				res = b;
			}
			else {
				res = c;
			}
			onp.remove(i);
			onp.remove(i - 1);
			onp.remove(i - 2);
			onp.remove(i - 3);
			removed = 3;
		}
	}
	else if (rank == 4) {
		int count = atoi(onp[i] + 3);
		int* arr = new int[count];
		for (int j = 0; j < count; j++) {
			arr[j] = atoi(onp[i - count + j]);
		}
		if (onp[i][2] == 'N') {		 // MIN
			res = arr[0];
			for (int j = 1; j < count; j++) {
				if (arr[j] < res) res = arr[j];
			}
		}
		else {						// MAX
			res = arr[0];
			for (int j = 1; j < count; j++) {
				if (arr[j] > res) res = arr[j];
			}
		}
		for (int j = 0; j <= count; j++) {
			onp.remove(i - count);
		}
		removed = count;
		delete[] arr;
	}
	int num = 0;
	if (res == 0) {
		num = 2;
	}
	else {
		num = res > 0 ? floor(log10(res) + 2) : floor(log10(abs(res)) + 3);
	}
	char* buff = new char[num];
	
	sprintf(buff, "%d", res);
	onp.insert(buff, i - removed);
	delete[] buff;
}

void solve(List& onp) {
	bool err = false;
	while (onp.get_size() > 1) {
		solve_step(onp, err);
		if (err) {
			cout << "ERROR" << endl;
			return;
		}
	}
	cout << onp[0] << endl;
	cout << endl;
}

void infix_to_postfix(List& onp) {
	Stack *operators = new Stack;
	Stack *min_max_count = new Stack();
	char buffor[5];
	do {
		cin >> buffor;
		if (buffor[0] == '.') break;
		if (buffor[0] == ',') {
			if (min_max_count->get_size() != 0) {
				min_max_count->increment();
			}
			while (operators->get_size() != 0) {
				char* op = operators->pop();
				if (op[0] == '(') {
					operators->append(op);
					break;
				}
				else onp.push_back(op);
			}
			continue;
		}
		if (buffor[0] == 'I' && min_max_count->get_size() != 0) {
			min_max_count->decrement(2);
		}
		//cout << buffor << endl;
		if (det_rank(buffor) == 0) {
			onp.push_back(buffor);
			/*if (operators->get_size() != 0) {
				char* op = operators->pop();
				if (op[0] == 'N') {
					onp.push_back(op);
				}
				else operators->append(op);
			}*/
		}
		else if (buffor[0] == '(') {
			operators->append(buffor);
		}
		else if (buffor[0] == ')') {
			while (operators->get_size() != 0) {
				char* op = operators->pop();
				if (op[0] == '(') {
					if (operators->get_size() != 0) {
						char* min_max_chech = operators->pop();
						if (min_max_chech[0] == 'M') {
							char* tmp = min_max_count->pop();
							int count = atoi(tmp);
							int num = strlen(tmp) + strlen(min_max_chech);
							char* buff = new char[num + 1];
							buff[num] = '\0';
							sprintf(buff, "%s%d", min_max_chech, count);
							onp.push_back(buff);
							delete[] buff;
						}
						else if (min_max_chech[0] == 'N') {
							onp.push_back(min_max_chech);
						}
						else operators->append(min_max_chech);
					}
					break;
				}
				else {
					if (op[0] == 'M') {
						char* tmp = min_max_count->pop();
						int count = atoi(tmp);
						int num = strlen(tmp) + strlen(op);
						char* buff = new char[num + 1];
						buff[num] = '\0';
						sprintf(buff, "%s%d", op, count);
						onp.push_back(buff);
						delete[] buff;
					}
					else
					onp.push_back(op);
				}
			}
		}
		else {
			while (operators->get_size() != 0) {
				char* op = operators->pop();
				if (op[0] == '(' || det_rank(op) < det_rank(buffor) || (det_rank(op) == 2 && buffor[0] == 'N')) {
					operators->append(op);
					break;
				}
				if (op[0] == 'M') {
					char* tmp = min_max_count->pop();
					int count = atoi(tmp);
					int num = strlen(tmp) + strlen(op);
					char* buff = new char[num + 1];
					buff[num] = '\0';
					sprintf(buff, "%s%d", op, count);
					onp.push_back(buff);
					delete[] buff;
				}
				else
					onp.push_back(op);
			}
			if (strcmp(buffor, "MIN") == 0 || strcmp(buffor, "MAX") == 0) {
				min_max_count->append((char*)"1");
			}
			operators->append(buffor);
		}
		/*for (int i = 0; i < onp.get_size(); i++) {
			cout << onp[i] << ' ';
		}
		cout << endl;*/
	} while (buffor[0] != '.');
	while (operators->get_size() > 0) {
		char* op = operators->pop();
		if (op[0] == 'M') {
			char* tmp = min_max_count->pop();
			int count = atoi(tmp);
			int num = strlen(tmp) + strlen(op);
			char* buff = new char[num + 1];
			buff[num] = '\0';
			sprintf(buff, "%s%d", op, count);
			onp.push_back(buff);
			delete[] buff;
		}
		else
			onp.push_back(op);
	}
	delete operators;
	delete min_max_count;
}

int det_rank(char* c) {
	if (c[0] == '+' || (c[0] == '-' && strlen(c) == 1)) {
		return 1;
	}
	else if (c[0] == '*' || c[0] == '/' || c[0] == 'N') {
		return 2;
	}
	else if (c[0] == 'I') {
		return 3;
	}
	else if (strstr(c, "MIN") != NULL || strstr(c, "MAX") != NULL) {
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

	ios_base::sync_with_stdio(false);
	
	int exp_count = 0;

	double time = clock();


	cin >> exp_count;

	for (int i = 0; i < exp_count; i++) {

		List* onp = new List;

		infix_to_postfix((*onp));

		for (int i = 0; i < (*onp).get_size(); i++) {
			cout << (*onp)[i] << ' ';
		}

		cout << endl;

		solve((*onp));

		delete onp;
	}

	cout << endl;
	
	double time2 = clock();

	cout << "Time: " << (time2 - time) / CLOCKS_PER_SEC << endl;

	return 0;
}