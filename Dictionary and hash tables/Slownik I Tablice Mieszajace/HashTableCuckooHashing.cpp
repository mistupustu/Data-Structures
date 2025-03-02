#include "HashTableCuckooHashing.h"
#include <iostream>

void HashTableCuckooHashing::Resize(int newCapacity)
{
    int oldCapacity = _capacity;
    _capacity = newCapacity;
    _cycleTreshhold = _capacity / 2;
    _size = 0;
    KeyValuePairCuckoo* tempT1 = T1;
    KeyValuePairCuckoo* tempT2 = T2;

    InitTable();

    for (int i = 0; i < oldCapacity / 2; i++) {
        if (tempT1[i].GetState()) {
            Insert(tempT1[i].GetKey(), tempT1[i].GetValue());
        }
        if (tempT2[i].GetState()) {
            Insert(tempT2[i].GetKey(), tempT2[i].GetValue());
        }
    }

    delete[] tempT1;
    delete[] tempT2;
}

unsigned int HashTableCuckooHashing::HashFunction(int key, int tableID) const
{
    if (key < 0) key = -key;
    return tableID == 0 ? key % (_capacity / 2) : (key / (_capacity / 2)) % (_capacity / 2);
}

void HashTableCuckooHashing::Rehash(int key, int value)
{
    Resize(_capacity * 2);
    Insert(key, value);
}

void HashTableCuckooHashing::InitTable()
{
    T1 = new KeyValuePairCuckoo[_capacity / 2];
    T2 = new KeyValuePairCuckoo[_capacity / 2];
}

HashTableCuckooHashing::~HashTableCuckooHashing()
{
    delete[] T1;
    delete[] T2;
}

HashTableCuckooHashing::HashTableCuckooHashing()
{
    _size = 0;
    _capacity = 20;
    _cycleTreshhold = _capacity / 2;
    InitTable();
}

void HashTableCuckooHashing::Insert(int key, int value)
{
    if (_size >= _capacity / 2) {
        Resize(_capacity * 2);
    }

    unsigned int pos;
    int cycleCount = 0;
    while (cycleCount < _cycleTreshhold) {
        pos = HashFunction(key, 0);
        if (!T1[pos].GetState() || T1[pos].GetKey() == key) {
            if (!T1[pos].GetState()) _size++;
            T1[pos] = KeyValuePairCuckoo(key, value);
            return;
        }

        int tempKey = T1[pos].GetKey();
        int tempVal = T1[pos].GetValue();
        T1[pos].SetKey(key);
        T1[pos].SetValue(value);
        key = tempKey;
        value = tempVal;

        pos = HashFunction(key, 1);
        if (!T2[pos].GetState() || T2[pos].GetKey() == key) {
            if (!T2[pos].GetState()) _size++;
            T2[pos] = KeyValuePairCuckoo(key, value);
            return;
        }

        tempKey = T2[pos].GetKey();
        tempVal = T2[pos].GetValue();
        T2[pos].SetKey(key);
        T2[pos].SetValue(value);
        key = tempKey;
        value = tempVal;
        cycleCount++;
    }
    Rehash(key, value);
}

KeyValuePair HashTableCuckooHashing::Remove(int key)
{
    KeyValuePairCuckoo deletedKVP;
    int pos1 = HashFunction(key, 0);
    if (T1[pos1].GetKey() == key) {
        deletedKVP = T1[pos1];
        T1[pos1] = KeyValuePairCuckoo();
        _size--;
        return deletedKVP;
    }

    int pos2 = HashFunction(key, 1);
    if (T2[pos2].GetKey() == key) {
        deletedKVP = T2[pos2];
        T2[pos2] = KeyValuePairCuckoo();
        _size--;
        return deletedKVP;
    }
    std::cout << "Unable to find element with specified key" << std::endl;
    return KeyValuePair();
}

KeyValuePair* HashTableCuckooHashing::Get(int key)
{
    int pos1 = HashFunction(key, 0);
    if (T1[pos1].GetKey() == key) {
        return &T1[pos1];
    }

    int pos2 = HashFunction(key, 1);
    if (T2[pos2].GetKey() == key) {
        return &T2[pos2];
    }
    std::cout << "Unable to find element with specified key" << std::endl;
    return nullptr;
}

void HashTableCuckooHashing::PrintAll() const
{
    std::cout << "First Table" << std::endl;
    for (int i = 0; i < _capacity / 2; i++) {
        if (T1[i].GetState())
            std::cout << i << ". KEY :: " << T1[i].GetKey() << ", VALUE :: " << T1[i].GetValue() << std::endl;
        else {
            std::cout << i << ". NO VALUE" << std::endl;
        }
    }
    std::cout << "Second Table" << std::endl;
    for (int i = 0; i < _capacity / 2; i++) {
        if (T2[i].GetState())
            std::cout << i << ". KEY :: " << T2[i].GetKey() << ", VALUE :: " << T2[i].GetValue() << std::endl;
        else {
            std::cout << i << ". NO VALUE" << std::endl;
        }
    }
}

int HashTableCuckooHashing::GetSize() const
{
    return _size;
}

void HashTableCuckooHashing::Clear()
{
    delete[] T1;
    delete[] T2;
    _size = 0;
    _capacity = 20;
    _cycleTreshhold = _capacity / 2;
    InitTable();
}

bool HashTableCuckooHashing::IsEmpty() const
{
    return _size == 0;
}