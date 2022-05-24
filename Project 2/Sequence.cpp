#include "Sequence.h"
#include <iostream>
#include <string>
using namespace std;

//PRIVATE FUNCTIONs
void Sequence::addValue(Node* x, const ItemType& value) { //similar to insert, but w/o a return value and takes in Node* 
	Node* temp = new Node;
	temp->next = x->next; //set new temp node pointer to new node
	temp->value = value; 
	x->next = temp; 
	temp->prev = x;
	temp->next->prev = temp;
}

void Sequence::nodeBefore(int pos, Node*& x) { //need since addValue's x node is actually one node before position we want to insert
	int i = 1;
	if (pos == 0) {
		x = head;
		return;
	}
	for (Node* p = head->next; p != head; p = p->next) { //loop through nodes
		if (i == pos) {
			x = p;
			return;
		}
		i++;
	}
}

Sequence::Sequence() { 
	seqSize = 0; // sets sequence size to equal 0
	head = new Node; // creates "dummy" head node
	//both next and previous should be equal to head ( circular)
	head->next = head;
	head->prev = head; 
}

Sequence::Sequence(const Sequence& old) { //copy constructor
	// same stuff as constructor...
	seqSize = 0; 
	head = new Node; 
	head->next = head;
	head->prev = head;
	// anddd ...
	if(old.size() != 0){ // if not empty..
		Node* p = old.head->next; // ( since linked list we must loop)
		int i = 0;
		while (i < old.size()) {
			this->insert(i, p->value); //copys the value using our insert fxn
			p = p->next; // go to next node
			i++;
		}
	}
}
Sequence& Sequence:: operator = (const Sequence& old) { //assignment op
	if (this == &old) // just return *this if they already =
		return *this;
	seqSize = 0;
	head = new Node; // new sequence
	head->next = head;
	head->prev = head;
	if (this->size() > 0) {
		Node* p = head->next;
		while (p != head) { //loop
			Node* holder = p->next;
			delete p; //delete the current sequence's nodes
			p = holder;
		}
	}
	Node* j = old.head->next;
	int i = 0;
	if (old.size() != 0) //if 'old' sequence is not empty
		while (i < old.size()) {
			this->insert(i, j->value); //copy/assign value over to sequence
			j = j->next; 
			i++; // must increment up

		}
	return *this;
}

Sequence::~Sequence() {
	Node* p = head->next; // p should start at the 0th index
	while (p != head) {
		Node*holder = p->next; // create a holder  to hold the next node pointer
		delete p; //gets rid of node at p
		p = holder;
	}

	delete head; //delete the dummy node
}

bool Sequence::empty() const { // if sequence is empty, then return true ( else - false)
	if (size() == 0)
		return true;
	else
		return false;
}

int Sequence::size() const { // returns the size of the array
	return seqSize;
}

int Sequence::insert(int pos, const ItemType& value) { // checks given parameters, and if passed, puts value and given position
	if (pos < 0 || pos > size()) // first check to make sure that the position is greater than 0 and less than the sequence size
		return -1;
	else if (pos == 0) { // adding to position 0
		addValue(head, value);
		seqSize++;
		return pos;
	}
	else {
		Node* x;
		nodeBefore(pos, x);
		addValue(x, value);
		seqSize++; //make sure to add 1 to sequence size
		return pos;
	}

}

int Sequence::insert(const ItemType& value) {
	int k = -100; // doesn't really matter what this value is, as long as its less than 0
	int p = 0;
	int counter = 0;
	
	if (size() == 0) {
		insert(0, value);
		seqSize++;
		return p;
	}
	for(Node* x = head->next;x!=head; x= x->next){ // create a loop through sequence
		if (value <= x->value) {// check to see if our value is less than or equal to the actual value held in the node
			k = counter;
			break;
		}
		counter++;
	}
	if (k == -100) // if k was unchanged, that means our value was larger than all other values
		k = size();
	Node* t;
	nodeBefore(k, t); // finds node before the index we want to insert
	addValue(t, value); // adds value after the node found in nodeBefore()
	seqSize++;
	return k;
}

bool Sequence::erase(int pos) {
	if (pos < 0 || pos >= size())
		return false;
	else {
		Node* y;
		nodeBefore(pos, y); //gets the node which is before pos

		Node* x;
		x = y->next; //node at position pos

		x->next->prev = y; //move node after pos's prev pointer
		y ->next = x->next;
		delete x;
		x = nullptr;
		seqSize--;
		return true;
		}
}

int Sequence::remove(const ItemType& value) {
	int counter = 0;
	int counterForErase = 0;
	for (Node* x = head; x != head->prev; x = x->next) { // loop through sequence
		if (x->next->value == value) { // if the given value and nodes value mathc, erase that value
			erase(counter);
			counterForErase++;
			counter--; // since the size of array is decreasing
			x = x->prev;
		}
		counter++;
	}
	return counterForErase;
}

bool Sequence::get(int pos, ItemType& value) const {
	if (pos < 0 || pos >= size()) // check for a valid position
		return false;
	int counter = 0;
	for (Node* x = head->next; x != head; x = x->next) {// loop through nodes until we reach desired position
		if (counter == pos) {
			value = x->value; // set value equal to nodes value
			return true;
		}
		counter++;
	}
	return false;
}

bool Sequence::set(int pos, const ItemType& value) {// same as get, except NODES value is being set equal to given value
	if (pos < 0 || pos >= size())
		return false;
	int counter = 0;
	for (Node* x = head->next; x != head; x = x->next) {// loop through sequence
		if (counter == pos) { // we want to find the element at pos, so we keep track with a counter
			x->value = value;// sets value in sequence with OUR given value
			return true; // since changed return true
		}
		counter++;
	}
	return false;
}

