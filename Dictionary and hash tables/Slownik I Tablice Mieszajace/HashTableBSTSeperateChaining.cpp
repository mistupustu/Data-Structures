#include "HashTableBSTSeperateChaining.h"



void HashTableBSTSeperateChaining::resize(int newSize)
{
    BinarySearchTree* newArray = new BinarySearchTree[newSize];
    //Przejscie przez kazdy bucket i dodawanie kazdego elementu do nowego bucketa w nowej tablicy
    for (int i = 0; i < numberOfBuckets; ++i) {
        Node* rootNode = bst[i].GetRoot();
        InsertIntoArray(rootNode, newArray, newSize);
        bst[i].Clear();
    }
    delete[] bst;

    bst = newArray;
    numberOfBuckets = newSize;
}
unsigned int HashTableBSTSeperateChaining::HashFunction(int key)
{
    if (key < 0)
        key *= -1;
    return key % numberOfBuckets;
}

void HashTableBSTSeperateChaining::InsertIntoArray(Node* node, BinarySearchTree* arr, int newSize)
{
    if (node == nullptr)
        return;
    //Przejscie przez wszystkie elementy BST i dodanie ich do nowej tablicy
    InsertIntoArray(node->leftChild, arr, newSize);

    unsigned int hashValue = node->value.GetKey() % newSize;
    arr[hashValue].Insert(node->value.GetKey(), node->value.GetValue());

    InsertIntoArray(node->rightChild, arr, newSize);
}

HashTableBSTSeperateChaining::~HashTableBSTSeperateChaining()
{
    for (int i = 0; i < numberOfBuckets; i++) {
        bst[i].Clear();
    }
    delete[] bst;
}

HashTableBSTSeperateChaining::HashTableBSTSeperateChaining()
{
    numberOfBuckets = 8;
    bst = new BinarySearchTree[numberOfBuckets];
}

void HashTableBSTSeperateChaining::Insert(int key, int value)
{
    if (GetSize() / numberOfBuckets >= _loadFactorTreshold) {
        resize(numberOfBuckets * 2);
    }
    unsigned int hashValue = HashFunction(key);
    int oldSize = bst[hashValue].GetSize();
    bst[hashValue].Insert(key, value);
    if (oldSize != bst[hashValue].GetSize())
        _size++;
}

KeyValuePair HashTableBSTSeperateChaining::Remove(int key)
{
    unsigned int hashValue = HashFunction(key);
    KeyValuePair deletedValue = bst[hashValue].Remove(key).value;
    _size--;
    return (KeyValuePair)deletedValue;
}

KeyValuePair* HashTableBSTSeperateChaining::Get(int key)
{
    unsigned int hashValue = HashFunction(key);
    Node* node = bst[hashValue].Find(key);
    if (node != nullptr) {
        return &(node->value);
    }
    else {
        return nullptr;
    }
}

void HashTableBSTSeperateChaining::PrintAll() const
{
    for (int i = 0; i < numberOfBuckets; i++) {
        std::cout << "Bucket number " << i << ". " << std::endl;
        if (!bst[i].isEmpty())
            bst[i].PrintAll();
        else
            std::cout << "Bucket is empty!" << std::endl;
    }
}

int HashTableBSTSeperateChaining::GetSize() const
{
    return _size;
}

bool HashTableBSTSeperateChaining::IsEmpty() const
{
    return _size == 0;
}

void HashTableBSTSeperateChaining::Clear()
{
    for (int i = 0; i < numberOfBuckets; i++) {
        bst[i].Clear();
    }
}