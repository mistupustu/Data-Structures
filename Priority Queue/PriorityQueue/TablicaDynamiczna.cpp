#include "TablicaDynamiczna.h"
#include <iostream>

TablicaDynamiczna::TablicaDynamiczna()
{
	_size = 0;
	_capacity = 4;
	_dynamic_array = new Element[_capacity]; //Tworzymy pusta tablice o wielkoœci capacity
}

TablicaDynamiczna::~TablicaDynamiczna()
{
	delete[] _dynamic_array; //Zwolnienie pamiêci przy wywo³aniu destruktora
}

void TablicaDynamiczna::InsertAt(int index, Element element)
{
	//Sprawdzenie czy podany index jest poprawny
	if (index < 0 || index > _size) {
		std::cout << "Can't insert element out of dynamic array bounds" << std::endl;
		return;
	}
	//Sprawdzenie czy tablica ma miejsce na dodanie, je¿eli nie to zwiêksza siê j¹
	if (_size == _capacity) {
		_capacity *= 2;
		Element* new_arr = (Element*)realloc(_dynamic_array, _capacity * sizeof(Element)); //Proba zmiany rozmiaru tablicy. Jezeli sie nie uda zwraca NULL
		//Sprawdzenie czy zmiana rozmiaru sie uda³a
		if (new_arr == NULL) {
			Element* new_dynamic_array = new Element[_capacity];
			memcpy(new_dynamic_array, _dynamic_array, _size * sizeof(Element)); // Skopiowanie danych ze starej tablicy do nowej zwiekszonej dwukrotnie
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
		_dynamic_array[0] = element;
	}
	//Dodanie na ostatnia pozycje
	else if (index == _size && _size > 0) {
		//Zwyczajne przypisanie wartosci, bo tablica dynamiczna ma miejsce, bo wczesniej bylo wywolane IncreaseCapacity
		_dynamic_array[index] = element;
	}
	//Dodanie na index miêdzy 0, a size
	else {
		//Przesuniecie w prawo elementow wiêkszych od indeksu, gdzie chcemy dodac element
		//Wartosc na indeks jest rowniez przesunieta
		for (int i = _size; i > index; i--) {
			_dynamic_array[i] = _dynamic_array[i - 1];
		}
		//Przypisanie nowej wartosci dla elementu na pozycju index
		_dynamic_array[index] = element;
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
		Element* new_arr = (Element*)realloc(_dynamic_array, _capacity * sizeof(Element)); //Proba zmiany rozmiaru tablicy. Jezeli sie nie uda zwraca NULL
		//Sprawdzenie czy zmiana rozmiaru sie uda³a
		if (new_arr == NULL) {
			Element* new_dynamic_array = new Element[_capacity];
			memcpy(new_dynamic_array, _dynamic_array, _size * sizeof(Element)); // Skopiowanie danych ze starej tablicy do nowej zwiekszonej dwukrotnie
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


int TablicaDynamiczna::GetSize() const
{
	return _size;
}

bool TablicaDynamiczna::IsEmpty() const
{
	return _size == 0;
}


void TablicaDynamiczna::Clear()
{
	delete[] _dynamic_array;
	_size = 0;
	_capacity = 4;
	_dynamic_array = new Element[_capacity];
}

Element& TablicaDynamiczna::GetAt(int index)
{
	if (index < 0 || index >= _size)
		throw std::out_of_range("Dynamic array is empty");
	return _dynamic_array[index];
}

void TablicaDynamiczna::PrintAll()
{
	for (int i = 0; i < _size; i++) {
		std::cout << "Priority: " << _dynamic_array[i].priority << ", Value: " << _dynamic_array[i].value << std::endl;
	}
}

