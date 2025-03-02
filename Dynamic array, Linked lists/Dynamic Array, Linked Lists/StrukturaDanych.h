#pragma once
class StrukturaDanych
{
public:
	virtual void InsertAt(int index, int value) = 0;
	virtual void DeleteAt(int index) = 0;
	virtual int FindValue(int value) const = 0;
	virtual int GetSize() const = 0;
	virtual bool IsEmpty() const = 0;
	virtual void PrintAll() const = 0;
	virtual void Clear() = 0;
};

