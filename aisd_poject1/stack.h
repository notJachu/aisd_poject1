#pragma once

class Stack {
private:
	int size;
	struct Node {
		char data;
		Node* next;
	};
	Node* top;
	Node* createNode(char data);
public:
	void append(char data);
	char pop();
	char get() const;
	int get_size() const;
	Stack();
	~Stack();
};