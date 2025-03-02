#pragma once
#include "PriorityQueueMax.h"
class TablicaDynamiczna
{
private:
	int _capacity;
	Element* _dynamic_array;
	int _size;
public:
	TablicaDynamiczna();
	~TablicaDynamiczna();
	void InsertAt(int index, Element element);
	void DeleteAt(int index);
	int GetSize() const;
	bool IsEmpty() const;
	void Clear();
	Element& GetAt(int index);
	void PrintAll();
};

