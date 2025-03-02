#pragma once

struct Element {
    int value;
    int priority;
    Element(int value, int priority) : value(value), priority(priority) {}
    Element() {}
};

class PriorityQueueMax
{
private:

public:
    PriorityQueueMax() {}
    virtual ~PriorityQueueMax() {}

    virtual void Insert(int value, int priority) = 0;
    virtual Element ExtractMax() = 0;
    virtual Element& Peek() = 0;
    virtual void ModifyKey(int oldPriority, int newPriority) = 0;
    virtual bool isEmpty() const = 0;
    virtual int GetSize() const = 0;
    virtual void Clear() = 0;
    virtual void PrintAll() = 0;
};