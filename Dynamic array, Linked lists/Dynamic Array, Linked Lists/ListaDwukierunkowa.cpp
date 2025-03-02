#include "ListaDwukierunkowa.h"
#include <iostream>

ListaDwukierunkowa::ListaDwukierunkowa()
{
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
}

ListaDwukierunkowa::~ListaDwukierunkowa()
{
    if (_size > 0) {
        Node* current = _head;
        while (current->next != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete _head;
    delete _tail;
}


void ListaDwukierunkowa::InsertAt(int index, int value)
{
    //Sprawdzenie czy podany index jest poprawny
    if (index < 0 || index > _size) {
        std::cout << "Can't insert element out of single linked list bounds" << std::endl;
        return;
    }
    //Dodanie na poczatek
    if (index == 0) {
        //Sprawdzenie, czy tablica jest pusta, zeby poprawnie zinicializowac Node
        if (_size == 0) {
            Node* node_to_insert = new Node(value, nullptr, nullptr);
            _head = _tail = node_to_insert;
        }
        else {
            //Tworzy siê nowy node, ktorego nastepnym nodem jest nastepny node heada, a head teraz = nowy node
            Node* node_to_insert = new Node(value, _head, nullptr);
            _head = node_to_insert;
            //Sprawdzenie, czy next heada jest rozny niz nullptr zeby nie odnosic sie do nullptr
            if (_head->next != nullptr)
                _head->next->previous = node_to_insert;
        }
    }
    //Dodanie na koniec
    else if (index == _size && index > 0) {
        _tail->next = new Node(value, nullptr, _tail);
        _tail = _tail->next;
        //Sprawdzenie, czy previous taila jest rozny niz nullptr zeby nie odnosic sie do nullptr
        if (_tail->previous != nullptr)
            _tail->previous->next = _tail;
    }
    //Dodawanie na pozostale pozycje
    else {
        bool firstHalf = _size / index > 2; //Zmienna ktora mowi, czy zaczynac od head, czy tail dla lepszej wydajnoœci
        if (firstHalf) {
            Node* current = _head;
            //Przejscie po elementach, a¿ nie dojdzie sie do elementu po lewej od indeksu
            for (int i = 1; i < index; i++) {
                current = current->next;
            }
            //Tworzy sie node, ktorego poprzednim jest current, a nastepnym jest ten, ktory wczesniej byl nastepnym currenta
            Node* node_to_insert = new Node(value, current->next, current);
            //Przypisanie wskaznika previous nastepnego node jako dodanego node
            current->next = node_to_insert;
            node_to_insert->next->previous = node_to_insert;
        }
        else {
            Node* current = _tail;
            //Przejscie po elementach, a¿ nie dojdzie sie do elementu po prawej od indeksu
            for (int i = _size - 1; i > index; i--) {
                current = current->previous;
            }
            //Tworzy sie node, ktorego poprzednim jest poprzednik currenta, a nastepnym jest current
            Node* node_to_insert = new Node(value, current, current->previous);
            //Przypisanie wskaznika next poprzedniego node jako dodanego node
            current->previous->next = node_to_insert;
            current->previous = node_to_insert;
        }
    }
    _size++;
}
void ListaDwukierunkowa::DeleteAt(int index)
{
    //Sprawdzenie czy podany index jest poprawny
    if (index < 0 || index > _size) {
        std::cout << "Can't insert element out of single linked list bounds" << std::endl;
        return;
    }
    //Usuniecie z poczatku
    if (index == 0) {
        Node* node_to_delete = _head;
        _head = _head->next;
        delete node_to_delete;
    }
    //usuniecie z konca
    else if (index == _size - 1 && index > 0) {
        Node* node_to_delete = _tail;
        _tail->previous->next = nullptr;
        _tail = node_to_delete->previous;
        delete node_to_delete;
    }
    //Usuniecie z pozostalych pozycji
    else {
        bool firstHalf = _size / index > 2; //Zmienna ktora mowi, czy zaczynac od head, czy tail dla lepszej wydajnoœci
        if (firstHalf) {
            Node* current = _head;
            //Przejscie po elementach, a¿ nie dojdzie sie do elementu po lewej od indeksu
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            Node* node_to_delete = current->next;
            current->next = node_to_delete->next;
            node_to_delete->next->previous = current;
            delete node_to_delete;
        }
        else {
            Node* current = _tail;
            //Przejscie po elementach, a¿ nie dojdzie sie do elementu po prawej od indeksu
            for (int i = _size - 1; i > index + 1; i--) {
                current = current->previous;
            }
            Node* node_to_delete = current->previous;
            node_to_delete->previous->next = current;
            current->previous = node_to_delete->previous;
            delete node_to_delete;
        }
    }
    _size--;
    if (_size == 0)
        _tail = _head = nullptr;
}

int ListaDwukierunkowa::FindValue(int value) const
{
    //Jezeli lista jest pusta to zwraca -1
    if (IsEmpty()) {
        std::cout << "Can't find an element in an empty list" << std::endl;
        return -1;
    }
    if (_tail->value == value)
        return _size - 1;
    Node* current = _head;
    int index = 0; //Zmienna index do znania pozycji na ktorej aktualnie jestesmy
    //Przejscie po wszystkich node'ach listy dopoki nie znajdziemy wartosci lub do jej konca
    while (current->next != nullptr) {
        if (current->value == value)
            return index;
        current = current->next;
        index++;
    }
    //Zwrocenie -1 jezeli nie znajdzie sie wartosci w liscie
    std::cout << "Unable to find value in list" << std::endl;
    return -1;
}

int ListaDwukierunkowa::GetSize() const
{
    return _size;
}

bool ListaDwukierunkowa::IsEmpty() const
{
    return _size == 0;
}

void ListaDwukierunkowa::PrintAll() const
{
    if (IsEmpty()) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node* current = _head;
    int i = 0;
    //Przejscie po wszystkich pozycjach, wypisanie ich oraz ich indeksu
    while (current != nullptr) {
        std::cout << i << ". " << current->value << std::endl;
        current = current->next;
        i++;
    }
}

void ListaDwukierunkowa::Clear()
{
    if (_size > 0) {
        Node* current = _head;
        while (current->next != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    _head = _tail = nullptr;
    _size = 0;
}
