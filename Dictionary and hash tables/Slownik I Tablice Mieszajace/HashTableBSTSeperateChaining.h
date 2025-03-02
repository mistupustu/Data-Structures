#pragma once
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "KeyValuePair.h"

class HashTableBSTSeperateChaining : public HashTable, protected BinarySearchTree
{
private:
	int _size;
	const float _loadFactorTreshold = 0.8;
	void resize(int newSize);
	BinarySearchTree* bst;
	int numberOfBuckets;
	unsigned int HashFunction(int key);
	void InsertIntoArray(Node* node, BinarySearchTree* arr, int size);
public:
	~HashTableBSTSeperateChaining();
	HashTableBSTSeperateChaining();
	void Insert(int key, int value) override;
	KeyValuePair Remove(int key);
	KeyValuePair* Get(int key);
	void PrintAll() const override;
	int GetSize() const override;
	bool IsEmpty() const override;
	void Clear() override;
};