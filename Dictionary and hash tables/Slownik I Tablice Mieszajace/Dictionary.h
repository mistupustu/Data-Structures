#pragma once
#include "HashTable.h"
#include "HashTableBSTSeperateChaining.h"
#include "HashTableCuckooHashing.h"
#include "HashTableOpenAdressing.h"

class Dictionary
{
private:
	HashTable* _hashTable;

public:
	Dictionary(int type);
	~Dictionary();

	void Insert(int key, int value);
	KeyValuePair Remove(int key);
	KeyValuePair* Get(int key);


	int GetSize() const;
	bool isEmpty() const;
	void PrintAll() const;
	void Clear();
};

