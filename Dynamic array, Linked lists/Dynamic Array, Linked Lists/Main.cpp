#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <random>
#include "TablicaDynamiczna.h"
#include "ListaJednokierunkowa.h"
#include "ListaJednokierunkowaTail.h"
#include "ListaDwukierunkowa.h"
#include "StrukturaDanych.h"



//TESTY
std::string OperationByNumber(int operation) {
	return operation == 0 ? "Dodowanie" : "Usuwanie";
}
std::string PositionByNumber(int position) {
	switch (position) {
	case 0:
		return "Poczatek";
	case 1:
		return "Koniec";
	case 2:
		return "Losowo";
	}
	return "Nieznane";
}
void AddTests(StrukturaDanych* dataStructure, const std::string& fileName) {
	const int testCount = 50;
	const int arraySizes[] = { 100, 1000, 5000, 8000, 10000, 16000, 20000, 40000, 80000, 120000, 160000 }; //Rozmiary na ktorych badania sa przeprowadzane

	std::ofstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Can't open the file: " << fileName << std::endl;
		return;
	}

	srand(std::time(nullptr));

	for (int operation = 0; operation < 2; ++operation) { // 0 - dodawanie, 1 - odejmowanie
		for (int operationPosition = 0; operationPosition < 3; ++operationPosition) { // 0 - poczatek, 1 - koniec, 2 - losowoo
			file << "Operation - " << OperationByNumber(operation) << ", At position - " << PositionByNumber(operationPosition) << std::endl;

			for (int sizeIndex = 0; sizeIndex < 11; sizeIndex++) { //Dla kazdego rozmiaru z tablicy
				long long totalTime = 0;

				for (int i = 0; i < testCount; i++) { //Badania dla kazdego rozmiaru sa przeprowadzane X razy
					dataStructure->Clear(); //Czyszenie struktury

					for (int j = 0; j < arraySizes[sizeIndex]; j++) { //Populacja strukury
						dataStructure->InsertAt(0, rand() % 2000000);
					}

					int indexOperation;
					std::random_device rnd;  // Ziarno losowe
					std::mt19937 gen(rnd()); // mersenne_twister_engine 
					//Ustalenie na jakim indeksie ma odbyc sie operacja na strukturze
					switch (operationPosition) {
					case 0:
						indexOperation = 0;
						break;
					case 1:
						indexOperation = (operation == 0) ? arraySizes[sizeIndex] : (arraySizes[sizeIndex] - 1);
						break;
					case 2:
						//UZYTE ZOSTALO TO ZAMAIST rand(), poniewaz rand() generuje wartosci jedynie do 2^15.
						//https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
						if (operation == 1) {
							std::uniform_int_distribution<int> distrib(0, arraySizes[sizeIndex] - 1);
							indexOperation = distrib(gen);
						}
						else {
							std::uniform_int_distribution<int> distrib(0, arraySizes[sizeIndex]);
							indexOperation = distrib(gen);
						}
						break;
					default:
						indexOperation = 0; //Dla default bedzie to poczatek
						break;
					}

					//Mierzenie czasu
					auto start = std::chrono::high_resolution_clock::now();
					if (operation == 0) {
						dataStructure->InsertAt(indexOperation, rand() % 2000000);
					}
					else {
						dataStructure->DeleteAt(indexOperation);
					}
					auto stop = std::chrono::high_resolution_clock::now();
					totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
				}

				//Obliczenie sredniej dla kazdego z rozmiarow danych
				file << arraySizes[sizeIndex] << ";";
				file << (totalTime / testCount) << std::endl;
			}
		}
	}

	file.close();
}


void FindTests(StrukturaDanych* dataStructure, const std::string& fileName) {
	const int testCount = 200;
	const int arraySizes[] = { 100, 1000, 5000, 8000, 10000, 16000, 20000, 40000, 80000, 120000, 160000 }; //Rozmiary na ktorych badania sa przeprowadzane

	std::ofstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Can't open the file: " << fileName << std::endl;
		return;
	}

	for (int sizeIndex = 0; sizeIndex < 11; sizeIndex++) { //Dla kazdego rozmiaru z tablicy
		long long totalTime = 0;
		for (int i = 0; i < testCount; i++) { //Badania dla kazdego rozmiaru sa przeprowadzane X razy
			dataStructure->Clear(); //Czyszenie struktury
			//UZYTE ZOSTALO TO ZAMAIST rand(), poniewaz rand() generuje wartosci jedynie do 2^15.
			//https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
			std::random_device rnd;  // Ziarno losowe
			std::mt19937 gen(rnd()); // mersenne_twister_engine 
			std::uniform_int_distribution<int> distrib(0, arraySizes[sizeIndex] - 1);
			int randomIndex = distrib(gen);
			int valueToFind = 1;
			for (int j = 0; j < arraySizes[sizeIndex]; j++) { //Populacja strukury
				if (j == randomIndex) {
					dataStructure->InsertAt(0, valueToFind);
				}
				else
					dataStructure->InsertAt(0, rand() % (2000000 + valueToFind + 1));
			}


			//Mierzenie czasu
			
			auto start = std::chrono::high_resolution_clock::now();
			dataStructure->FindValue(valueToFind);
			auto stop = std::chrono::high_resolution_clock::now();
			totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
		}

		//Obliczenie sredniej dla kazdego z rozmiarow danych
		file << arraySizes[sizeIndex] << ";";
		file << (totalTime / testCount) << std::endl;
	}

	file.close();
}
//KONIEC TESTOW





