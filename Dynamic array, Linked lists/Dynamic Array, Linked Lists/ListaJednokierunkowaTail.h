#pragma once
#include "StrukturaDanych.h"
class ListaJednokierunkowaTail : public StrukturaDanych
{
private:
	struct Node {
		Node* next;
		int value;
		Node(int value, Node* next) {
			this->value = value;
			this->next = next;
		}
	};
	int _size;
	Node* _head;
	Node* _tail;
public:
	ListaJednokierunkowaTail();
	~ListaJednokierunkowaTail();
	void InsertAt(int index, int value);
	void DeleteAt(int index);
	int FindValue(int value) const;
	int GetSize() const override;
	bool IsEmpty() const override;
	void PrintAll() const override;
	void Clear() override;
};

