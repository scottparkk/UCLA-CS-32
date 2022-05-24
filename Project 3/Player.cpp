#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
//#include <chrono>

//class Timer
//{
//public:
//    Timer()
//    {
//        start();
//    }
//    void start()
//    {
//        m_time = std::chrono::high_resolution_clock::now();
//    }
//    double elapsed() const
//    {
//        std::chrono::duration<double, std::milli> diff =
//            std::chrono::high_resolution_clock::now() - m_time;
//        return diff.count();
//    }
//private:
//    std::chrono::high_resolution_clock::time_point m_time;
//};
//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
  public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                                bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
  private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
 : Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
      // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if (!b.placeShip(Point(k, 0), k, HORIZONTAL)) {
            //cerr << "board place ship is faulty..." << endl;
            return false;
        }
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
      // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
      // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string nm, const Game& g): Player(nm,g){}
    virtual ~HumanPlayer() {}
    virtual bool isHuman() const { return true; } // isHuman of HumanPlayer should override Players' isHuman
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
};

bool HumanPlayer::placeShips(Board& b) {

    //for however many ships there are...
    for (int k = 0; k < game().nShips(); k++) { 
        b.display(false);
        int validPoint;
        char ch;
        //must loop until either h or v is specified
        do {
            cout << "Enter h or v for direction of " << game().shipName(k) << " (length " << game().shipLength(k) << "): ";
            //cin >> ch;
            cin.get(ch);
            cin.clear();
            cin.ignore(10000, '\n');
            //if a char other than h or v is given...
            if (ch != 'v' && ch != 'h') {
                cout << "Direction must be h or v."<< endl;
                validPoint = 1;
            }
            else
                validPoint = 0;   
        } while (validPoint == 1);
        // if human is placing the ship vertically...
        if (ch == 'v') {
            Direction dir = VERTICAL;
            int r, c;
            //store the received point in a variable called place
            Point place;
            //place.r = r;
            //place.c = c;
           
            bool possiblePlace = true;
            int temp = 0;
            do {
                //get input of where to place ship, and ensure it is valid!!
                cout << "Enter row and column of topmost cell (e.g., 3 5): ";
                bool integer = getLineWithTwoIntegers(r, c);
                place.r = r;
                place.c = c;
                //must be in board bounds
                if (r > game().rows() - 1|| c > game().cols() - 1 || r < 0|| c < 0) {
                    cout << "The ship can not be placed there." << endl;
                    temp = 1;
                    
                }
                // ensure two integers are entered
                else if (!integer) {
                    cout << "You must enter two integers." << endl;
                    temp = 1;
                }
                else
                    temp = 0;
                // call the board placeShip function to place the ship on it's board, if it can be placed that is
                if (temp == 0) {
                    if (!b.placeShip(place, k, dir)) {
                        cout << "The ship can not be placed there." << endl;
                        possiblePlace = false;
                    }
                    else
                        possiblePlace = true;
                }
              

            } while (temp == 1 || possiblePlace == false);


        }
        // if human is placing the ship horizontally...
        else if (ch == 'h') {
            Direction dir = HORIZONTAL;
            int r, c;
            //store the received point in a variable called place
            Point place;
            //place.r = r;
            //place.c = c;
            
            bool possiblePlace = true;
            int temp = 0;
            do {
                //get input of where to place ship, and ensure it is valid!!
                cout << "Enter row and column of leftmost cell (e.g., 3 5): ";
                bool integer = getLineWithTwoIntegers(r, c);
                place.r = r;
                place.c = c;
                //must be in board bounds
                if (r > game().rows() - 1 || c > game().cols() - 1 || r < 0 || c < 0) {
                    cout << "The ship can not be placed there." << endl;
                    temp = 1;
                }
                // ensure 2 integers are entered
                else if (!integer) {
                    cout << "You must enter two integers." << endl;
                    temp = 1;
                }
                else
                    temp = 0;
                // call the board placeShip function to place the ship on it's board, if it can be placed that it
                if (temp == 0) {
                    if (!b.placeShip(place, k, dir)) {
                        cout << "The ship can not be placed there." << endl;
                        possiblePlace = false;
                    }
                    else
                        possiblePlace = true;
                }
                

            } while (temp == 1 || possiblePlace == false);
     
        }
    }
    return true;
}
Point HumanPlayer::recommendAttack() {
    int r, c;
    int temp = 0;
    // keep looping until a two integers are entered for an attack
    do {
        cout << "Enter the row and column to attack (e.g., 3 5): ";
        bool integer = getLineWithTwoIntegers(r, c);
        if (!integer) {
            cout << "You must enter two integers." << endl;
            temp = 1;
        }
        else {
            temp = 0;
        }
    } while (temp == 1);
    //return the point which is input by human
    return Point(r, c);
}