int Sequence::find(const ItemType& value) const {
	int counter = 0;
	for (Node* x = head->next; x != head; x = x->next) { //loop through sequence
		if (value == x->value) {// check if given value matches value in node
			return counter;// if so then return position of node
		}
		counter++;
	}
	return -1;
}

void Sequence::swap(Sequence& other) {
	head->prev->next = other.head; //swap head values
	other.head->prev->next = head;

	Node* temp = head->next; // swap head's next values
	Node* temp2 = other.head->next;
	head->next = other.head->next;
	other.head->next = temp;

	temp->prev = head; // swap prev values
	temp2->prev = other.head;

	int tempSize = seqSize;//swap sizes
	seqSize = other.seqSize;
	other.seqSize = tempSize;
	
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
	if (seq1.size() == 0) // seq1 cannot be empty
		return -1;
	else if (seq2.size() == 0) // seq2 cannot be empty either
		return -1;
	else if (seq2.size() > seq1.size()) // the size of seq2 cannot be larger than seq1
		return -1;
	else {
		ItemType object1, object2; // to hold a value of seq1 and seq2 respectively
		int i = 0; 
		for (int j = 0; j <= seq1.size() - seq2.size(); j++) {// loop through seq1 first
			for (int k = 0; k < seq2.size(); k++) { // nested for loop for seq2
				seq2.get(k, object2); //gets value of seq2 at kth index
				seq1.get(j + k, object1); // gets value of seq1 at jth ( +k) index
				if (object2 != object1) { // if values are equal to eachother, break out of seq2 loop and move to next item of seq1
					i = 0;
					break;
				}
				i++;
			}
			if (i == seq2.size())
				return j; // j is the index value of the first consecutive instance of seq2 in seq1
		}
		return -1;
	}
}
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {

	Sequence seq1a = seq1;
	Sequence seq2a = seq2;
	if (seq1.size() == 0 && seq2.size() == 0) { // if both sequences are empty, then result should be empty
		if (result.size() != 0) {  //makes sure that result is empty( this code will repeat throughout)
			while (result.size() > 0)
				result.erase(0);  
		}
		return; // result should be empty if both seq1 and seq2 are empty
	}
	else if (seq1.size() == 0) { // if only seq1 is empty, result should contain only seq2
		if (result.size() != 0) {
			while (result.size() > 0)
				result.erase(0);
		}
		result = seq2a;//result should equal seq2
		return;
	}
	else if (seq2.size() == 0) { // if only seq2 is empty, result should contain only seq1
		if (result.size() != 0) {
			while (result.size() > 0)
				result.erase(0);
		}
		result = seq1a; //result should equal seq1
		return;
	}
	else if (seq1.size() == seq2.size()) { // if both have equal sizes, result should contain alternating values from seq 1 then 2
		//alternate 1 and 2
		if (result.size() != 0) {
			while (result.size() > 0)
				result.erase(0);
		}
		int counter = 0; // keep track of result size
		ItemType object1, object2; // to hold values from seq1 and seq2 respectively
		for (int i = 0; i < seq1a.size(); i++) {
			seq1a.get(i, object1); // gets values held by seq1 and seq2 at position i
			seq2a.get(i, object2);
			result.insert(counter, object1); // inserts values from get() into result sequence
			result.insert(counter + 1, object2);
			counter = counter + 2;
		}
		return;
	}
	else if (seq1.size() > seq2.size()) {// if seq1 has more items than seq2, alternate values in result from 1 then 2 until all values from 2 are used, to which you fill the rest with 1
		//alternate 1 and 2, then fill with rest of 1
		if (result.size() != 0) {
			while (result.size() > 0)
				result.erase(0);
		}
		int counter = 0; // keep track of result size
		ItemType object1, object2; // to hold values from seq1 and seq2 respectively
		for (int i = 0; i < seq2a.size(); i++) {//create loop to get values from sequence with get function, and then use insert
			seq1a.get(i, object1);
			seq2a.get(i, object2);
			result.insert(counter, object1);
			result.insert(counter + 1, object2);
			counter = counter + 2;
		}
		for (int j = 0; j < seq1a.size() - seq2a.size(); j++) {//since seq1 has more elements, fill remainder of list with seq1 items
			seq1a.get(j + seq2a.size(), object1);
			result.insert(counter, object1);
			counter++;
		}
		return;
	}
	else if (seq2.size() > seq1.size()) { // if seq2 has more items than seq1, alternate values in result from 1 then 2 until all values from 1 are used, to which you fill the rest with 2
		//alternate 1 and 2, then fill rest of 2
		if (result.size() != 0) {
			while (result.size() > 0)
				result.erase(0);
		}
		int counter = 0; // keep track of result size
		ItemType object1, object2; // to hold values from seq1 and seq2 respectively
		for (int i = 0; i < seq1a.size(); i++) { //create loop to get values from sequence with get function, and then use insert on result sequence
			seq2a.get(i, object1);
			seq1a.get(i, object2);
			result.insert(counter, object1);
			result.insert(counter + 1, object2);
			counter = counter + 2; // we are adding 2 items, so counter +2
		}
		for (int j = 0; j < seq2a.size() - seq1a.size(); j++) {// since seq2 has more elements, fill the remainder with seq2 items
			seq2a.get(j + seq1a.size(), object1);
			result.insert(counter, object1);
			counter++;// we are only adding 1 item, so keep track with counter + 1
		}
		return;
	}
}