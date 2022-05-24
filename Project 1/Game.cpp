#include "Game.h"
#include "Mesa.h"
#include "Player.h"
#include "globals.h"
#include <string>
#include <iostream>

using namespace std;

int decodeDirection(char dir)
{
    switch (dir)
    {
    case 'u':  return UP;
    case 'd':  return DOWN;
    case 'l':  return LEFT;
    case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

Game::Game(int rows, int cols, int nGarks)
{
    if (nGarks < 0)
    {
        cout << "***** Cannot create Game with negative number of garks!" << endl;
        exit(1);
    }
    if (nGarks > MAXGARKS)
    {
        cout << "***** Trying to create Game with " << nGarks
            << " garks; only " << MAXGARKS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1 && cols == 1 && nGarks > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the garks!" << endl;
        exit(1);
    }

    // Create mesa
    m_mesa = new Mesa(rows, cols);

    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_mesa->addPlayer(rPlayer, cPlayer);

    // Populate with garks
    while (nGarks > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a gark where the player is
        if (r == rPlayer && c == cPlayer)
            continue;
        m_mesa->addGark(r, c);
        nGarks--;
    }
}

Game::~Game()
{
    delete m_mesa;
}

void Game::play()
{
    m_mesa->display();
    Player* player = m_mesa->player();
    if (player == nullptr)
        return;
    while (!player->isDead() && m_mesa->garkCount() > 0)
    {
        cout << endl;
        cout << "Move (u/d/l/r/h/q or nothing): ";
        string action;
        getline(cin, action);
        if (action[0] == 'h') {
            m_mesa->history().display();
            cout << "Press enter to continue.";
            cin.ignore(10000, '\n');
            m_mesa->display();
        }
        else {
            if (action.size() == 0)  // player stands
                player->stand();
            else
            {
                switch (action[0])
                {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                    //case 'h':
                    //    m_mesa-> history().display();
                    //    cout << "Press enter to continue." << endl;
                    //    break;
                    //    
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    player->moveOrAttack(decodeDirection(action[0]));
                    break;
                }
            }
            m_mesa->moveGarks();
            m_mesa->display();
        }
        //if (action.size() == 0)  // player stands
        //    player->stand();
        //else
        //{
        //    switch (action[0])
        //    {
        //    default:   // if bad move, nobody moves
        //        cout << '\a' << endl;  // beep
        //        continue;
        //    case 'q':
        //        return;
        //    //case 'h':
        //    //    m_mesa-> history().display();
        //    //    cout << "Press enter to continue." << endl;
        //    //    break;
        //    //    
        //    case 'u':
        //    case 'd':
        //    case 'l':
        //    case 'r':
        //        player->moveOrAttack(decodeDirection(action[0]));
        //        break;
        //    }
        //}
        //m_mesa->moveGarks();
        //m_mesa->display();
    }
}