void HumanPlayer::recordAttackResult(Point , bool , bool , bool , int ){}
void HumanPlayer::recordAttackByOpponent(Point ){}
//typedef AwfulPlayer HumanPlayer;

//*********************************************************************
//  MediocrePlayer
//*********************************************************************

class MediocrePlayer : public Player {
public:
    MediocrePlayer(std::string nm, const Game& g) : Player(nm, g), state(false) {}
    virtual ~MediocrePlayer() {}
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    bool mHelper(Board& b, int shipId);
private:
    vector <Point> attacksMade;
    vector <Point> possibleShots;//cross
    bool state; // true is state 2

};






//recursive helper function
bool MediocrePlayer::mHelper(Board& b, int shipId) {
    //int r = game().rows();
    int c = game().cols();
    int allShips = game().nShips();
    int allSpots = (game().rows() * game().cols());
    //loop through every spot on the board
    for (int i = 0; i < allSpots; i++) {
        Point p;
        p.r = i / c;
        p.c = (i - (p.r * c));
        //cerr << p.r << "    " << p.c << endl;
        bool succesfulPlacementH = b.placeShip(p, shipId, HORIZONTAL);  
        // if the ship was placed succesfully horizontally..
        if (succesfulPlacementH) {
            //if all the ships were placed succesfully, then we can return true ( base case )
            if (shipId + 1 == allShips) {
                //cerr << "true" << endl;
                return true;
            }
            // if we aren't on the last ship placement, then RECURSIVELY call mHelper again of the next ship
            bool first = mHelper(b, shipId + 1);
            // if the recursive call returned false, then we must unplace the previous ship and try again
            if (!first) {
                //    cerr <<"ship " << shipId << " unplaced Horizontal" << endl;
                b.unplaceShip(p, shipId, HORIZONTAL);
            }
            else {
                return true;
            }

        }
        // if the ship was placed succesfully vertically...
        bool succesfulPlacementV = b.placeShip(p, shipId, VERTICAL);
        if (succesfulPlacementV) {
            //cerr << "ship " << shipId << " placed vertically" << endl;
            // if we placed every ship, then return true
            if (shipId + 1 == allShips)
                return true;
            // if we haven't placed our last ship, recursively call mHelper 
            bool second = mHelper(b, shipId + 1);
            // if the recursive call returned false, we must unplave our last ship
            if (!second) {
                //cerr <<"ship " << shipId <<  " unplace vertical" << endl;
                b.unplaceShip(p, shipId, VERTICAL);
            }
            else {
                return true;
            }
        }
    }
    //cerr <<"ship " << shipId << " cannot be placed in this configuration, retry" << endl;
    //ships cannot be placed in this blocked board
    return false;

}

