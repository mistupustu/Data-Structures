#include "TablicaDynamiczna.h"
#include <iostream>

TablicaDynamiczna::TablicaDynamiczna()
{
	_size = 0;
	_capacity = 4;
	_dynamic_array = new int[_capacity]; //Tworzymy pusta tablice o wielkoœci capacity
}

TablicaDynamiczna::~TablicaDynamiczna()
{
	delete [] _dynamic_array; //Zwolnienie pamiêci przy wywo³aniu destruktora
}

void TablicaDynamiczna::InsertAt(int index, int value)
{
	//Sprawdzenie czy podany index jest poprawny
	if (index < 0 || index > _size) {
		std::cout << "Can't insert element out of dynamic array bounds" << std::endl;
		return;
	}
	//Sprawdzenie czy tablica ma miejsce na dodanie, je¿eli nie to zwiêksza siê j¹
	if (_size == _capacity) {
		_capacity *= 2;
		int* new_arr = (int*)realloc(_dynamic_array, _capacity * sizeof(int)); //Proba zmiany rozmiaru tablicy. Jezeli sie nie uda zwraca NULL
		//Sprawdzenie czy zmiana rozmiaru sie uda³a
		if (new_arr == NULL) {
			int* new_dynamic_array = new int[_capacity];
			memcpy(new_dynamic_array, _dynamic_array, _size * sizeof(int)); // Skopiowanie danych ze starej tablicy do nowej zwiekszonej dwukrotnie
			// Usuniecie starej tablicy, a nastepnie ustawienie jej na nowa, zwiekszona
			delete[] _dynamic_array; 
			_dynamic_array = new_dynamic_array;
		}
		else {
			//Jezeli udalo sie zmienic rozmiar tablicy, to ustawienie zmiennej tablicy na nowa, zwiekszona
			_dynamic_array = new_arr;
		}
	}
	//Dodanie na index 0
	if (index == 0) {
		//Przesuniecie wszystkich elementow o jeden w prawo
		for (int i = _size; i > index; i--) {
			_dynamic_array[i] = _dynamic_array[i - 1];
		}
		//Przypisanie pierwszej wartosci jako value
		_dynamic_array[index] = value;
	}
	//Dodanie na ostatnia pozycje
	else if (index == _size && _size > 0) {
		//Zwyczajne przypisanie wartosci, bo tablica dynamiczna ma miejsce, bo wczesniej bylo wywolane IncreaseCapacity
		_dynamic_array[index] = value;
	}
	//Dodanie na index miêdzy 0, a size
	else {
		//Przesuniecie w prawo elementow wiêkszych od indeksu, gdzie chcemy dodac element
		//Wartosc na indeks jest rowniez przesunieta
		for (int i = _size - 1; i > index; i--) {
			_dynamic_array[i] = _dynamic_array[i - 1];
		}
		//Przypisanie nowej wartosci dla elementu na pozycju index
		_dynamic_array[index] = value;
	}
	//Po dodaniu zwiekszyc rozmiar tablicy dynamicznej
	_size++;
}

void TablicaDynamiczna::DeleteAt(int index)
{
	//Sprawdzenie czy podany index jest poprawny
	if (index < 0 || index > _size - 1) {
		std::cout << "Can't delete element out of dynamic array bounds" << std::endl;
		return;
	}
	//Sprawdzenie czy tablica dynamiczna jest pusta
	if (IsEmpty()) {
		std::cout << "Can't delete from an empty dynamic array" << std::endl;
		return;
	}
	//Gdy Usuwamy ustatni element zmniejszamy rozmiar tablicy dynamicznej
	if (index == _size - 1) {
		_size--;
	}
	else {
		//Przesuniecie elementow wiekszych od indeks o 1 pozycje w lewo
		for (int i = index; i < _size - 1; i++) {
			_dynamic_array[i] = _dynamic_array[i + 1];
		}
		_size--;
	}
	//Zmniejszenie capacity gdy wielkosc tablicy jest o polowe mniejsza od jej rozmiaru zajmowanego w pamieci
	if (_size <= _capacity / 2) {
		_capacity /= 2;
		int* new_arr = (int*)realloc(_dynamic_array, _capacity * sizeof(int)); //Proba zmiany rozmiaru tablicy. Jezeli sie nie uda zwraca NULL
		//Sprawdzenie czy zmiana rozmiaru sie uda³a
		if (new_arr == NULL) {
			int* new_dynamic_array = new int[_capacity];
			memcpy(new_dynamic_array, _dynamic_array, _size * sizeof(int)); // Skopiowanie danych ze starej tablicy do nowej zwiekszonej dwukrotnie
			// Usuniecie starej tablicy, a nastepnie ustawienie jej na nowa, zwiekszona
			delete[] _dynamic_array;
			_dynamic_array = new_dynamic_array;
		}
		else {
			//Jezeli udalo sie zmienic rozmiar tablicy, to ustawienie zmiennej tablicy na nowa, zwiekszona
			_dynamic_array = new_arr;
		}
	}
}

int TablicaDynamiczna::FindValue(int value) const
{
	if (IsEmpty()) {
		std::cout << "Dynamic array is empty" << std::endl;
		return -1; //Je¿eli tablica jest pusta to zwraca index = -1
	}
	for (int i = 0; i < _size; i++) {
		if (_dynamic_array[i] == value)
			return i;
	}
	std::cout << "Unable to find value in dynamic array" << std::endl;
	return -1;
}

int TablicaDynamiczna::GetSize() const
{
	return _size;
}

bool TablicaDynamiczna::IsEmpty() const
{
	return _size == 0;
}

void TablicaDynamiczna::PrintAll() const
{
	if (IsEmpty()) {
		std::cout << "Can't print from an empty dynamic array" << std::endl;
		return;
	}
	for (int i = 0; i < _size; i++) {
		std::cout << i << ". " << _dynamic_array[i] << std::endl;
	}
}

int TablicaDynamiczna::GetAt(int index) const
{
	if (index < 0 || index >= _size) {
		std::cout << "Can't get value out of range" << std::endl;
		return -1;
	}
	return _dynamic_array[index];
}

void TablicaDynamiczna::Clear()
{
	delete[] _dynamic_array;
	_size = 0;
	_capacity = 4;
	_dynamic_array = new int[_capacity];
}

