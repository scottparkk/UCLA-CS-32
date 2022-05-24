#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

#include <algorithm>
#include <vector>

using namespace std;

class Ship { // ship class
public:
    Ship( int l, char s, string n, int id);
    int theShipLength();
    char theShipSymbol();
    string theShipName();
private: // ship private data members to store the ships length, symbol, name, and id
    int m_length;
    char m_symbol;
    string m_name;
    int m_id;
};

class GameImpl
{
  public:
    GameImpl(int nRows, int nCols);
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    ~GameImpl();
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);

 private:
     int m_rows;
     int m_columns;
     int m_ships ;
     vector <Ship*> allships;
     
};

//destructor for gameimpl
GameImpl::~GameImpl() {
    Ship* temp;
    while (!allships.empty()) {
        temp = allships.back();
        allships.pop_back();
        delete temp;
    }
}
//ship constructor
Ship::Ship( int l, char s, string n, int id) 
    :  m_length(l), m_symbol(s), m_name(n), m_id(id){} 

//returns the ship length
int Ship::theShipLength() {
    return m_length;
}

//returns the ship symbol
char Ship::theShipSymbol() {
    return m_symbol;
}

// returns the ship name
string Ship::theShipName() {
    return m_name;
}

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

// create a new game, setting the m_rows and m_column variables based on given dimension
GameImpl::GameImpl(int nRows, int nCols): 
    m_rows(nRows), m_columns(nCols), m_ships(0)
{}

//return the number of rows in a game
int GameImpl::rows() const
{
    return m_rows;  
}

//returns column dimension of a game
int GameImpl::cols() const
{
    return m_columns; 
}

//true if point is within the dimension, and false if not
bool GameImpl::isValid(Point p) const
{
    return p.r >= 0  &&  p.r < rows()  &&  p.c >= 0  &&  p.c < cols();
}

//returns a random point within your game
Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

//add a new ship to the game
bool GameImpl::addShip(int length, char symbol, string name)
{
    //dynamically allocate a new ship
    allships.push_back(new Ship( length, symbol, name, m_ships));
    //increment m_ship by 1 ( holds number of ships in a game )
    m_ships++;
    //ship was succesfully added
    return true;  
}

//returns amount of ships in a game
int GameImpl::nShips() const
{
    return m_ships;  
}

//given a shipId, return the length of that ship
int GameImpl::shipLength(int shipId) const
{
    return allships[shipId]->theShipLength();  
}

//given a shipId, return the symbol of that ship
char GameImpl::shipSymbol(int shipId) const
{
    return allships[shipId]->theShipSymbol();
}