bool MediocrePlayer::placeShips(Board& b) {
    // attempts to place ships 50 times with new blocked spaced every try
    for (int fiftyTimes = 0; fiftyTimes < 50; fiftyTimes++) {
        //first begin by blocking half the spots on the board...
        b.block();
        if (mHelper(b, 0)) {
            b.unblock();
            //cerr << "true in placeShips" << endl;
            return true;
        }
        b.unblock();
    }
    return false; 
}
Point MediocrePlayer::recommendAttack()
{

    int r = game().rows();
    int c = game().cols();
    Point p;
    //when in state 1...
    if (!state) {
        // make sure this point hasn't been attacked before...
        bool beenAttacked = false;
        do {
            beenAttacked = false;
            // generates a random point
            p.r = randInt(r);
            p.c = randInt(c);
            int counter = 0;
            for (int i = 0; i < attacksMade.size(); i++) {
                if (p.r != attacksMade[i].r || p.c != attacksMade[i].c)
                    counter++;
            }
            if(counter != attacksMade.size())
                beenAttacked = true;
        } while (beenAttacked);
        // return if unattacked
        return p;
    }
    //when in state 2...
    else {
        //cerr << "possible shot size is " << possibleShots.size() << endl;
        // pick a random point from possibleShots to return
        int random = randInt(possibleShots.size());
        p = possibleShots[random];
        //erase that point from possibleShots
        possibleShots.erase(possibleShots.begin() + random );
        return p;
    }

}
void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int )
{
    int r = game().rows();
    int c = game().cols();
    //shouldn't ever be invalid shot but...
    if (validShot) {
        //add that this point was attacked
        attacksMade.push_back(p);
        //if we are in state 1
        if (!state) {
            if (shotHit) {
                //count++;
                if (shipDestroyed) { // if ship is destroyed, then state stays 1
                    state = false;
                    possibleShots.clear();
                }
                else {
                    // when we hit a ship that doesn't get destroyed, move to state 2
                    Point q(p.r, p.c);
                    Point original(p.r, p.c);
                    // add up to 4 points north of the point hit to possibleShots, only if unattacked and on the board!
                    for (int n = 1; n < 5; n++) {
                        if (p.r - n >= 0) {
                            q.r = p.r - n;
                            int counter = 0;
                            for (int i = 0; i < attacksMade.size(); i++) {
                                if (q.r != attacksMade[i].r || q.c != attacksMade[i].c) {
                                    counter++;
                                    
                                }
                            }
                            if( counter == attacksMade.size())
                                possibleShots.push_back(q);
                        }
                        
                    }
                    q.r = p.r;
                    q.c = p.c;
                    // add up to 4 points east of the point hit to possibleShots, only if unattacked and on the board!
                    for (int e = 1; e < 5; e++) {
                        if (p.c + e < c ) {

                            q.c = p.c + e;
                            int counter = 0;
                            for (int i = 0; i < attacksMade.size(); i++) {
                                if (q.r != attacksMade[i].r || q.c != attacksMade[i].c) {
                                    counter++;
                                }
                            }
                            if (counter == attacksMade.size())
                                possibleShots.push_back(q);

                        }
                        
                    }
                    q.r = p.r;
                    q.c = p.c;
                    // add up to 4 points south of the point hit to possibleShots, only if unattacked and on the board!
                    for (int s = 1; s < 5; s++) {
                        if (p.r + s < r) {
                           
                            q.r = p.r + s;
                            int counter = 0;
                            for (int i = 0; i < attacksMade.size(); i++) {
                                if (q.r != attacksMade[i].r || q.c != attacksMade[i].c) {
                                    counter++;
                                }
                            }
                            if (counter == attacksMade.size())
                                possibleShots.push_back(q);
                        }
                        
                    }
                    q.r = p.r;
                    q.c = p.c;
                    // add up to 4 points west of the point hit to possibleShots, only if unattacked and on the board!
                    for (int w = 1; w < 5; w++) {
                        if (p.c - w >= 0) {     
                            q.c = p.c - w;
                            int counter = 0;
                            for (int i = 0; i < attacksMade.size(); i++) {
                                if (q.r != attacksMade[i].r || q.c != attacksMade[i].c) {
                                    counter++;
                                }
                            }
                            if (counter == attacksMade.size())
                                possibleShots.push_back(q);
                        }
                        

                    }
                    // move to state 2!
                    state = true;
                    //cerr << "possibleShots size " << possibleShots.size() << endl << "the container is ...";
                    //for (int l = 0; l < possibleShots.size(); l++)
                    //    cerr << "(" << possibleShots[l].r << "," << possibleShots[l].c << ") ";
                    //cerr << endl;
                }
            }
           
        }
        // if already in state 2...
        if (state) {
            // if we already checked whole cross, then reset count and revert to state 1
            //if (count > possibleShots.size()) {
            if(possibleShots.size() == 0){
                //cerr << "count is " << count;
                //cerr << "reset cross" << endl;
                state = false;
                possibleShots.clear();
            }
            if (shotHit) {
                if (shipDestroyed) { // if ship is destroyed, then state goes back to 1
                    state = false;
                    possibleShots.clear();
                }
                else {
                    // when the ship isn't destroyed, state stays in 2
                    state = true;
                }
            }
            
        }
    }
    else {
        //cerr << endl << "problem problem problem" << endl;
    }
}
void MediocrePlayer::recordAttackByOpponent(Point ) {}

