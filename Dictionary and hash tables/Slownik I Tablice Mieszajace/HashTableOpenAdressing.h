#pragma once
#include "HashTable.h"

//HASH TABLE WITH OPEN ADDRESSING AND LINEAR PROBING

class HashTableOpenAdressing : public HashTable
{
private:
	KeyValuePairOpenAdressing* _dynamicArray;
	int _size, _capacity, _sizeWithTombstones;
	const float _loadFactorTreshhold = 0.6;
	unsigned int HashFunction(int key, int probeCounter) const;
	void Resize(int newCapacity);
public:
	~HashTableOpenAdressing();
	HashTableOpenAdressing();
	void Insert(int key, int value) override;
	KeyValuePair Remove(int key) override;
	KeyValuePair* Get(int key) override;
	void PrintAll() const override;
	int GetSize() const override;
	bool IsEmpty() const override;
	void Clear() override;
};

