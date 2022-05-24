#include "Mesa.h"
#include "Gark.h"
#include "History.h"
#include "Player.h"
#include "globals.h"
#include <iostream>

using namespace std;

Mesa::Mesa(int nRows, int nCols)
    : m_rows(nRows), m_cols(nCols), m_player(nullptr), m_nGarks(0), m_history(nRows,nCols)
{
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
    {
        cout << "***** Mesa created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);
    }
}

Mesa::~Mesa()
{
    for (int k = 0; k < m_nGarks; k++)
        delete m_garks[k];
    delete m_player;
}

int Mesa::rows() const
{
    return m_rows;
}

int Mesa::cols() const
{
    return m_cols;
}

Player* Mesa::player() const
{
    return m_player;
}

int Mesa::garkCount() const
{
    return m_nGarks;
}

int Mesa::numGarksAt(int r, int c) const
{
    int count = 0;
    for (int k = 0; k < m_nGarks; k++)
    {
        const Gark* gp = m_garks[k];
        if (gp->row() == r && gp->col() == c)
            count++;
    }
    return count;
}

History &Mesa::history() {
    return m_history;
}
bool Mesa::determineNewPosition(int& r, int& c, int dir) const
{
    switch (dir)
    {
    case UP:     if (r <= 1)      return false; else r--; break;
    case DOWN:   if (r >= rows()) return false; else r++; break;
    case LEFT:   if (c <= 1)      return false; else c--; break;
    case RIGHT:  if (c >= cols()) return false; else c++; break;
    default:     return false;
    }
    return true;
}

void Mesa::display() const
{
    // Position (row,col) in mesa coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

    // Indicate each gark's position
    for (int k = 0; k < m_nGarks; k++)
    {
        const Gark* gp = m_garks[k];
        char& gridChar = grid[gp->row() - 1][gp->col() - 1];
        switch (gridChar)
        {
        case '.':  gridChar = 'G'; break;
        case 'G':  gridChar = '2'; break;
        case '9':  break;
        default:   gridChar++; break;  // '2' through '8'
        }
    }

    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set char to '@', unless there's also a gark there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row() - 1][m_player->col() - 1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    // Write message, gark, and player info
    cout << endl;
    cout << "There are " << garkCount() << " garks remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Mesa::addGark(int r, int c)
{
    // Dynamically allocate a new Gark and add it to the mesa
    if (m_nGarks == MAXGARKS)
        return false;
    m_garks[m_nGarks] = new Gark(this, r, c);
    m_nGarks++;
    return true;
}

bool Mesa::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    // Dynamically allocate a new Player and add it to the mesa
    m_player = new Player(this, r, c);
    return true;
}

bool Mesa::attackGarkAt(int r, int c, int dir)
{
    // Attack one gark.  Returns true if a gark was attacked and destroyed,
    // false otherwise (no gark there, or the attack did not destroy the
    // gark).
    int k = 0;
    for (; k < m_nGarks; k++)
    {
        if (m_garks[k]->row() == r && m_garks[k]->col() == c)
            break;
    }
    if (k < m_nGarks && m_garks[k]->getAttacked(dir))  // gark dies
    {
        delete m_garks[k];
        m_garks[k] = m_garks[m_nGarks - 1];
        m_nGarks--;
        return true;
    }
    return false;
}

bool Mesa::moveGarks()
{
    for (int k = 0; k < m_nGarks; k++)
    {
        Gark* gp = m_garks[k];
        gp->move();
        if (gp->row() == m_player->row() && gp->col() == m_player->col())
            m_player->setDead();
    }

    // return true if the player is still alive, false otherwise
    return !m_player->isDead();
}
