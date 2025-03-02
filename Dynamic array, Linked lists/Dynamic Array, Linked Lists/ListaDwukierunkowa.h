#pragma once
#include "StrukturaDanych.h"
class ListaDwukierunkowa : public StrukturaDanych
{
private:
	struct Node {
		Node* next;
		Node* previous;
		int value;
		Node(int value, Node* next, Node* previous) {
			this->value = value;
			this->next = next;
			this->previous = previous;
		}
	};
	int _size;
	Node* _head;
	Node* _tail;
public:
	ListaDwukierunkowa();
	~ListaDwukierunkowa();
	void InsertAt(int index, int value);
	void DeleteAt(int index);
	int FindValue(int value) const;
	int GetSize() const override;
	bool IsEmpty() const override;
	void PrintAll() const override;
	void Clear() override;
};

