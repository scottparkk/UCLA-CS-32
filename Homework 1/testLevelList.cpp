#include "LevelList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	LevelList l;
	LevelList p;
	assert(l.size() == 0);
	assert(l.maximum() == NO_LEVEL);
	assert(l.minimum() == NO_LEVEL);
	assert(l.add(20) == false);
	assert(l.add(35) == true);
	assert(l.add(40) == true);
	assert(l.add(100) == true);
	assert(l.add(69) == true);
	assert(l.remove(35) == true);
	assert(l.remove(50) == false);
	assert(l.size() == 3);
	assert(l.maximum() == 100);
    assert(l.minimum() == 40);

	p.add(40);
	p.add(40);
	p.add(35);
	assert(p.remove(40) == true);
	assert(p.size() == 2);
}