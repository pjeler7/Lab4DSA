#include "Set.h"
#include "SetITerator.h"
#include <iostream>

//Worst case: O(1), Best Case: O(1), Average case: O(1)
int Set::hashFunction(TElem elem) const
{
	return abs(elem % m);
}

//Worst case:O(n), Best Case: O(m), Average: Theta(n)
void Set::resize()
{
	m *= 2;
	Node** newHash = new Node * [m];
	for (int i = 0; i < this->m; i++)
		newHash[i] = nullptr;
	int count = m / 2;
	for (int i = 0; i < count; i++) {
		Node* current = hash[i];
		while (current != nullptr) {
			int newPos = hashFunction(current->elem);
			Node* nextPos = current->next;
			current->next = newHash[newPos];
			newHash[newPos] = current;
			current = nextPos;
		}
	}

	delete[] hash;
	hash = newHash;
}
//Worst case: O(1), Best Case: O(1), Average case: Theta(1)
Set::Set() {
	this->length = 0;
	this->m = 10;
	this->hash = new Node * [this->m];
	for (int i = 0; i < this->m; i++)
		this->hash[i] = NULL;
}


//Worst case: O(n), Best Case: O(1), Average case: Theta(m)
bool Set::add(TElem elem) {
	if (this->length / this->m > 0.7) {
		this->resize();
	}
	int pos = hashFunction(elem);

	Node* node = this->hash[pos];
	Node* prev = this->hash[pos];

	while (node != NULL) {
		if (node->elem == elem) {
			return false;
		}
		prev = node;
		node = node->next;
	}

	Node* newNode = new Node();
	newNode->next = NULL;
	newNode->elem = elem;

	if (prev != NULL) {
		prev->next = newNode;
	}
	else {
		this->hash[pos] = newNode;
	}

	this->length++;
	return true;
}

//Worst case: O(n), Best Case: O(1), Average case: O(n)
bool Set::remove(TElem elem) {
	int pos = this->hashFunction(elem);
	Node* currentNode = this->hash[pos];
	Node* prevNode = NULL;
	if (currentNode == NULL)
		return false;

	while (currentNode != NULL) {
		if (currentNode->elem == elem) {
			if (prevNode == NULL) {
				//currentNode = currentNode->next;
				this->hash[pos] = currentNode->next;
				this->length--;
				delete currentNode;
				return true;
			}
			else {
				prevNode->next = currentNode->next;
				this->length--;
				delete currentNode;
				return true;
			}
		}
		prevNode = currentNode;
		currentNode = currentNode->next;
	}
	return false;
}

//Worst case: O(n), Best Case: O(1), Average case: O(n)
bool Set::search(TElem elem) const {
	int pos = this->hashFunction(elem);
	Node* currentNode = this->hash[pos];
	while (currentNode != NULL) {
		if (currentNode->elem == elem)
			return true;
		currentNode = currentNode->next;
	}
	return false;
}

//Worst case: O(1), Best Case: O(1), Average case: O(1)
int Set::size() const {
	return this->length;
}

//Worst case: O(1), Best Case : O(1), Average case: O(1)
bool Set::isEmpty() const {
	return this->length == 0;
}

//Worst case: O(n), Best Case: O(n), Average case: O(n)
Set::~Set() {
	for (int i = 0; i < m; i++)
		delete this->hash[i];
	delete[] this->hash;
}

//Worst case: O(1), Best Case: O(1), Average case: O(1)
SetIterator Set::iterator() const {
	return SetIterator(*this);
}


