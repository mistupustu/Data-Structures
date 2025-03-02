#pragma once
#include "StrukturaDanych.h"

class TablicaDynamiczna : public StrukturaDanych
{
private: 
	int _capacity;
	int* _dynamic_array;
	int _size;
public:
	TablicaDynamiczna();
	~TablicaDynamiczna();
	void InsertAt(int index, int value);
	void DeleteAt(int index);
	int FindValue(int value) const;
	int GetSize() const override;
	bool IsEmpty() const override;
	void PrintAll() const override;
	int GetAt(int index) const;
	void Clear() override;
};

