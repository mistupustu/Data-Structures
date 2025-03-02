#include <iostream>
#include "PriorityQueueDynamicArray.h"
#include "PriorityQueueMax.h"
#include "PriorityQueueHeap.h"
#include <random>
#include <fstream>
#include <chrono>
#include <windows.h>


std::string GetOperationName(int operationIndex) {
	switch (operationIndex) {
	case 0:
		return "Insert";
	case 1:
		return "Extract Max";
	case 2:
		return "Peek";
	case 3:
		return "Modify Key";
	case 4:
		return "Get Size";
	default:
		return "Unknown Operation";
	}
}

void Tests(PriorityQueueMax* queue, std::string fileName) {
	std::ofstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Can't open the file: " << fileName << std::endl;
		return;
	}

	int sizes[] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
	int testCount = 75;

	const int min = 0;
	const int max = 1000000;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(min, max);

	for (int operation = 0; operation < 5; operation++) {
		std::string operationName = GetOperationName(operation);
		file << operationName << std::endl;
		for (int size : sizes) {
			long long totalTime = 0;
			std::uniform_int_distribution<int> randomPriorityDistrubution(0, size - 1);
			std::cout << size << std::endl;
			for (int i = 0; i < testCount; i++) {
				//std::cout << fileName << " :: " << operationName << " :: " << size << " :: " << i << "/" << testCount << std::endl;
				int indexOfElementToChangePriority = randomPriorityDistrubution(generator);
				int oldPriority = 0;
				for (int j = 0; j < size; j++) {
					int priorityToInsert = distribution(generator);
					int valueToInsert = distribution(generator);

					if (j == indexOfElementToChangePriority)
						oldPriority = priorityToInsert;

					queue->Insert(valueToInsert, priorityToInsert);
				}
				auto start = std::chrono::high_resolution_clock::now();
				auto stop = std::chrono::high_resolution_clock::now();
				int priority, value, newPriority;
				switch (operation) {
				case 0:
					priority = distribution(generator);
					value = distribution(generator);
					start = std::chrono::high_resolution_clock::now();
					queue->Insert(value, priority);
					stop = std::chrono::high_resolution_clock::now();
					totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
					break;
				case 1:
					start = std::chrono::high_resolution_clock::now();
					queue->ExtractMax();
					stop = std::chrono::high_resolution_clock::now();
					totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
					break;
				case 2:
					start = std::chrono::high_resolution_clock::now();
					queue->Peek();
					stop = std::chrono::high_resolution_clock::now();
					totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
					break;
				case 3:
					newPriority = distribution(generator);
					start = std::chrono::high_resolution_clock::now();
					queue->ModifyKey(oldPriority, newPriority);
					stop = std::chrono::high_resolution_clock::now();
					totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
					break;
				case 4:
					start = std::chrono::high_resolution_clock::now();
					queue->GetSize();
					stop = std::chrono::high_resolution_clock::now();
					totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
					break;
				}
				queue->Clear();
			}
			file << size << "," << totalTime / testCount << std::endl;
		}
	}
	file.close();
}


void FastTests(PriorityQueueMax* queue, std::string fileName) {
	std::ofstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Can't open the file: " << fileName << std::endl;
		return;
	}

	int sizes[] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
	int testCount = 75;

	const int min = 0;
	const int max = 1000000;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(min, max);

	file << "Rozmiar" << "," << GetOperationName(0) << "," << GetOperationName(1) << "," << GetOperationName(2) << "," << GetOperationName(3) << "," << GetOperationName(4) << std::endl;

	for (int size : sizes) {
		long long totalTimeInsert = 0;
		long long totalTimeExtract = 0;
		long long totalTimePeek = 0;
		long long totalTimeModifyKey = 0;
		long long totalTimeGetSize = 0;
		std::uniform_int_distribution<int> randomPriorityDistrubution(0, size - 1);
		std::cout << size << std::endl;
		for (int i = 0; i < testCount; i++) {
			std::cout << fileName << " :: " << " :: " << size << " :: " << i << "/" << testCount << std::endl;
			int indexOfElementToChangePriority = randomPriorityDistrubution(generator);
			int oldPriority = 0;
			for (int j = 0; j < size; j++) {
				int priorityToInsert = distribution(generator);
				int valueToInsert = distribution(generator);

				if (j == indexOfElementToChangePriority)
					oldPriority = priorityToInsert;

				queue->Insert(valueToInsert, priorityToInsert);
			}
			auto start = std::chrono::high_resolution_clock::now();
			auto stop = std::chrono::high_resolution_clock::now();
			int priority, value, newPriority;

			priority = distribution(generator);
			value = distribution(generator);
			start = std::chrono::high_resolution_clock::now();
			queue->Insert(value, priority);
			stop = std::chrono::high_resolution_clock::now();
			totalTimeInsert += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();


			queue->ExtractMax();


			start = std::chrono::high_resolution_clock::now();
			queue->ExtractMax();
			stop = std::chrono::high_resolution_clock::now();
			totalTimeExtract += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();


			priority = distribution(generator);
			value = distribution(generator);
			queue->Insert(value, priority);


			start = std::chrono::high_resolution_clock::now();
			queue->Peek();
			stop = std::chrono::high_resolution_clock::now();
			totalTimePeek += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();


			newPriority = distribution(generator);
			start = std::chrono::high_resolution_clock::now();
			queue->ModifyKey(oldPriority, newPriority);
			stop = std::chrono::high_resolution_clock::now();
			totalTimeModifyKey += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();


			start = std::chrono::high_resolution_clock::now();
			queue->GetSize();
			stop = std::chrono::high_resolution_clock::now();
			totalTimeGetSize += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

			queue->Clear();
		}
		file << size << "," << totalTimeInsert / testCount << "," << totalTimeExtract / testCount << "," << totalTimePeek / testCount << "," << totalTimeModifyKey / testCount << "," << totalTimeGetSize / testCount << std::endl;
	}

	file.close();
}



