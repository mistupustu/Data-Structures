#include "ListaJednokierunkowaTail.h"
#include <iostream>

ListaJednokierunkowaTail::ListaJednokierunkowaTail()
{
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
}

ListaJednokierunkowaTail::~ListaJednokierunkowaTail()
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

void ListaJednokierunkowaTail::InsertAt(int index, int value)
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
            Node* node_to_insert = new Node(value, nullptr);
            _head = _tail = node_to_insert;
        }
        else {
            //Tworzy siê nowy node, ktorego nastepnym nodem jest nastepny node heada, a head teraz = nowy node
            Node* node_to_insert = new Node(value, _head);
            _head = node_to_insert;
        }        
    }
    //Dodanie na koniec
    else if (index == _size && index > 0) {
        _tail->next = new Node(value, nullptr);
        _tail = _tail->next;
    }
    //Dodawanie na pozostale pozycje
    else {
        Node* current = _head;
        //Przejscie po nodach dopoki nie jestesmy na node z indeksem o jeden mniejszy od tego, gdzie chcemy dodac
        for (int i = 1; i < index; i++) {
            current = current->next;
        }
        //next dodanego node przyjmuje wartosc next node, ktory byl na pozycji wczesniej, a next poprzedniego teraz wskazuje na dodanego node
        Node* node_to_insert = new Node(value, current->next);
        current->next = node_to_insert;
    }
    _size++;
}

void ListaJednokierunkowaTail::DeleteAt(int index)
{
    //Sprawdzenie czy podany index jest poprawny
    if (index < 0 || index > _size - 1) {
        std::cout << "Can't delete element out of single linked list bounds" << std::endl;
        return;
    }
    if (IsEmpty()) {
        std::cout << "Can't delete from an empty list" << std::endl;
        return;
    }
    //Usuniecie na poczatku
    if (index == 0) {
        //Pomocniczy wskaznik na head
        Node* node_to_delete = _head;
        //Zmiana head, zeby wskazywal na nastepny node
        _head = _head->next;
        //Usuniecie poczatkowego node
        delete node_to_delete;
    }
    //Usuniecie z pozosta³ych pozycji
    else {
        Node* current = _head;
        //Przejscie po nodach dopoki nie jestesmy na node z indeksem o jeden mniejszy od tego, gdzie chcemy usunac
        for (int i = 1; i < index; i++) {
            current = current->next;
        }
        //Pomocniczy wskaznik wskazujacy na element o indekcie podanym
        Node* node_to_delete = current->next;
        //Element o indeks mniejszy od usuwanego wskazuje na element o indeksie o jeden wiekszy od usuwanego
        current->next = node_to_delete->next;
        //Usuniecie elementu o indeksie podanym
        delete node_to_delete;
    }
    _size--;
    if (_size == 0)
        _tail = _head = nullptr;
}

int ListaJednokierunkowaTail::FindValue(int value) const
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

int ListaJednokierunkowaTail::GetSize() const
{
    return _size;
}

bool ListaJednokierunkowaTail::IsEmpty() const
{
    return _size == 0;
}

void ListaJednokierunkowaTail::PrintAll() const
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

void ListaJednokierunkowaTail::Clear()
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
