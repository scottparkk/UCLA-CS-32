#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>

using namespace std;

class BoardImpl
{
  public:
    BoardImpl(const Game& g);
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;
  private:
      // TODO:  Decide what private members you need.  Here's one that's likely
      //        to be useful:
    const Game& m_game;
    char grid[MAXROWS][MAXCOLS];
    int rows, cols;
    int blockSize = 0;

};


BoardImpl::BoardImpl(const Game& g)
 : m_game(g), rows(g.rows()), cols(g.cols())
{
    //fill the the grid with dots '.'
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            grid[i][j] = '.';
    }
}

//clear the board 
void BoardImpl::clear()
{
    //clears board by filling with dots '.'
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            grid[i][j] = '.';
    }
}

//block half of the points on the board
void BoardImpl::block()
{
    //variable which is equal to half the number of points on the board
    int n = ((rows * cols) / 2); 
    //loop through random points, only progressing through the loop when blocking an UNBLOCKED point
    do {
        int randomRow = randInt(rows);
        int randomCol = randInt(cols);
        if (grid[randomRow][randomCol] == '.') {
            grid[randomRow][randomCol] = '#';
            n--;
        }
    } while (n != 0);
}

//unblock any previously blocked points
void BoardImpl::unblock()
{
    //loop through every point on the board, and change blocked points [#] to an unblocked point [.]
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '#')
                grid[i][j] = '.';
        }
    }

}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{   
    //if ship ID is invalid, return false
    if (shipId < 0 || shipId > this->m_game.nShips())
        return false;
    
    // first check to see if the intial point ( top or left) is on the board...
    //if (topOrLeft.r < 0 || topOrLeft.c < 0 || topOrLeft.r > rows - 1 || topOrLeft.c < cols - 1)
    if(!m_game.isValid(topOrLeft))
        return false;
    
    // if the orientation of the ship is vertical...
    if (dir == VERTICAL) {
        //check to see if the ship would go past the final row ( return false if so )
        if (topOrLeft.r + m_game.shipLength(shipId) - 1 >= rows)
            return false;
        // loop shipLength amount of times to ensure we are placing ships in unblocked spots w/o ships...
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            if (grid[topOrLeft.r + i][topOrLeft.c] != '.')
                return false;
        }
    }
    if (dir == HORIZONTAL) {
        //check to see if the ship would go past the final column ( return false if so )
        if (topOrLeft.c + m_game.shipLength(shipId)-1 >= cols)
            return false;
        // loop shipLength amount of times to ensure we are placing ships in unblocked spots w/o ships...
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            if (grid[topOrLeft.r ][topOrLeft.c + i] != '.')
                return false;
        }

    }
    // return false if the ship with that ship ID has previously been placed on this Board and not
    // yet been unplaced since its most recent placement.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            if (grid[i][j] == m_game.shipSymbol(shipId))
                return false;
    }
    // Now, we place the ship on the board 
    if (dir == VERTICAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            grid[topOrLeft.r + i][topOrLeft.c] = m_game.shipSymbol(shipId);
        }
    }
    if (dir == HORIZONTAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            grid[topOrLeft.r][topOrLeft.c + i] = m_game.shipSymbol(shipId);
        }
    }
    
    return true; //ship has been placed
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    //if ship ID is invalid, return false
    if (shipId < 0 || shipId > this->m_game.nShips())
        return false;

    // if the orientation of the ship is vertical...
    if (dir == VERTICAL) {
        //make sure that the ship is actually placed where it claims to be placed
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            if (grid[topOrLeft.r + i][topOrLeft.c] != m_game.shipSymbol(shipId))
                return false;
            // and if so, then unplace the ship
            for (int j = 0; j < m_game.shipLength(shipId); j++)
                grid[topOrLeft.r + j][topOrLeft.c] = '.';

        }
    }
    // if the orientation of the ship is horizontal...
    if (dir == HORIZONTAL){
        // make sure that the ship is actually placed where it claims to be placed
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            if (grid[topOrLeft.r ][topOrLeft.c +i] != m_game.shipSymbol(shipId))
                return false;
            // and if so, then unplace the ship
            for (int j = 0; j < m_game.shipLength(shipId); j++)
                grid[topOrLeft.r ][topOrLeft.c + j] = '.';
        }
    }

    return true; 
}

void BoardImpl::display(bool shotsOnly) const
{
    //dipslay the initial two empty spaces
    cout << "  ";
    // display the column numbers
    for (int i = 0; i < cols; i++)
        cout << i;
    cout << endl;
    // if we want to only display the entire board
    if (!shotsOnly) {
        // first display the row numbering followed my an empty space, then display that row's grid
        for (int i = 0; i < rows; i++) {
            cout << i << " ";
            for (int j = 0; j < cols; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
    }
    // if we want to only display the shots fired
    if (shotsOnly) {
        // first display the row numbering followed my an empty space, then display that row's grid 
        for (int i = 0; i < rows; i++) {
            cout << i << " ";
            for (int j = 0; j < cols; j++) {
                // ensure that the grid only contains the shots, no ships!
                if (grid[i][j] != 'X' && grid[i][j] != 'o' && grid[i][j] != '.')
                    cout << '.';
                else
                    cout << grid[i][j];
            }
            cout << endl;
        }
    }

}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    // first check to see if the point is on the board...
    if (!m_game.isValid(p))
        return false;
    // if this point has been previously attacked, return false
    if (grid[p.r][p.c] == 'X' || grid[p.r][p.c] == 'o')
        return false;
    // if we hit a ship, then our board must show so...
    if (grid[p.r][p.c] != '.') {
        shotHit = true;
        char holder = grid[p.r][p.c];
        grid[p.r][p.c] = 'X';
        // check to see if this completely destroyed the ship...
        int nothing = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // if the ship wasn't completely destroyed, then set shipDestroyed to false
                if (grid[i][j] == holder) {
                    shipDestroyed = false;
                    nothing++;
                }
            }
        }
        // if ship was completely destroyed, then set shipDestroyed to true
        if (nothing == 0) {
            shipDestroyed = true;
            //figure out which id matches the the ship symbol, and set shipId
            for (int j = 0; j <= m_game.nShips(); j++) {
                if (m_game.shipSymbol(j) == holder) {
                    shipId = j;
                    break;
                }

            }
        }

    }
    // the shot misses
    else {
        shotHit = false;
        grid[p.r][p.c] = 'o';
    }
    // was a valid shot
    return true; 

}

bool BoardImpl::allShipsDestroyed() const
{
    // loop through every spot to check if any ship symbols stil exist
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != 'X' && grid[i][j] != 'o' && grid[i][j] != '.')
                return false;
        }
    }
    // if not, return true because all the ships were sunk
    return true;

}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
