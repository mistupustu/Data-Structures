#include "BinarySearchTree.h"
#include <format>


Node* BinarySearchTree::findMin(Node* node)
{
	if (node == nullptr)
		return nullptr;
	else if (node->leftChild == nullptr)
		return node;
	else
		return findMin(node->leftChild);
}

Node* BinarySearchTree::insertRecursivly(Node* node, KeyValuePair element)
{
	//Jezeli node jest nullptr to stworzony zostaje nowy node, ktorego dzieci sa nullptr
	if (node == nullptr) {
		KeyValuePair kvp(element.GetKey(), element.GetValue());
		Node* newNode = new Node(kvp);
		newNode->leftChild = nullptr;
		newNode->rightChild = nullptr;
		return newNode;
	}
	//Jezeli istnieje juz klucz w bst, to zmienia sie jego wartosc na nowa
	else if (node->value.GetKey() == element.GetKey()) {
		node->value.SetValue(element.GetValue());
		return node;
	}
	//Jezeli klucz elementu, ktory chcemy dodac jest mniejszy, niz klucz w node, to wywolujemy te sama funckje na jego lewe dziecko
	else if (element.GetKey() < node->value.GetKey()) {
		node->leftChild = insertRecursivly(node->leftChild, element);
	}
	//Jezeli klucz elementu, ktory chcemy dodac jest wiekszy, niz klucz w node, to wywolujemy te sama funckje na jego prawe dziecko
	else if (element.GetKey() > node->value.GetKey()) {
		node->rightChild = insertRecursivly(node->rightChild, element);
	}
	//Na koniec zwracamy node
	return node;
}

Node* BinarySearchTree::removeRecursivly(Node* node, int key, Node& deletedNode, bool& found)
{
	if (node == nullptr) {
		return node;
	}
	//Jezeli klucz jest mniejszy niz klucz node, to element do usuniecia znajduje sie po stronie lewego dziecka
	else if (key < node->value.GetKey()) {
		node->leftChild = removeRecursivly(node->leftChild, key, deletedNode, found);
	}
	//Jezeli klucz jest wiekszy niz klucz node, to element do usuniecia znajduje sie po stronie prwaego dziecka
	else if (key > node->value.GetKey()) {
		node->rightChild = removeRecursivly(node->rightChild, key, deletedNode, found);
	}
	//Jezeli node ma wartosc klucza
	else {
		if (!found) {
			deletedNode = *node;
			found = true;
		}

		//Przypadek 1: Node nie ma dzieci
		if (node->leftChild == nullptr && node->rightChild == nullptr) {
			delete node;
			return nullptr;
			//Zwyczajne usuniecie node. Nie trzeba nic zmieniac w BST
		}
		//Przypadek 2: Node ma jedno dziecko
		else if (node->leftChild == nullptr) {
			//Node ma tylko prawe dziecko, wiec ptr node wskazuje na dziecko ktore posiada, a nastepnie sie go usuwa.
			Node* temp = node;
			node = node->rightChild;
			delete temp;
		}
		else if (node->rightChild == nullptr) {
			//Node ma tylko lewe dziecko, wiec ptr node wskazuje na dziecko ktore posiada, a nastepnie sie go usuwa.
			Node* temp = node;
			node = node->leftChild;
			delete temp;
		}
		//Przypadek 3: Node ma 2 dzieci
		else {
			Node* temp = findMin(node->rightChild);
			node->value = temp->value;
			node->rightChild = removeRecursivly(node->rightChild, temp->value.GetKey(), deletedNode, found);
		}
		return node;
	}
	return node;
}

Node* BinarySearchTree::findRecursivly(Node* node, int key)
{
	//Jezeli jest null to zwroc null
	if (node == nullptr) {
		return nullptr;
	}
	//Jezeli znajdzie sie to zwroc odpowiedni node
	else if (node->value.GetKey() == key)
		return node;
	//Jezeli szukany key jest mniejszy niz aktualnego node, to sprawdzamy jego lewe dziecko.
	else if (key < node->value.GetKey())
		return findRecursivly(node->leftChild, key);
	//Jezeli szukany key jest wiekszy niz aktualnego node, to sprawdzamy jego prawe dziecko.
	else if (key > node->value.GetKey())
		return findRecursivly(node->rightChild, key);
}

void BinarySearchTree::PrintElement(Node* node, std::string message) const
{
	if (node == nullptr)
		return;
	std::cout << message << ":: Key :: " << node->value.GetKey() << ", Value :: " << node->value.GetValue() << std::endl;

	PrintElement(node->leftChild, "Left Child");
	PrintElement(node->rightChild, "Right Child");
}

void BinarySearchTree::ClearRecursivly(Node* node)
{
	if (node == nullptr)
		return;
	ClearRecursivly(node->leftChild);
	ClearRecursivly(node->rightChild);
	delete node;
	node = nullptr;
}

BinarySearchTree::BinarySearchTree()
{
	_size = 0;
	root = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
	if (isEmpty())
		return;
	ClearRecursivly(root);
	_size = 0;
}

void BinarySearchTree::Insert(int key, int value)
{
	KeyValuePair kvp(key, value);

	root = insertRecursivly(root, kvp);
	_size++;
}

Node BinarySearchTree::Remove(int value)
{
	if (root == nullptr)
		throw std::out_of_range("BST is empty!");

	Node& deletedNode = *(new Node());
	bool& found = *(new bool(false));
	root = removeRecursivly(root, value, deletedNode, found);
	if (!found) {
		std::cout << "Unable to find element with specified key" << std::endl;
		return Node();
	}
	_size--;
	return deletedNode;
}

Node* BinarySearchTree::Find(int value)
{
	if (root == nullptr)
		throw std::out_of_range("BST is empty!");


	Node* tempForSearching = findRecursivly(root, value);
	if (tempForSearching == nullptr) {
		std::cout << "Unable to find element with this key in BST" << std::endl;
		return nullptr;
	}
	return tempForSearching;
}

bool BinarySearchTree::isEmpty() const
{
	return _size == 0;
}

int BinarySearchTree::GetSize() const
{
	return _size;
}

void BinarySearchTree::PrintAll() const
{
	if (root == nullptr) {
		std::cout << "BST is empty!" << std::endl;
		return;
	}
	PrintElement(root, "Root");
}

void BinarySearchTree::Clear()
{
	if (isEmpty())
		return;
	ClearRecursivly(root);
	root = nullptr;
	_size = 0;
}

Node* BinarySearchTree::GetRoot() const
{
	return root;
}