//*********************************************************************
//  GoodPlayer
//*********************************************************************

class GoodPlayer : public Player {
public:
    GoodPlayer(std::string nm, const Game& g) : Player(nm, g), state(1), count(0), center(0,0), rr(0), cc(1) {}
    virtual ~GoodPlayer() {}
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    bool pHelper(Board& n, int shipId);
    void addSurrounding(Point p);
private:
    vector <Point> attacksMade;
    vector <Point> possibleShots;
    int state;
    int count; 
    Point center;
    int rr, cc;
    
};

//given a Point p, add the surround points (if not already hit or an edge) to the possiblePoints
void GoodPlayer::addSurrounding(Point p) {
    //Northern ( check if spot above is valid )
    if (p.r - 1 != -1) {
        Point n(p.r - 1, p.c);
        int counter = 0;
        // ensure that the point is unattacked
        for (int i = 0; i < attacksMade.size(); i++) {
            if (n.r != attacksMade[i].r || n.c != attacksMade[i].c) {
                counter++;
            }
        }
        // ensure that we havent added it to possibleShots yet
        if (counter == attacksMade.size()) {
            bool check = true;
            for (int j = 0; j < possibleShots.size(); j++) {
                if (n.r == possibleShots[j].r && n.c == possibleShots[j].c)
                    check = false;
            }
            if(check)
                possibleShots.push_back(n);
        }
    }
    //Eastern( check if point to the right is valid)
    if (p.c + 1 < game().cols()) {
        Point e(p.r , p.c + 1);
        int counter = 0;
        // ensure that the point is unattacked
        for (int i = 0; i < attacksMade.size(); i++) {
            if (e.r != attacksMade[i].r || e.c != attacksMade[i].c) {
                counter++;
            }
        }
        // ensure that we havent added it to possibleShots yet
        if (counter == attacksMade.size()) {
            bool check = true;
            for (int j = 0; j < possibleShots.size(); j++) {
                if (e.r == possibleShots[j].r && e.c == possibleShots[j].c)
                    check = false;
            }
            if (check)
                possibleShots.push_back(e);
        }
    }
    //Southern( check if point below is valid )
    if (p.r + 1 < game().rows()) {
        Point s(p.r + 1, p.c);
        int counter = 0;
        // ensure that the point is unattacked
        for (int i = 0; i < attacksMade.size(); i++) {
            if (s.r != attacksMade[i].r || s.c != attacksMade[i].c) {
                counter++;
            }
        }
        // ensure that we havent added it to possibleShots yet
        if (counter == attacksMade.size()) {
            bool check = true;
            for (int j = 0; j < possibleShots.size(); j++) {
                if (s.r == possibleShots[j].r && s.c == possibleShots[j].c)
                    check = false;
            }
            if (check)
                possibleShots.push_back(s);
        }
    }
    //Western ( check if point to left is valid )
    if (p.c - 1 != -1) {
        Point w(p.r, p.c - 1);
        int counter = 0;
        // ensure that the point is unattacked
        for (int i = 0; i < attacksMade.size(); i++) {
            if (w.r != attacksMade[i].r || w.c != attacksMade[i].c) {
                counter++;
            }
        }
        // ensure that we havent added it to possibleShots yet
        if (counter == attacksMade.size()) {
            bool check = true;
            for (int j = 0; j < possibleShots.size(); j++) {
                if (w.r == possibleShots[j].r && w.c == possibleShots[j].c)
                    check = false;
            }
            if (check)
                possibleShots.push_back(w);
        }
    }
}


