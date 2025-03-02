#include "HashTableOpenAdressing.h"
#include <iostream>





unsigned int HashTableOpenAdressing::HashFunction(int key, int probeCounter) const
{
	return (key + probeCounter) % _capacity;
}

void HashTableOpenAdressing::Resize(int newCapacity)
{
	int oldCapacity = _capacity;
	_capacity = newCapacity;
	KeyValuePairOpenAdressing* newDynamicArray = new KeyValuePairOpenAdressing[newCapacity];
	_size = 0;
	for (int i = 0; i < oldCapacity; i++) {
		if (_dynamicArray[i].GetState() == StateOfKeyValuePair::ADDED) {
			int probeCounter = 0;
			unsigned int hashValue = HashFunction(_dynamicArray[i].GetKey(), probeCounter);
			while (newDynamicArray[hashValue].GetState() == StateOfKeyValuePair::ADDED) {
				hashValue = HashFunction(_dynamicArray[i].GetKey(), ++probeCounter);
			}
			newDynamicArray[hashValue] = _dynamicArray[i];
			_size++;
		}
	}
	delete[] _dynamicArray;
	_sizeWithTombstones = _size;
	_dynamicArray = newDynamicArray;
}

HashTableOpenAdressing::~HashTableOpenAdressing()
{
	delete[] _dynamicArray;
}

HashTableOpenAdressing::HashTableOpenAdressing()
{
	_size = 0;
	_sizeWithTombstones = 0;
	_capacity = 8;
	_dynamicArray = new KeyValuePairOpenAdressing[_capacity];
}

void HashTableOpenAdressing::Insert(int key, int value)
{
	if ((float)_sizeWithTombstones / _capacity >= _loadFactorTreshhold) {
		Resize(_capacity * 2);
	}

	int probeCounter = 0;
	unsigned int hashValue = HashFunction(key, probeCounter);

	while (_dynamicArray[hashValue].GetState() != StateOfKeyValuePair::NOT_INITIALIZED) {
		if (_dynamicArray[hashValue].GetKey() == key) {
			_dynamicArray[hashValue].SetValue(value);
			return;
		}
		hashValue = HashFunction(key, ++probeCounter);
	}

	_dynamicArray[hashValue] = KeyValuePairOpenAdressing(key, value);
	_size++;
	_sizeWithTombstones++;
}

KeyValuePair HashTableOpenAdressing::Remove(int key)
{
	if (_capacity > 8 && ((float)_size / _capacity) * 3 <= _loadFactorTreshhold) {
		Resize(_capacity / 3);
	}


	int probeCounter = 0;
	unsigned int hashValue = HashFunction(key, probeCounter);
	while (_dynamicArray[hashValue].GetState() != StateOfKeyValuePair::NOT_INITIALIZED) {
		if (_dynamicArray[hashValue].GetState() == StateOfKeyValuePair::ADDED && _dynamicArray[hashValue].GetKey() == key) {
			_dynamicArray[hashValue].SetState(StateOfKeyValuePair::DELETED);
			_size--;

			return (KeyValuePair)_dynamicArray[hashValue];
		}
		hashValue = HashFunction(key, ++probeCounter);
	}

	std::cout << "Unable to find element with specified key" << std::endl;
}

KeyValuePair* HashTableOpenAdressing::Get(int key)
{
	int probeCounter = 0;
	unsigned int hashValue = HashFunction(key, probeCounter);

	while (_dynamicArray[hashValue].GetState() != StateOfKeyValuePair::NOT_INITIALIZED) {
		if (_dynamicArray[hashValue].GetState() == StateOfKeyValuePair::ADDED && _dynamicArray[hashValue].GetKey() == key) {
			return static_cast<KeyValuePair*>(&_dynamicArray[hashValue]);
		}
		hashValue = HashFunction(key, ++probeCounter);
	}

	throw std::invalid_argument("Unable to find a element with specified key");
}

void HashTableOpenAdressing::PrintAll() const
{
	for (int i = 0; i < _capacity; i++) {
		if (_dynamicArray[i].GetState() != StateOfKeyValuePair::ADDED) {
			std::cout << i << ". NO VALUE" << std::endl;
		}
		else {
			std::cout << i << ". Key :: " << _dynamicArray[i].GetKey() << ", Value :: " << _dynamicArray[i].GetValue() << std::endl;
		}
	}
}

int HashTableOpenAdressing::GetSize() const
{
	return _size;
}

bool HashTableOpenAdressing::IsEmpty() const
{
	return _size == 0;
}

void HashTableOpenAdressing::Clear()
{
	delete[] _dynamicArray;
	_size = 0;
	_sizeWithTombstones = 0;
	_capacity = 8;
	_dynamicArray = new KeyValuePairOpenAdressing[_capacity];
}
