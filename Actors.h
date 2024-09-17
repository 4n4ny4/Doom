
#ifndef Actors_hpp
#define Actors_hpp
#include <string>
#include <vector>
#include "globals.h"

class Weapon;
class Level;
class GameObject;

class Actor{
public:
    Actor(int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, int sleepTime, int maxHitPoints, Weapon * weapon, Level *l, std::string name);
    //position getters/move-related functions
    int getRowPos();
    int getColPos();
    void setRowPos(int newRowPos);
    void setColPos(int newColPos);
    bool isAsleep();

    //functions related to win/lose game
    bool reduceHitPoints(int reduceBy);
    void applyWeaponDamage(Weapon *otherActorWeapon, Actor *otherActor); 
    
    // getters
    int getSleepTime() const;
    int getDexterityPts() const;
    int getStrengthPts() const;
    int getArmorPts() const;
    Level *getLevel() const;
    void setLevel(Level *);
    int getHitPts();
    std::string getActorName();
    int getMaxHitPts();

    //setters - applies to players and Monsters
    bool setSleepTime(Weapon *otherWeapon);
    void reduceSleepTime();
    bool setHitPoints(int reduceHitPointsBy, Actor *a);
    Weapon *getWeapon();
    void setWeapon(Weapon*);
    
    //setters unqiue to palyers (checks if actor is a player before changing private members)
    bool setDexterityPts(int toAdd, Actor *a);
    bool setStrengthPts(int toAdd, Actor *a);
    bool enhanceHealthMaxHitPts(Actor *a);
    bool setArmorPts(int toAdd, Actor *a);
    bool cheat(Actor *a);
    void strengthPointsTo(int num);
    
    //Action-string related functions
    void setActionString(std::string);
    std::string getActionString();
    
    // increases hit points 1/10th chance
    void increaseHitPts(Actor *a);

    // destructor
    virtual ~Actor();
    

    
private:
    //position
    int m_row;
    int m_col;

    // points
    int m_hitPoints;
    int m_armorPts;
    int m_strengthPts;
    int m_dexterityPts;
    int m_sleepTime;
    int m_maxHitPts;
    
    //action string
    std::string m_action;
    std::string m_actorName;
    
    //pointers to current weapon and level
    Weapon* m_weapon;
    Level *m_level;
};


class Player: public Actor{
public:
    // constructor
    Player(Weapon * weapon, Level *l);
    
    // define pure virtual functions from Actor Class
    bool hasLost();
    
    //Inventory-related Functions
    bool addToInventory(GameObject *g);
    bool readScroll(char input);
    bool readScrollHelper(GameObject *g);
    bool pickUpGameObject(Level *l);
    bool switchWeapon(char input); 
    void displayInventory();
    void hasWon();
    int getCoordinatesForMove(char input, int r, int c, int monsterCoord[2]);
    
  
    ~Player();
    
private:
    std::vector<GameObject*> inventory;
    int m_inventorySize = 0;
};


class Monsters: public Actor
    {
    public:
    Monsters(int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, int maxHitPoints, Weapon * weapon, Level *l, std:: string name);
    virtual bool hasLost(int row, int col, Monsters* m, int index) = 0;
    // checks if player is nearby
      bool isPlayerCloseBy(int playerR, int playerC, int monsterR, int monsterC);
      // checks if can reach player in limited steps
      virtual bool canReachPlayer(int playerR, int playerC, int monsterR, int monsterC, int depth, int maxNumberOfMoves);
      virtual bool move(int playerR, int playerC, int numberOfMovesSoFar, int maxNumberOfMoves, char c, Monsters* m);
      bool isSafeToMove(int row, int col);
      ~Monsters();
    };

class Bogeyman: public Monsters{
public:
    Bogeyman(Level *l);
    bool hasLost(int row, int col, Monsters* m, int index);
};

class SnakeWoman: public Monsters{
public:
    SnakeWoman(Level *l);
    bool hasLost(int row, int col, Monsters* m, int index);
};

class Dragon: public Monsters{
public:
    Dragon(Level *l);    
    bool hasLost(int row, int col, Monsters* m, int index);
};

class Goblin: public Monsters{
public:
    Goblin(Level *l);
    bool hasLost(int row, int col, Monsters* m, int index);
    // specific move function for goblin (polymorphism!)
    bool move(int playerR, int playerC, int numberOfMovesSoFar, int maxNumberOfMoves, char c, Monsters* m);
    bool canReachPlayer(int gobRow, int gobCol, int playerRow, int playerCol, int maxDistance, int numberOfMovesSoFar);
    int shortestDistanceToPlayer(int playerR, int playerC, int monsterR, int monsterC);
    void generateTemplateMaze();
    // used to mark goblin path
    void printTemplateMaze();
    // used so that next path reading can be taken
    void clearPath();
    private:
        char tempMaze[LEVELROWS][LEVELCOLS];
        struct Coord{
        int r;
        int c;

        Coord(int row, int col)
        {
            r = row;
            c = col;
        };
            
        int getRow() {
            return r;
        }

        int getCol() {
            return c;
        }
        };
        std::vector<Coord> path;

    };




#endif /* Actors_hpp */
