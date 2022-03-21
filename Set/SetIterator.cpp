#include "SetIterator.h"
#include "Set.h"
#include <exception>
#include <iostream>

// Best Case: O(n), Worst Case: O(n^2), Average case: O(n^2)
SetIterator::SetIterator(const Set& m) : set(m)
{
	this->currentPos = 0;
	this->currentNode = nullptr;
	while (currentPos < set.m && set.hash[currentPos] == NULL)
		currentPos++;
	if (currentPos < set.m)
		currentNode = set.hash[currentPos];
	else
		currentNode = NULL;
}


///Worst case: O(1), Best Case: O(n), Average case: O(1)
void SetIterator::first() {
	this->currentPos = 0;
	while (currentPos < set.m && set.hash[currentPos] == NULL)
		currentPos++;
	if (this->currentPos < set.m)
		this->currentNode = set.hash[currentPos];
	else
		this->currentNode = NULL;

}

///Worst case: O(1), Best Case: O(n), Average case: O(n)
void SetIterator::next() {
	if (!valid())
		throw std::exception();
	if (this->currentNode->next != NULL)
		this->currentNode = this->currentNode->next;
	else {
		while (this->currentPos < set.m) {
			this->currentPos++;
			if (set.hash[currentPos] != NULL) {
				this->currentNode = set.hash[currentPos];
				return;
			}
		}
	}
}

//Worst case: O(1), Best Case: O(1), Average case: O(1)
TElem SetIterator::getCurrent()
{
	if (!valid())
		throw std::exception();
	return this->currentNode->elem;
}
//Worst case: O(1), Best Case: O(1), Average case: O(1)
bool SetIterator::valid() const {
	if (this->currentPos < 0 || this->currentPos >= set.m) {
		return false;
	}
	return true;
}



