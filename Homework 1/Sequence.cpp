#include "Sequence.h"
#include <iostream>
#include <string>
using namespace std;

Sequence::Sequence() { //creates the empty sequence
	arraySize = 0;
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
	if (pos < 0 || pos > size())
		return -1;
	else if (pos >= DEFAULT_MAX_ITEMS)
		return -1;
	else if (pos == size()) { // Basically adding value to the end of the array
		sequence[pos] = value;
		arraySize++;
		return pos;
	}
	else{
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
	if (pos >= DEFAULT_MAX_ITEMS) // if pos is greater than max amount
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
	int maxSize = size();
	ItemType temp;

	if (other.size() > maxSize) {
		maxSize = other.size(); // to see which size() is bigger
	} 
	for (int i = 0; i < maxSize; i++) {
		temp = sequence[i];
		sequence[i] = other.sequence[i]; 
		other.sequence[i] = temp; //swaps temp and other element
	}

	int tempSize = size();
	arraySize = other.size(); 
	other.arraySize = tempSize; 

}
