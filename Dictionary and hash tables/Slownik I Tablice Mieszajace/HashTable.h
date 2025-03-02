#pragma once
#include "KeyValuePair.h"

class HashTable
{
public:
	virtual ~HashTable() {}
	virtual void Insert(int key, int value) = 0;
	virtual KeyValuePair Remove(int key) = 0;
	virtual KeyValuePair* Get(int key) = 0;
	virtual void PrintAll() const = 0;
	virtual int GetSize() const = 0;
	virtual void Clear() = 0;
	virtual bool IsEmpty() const = 0;
};