std::string GetNameOfDataStructure(short choice) {
	return choice == 1 ? "Priority queue based on dynamic array" : "Priority queue based on heap";
}

PriorityQueueMax* CreateEmpty(short choice) {
	if (choice == 1) {
		return new PriorityQueueDynamicArray();
	}
	return new PriorityQueueHeap();
}

int main()
{
	/*PriorityQueueDynamicArray* priorityQueue = new PriorityQueueDynamicArray;
	PriorityQueueHeap* priorityQueueHeap = new PriorityQueueHeap;
	std::cout << "0/6" << std::endl;
	FastTests(priorityQueue, "Fast Tests Priority Queue Dynamic Array1.txt");
	priorityQueue->Clear();
	std::cout << "1/6" << std::endl;
	FastTests(priorityQueue, "Fast Tests Priority Queue Dynamic Array2.txt");
	priorityQueue->Clear();
	std::cout << "2/6" << std::endl;
	FastTests(priorityQueue, "Fast Tests Priority Queue Dynamic Array3.txt");
	priorityQueue->Clear();
	std::cout << "3/6" << std::endl;
	FastTests(priorityQueueHeap, "Fast Tests Priority Queue Heap1.txt");
	priorityQueueHeap->Clear();
	std::cout << "4/6" << std::endl;
	FastTests(priorityQueueHeap, "Fast Tests Priority Queue Heap2.txt");
	priorityQueueHeap->Clear();
	std::cout << "5/6" << std::endl;
	FastTests(priorityQueueHeap, "Fast Tests Priority Queue Heap3.txt");
	priorityQueueHeap->Clear();
	std::cout << "6/6" << std::endl;

	delete priorityQueue;
	delete priorityQueueHeap;*/

	std::cout << "Select your data structure:" << std::endl;
	std::cout << "1. Priority queue based on dynamic array" << std::endl;
	std::cout << "2. Priority queue based on heap" << std::endl;

	short chosedDataStructure = 0;

	while (chosedDataStructure < 1 || chosedDataStructure > 2) {
		std::cin >> chosedDataStructure;
		std::cout << std::endl;
	}
	std::string structureName = GetNameOfDataStructure(chosedDataStructure);

	std::cout << structureName << std::endl;

	short selection = 0;

	const int min = 0;
	const int max = 1000000;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(min, max);

	PriorityQueueMax* queue = CreateEmpty(chosedDataStructure);
	while (selection != 8) {
		selection = 0;
		std::cout << "1. Insert element" << std::endl;
		std::cout << "2. Extract max" << std::endl;
		std::cout << "3. Peek" << std::endl;
		std::cout << "4. Modify Key" << std::endl;
		std::cout << "5. Get Size" << std::endl;
		std::cout << "6. Insert Random Elements" << std::endl;
		std::cout << "7. Print All" << std::endl;
		std::cout << "8. Exit" << std::endl;

		while (selection < 1 || selection > 8) {
			std::cin >> selection;
			std::cout << std::endl;
		}

		int priority, value, oldPriority, newPriority, numberOfElements;
		Element extracted;
		switch (selection) {
		case 1:
			std::cout << "Provide Priority" << std::endl;
			std::cin >> priority;
			std::cout << "Provide value" << std::endl;
			std::cin >> value;
			queue->Insert(value, priority);
			break;
		case 2:
			extracted = queue->ExtractMax();
			std::cout << "Extracted priority " << extracted.priority << ", value " << extracted.value << std::endl;
			break;
		case 3:
			std::cout << "Peeked priority " << queue->Peek().priority << ", value " << queue->Peek().value << std::endl;
			break;
		case 4:
			std::cout << "Provide old priority" << std::endl;
			std::cin >> oldPriority;
			std::cout << "Provide new priority" << std::endl;
			std::cin >> newPriority;
			queue->ModifyKey(oldPriority, newPriority);
			break;
		case 5:
			std::cout << queue->GetSize();
			break;
		case 6:
			std::cout << "How many elements?" << std::endl;
			std::cin >> numberOfElements;

			for (int i = 0; i < numberOfElements; i++) {
				queue->Insert(distribution(generator), distribution(generator));
			}
			break;
		case 7:
			queue->PrintAll();
			break;
		case 8 :
			selection = 8;
			break;
		}
	}
	

	
	return 0;
}