// THE SAME AS mHelper for MEDIOCRE
bool GoodPlayer::pHelper(Board& b, int shipId) {
    //int r = game().rows();
    int c = game().cols();
    int allShips = game().nShips();

    int allSpots = (game().rows() * game().cols());
    //loop through every spot
    for (int i = 0; i < allSpots; i++) {
        Point p;
        p.r = i / c;
        p.c = (i - (p.r * c));
        //cerr << p.r << "    " << p.c << endl;
        // if we succesfully placed the ship
        bool succesfulPlacementH = b.placeShip(p, shipId, HORIZONTAL);
        if (succesfulPlacementH) {
            //cerr << "ship " << shipId << " placed horizontal" << endl;
            if (shipId + 1 == allShips) {
                //cerr << "true" << endl;
                return true;
            }
            bool first = pHelper(b, shipId + 1);
            // we must unplace the ship
            if (!first) {
                //    cerr <<"ship " << shipId << " unplaced Horizontal" << endl;
                b.unplaceShip(p, shipId, HORIZONTAL);
            }
            else {
                return true;
            }

        }
        // if we succesfully placed the ship vertically...
        bool succesfulPlacementV = b.placeShip(p, shipId, VERTICAL);
        if (succesfulPlacementV) {
            //cerr << "ship " << shipId << " placed vertically" << endl;
            if (shipId + 1 == allShips)
                return true;
            bool second = pHelper(b, shipId + 1);
            // we must unplace the ship
            if (!second) {
                //cerr <<"ship " << shipId <<  " unplace vertical" << endl;
                b.unplaceShip(p, shipId, VERTICAL);
            }
            else {
                return true;
            }
        }
    }
    //cerr <<"ship " << shipId << " cannot be placed in this configuration, retry" << endl;
    return false;

}


bool GoodPlayer::placeShips(Board& b){
    // when its a 10x10 board...
    if (game().rows() == 10 && game().cols() == 10) {
        //check to see if only the standard ships are used, and if so then place the ships...
        if (game().nShips() == 5) {
            bool three = false;
            int count = 0;
            Point ee(5, 4);
            Point dd(2, 2);
            Point cc(8, 1);
            Point bb(8, 6);
            Point aa(1, 4);
            for (int i = 0; i < 5; i++) { 
                //place the ship of length 5 at 1,4
                if (game().shipLength(i) == 5) {
                    b.placeShip(aa, i, HORIZONTAL);
                    count++;
                }
                //place the ship of length 4
                else if (game().shipLength(i) == 4) {
                    b.placeShip(bb, i, HORIZONTAL);
                    count++;

                }
                //place the ship of length 2
                else if (game().shipLength(i) == 2) {
                    b.placeShip(cc, i, VERTICAL);
                    count++;
                }
                //place the ship of length 3
                else if (game().shipLength(i) == 3 && three == false) {
                    b.placeShip(dd, i, VERTICAL);
                    three = true;
                    count++;
                }
                //place the ship of length 3
                else if (game().shipLength(i) == 3 && three == true) {
                    b.placeShip(ee, i, VERTICAL);
                    count++;
                }

            }
            // if not every ship was placed, then game isn't standard...
            if (count == 5) {
                return true;
            }
            else if (count != 5) {
                //unplace every ship!!!!
                for (int j = 0; j < 5; j++) {
                    b.unplaceShip(aa, j, HORIZONTAL);
                }
                for (int k = 0; k < 5; k++) {
                    b.unplaceShip(bb, k, HORIZONTAL);
                }
                for (int s = 0; s < 5; s++) {
                    b.unplaceShip(cc, s, VERTICAL);
                }
                for (int w = 0; w < 5; w++) {
                    b.unplaceShip(dd, w, VERTICAL);
                }
                for (int h = 0; h < 5; h++) {
                    b.unplaceShip(ee, h, VERTICAL);
                }
                
            }

        }
        
    }
    // run the recursive placement  ( same as mediocre )
    for (int fiftyTimes = 0; fiftyTimes < 50; fiftyTimes++) {
        //first begin by blocking half the spots on the board...
        b.block();
        if (pHelper(b, 0)) {
            b.unblock();
            //cerr << "true in placeShips" << endl;
            return true;
        }
        b.unblock();
    }
    return false;

}



