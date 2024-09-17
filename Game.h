

// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

class Level;

class Game
{
public:
    Game(int goblinSmellDistance);
    // to play game
    void play();
    // display stats
    void displayStats();
    // move monsters
    void monstersMove();
    ~Game();
private:
    Level *l[5];
    int currLevelNum;
    int m_goblinSmellDistance;
};

#endif // GAME_INCLUDED
