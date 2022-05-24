#include "History.h"
#include "globals.h"
#include <iostream>

using namespace std;

class Mesa;

History::History(int nRows, int nCols)
{
	rows = nRows;
	cols = nCols;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			histGrid[i][j] = '.';
	}
}

bool History::record(int r, int c)
{
	char s('.');
	s = histGrid[r-1][c-1];

	if (r > rows || c > cols || r < 1 || c < 1)
		return false;

	switch (s) {
	case '.':
		histGrid[r-1][c-1] = 'A';
		break;
	case 'Z':
		break;
	default:
		histGrid[r-1][c-1] += 1;
	}
	return true;
}
void History::display() const 
{
	clearScreen();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << histGrid[i][j];
		cout << endl;
	}
	cout << endl;

}

