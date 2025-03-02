#pragma once
#include "HashTable.h"
#include <iostream>

struct Node {
	KeyValuePair value;
	Node* leftChild;
	Node* rightChild;
	Node(KeyValuePair value) : value(value) {}
	Node() { }
};

class BinarySearchTree
{
private:
	Node* root;
	int _size;
	Node* findMin(Node* node);
	Node* insertRecursivly(Node* node, KeyValuePair element);
	Node* removeRecursivly(Node* node, int key, Node& deletedNode, bool& found);
	Node* findRecursivly(Node* node, int key);
	void PrintElement(Node* node, std::string message) const;
	void ClearRecursivly(Node* node);
public:
	BinarySearchTree();
	~BinarySearchTree();
	void Insert(int key, int value);
	Node Remove(int key);
	Node* Find(int key);
	bool isEmpty() const;
	int GetSize() const;
	void PrintAll() const;
	void Clear();
	Node* GetRoot() const;
};