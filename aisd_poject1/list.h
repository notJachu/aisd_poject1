#pragma once

class List {
private:
	int size;
	struct Node
	{
		char* data;
		Node* next;
		Node* prev;
	};
	Node* first;
	Node* last;
	Node* createNode(char* data);
public:
	List();
	void insert(char* data, int index);
	char* remove(int index);
	int get_size() const;
	~List();
};