#include "list.h"
#include <iostream>

List::List() {
	size = 0;
	first = NULL;
	last = NULL;
}

List::Node* List::createNode(char* data) {
	Node* newNode = new Node();
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void List::insert(char* data, int index) {
	if (index < 0 || index > size) {
		std::cout << "Index out of bounds" << std::endl;
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

void List::remove(int index) {
	if (index < 0 || index >= size) {
		std::cout << "Index out of bounds" << std::endl;
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
		std::cout << "Index out of bounds" << std::endl;
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

List::~List() {
	while (size > 0) {
		remove(0);
	}
	std::cout << "List deleted" << std::endl;
}
