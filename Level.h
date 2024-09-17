

#ifndef level_hpp
#define level_hpp


#include "globals.h" 
#include <vector>
class Weapon;
class Player;
class Monsters;
class GameObject;
class Stairs;
class GoldenIdol;
class Level
{
public:
    // level generation functions
    Level(int n);
    void printLevel();
    void printPlayer(int row, int col);
    void printObjects();
    void printStairs();

    // generating rooms
    void createRooms();
    void fillRooms();
    bool isOverlapping(int newPosx, int newPosy, int newC, int newR, int roomNum);
    void createCorridors();
    
    // setting up objects/actors
    void addPlayerToLevel();
    void addMonsterToLevel();
    void addObjectsToLevel();
    void addStairsToLevel();
    void removeObjects(GameObject * g, int i);
    bool reduceNumMonstersOnBoard(int reduceBy);
    void addObjectsAfterMonstersDie(int row, int col, char monsterName);

      // move to next level 
    void movePlayerToNextLevel(Player *p, Level *l);
    bool monsterAttack(Monsters *m);
    bool playerAttack();

    //control functions
    bool isPlayerAt(int r, int c);
    bool isInBounds(int r, int c) const;
    
    //accessor functions
    void setPlayer(Player *p);
    Player* getPlayer() const;
    Stairs* getStairs();
    GoldenIdol* getGoldenIdol();
    char getMaze(int row, int col) const;
    void setMaze(int row, int col, char value);
    int getLevelNum() const;
    void eraseAMonster(int index);
    void printMonsters();

    // Destructors
    ~Level();
    
    //getters
    GameObject* getObject(int index) const;
    Monsters* getMonster(int index) const;
    int getNumberMonsters();

    int getNumObjectsOnBoard() const;
    int getNumMonstersOnBoard() const;
   

private:
    struct Room
    {
    public:
        Room();
        int getPosY() const;
        int getPosX() const;
        int getRows() const;
        int getCols() const;
        
        bool setPosY(int y);
        bool setPosX(int x);
        bool setRows(int r);
        bool setCols(int c);
        
    private:
        int m_roomRows;
        int m_roomCols;
        int m_leftTopPosX;
        int m_leftTopPosY;
    };
    
    const int m_levelRows;
    const int m_levelCols;
    int m_rooms;
    Room *rooms[12];
    char maze[LEVELROWS][LEVELCOLS];
    int m_levelNumber;
    
    
    Player *m_player; 
    Stairs *m_stairs;
   

    std::vector <GameObject*> objects;
    int m_numObjectsOnBoard = 0;

    std::vector <Monsters*> monsters;
     int m_numMonsters;

    
};

#endif /* level_hpp */
