#include "PriorityQueueHeap.h"
#include <iostream>

int PriorityQueueHeap::parentOf(int index)
{
	return index / 2;
}

int PriorityQueueHeap::leftChildOf(int index)
{
	return index * 2;
}

int PriorityQueueHeap::rightChildOf(int index)
{
	return (index * 2) + 1;
}

void PriorityQueueHeap::heapifyUp(int index)
{
	if (index > _size || index < 1)
		return;
	if (index == 1)
		return; //Jest na pozycji 1, nie potrzebna zmiana pozycji

	if (_heap->GetAt(index).priority > _heap->GetAt(parentOf(index)).priority) {
		std::swap(_heap->GetAt(index), _heap->GetAt(parentOf(index)));
	}
	heapifyUp(parentOf(index)); //Rekrurencyjne wywolanie funckji aby wszystkie wartosci byly poprawne
	//Wykonywane az do dojscia do pierwszej pozycji
}

void PriorityQueueHeap::heapifyDown(int index)
{
	if (index > _size)
		return;

	int indexToSwap = index; //Zmienna pomocnicza przechowujaca indeks wiekszego dziecka
	if (leftChildOf(index) <= _size && _heap->GetAt(leftChildOf(index)).priority > _heap->GetAt(index).priority) {
		indexToSwap = leftChildOf(index); // Jezeli lewe dziecko jest wieksze od rodzica to zmienna ma wartosc indeksu lewego dziecka
	}
	if (rightChildOf(index) <= _size && _heap->GetAt(rightChildOf(index)).priority > _heap->GetAt(indexToSwap).priority) {
		indexToSwap = rightChildOf(index); // Jezeli prawe dziecko jest wieksze od lewego dziecka lub rodzica to zmienna pomocnicza ma wartosc indeksu prawego dziecka
	}
	if (indexToSwap != index) {
		// Jezeli rodzic nie jest wiekszy niz jego dzieci to zamien rodzica z wiekszym od niego dzieckiem
		std::swap(_heap->GetAt(index), _heap->GetAt(indexToSwap));
		//Wywolanie rekurencyjne tej samej metody, zeby sprawdzic czy dziecko, ktore zamienione zostalo z rodzicem jest uporzadkowane dobrze
		//Wykonywane jest to momentu kiedy rodzic jest wiekszy niz jego dzieci lub indeks jest poza zasiegiem
		heapifyDown(indexToSwap);
	}
}

int PriorityQueueHeap::indexOfElement(int index, int oldPriority)
{
	if (index >= _size)
		return -1;

	for (int i = 1; i <= _size; i++) {
		if (oldPriority == _heap->GetAt(i).priority)
			return i;
	}
	return -1;
}


PriorityQueueHeap::PriorityQueueHeap()
{
	_size = 0;
	Element firstElement(-1, -1);
	_heap = new TablicaDynamiczna();
	_heap->InsertAt(0, firstElement);
}

PriorityQueueHeap::~PriorityQueueHeap()
{
	delete[] _heap;
}

void PriorityQueueHeap::Insert(int value, int priority)
{
	Element elementToInsert(value, priority);
	_heap->InsertAt(_size + 1, elementToInsert); // Dodanie nowego elementu na koniec
	heapifyUp(++_size); // Uporzadkowanie kopca od dodanego elementu
}

Element PriorityQueueHeap::ExtractMax()
{
	if (isEmpty()) {
		throw std::out_of_range("The priority queue is empty");
	}

	Element maximumElement = _heap->GetAt(1);

	std::swap(_heap->GetAt(1), _heap->GetAt(_size)); // Przeniesienie ostatniego elementu na miejsce pierwsze
	_size--; // Zmiejszenie wielkosci kopca
	_heap->DeleteAt(_size);
	heapifyDown(1); // Uporzadkowanie kopca 
	return maximumElement; // Zwrocenie usunietego elementu
}

Element& PriorityQueueHeap::Peek()
{
	if (isEmpty()) {
		throw std::out_of_range("The priority queue is empty");
	}
	return _heap->GetAt(1);
}

void PriorityQueueHeap::ModifyKey(int oldPriority, int newPriority)
{
	if (isEmpty()) {
		std::cout << "The priority queue is empty" << std::endl;
		return;
	}
	if (oldPriority == newPriority) {
		std::cout << "Priorities are the same!" << std::endl;
		return;
	}
	int newIndex = indexOfElement(1, oldPriority);
	if (newIndex == -1) {
		std::cout << "Unable to find an element with this priority" << std::endl;
		return;
	}
	_heap->GetAt(newIndex).priority = newPriority;
	if (oldPriority > newPriority)
		heapifyDown(newIndex);
	else
		heapifyUp(newIndex);
}

bool PriorityQueueHeap::isEmpty() const
{
    return _size == 0;
}

int PriorityQueueHeap::GetSize() const
{
    return _size;
}

void PriorityQueueHeap::PrintAll()
{
	if (isEmpty()) {
		std::cout << "The priority queue is empty" << std::endl;
		return;
	}
	std::cout << "Size of heap: " << _size << std::endl;
	for (int i = 1; i <= _size; i++) {
		if (leftChildOf(i) > _size && rightChildOf(i) > _size)
			break;
		std::cout << "Parent Node :: Priority: " << _heap->GetAt(i).priority << ", Value: " << _heap->GetAt(i).value << " ";
		if (leftChildOf(i) <= _size) {
			std::cout << "Left Child Node :: Priority: " << _heap->GetAt(leftChildOf(i)).priority << ", Value: " << _heap->GetAt(leftChildOf(i)).value << " ";
		}
		if (rightChildOf(i) <= _size) {
			std::cout << "Right Child Node :: Priority: " << _heap->GetAt(rightChildOf(i)).priority << ", Value: " << _heap->GetAt(rightChildOf(i)).value << " ";
		}
		std::cout << std::endl;
	}
}

void PriorityQueueHeap::Clear()
{
	_heap->Clear();
	_size = 0;
	Element firstElement(-1, -1);
	_heap->InsertAt(0, firstElement);
}
