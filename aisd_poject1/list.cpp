#define _CRT_SECURE_NO_WARNINGS
#include "list.h"
#include <iostream>
#include <cstring>

List::List() {
	size = 0;
	first = NULL;
	last = NULL;
}

List::Node* List::createNode(char* data) {
	Node* newNode = new Node();
	int len = strlen(data);
	newNode->data = new char[len + 1];			// this prevents from copying 
	strncpy(newNode->data, data, len);	// copy data to newNode->data
	newNode->data[len] = '\0';			
	newNode->next = NULL;
	return newNode;
}

void List::insert(char* data, int index) {
	if (index < 0 || index > size) {
		//std::cout << "Index out of bounds" << std::endl;
		return;
	}
	Node* newNode = createNode(data);
	if (size == 0) {
		first = newNode;
		last = newNode;
		size = 1;
	} else if (index == 0) {
		newNode->next = first;
		first = newNode;
		size += 1;
	} else if (index == size) {
		last->next = newNode;
		last = newNode;
		size += 1;
	} else {
		Node* current = first;
		for (int i = 0; i < index - 1; i++) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
		size += 1;
	}
}

void List::push_back(char* data) {
	insert(data, size);
}

void List::remove(int index) {
	if (index < 0 || index >= size) {
		//std::cout << "Index out of bounds" << std::endl;
		return;
	}
	if (size == 1) {
		delete first;
		first = NULL;
		last = NULL;
		size = 0;
	} else if (index == 0) {
		Node* temp = first;
		first = first->next;
		delete temp;
		size -= 1;
	} else {
		Node* current = first;
		for (int i = 0; i < index - 1; i++) {
			current = current->next;
		}
		Node* temp = current->next;
		current->next = current->next->next;
		delete temp;
		size -= 1;
	}
}

char* List::get(int index) const {
	if (index < 0 || index >= size) {
		//std::cout << "Index out of bounds" << std::endl;
		return NULL;
	}
	Node* current = first;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	return current->data;
}

int List::get_size() const {
	return size;
}

char* List::operator[](int index) const {
	return get(index);
}

List::~List() {
	while (first != NULL) {
		Node* temp = first;
		first = first->next;
		delete[] temp->data;
		delete temp;
	}
	//std::cout << "List deleted" << std::endl;
}
