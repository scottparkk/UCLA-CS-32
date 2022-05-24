#ifndef GAMEINCLUDE
#define GAMEINCLUDE

class Mesa;

int decodeDirection(char dir);

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

    // Mutators
    void play();

private:
    Mesa* m_mesa;
};

#endif //GAMEINCLUDE