//given a shipId, return the name of that ship
string GameImpl::shipName(int shipId) const
{
    return allships[shipId]->theShipName();
}

Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)
{
    bool p1human = p1->isHuman();
    bool p2human = p2->isHuman();
    bool shotHit1, shotHit2;
    bool shipDestroyed1, shipDestroyed2;
    int shipId1, shipId2;
    bool validShot1, validShot2;
    //place player 1's ships on their board, unless not possible, to which we return nullptr
    if (p1->placeShips(b1) == false) {
        return nullptr;
    }
    //place player 2's ships on their board, unless not possible, to which we return nullptr
    if (p2->placeShips(b2) == false) {
        return nullptr;
    }
    //until one of the players wins the game...
    do {
        cout << p1->name() << "'s turn.  Board for " << p2->name() << ':' << endl;
        //when p1 is a human, display shots only
        if (p1human) {
            b2.display(true);
            //have p1 attack p2's board...
            Point p1Attack = p1->recommendAttack();
            bool holder1 = b2.attack(p1Attack, shotHit2, shipDestroyed2, shipId2);
            
            //output message based on the result of the attack...
            // player wastes a shot ( out of bounds or previously hit)
            if (!holder1) {
                validShot2 = false;
                cout << p1->name() << " wasted a shot at (" << p1Attack.r << ',' << p1Attack.c << ")." << endl;
            }
            // player makes a valid shot
            else {
                validShot2 = true;
                p2->recordAttackByOpponent(p1Attack);
                cout << p1->name() << " attacked (" << p1Attack.r << ',' << p1Attack.c << ") and ";
                // we hit a ship
                if (shotHit2 == true) {
                    // and that hit destroys the ship
                    if (shipDestroyed2 == true) {
                        cout << "destroyed the " << shipName(shipId2) << ", resulting in:" << endl;
                    }
                    // and that hit doesn't destroy it
                    else
                        cout << "hit something, resulting in:" << endl;
                }
                //we miss a ship
                else {
                    if (isValid(p1Attack)) 
                        cout << "missed, resulting in:" << endl;
                }
            }
            // record the result of the attack
            p1->recordAttackResult(p1Attack, validShot2, shotHit2, shipDestroyed2, shipId2);
            // display result of the attack, unles wasted
            if(holder1)
                b2.display(true);
            if (b2.allShipsDestroyed() == true)
                break;
            //pause game if parameter says so
            if (shouldPause == true)
                waitForEnter();
        }
        // when p1 isnt human, we can display everything
        if (!p1human) {
            b2.display(false);
            //have p1 attack p2's board
            Point p1Attack = p1->recommendAttack();
            bool holder1 = b2.attack(p1Attack, shotHit2, shipDestroyed2, shipId2);
            // player wastes a shot out of bounds or by making a shot it made earlier
            if (!holder1) {
                validShot2 = false;
                cout << p1->name() << " wasted a shot at (" << p1Attack.r << ',' << p1Attack.c << ")." << endl;
            }
            // player makes a valid shot
            else {
                validShot2 = true;
                p2->recordAttackByOpponent(p1Attack);
                cout << p1->name() << " attacked (" << p1Attack.r << ',' << p1Attack.c << ") and ";
                // the player hits a ship
                if (shotHit2 == true) {
                    //destorying it
                    if (shipDestroyed2 == true) {
                        cout << "destroyed the " << shipName(shipId2) << ", resulting in:" << endl;
                    }
                    // but doesn't destroy it
                    else
                        cout << "hit something, resulting in:" << endl;
                }
                // the player misses their shot
                else {
                    if (isValid(p1Attack)) 
                        cout << "missed, resulting in:" << endl;
                }
            }
            // record the result of the attack
            p1->recordAttackResult(p1Attack, validShot2, shotHit2, shipDestroyed2, shipId2);
            //display board after attack, unless wasted
            if(holder1)
                b2.display(false);
            //if p1 destroyed all of p2's ships, then break out of loop
            if (b2.allShipsDestroyed() == true)
                break;
            // pause game if parameter says so
            if (shouldPause == true)
                waitForEnter();
        }
        
        if (b2.allShipsDestroyed() == true)
            break;

        cout << p2->name() << "'s turn.  Board for " << p1->name() << ':' << endl;
        //when p2 is a human, we only want to display the shot's of p1's board
        if (p2human) {
            b1.display(true);
            //have p2 attack p1
            Point p2Attack = p2->recommendAttack();
            bool holder2 = b1.attack(p2Attack, shotHit1, shipDestroyed1, shipId1);
            //output the resulting message based on the attack
            // shot is wasted if made off the boardor was a previously made shot
            if (!holder2) {
                validShot1 = false;
                cout << p2->name() << " wasted a shot at (" << p2Attack.r << ',' << p2Attack.c << ")." << endl;
            }
            //shot is valid
            else{
                validShot1 = true;
                p1->recordAttackByOpponent(p2Attack);
                cout << p2->name() << " attacked (" << p2Attack.r << ',' << p2Attack.c << ") and ";
                // shot hits a ship
                if (shotHit1 == true) {
                    //destroying it
                    if (shipDestroyed1 == true) {
                        cout << "destroyed the " << shipName(shipId1) << ", resulting in:" << endl;
                    }
                    // but doesn't destroy it
                    else
                        cout << "hit something, resulting in:" << endl;
                }
                else {
                    if (isValid(p2Attack)) 
                        cout << "missed, resulting in:" << endl;
                }
            }
            p2->recordAttackResult(p2Attack, validShot1, shotHit1, shipDestroyed1, shipId1);
            // display the board after p2 attacked p1, unless shot wasted
            if(holder2)
                b1.display(true);
            // if all the ships of p1 were sunk, then break out of loop
            if (b1.allShipsDestroyed() == true)
                break;
            // pause the game if the parameter says so
            if (shouldPause == true)
                waitForEnter();
        }
        
        // when p2 isn't human, we can display everything of p1's board
        if (!p2human) {
            b1.display(false);
            // have p2 attack p1's board
            Point p2Attack = p2->recommendAttack();
            bool holder2 = b1.attack(p2Attack, shotHit1, shipDestroyed1, shipId1);
            // output the message based on the result of the attack
            // shot is wasted if off the board or if repeated
            if (!holder2) {
                validShot1 = false;
                cout << p2->name() << " wasted a shot at (" << p2Attack.r << ',' << p2Attack.c << ")." << endl;
            }
            // shot is valid
            else {
                validShot1 = true;
                p1->recordAttackByOpponent(p2Attack);
                cout << p2->name() << " attacked (" << p2Attack.r << ',' << p2Attack.c << ") and ";
                // shot hit a ship
                if (shotHit1 == true) {
                    // destroying it
                    if (shipDestroyed1 == true) {
                        cout << "destroyed the " << shipName(shipId1) << ", resulting in:" << endl;
                    }
                    // but doesn;t sink it
                    else
                        cout << "hit something, resulting in:" << endl;
                }
                // shot misses a ship
                else {
                    if (isValid(p2Attack)) 
                        cout << "missed, resulting in:" << endl;
                }
            }
            p2->recordAttackResult(p2Attack, validShot1, shotHit1, shipDestroyed1, shipId1);
            // display p1's board after it was attacked
            if (holder2) {
                b1.display(false);
            }
            if (b1.allShipsDestroyed() == true)
                break;
            //pause if the parameter specifys a game w/ pauses
            if (shouldPause == true)
                waitForEnter();
        }
        
    } while (b1.allShipsDestroyed() != true && b2.allShipsDestroyed() != true);
    // if all of p1's ships were destroyed, then p2 wins!
    if (b1.allShipsDestroyed() == true) {
        cout << p2->name() << " wins!" << endl;
        // display the board of the winner if loser is human
        if (p1human) {
            cout << "Here is where " << p2->name() << " ships were:" << endl;
            b2.display(false);
        }
        //return player that won
        return p2;
    }
    // if all of p2's ships were destroyed, then p1 wins!
    else if (b2.allShipsDestroyed() == true) {
        cout << p1->name() << " wins!" << endl;
        //display the board of the winner if the loser is human
        if (p2human) {
            cout << "Here is where " << p1->name() << " ships were:" << endl;
            b1.display(false);
        }
        //return player that won
        return p1;
    }

    return nullptr;
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1  ||  nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1  ||  nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows()  &&  length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
             << endl;
        return false;
    }
    if (!isascii(symbol)  ||  !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
             << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X'  ||  symbol == '.'  ||  symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
             << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                 << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause)
{
    if (p1 == nullptr  ||  p2 == nullptr  ||  nShips() == 0)
        return nullptr;
    Board b1(*this);
    Board b2(*this);
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}

