#include "newSequence.h"
#include <iostream>
#include <string>
using namespace std;


Sequence::Sequence() {
	maximum = DEFAULT_MAX_ITEMS;
	arraySize = 0;
	sequence = new ItemType[maximum];
}

Sequence::Sequence(int items) {
	maximum = items;
	arraySize = 0;
	sequence = new ItemType[items];
}

Sequence:: ~Sequence() {
	delete[] sequence;
}

Sequence::Sequence(const Sequence& other) { // COPYYYYY CONSTRUCTA
	arraySize = other.size();
	maximum = other.maximum;
	sequence = new ItemType[arraySize];
	for (int i = 0; i < other.size(); i++) { // loop through in order to copy the contents of one sequence to other
		sequence[i] = other.sequence[i];

	}
}

Sequence& Sequence:: operator = (const Sequence& oldSeq) {
	if (&oldSeq == this)
		return *this;
	delete[] sequence;
	arraySize = oldSeq.size();
	maximum = oldSeq.maximum;
	sequence = new ItemType[arraySize];

	for (int i = 0; i < oldSeq.size(); i++) {
		sequence[i] = oldSeq.sequence[i]; //copying contents of array
	}
	return *this;
}


bool Sequence::empty() const { // if sequence is empty, then return true ( else - false)
	if (arraySize == 0)
		return true;
	else
		return false;
}

int Sequence::size() const { // returns the size of the array
	return arraySize;
}

int Sequence::insert(int pos, const ItemType& value) { // checks given parameters, and if passed, puts value and given position
	if (pos < 0 || size() >= maximum)
		return -1;
	else if (pos >= maximum)
		return -1;
	else if (pos == size()) { // Basically adding value to the end of the array
		sequence[pos] = value;
		arraySize++;
		return pos;
	}
	else {
		ItemType temp = sequence[pos]; // what was already at requested pos
		ItemType otherTemp;
		sequence[pos] = value; // now that we made a temp, can set new value at pos

		for (int i = pos + 1; i <= arraySize; i++) {
			otherTemp = sequence[i];
			sequence[i] = temp;
			temp = otherTemp;

		}
		arraySize++;
		return pos;
	}
}

int Sequence::insert(const ItemType& value) {
	if (size() >= maximum) // if pos is greater than max amount
		return -1;
	else if (size() == 0) { // if empty, insert at pos 0
		insert(0, value);
		pos = 0;
		return pos;
	}
	ItemType temp, otherTemp;
	for (int i = 0; i <= size(); i++) { // loop through sequence
		if (value <= sequence[i]) { // if the given value is less than or equal to element, then insert
			temp = sequence[i];
			sequence[i] = value;
			for (int k = i + 1; k <= size(); k++) { // shift all elements right because of insert
				otherTemp = sequence[k];
				sequence[k] = temp;
				temp = otherTemp;
			}
			return i;
		}
	}
	insert(size(), value);
	return size();
}

bool Sequence::erase(int pos) {
	ItemType temp, otherTemp;
	if (pos < 0 || pos >= size())
		return false;
	else {
		for (int i = pos; i < size() - 1; i++) {
			sequence[i] = sequence[i + 1]; //shifts elements left 
		}
		arraySize--;
		return true;
	}

}

int Sequence::remove(const ItemType& value) {
	int counter = 0; //a counter for the elements removed
	if (size() == 0)
		return 0;
	for (int i = 0; i <= size(); i++) { //Loop through sequence
		if (sequence[i] == value) {
			counter++;
			erase(i);
			i--;

		}
	}
	return counter;
}

bool Sequence::get(int pos, ItemType& value) const {
	if (pos < 0 || pos >= size())
		return false;
	value = sequence[pos];
	return true;
}

bool Sequence::set(int pos, const ItemType& value) {
	if (pos < 0 || pos >= size())
		return false;
	sequence[pos] = value;
	return true;
}

int Sequence::find(const ItemType& value) const {
	for (int i = 0; i < size(); i++) {
		if (sequence[i] == value)
			return i;
	}
	return -1;

}

void Sequence::swap(Sequence& other) {
	int temp = size();
	int temp2 = maximum;

	arraySize = other.size();
	other.arraySize = temp;


	maximum = other.maximum;
	other.maximum = temp2;          // <- i believe

	ItemType* temp3 = sequence;
	sequence = other.sequence;
	other.sequence = temp3;

}