Point GoodPlayer::recommendAttack()
{
    /*Timer t;
    t.start();*/
    Point p;
    //when in state 1...
    //cerr << " the state "<< state << endl;
    if (state == 1 ) {
        // make sure this point hasn't been attacked before...
        bool beenAttacked = false;

        do {
            beenAttacked = false;
            p.r = rr;
            p.c =cc;
            int counter = 0;

            //checks if the point has been attacked
            for (int i = 0; i < attacksMade.size(); i++) {
                if (p.r != attacksMade[i].r || p.c != attacksMade[i].c)
                    counter++;
            }
            if (counter != attacksMade.size())
                beenAttacked = true;

            // when we reach an end column, set column to 1 or 0, and move to the next row
            if (cc == 9 ) {
                rr++;
                cerr << "rr is " << rr << endl;
                cc = 0;
            }
            else if (cc == 8 ) {
                cc = 1;
                rr++;
            }
            else
                cc = cc + 2;
        } while (beenAttacked);
       /* if (t.elapsed() > 3900) {
            cerr << t.elapsed() << "<---- TIME ELAPSED FOR RECOMEND" << endl;
        }*/
        return p;
    }
    //when in state 2...
    else {
        //returns the most recently added point from possibleShots
        p.r = possibleShots[possibleShots.size() - 1].r;
        p.c = possibleShots[possibleShots.size() -1].c;
        possibleShots.pop_back();
       /* if(t.elapsed() >3900)
            cerr << t.elapsed() << "<---- TIME ELAPSED FOR RECOMEND" << endl;*/
        return p;
    }

}
void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool , int ){
    
    //shouldn't ever be invalid shot so....
    if (validShot) {
        //add that this point was attacked
        attacksMade.push_back(p);
        //if we are not in state 2 yet...
        if (state == 1) {
            // if we hit something
            if (shotHit) {
                //add surrounding points to possibleShots
                addSurrounding(p);
                //move to state 2
                state = 2;
            }
        }
        // in state 2
        else {
            // if we hit something,then add surrounding points to possibleShots
            if (shotHit)
                addSurrounding(p);
            // if we run out of possibleShots, return to state 1
            if (possibleShots.size() == 0)
                state = 1;
        }
    }
}




void GoodPlayer::recordAttackByOpponent(Point ){
}

//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };
    
    int pos;
    for (pos = 0; pos != sizeof(types)/sizeof(types[0])  &&
                                                     type != types[pos]; pos++)
        ;
    switch (pos)
    {
      case 0:  return new HumanPlayer(nm, g);
      case 1:  return new AwfulPlayer(nm, g);
      case 2:  return new MediocrePlayer(nm, g);
      case 3:  return new GoodPlayer(nm, g);
      default: return nullptr;
    }
}
