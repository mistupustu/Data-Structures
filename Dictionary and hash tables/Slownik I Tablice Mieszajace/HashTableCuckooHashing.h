#pragma once
#include "HashTable.h"
#include "KeyValuePair.h"


class HashTableCuckooHashing : public HashTable
{
private:
	int _size, _capacity, _cycleTreshhold;
	const float _loadFactorTreshhold = 0.5;
	KeyValuePairCuckoo* T1;
	KeyValuePairCuckoo* T2;
	void Resize(int newCapacity);
	unsigned int HashFunction(int key, int tableID) const;
	void Rehash(int key, int value);
	void InitTable();

public:
	~HashTableCuckooHashing();
	HashTableCuckooHashing();
	void Insert(int key, int value) override;
	KeyValuePair Remove(int key);
	KeyValuePair* Get(int key);
	void PrintAll() const override;
	int GetSize() const override;
	void Clear() override;
	bool IsEmpty() const override;
};

