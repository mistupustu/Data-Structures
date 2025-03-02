#include <iostream>
#include "Dictionary.h"
#include "HashTable.h"
#include "HashTableOpenAdressing.h"
#include "BinarySearchTree.h"
#include "HashTableBSTSeperateChaining.h"
#include "HashTableCuckooHashing.h"
#include <random>
#include <fstream>
#include <chrono>



std::string OperationName(int operation) {
    return operation == 0 ? "Insert" : "Remove";
}

void Tests(Dictionary* dict, std::string fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Can't open the file: " << fileName << std::endl;
        return;
    }

    int sizes[] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
    int testCount = 100;

    const int min = 0;
    const int max = 1000000;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(min, max);
    for (int operation = 0; operation < 2; operation++) {
        file << OperationName(operation) << std::endl;
        for (int size : sizes) {
            long long totalTime = 0;
            std::uniform_int_distribution<int> distributionOfRandomIndex(0, size);
            for (int test = 0; test < testCount; test++) {
                dict->Clear();
                int keyToRemove{};
                int indexToRemove = distributionOfRandomIndex(generator);
                for (int i = 0; i < size; i++) {
                    int oldSize = dict->GetSize();
                    int keyInserted = distribution(generator);
                    dict->Insert(keyInserted, distribution(generator));
                    if (oldSize + 1 != dict->GetSize()) {
                        i--;
                    }
                    else {
                        if (i == indexToRemove) {
                            keyToRemove = keyInserted;
                        }
                    }
                }
                auto start = std::chrono::high_resolution_clock::now();
                auto stop = std::chrono::high_resolution_clock::now();
                switch (operation) {
                case 0:
                    start = std::chrono::high_resolution_clock::now();
                    dict->Insert(distribution(generator), distribution(generator));
                    stop = std::chrono::high_resolution_clock::now();
                    totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
                    break;
                case 1:
                    start = std::chrono::high_resolution_clock::now();
                    dict->Remove(keyToRemove);
                    stop = std::chrono::high_resolution_clock::now();
                    totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
                    break;
                }
            }
            file << size << "," << totalTime / testCount << std::endl;
        }
    }
    file.close();
}



std::string GetNameOfDataStructure(short selection) {
    switch (selection) {
    case 1:
        return "Dictionary based on hash table with open adressing";
    case 2:
        return "Dictionary based on hash table with seperate chaining with Binary Search Tree";
    case 3:
        return "Dictionary based on hash table with cuckoo hashing";
    default:
        return "Unknown";
    }
}

Dictionary* CreateEmpty(short selection) {
    switch (selection) {
    case 1:
        return new Dictionary(1);
    case 2:
        return new Dictionary(2);
    case 3:
        return new Dictionary(3);
    }
}

