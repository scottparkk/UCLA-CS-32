#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find("laobing") == -1);
    assert(s.insert("laobing") == 0);
    assert(s.size() == 1 && s.find("laobing") == 0);
    cout << "Passed all tests in Sequence" << endl;
}