#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <string>

using ItemType = std::string;

class Sequence
{
public:
    Sequence(); // constructor
    Sequence(const Sequence& old); // da copy constructor
    Sequence& operator = (const Sequence& old);  // assignment operator
    ~Sequence(); //DESTRUCCTORR
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);

private:
    struct Node { //struct for nodes
        ItemType value;
        Node* next;
        Node* prev;
    };
    int seqSize;  // # of elements in sequence
    Node* head; // head pointer
    void addValue(Node* x, const ItemType& value);
    void nodeBefore(int pos, Node*& x);


};
//NON MEMBER FUNCTIONS
int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif
