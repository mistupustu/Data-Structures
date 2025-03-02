#include "Dictionary.h"
#include <iostream>

Dictionary::Dictionary(int type)
{
	switch (type) {
	case 1:
		_hashTable = new HashTableOpenAdressing();
		break;
	case 2:
		_hashTable = new HashTableBSTSeperateChaining();
		break;
	case 3:
		_hashTable = new HashTableCuckooHashing();
		break;
	default:
		throw std::invalid_argument("Invalid hash table type");
	}
}


Dictionary::~Dictionary()
{
	delete _hashTable;
}

void Dictionary::Insert(int key, int value)
{
	_hashTable->Insert(key, value);
}

KeyValuePair Dictionary::Remove(int key)
{
	return _hashTable->Remove(key);
}

KeyValuePair* Dictionary::Get(int key)
{
	return _hashTable->Get(key);
}

int Dictionary::GetSize() const
{
	return _hashTable->GetSize();
}

bool Dictionary::isEmpty() const
{
	return _hashTable->IsEmpty();
}

void Dictionary::PrintAll() const
{
	_hashTable->PrintAll();
}

void Dictionary::Clear() {
	_hashTable->Clear();
}
