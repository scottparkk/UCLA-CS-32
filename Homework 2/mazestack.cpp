#include <stack>
#include <iostream>


using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};



bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    stack<Coord> s1;
    s1.push(Coord(sr, sc)); //push starting position onto stack.
    maze[sr][sc] = 'd'; // marking origin position as discovered

    while (s1.empty() == false) {
        Coord theTop = s1.top();
        //cout << theTop.r() <<','<< theTop.c() << endl;
        s1.pop();
        if (theTop.r() == er && theTop.c() == ec)
            return true; //found end
        //if (maze[theTop.r()][theTop.c() - 1] != 'd' && maze[theTop.r()][theTop.c() - 1] != 'X') {
        if (maze[theTop.r()][theTop.c() -1] == '.'){
            s1.push(Coord(theTop.r(), theTop.c() - 1));
            maze[theTop.r()][theTop.c() - 1] = 'd';
        }
        //if (maze[theTop.r() - 1][theTop.c()] != 'd' && maze[theTop.r() - 1][theTop.c()] != 'X') {
        if (maze[theTop.r()-1][theTop.c()] == '.') {
            s1.push(Coord(theTop.r() - 1, theTop.c()));
            maze[theTop.r() - 1][theTop.c()] = 'd';
        }
        //if (maze[theTop.r()][theTop.c() + 1] != 'd' && maze[theTop.r()][theTop.c() + 1] != 'X') {
        if (maze[theTop.r()][theTop.c() + 1] == '.') {
            s1.push(Coord(theTop.r(), theTop.c() + 1));
            maze[theTop.r()][theTop.c() + 1] = 'd';
        }
        //if (maze[theTop.r() + 1][theTop.c()] != 'd' && maze[theTop.r() + 1][theTop.c()] != 'X') {
        if (maze[theTop.r()+ 1][theTop.c() ] == '.') {
            s1.push(Coord(theTop.r() + 1, theTop.c()));
            maze[theTop.r() + 1][theTop.c()] = 'd';
        }
    } 
    return false;
}

//int main()
//{
//   char maze[10][10] = {
//        { 'X','X','X','X','X','X','X','X','X','X' },
//        { 'X','.','X','.','.','.','X','.','.','X' },
//        { 'X','.','X','.','X','X','X','X','.','X' },
//        { 'X','.','X','.','.','X','.','X','.','X' },
//        { 'X','.','X','X','.','X','.','.','.','X' },
//        { 'X','.','.','.','.','.','.','X','X','X' },
//        { 'X','.','X','X','X','X','.','X','.','X' },
//        { 'X','.','.','.','.','X','X','X','.','X' },
//        { 'X','.','X','.','.','X','.','.','.','X' },
//        { 'X','X','X','X','X','X','X','X','X','X' }
//    };
//
//    if (pathExists(maze, 5, 6, 8, 1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}