bool isStringANumber(std::string str) {
	int start;
	if (str[0] == '-' && isdigit(str[1])) {
		start = 1;
	}
	else {
		start = 0;
	}

	for (int i = start; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}
std::string SelectedDataStructure(short number) {
	switch (number) {
	case 1:
		return "Dynamic array";
	case 2:
		return "Single Linked List";
	case 3:
		return "Single Linked List with tail";
	case 4:
		return "Doubly Linked List";
	default:
		return "Unknown";
	}
}
StrukturaDanych* CreateEmptyDataStructure(short selection) {
	switch (selection) {
	case 1:
		return new TablicaDynamiczna();
		break;
	case 2:
		return new ListaJednokierunkowa();
		break;
	case 3:
		return new ListaJednokierunkowaTail();
		break;
	case 4:
		return new ListaDwukierunkowa();
		break;
	default:
		std::cout << "Unrecognized data type" << std::endl;
		return nullptr;
	}
}

int main()
{
	TablicaDynamiczna* dynamicArray = new TablicaDynamiczna();
	//AddTests(dynamicArray, "DynamicArrayTests.txt");
	//FindTests(dynamicArray, "DynamicArrayFindTests.txt");
	ListaJednokierunkowa* list = new ListaJednokierunkowa();
	//AddTests(list, "SingleLinkedListTests.txt");
	//FindTests(list, "SingleLinkedFindTests.txt");
	ListaJednokierunkowaTail* list1 = new ListaJednokierunkowaTail();
	//AddTests(list1, "SingleLinkedListWithTailTests.txt");
	//FindTests(list1, "SingleLinkedWithTailFindTests.txt");
	ListaDwukierunkowa* list2 = new ListaDwukierunkowa();
	//AddTests(list2, "DoublyLinkedListTests.txt");
	//FindTests(list2, "DoublyLinkedFindTests.txt");

	//MENU DO TESTOWANIA DZIALANIA
	//Wybor struktury danych
	std::cout << "Select data stucture you want to test" << std::endl;
	std::cout << "1. Dynamic Array" << std::endl;
	std::cout << "2. Single Linked List" << std::endl;
	std::cout << "3. Single Linked List with tail" << std::endl;
	std::cout << "4. Doubly Linked List" << std::endl;
	short data_structure_selection = 0;
	//Petla dopoki nie wybierze sie poprawnego numeru
	while (data_structure_selection < 1 || data_structure_selection > 4) {
		std::cin >> data_structure_selection;
		std::cout << std::endl;
	}
	std::string data_structure_name = SelectedDataStructure(data_structure_selection); // Nazwa struktury do wyswietlenia
	StrukturaDanych* data_structure = CreateEmptyDataStructure(data_structure_selection); // Tworzy nowa pusta strukture
	//Petla nieskonczona dopoki sie nie wyjdzie
	while (true) {
		std::cout << "Menu for " + data_structure_name << std::endl;
		std::cout << "1. Build from file" << std::endl;
		std::cout << "2. Delete" << std::endl;
		std::cout << "3. Insert" << std::endl;
		std::cout << "4. Create randomly" << std::endl;
		std::cout << "5. Print All" << std::endl;
		std::cout << "6. Clear" << std::endl;
		std::cout << "7. Exit" << std::endl;

		short menu_selection = 0;
		//Petla dopoki nie wybierze sie poprwanego numeru
		while (menu_selection < 1 || menu_selection > 6) {
			std::cin >> menu_selection;
			std::cout << std::endl;
		}
		switch (menu_selection) {
		case 1:
		{
			data_structure = CreateEmptyDataStructure(data_structure_selection); // Tworzy nowa strukture, zeby miec tylko te z pliku
			std::cout << "Please provide file path" << std::endl;
			std::string file_path;
			std::cin >> file_path;
			std::ifstream file(file_path);
			//Sprawdza czy udalo sie otworzyc plik
			if (!file.is_open()) {
				std::cout << "Can't open the file" << std::endl;
			}
			else {
				std::string line;
				int index_to_insert = 0;
				//Petla wykonuje sie tak dlugo jak std::getline() nie napotkal end of file
				while (std::getline(file, line)) {
					if (isStringANumber(line)) { // Sprawdza czy string jest intiger, zeby stoi() nie wyrzuci³o errora
						int number = std::stoi(line);
						data_structure->InsertAt(index_to_insert, number);
						index_to_insert++;
					}
				}
				file.close();
			}
			break;
		}

		case 2:
		{
			std::cout << "Please give index you want to delete" << std::endl;
			int index_to_delete;
			std::cin >> index_to_delete;
			data_structure->DeleteAt(index_to_delete);
			break;
		}

		case 3:
		{

			std::cout << "Please give index where you want to insert" << std::endl;
			int index_to_insert;
			std::cin >> index_to_insert;
			std::cout << "Please give value you want to insert" << std::endl;
			int value;
			std::cin >> value;
			data_structure->InsertAt(index_to_insert, value);
			break;
		}
		case 4:
		{
			std::cout << "How many values you want to insert?" << std::endl;
			int n;
			std::cin >> n;
			if (n < 1) {
				std::cout << "Number must be bigger than 1" << std::endl;
				break;
			}
			data_structure = CreateEmptyDataStructure(data_structure_selection);
			std::srand(std::time(nullptr));
			for (int i = 0; i < n; i++) {
				data_structure->InsertAt(i, std::rand() % 2000001);
			}
			break;
		}

		case 5:
			data_structure->PrintAll();
			break;
		case 7:
			return 0;
		case 6:
			data_structure->Clear();
			break;
		}

	}
	return 0;
}


