#ifndef LEVEL_H
#define LEVEL_H

#include "Sequence.h"
#include <limits>

const unsigned long NO_LEVEL = std::numeric_limits<unsigned long>::max();

class LevelList
{
public:
    LevelList();
    bool add(unsigned long level);
    bool remove(unsigned long level);
    int size() const;  
    unsigned long minimum() const;
    unsigned long maximum() const;
private:
    int SeqLevel;
    Sequence levels;


};
//#endif