int main()
{
    //Tests(new Dictionary(1), "Open Adressing1.txt");
    Tests(new Dictionary(2), "FIXED Separate Chaining1.txt");
    //Tests(new Dictionary(3), "Cuckoo Hashing2.txt");
    //Tests(new Dictionary(1), "Open Adressing2.txt");
    Tests(new Dictionary(2), "FIXED Separate Chaining2.txt");
    //Tests(new Dictionary(3), "Cuckoo Hashing3.txt");
    //Tests(new Dictionary(1), "Open Adressing3.txt");
    Tests(new Dictionary(2), "FIXED Separate Chaining3.txt");
    //Tests(new Dictionary(3), "Cuckoo Hashing1.txt");
    std::cout << "Select your type of dictionary:" << std::endl;
    std::cout << "1. Dictionary based on hash table with open adressing" << std::endl;
    std::cout << "2. Dictionary based on hash table with seperate chaining with Binary Search Tree" << std::endl;
    std::cout << "3. Dictionary based on hash table with cuckoo hashing" << std::endl;

    short chosedDataStructure = 0;

    while (chosedDataStructure < 1 || chosedDataStructure > 4) {
        std::cin >> chosedDataStructure;
        std::cout << std::endl;
    }
    std::string structureName = GetNameOfDataStructure(chosedDataStructure);

    std::cout << structureName << std::endl;

    Dictionary* dict = CreateEmpty(chosedDataStructure);
    short selection = 0;
    while (selection != 8) {


        std::cout << "1. Insert" << std::endl;
        std::cout << "2. Remove" << std::endl;
        std::cout << "3. Get element" << std::endl;
        std::cout << "4. Insert Random" << std::endl;
        std::cout << "5. Print All" << std::endl;
        std::cout << "6. Clear" << std::endl;
        std::cout << "7. Get Size" << std::endl;
        std::cout << "8. Exit" << std::endl;

        const int min = 0;
        const int max = 1000000;
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(min, max);

        while (selection < 1 || selection > 8) {
            std::cin >> selection;
            std::cout << std::endl;
        }
        int key, value, numberOfElements, oldSize;
        KeyValuePair* kvpPTR;
        switch (selection) {
        case 1:
            std::cout << "Please provide key you want to insert" << std::endl;
            std::cin >> key;
            std::cout << "Please provide value you want to insert" << std::endl;
            std::cin >> value;
            dict->Insert(key, value);
            break;
        case 2:
            std::cout << "Please provide key of the element you want to remove" << std::endl;
            std::cin >> key;
            dict->Remove(key);
            break;
        case 3:
            std::cout << "Please provide key of the element you want to get" << std::endl;
            std::cin >> key;
            kvpPTR = dict->Get(key);
            std::cout << "Key :: " << kvpPTR->GetKey() << ", Value :: " << kvpPTR->GetValue() << std::endl;
            break;
        case 4:
            std::cout << "How many elements you want to randomly insert" << std::endl;
            std::cin >> numberOfElements;
            for (int i = 0; i < numberOfElements; i++) {
                oldSize = dict->GetSize();
                dict->Insert(distribution(generator), distribution(generator));
                if (oldSize + 1 != dict->GetSize()) {
                    i--;
                }
            }
            break;
        case 5:
            dict->PrintAll();
            break;
        case 6:
            dict->Clear();
            break;
        case 7:
            std::cout << "Size :: " << dict->GetSize() << std::endl;
            break;
        case 8:
            selection = 8;
            break;
        }
        selection = -1;
    }


    //HashTableOpenAdressing ht;
    //ht.PrintAll();
    //ht.Insert(2, 15);
    //ht.Insert(3, 22);
    //ht.Insert(10, 151);
    //ht.Insert(18, 1);
    //ht.Insert(1, 11);
    //ht.Insert(0, 11);
    //ht.Insert(4, 11);
    //ht.Insert(5, 11);
    //ht.Insert(618, 11);
    //ht.Insert(20, 11);
    //ht.Insert(400, 11);
    //ht.Insert(600, 11);
    //ht.Insert(70000, 11);
    //ht.PrintAll();

    //ht.Get(10);

    //ht.Remove(20);
    //ht.Remove(3);
    //ht.Remove(2);
    //ht.Remove(1);
    //ht.Remove(10);
    //ht.Remove(18);
    //ht.Remove(0);
    //ht.Insert(6, 11);
    //ht.Insert(8, 11);
    //ht.PrintAll();

    //BinarySearchTree bst;
    //bst.Insert(12,33);
    //bst.Insert(22,44);
    //bst.Insert(33,55);
    //bst.Insert(1,55);
    //bst.Insert(5,55);
    //bst.Insert(4,55);
    //bst.Insert(444,55);
    //bst.PrintAll();
    //Node* n = bst.Find(444);
    //std::cout << n->value.GetKey() << " " << n->value.GetValue() << std::endl;
    //Node nd = bst.Remove(4);
    //std::cout << nd.value.GetKey() << " " << nd.value.GetValue() << std::endl;
    //bst.PrintAll();

    //BinarySearchTree htbts;
    //htbts.Insert(12, 12);
    //htbts.Remove(12);
    //htbts.Insert(111, 22);
    //htbts.Insert(11, 11);
    //htbts.Insert(9, 11);
    //htbts.Insert(22, 11);
    //htbts.Insert(76, 11);
    //htbts.Insert(1251, 11);
    //htbts.Remove(12);
    //htbts.PrintAll();



    //HashTableCuckooHashing htc;
    //htc.PrintAll();
    //htc.Insert(2, 15);
    //htc.Insert(10, 15);
    ////htc.Remove(2);
    //htc.PrintAll();
    //htc.Insert(3, 22);
    //htc.Insert(10, 151);
    //htc.Insert(18, 1);
    //htc.Insert(1, 11);
    //htc.Insert(0, 11);
    //htc.Insert(4, 11);
    //htc.Insert(5, 11);
    //htc.Insert(618, 11);
    //htc.Insert(20, 11);
    //htc.Insert(400, 11);
    //htc.Insert(600, 11);
    //htc.Insert(70000, 11);
    //htc.PrintAll();

    //htc.Get(10);

    
    //ht.PrintAll();


    
}

