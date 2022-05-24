#ifndef HISTORYINCLUDED
#define HISTORYINCLUDED

#include "globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
private:
	int rows, cols;
	char histGrid[MAXROWS][MAXCOLS];
};


#endif //HISTORYINCLUDED
