#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include <iostream>
#include <cstring>

Stack::Stack() {
	size = 0;
	top = NULL;
}

Stack::Node* Stack::createNode(char* data) {
	Node* newNode = new Node;
	int len = strlen(data);
	newNode->data = new char[len + 1];
	strncpy(newNode->data, data, len);
	newNode->data[len] = '\0';
	newNode->next = NULL;
	return newNode;
}

void Stack::append(char* data) {
	size += 1;
	Node* newNode = createNode(data);
	newNode->next = top;
	top = newNode;
}

char* Stack::pop() {
	if (top == NULL) {
		//std::cout << "Stack is empty" << std::endl;
		return NULL;
	}
	else {
		if (size == 1 || top->next == NULL) {
			char* data = top->data;
			delete top;
			top = NULL;
			size = 0;
			return data;
		}
		size -= 1;
		char* data = top->data;
		top = top->next;
		return data;
	}
}

char Stack::get() const {
	if (top == NULL) {
		//std::cout << "Stack is empty" << std::endl;
		return ' ';
	}
	else {
		return *(top->data);
	}
}

int Stack::get_size() const {
	return size;
}

void Stack::increment() {
	int num = atoi(top->data);
	num += 1;
	sprintf(top->data, "%d", num);
}

void Stack::decrement(int c) {
	int num = atoi(top->data);
	num -= c;
	sprintf(top->data, "%d", num);
}

Stack::~Stack() {
	// delete all nodes
	while (top != NULL) {
		Node* temp = top;
		top = top->next;
		for (int i = 0; i < strlen(temp->data); i++) {
			delete &temp->data[i];
			temp->data[i] = NULL;
		}
		delete[] temp->data;
		delete temp;					
		temp = NULL;
	}
	//std::cout << "Stack deleted" << std::endl;
}