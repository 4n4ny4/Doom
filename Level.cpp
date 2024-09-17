#include "Level.h"
#include "utilities.h"
#include "GameObject.h"
#include "Actors.h"
#include "globals.h"
#include <vector>

#include <iostream>
using namespace std;

Level::Level(int lvl):  m_levelRows(LEVELROWS), m_levelCols(LEVELCOLS), m_rooms(randInt(3,5)), m_levelNumber(lvl)
{
    // fills the board with #'s
    for(int i = 0; i < LEVELROWS; i++)
    {
        for(int j = 0; j < LEVELCOLS; j++)
        {
            maze[i][j] = '#';
        }
    }
    
    createRooms();
    fillRooms();
   // printLevel();
}

// checks if rooms are overlapping
bool Level::isOverlapping(int newPosX, int newPosY, int newNumCols, int newNumRows, int roomNum)
{
    int newEndX = newPosX + newNumRows - 1;
    int newEndY = newPosY + newNumCols - 1;

        for (int i = 0; i < roomNum; i++) {
            int roomEndX = rooms[i]->getPosX() + rooms[i]->getRows() - 1;
            int roomEndY = rooms[i]->getPosY() + rooms[i]->getCols() - 1;
            if (!(newPosX > roomEndX || newEndX < rooms[i]->getPosX()))
            {
                if (!(newPosY > roomEndY || newEndY < rooms[i]->getPosY()))
                {
                    return true; // Overlapping
                }
            }
        }
        return false; // Not overlapping
}

void Level::createCorridors()
{
    for(int i = 1; i < m_rooms; i++)
    {
        int r1X = rooms[i-1] -> getPosX();
        int r1Y = rooms[i-1] -> getPosY();
        int r2X = rooms[i] -> getPosX();
        int r2Y = rooms[i] -> getPosY();
        
        while(r1X != r2X && r1Y != r2Y)
        {
            if(maze[r1X][r1Y] == '#')
                maze[r1X][r1Y] = ' ';
      
            if(r1X < r2X)
            {
                r1X++;
            }
          
            if(r1X > r2X)
            {
                r1X--;
            }
        }
        while(r1Y != r2Y)
        {
            if(maze[r1X][r1Y] == '#')
                maze[r1X][r1Y] = ' ';
            if(r1Y > r2Y)
            {
                r1Y--;
            }
            if(r2Y > r1Y)
            {
                r1Y++;
            }
        }
    }
}


void Level::createRooms()
{
    rooms[0] = new Room;
    
    for(int i = 1; i < m_rooms; i++)
    {
        int newX, newY, newC, newR;
        do{
            rooms[i] = new Room;
            
            //setting new rows
            newR = randInt(7,10);
            while(!rooms[i] -> setRows(newR))
            {
                newR = randInt(7,10);
            }
            //setting new coloumns
            newC = randInt(10,15);
            while(!rooms[i] -> setCols(newC))
            {
                newC = randInt(5,10);
            }
            
            //setting new y coordinate
            newY = randInt(1,LEVELCOLS - 1);
            while(!rooms[i] -> setPosY(newY))
            {
                newY = randInt(1,LEVELROWS - 1);
            }
            
            //setting new x coordinate
            newX = randInt(1,LEVELROWS - 1);
            while(!rooms[i] -> setPosX(newX))
            {
                newX = randInt(1,LEVELROWS - 1);
            }
        }
        while (isOverlapping(newX, newY, newC, newR, i));
    }
    //creates corridors between rooms
    createCorridors();
}

Level::Room::Room()
{
    m_roomRows = randInt(2, 15);
    m_roomCols = randInt(2,10);
    m_leftTopPosY = randInt(1,LEVELCOLS - m_roomCols - 2);
    m_leftTopPosX = randInt(1,LEVELROWS - m_roomRows - 2);

}


// setters

bool Level::Room::setPosX(int x)
{
    if(1 <= x && x <= LEVELROWS - m_roomRows - 1)
    {
        m_leftTopPosX = x;
        return true;
    }
    return false;
}

bool Level::Room::setPosY(int y)
{
    if(1 <= y && y <= LEVELCOLS - m_roomCols - 1)
    {
        m_leftTopPosY = y;
        return true;
    }
    return false;
}

bool Level::Room::setRows(int r)
{
    if(2 <= LEVELROWS - r)
    {
        m_roomRows = r;
        return true;
    }
    return false;
}

bool Level::Room::setCols(int c)
{
    if(2 <= LEVELCOLS - c)
    {
        m_roomCols = c;
        return true;
    }
    return false;
}

// Set the player
 void Level::setPlayer(Player* p) {
        m_player = p;
    }

    // Get the player
 Player* Level::getPlayer() const{
        return m_player;
    }

//getters
int Level::Room::getPosY() const
{
    return m_leftTopPosY;
}

int Level::Room::getPosX() const
{
    return m_leftTopPosX;
}

int Level::Room::getRows() const
{
    return m_roomRows;
}
int Level::Room::getCols() const
{
    return m_roomCols;
}

char Level::getMaze(int row, int col) const {
   if (row >= 0 && row < LEVELROWS && col >= 0 && col < LEVELCOLS) {
        return maze[row][col];
    }
    return '\0';  // Return null character if out of bounds
}

void Level::setMaze(int row, int col, char value) {
    if (row >= 0 && row < LEVELROWS && col >= 0 && col < LEVELCOLS) {
        maze[row][col] = value;
    }
}

// fills rooms with ' '
void Level::fillRooms()
{
    for(int i = 0; i < m_rooms; i++)
    {
        int initX = rooms[i] -> getPosX();
         // Starting Y position for the room
        int rows = rooms[i]->getRows();
        int columns = rooms[i]->getCols();
        
        for(int j = 0; j < rows; j++)
        {
            int initY = rooms[i]->getPosY();
            for(int k = 0; k < columns; k++)
            {
                maze[initX][initY] = ' '; // need to replace this
                initY++;
            }
            initX++;
        }
    }
    
}

// prints the entire level
void Level::printLevel()
{
    for (int i = 0; i < LEVELROWS;i++)
    {
        for(int j = 0; j < LEVELCOLS; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

void Level::printObjects()
{
    for(int i = 0; i < m_numObjectsOnBoard; i++)
    {
        Weapon * isWeapon = dynamic_cast<Weapon *>(objects[i]);
        if(isWeapon != nullptr)
        {
            maze[objects[i] -> getRow()][objects[i] -> getCol()] = ')';
        }
        Scroll * isScroll = dynamic_cast<Scroll *>(objects[i]);
        if(isScroll != nullptr)
        {
            maze[objects[i] -> getRow()][objects[i] -> getCol()] = '?';
        }
        GoldenIdol * isGold = dynamic_cast<GoldenIdol *>(objects[i]);
        if(isGold != nullptr)
        {
            maze[objects[i] -> getRow()][objects[i] -> getCol()] = '&';
        }

    }
}

void Level::printMonsters()
{
        for(int i = 0; i < getNumMonstersOnBoard(); i++)
    {
        SnakeWoman* isSnakeWoman = dynamic_cast<SnakeWoman*>(monsters[i]);
        if(isSnakeWoman != nullptr)
        {
            maze[monsters[i] -> getRowPos()][monsters[i] -> getColPos()] = 'S';
        }
       Bogeyman* isBogey = dynamic_cast<Bogeyman*>(monsters[i]);
        if(isBogey != nullptr)
        {
            maze[monsters[i] -> getRowPos()][monsters[i] -> getColPos()] = 'B';
        }
        Dragon* isDragon = dynamic_cast<Dragon*>(monsters[i]);
        if(isDragon != nullptr)
        {
            maze[monsters[i] -> getRowPos()][monsters[i] -> getColPos()] = 'D';
        }
        Goblin* isGoblin = dynamic_cast<Goblin*>(monsters[i]);
        if(isGoblin != nullptr)
        {
            maze[monsters[i] -> getRowPos()][monsters[i] -> getColPos()] = 'G';
        }
    }


}



// cehcks if actor/object is in bounds
bool Level::isInBounds(int r, int c) const
{
    if((1 < r && r < LEVELROWS) && (1 < c && c < LEVELCOLS))
    {
        if(getMaze(r,c) == ' ')
            return true;
    }
    return false;
        
}

// prints player in maze
void Level::printPlayer(int row, int col)
{
    maze[row][col] = '@';
}

// adds different objects to level and places them in bounds of maze
void Level::addObjectsToLevel()
{
    int m_numObjects = randInt(2,3);
    int i;
    for (i = 0; i < m_numObjects; i++)
    {
        ObjectStore objectType = static_cast<ObjectStore>(randInt(MACES, ENHANCEDEXTERITYSCROLL));
        int r = -1;
        int c = -1;
        switch(objectType)
        {
            case MACES:
                objects.push_back(new Maces(this));
                r = objects.at(i) -> getRow();
                c = objects.at(i) -> getCol();
                maze[r][c] = ')';
                break;
            case SHORTSWORDS:
                objects.push_back(new shortSwords(this));
                r = objects.at(i) -> getRow();
                c = objects.at(i) -> getCol();
                maze[r][c] = ')';
                break;
            case LONGSWORDS:
                objects.push_back(new longSwords(this));
                r = objects.at(i) -> getRow();
                c = objects.at(i) -> getCol();
                maze[r][c] = ')';
                break;
            case IMPROVEARMORSCROLL:
                objects.push_back(new improveArmorScroll(this));
                r = objects.at(i) -> getRow();
                c = objects.at(i) -> getCol();
                maze[r][c] = '?';
                break;
            case RAISESTRENGTHSCROLL:
                objects.push_back(new raiseStrengthScroll(this));
                r = objects.at(i) -> getRow();
                c = objects.at(i) -> getCol();
                maze[r][c] = '?';
                break;
            case ENHANCEHEALTHSCROLL:
                objects.push_back(new enhanceHealthScroll(this));
                r = objects.at(i) -> getRow();
                c = objects.at(i) -> getCol();
                maze[r][c] = '?';
                break;
            case ENHANCEDEXTERITYSCROLL:
                objects.push_back(new enhanceDexterityScroll(this));
                r = objects.at(i) -> getRow();
                c = objects.at(i) -> getCol();
                maze[r][c] = '?';
                break;
        }
        m_numObjectsOnBoard++;
    }

    if(m_levelNumber == 4)
        {
            m_numObjectsOnBoard++;
            objects.push_back(new GoldenIdol(this));
            int r = objects.at(i) -> getRow();
            int c = objects.at(i) -> getCol();
            maze[r][c] = '&';
        }
}

//getters 
GameObject* Level::getObject(int index) const
{
    if(index < getNumObjectsOnBoard())
        return objects.at(index);
    else
        return nullptr;
    
}

int Level::getNumObjectsOnBoard() const
{
    return m_numObjectsOnBoard;
}

int Level::getLevelNum() const
{
    return m_levelNumber;
}

// adds player to the level each time clearScren() used
void Level::addPlayerToLevel()
{
    m_player = new Player(new shortSwords(this), this);
    int rowPos = m_player -> getRowPos();
    int colPos = m_player -> getColPos();
    maze[rowPos][colPos] = '@';
}

// ensures that player's inventory/stats remain the same between levels
void Level::movePlayerToNextLevel(Player *p, Level *l)
{
    int rowPos = randInt(1,LEVELROWS - 1);
    int colPos = randInt(1,LEVELCOLS - 1);
    while(!l -> isInBounds(rowPos, colPos))
    {
        rowPos = randInt(1,LEVELROWS - 1);
        colPos = randInt(1,LEVELCOLS - 1);
    }
    m_player = p;
    m_player -> setLevel(this);
    m_player -> setRowPos(rowPos);
    m_player -> setColPos(colPos);
    l -> maze[rowPos][colPos] = '@';
    
}

// adds monsters to level and sets valid positions for them
void Level::addMonsterToLevel()
{
    m_numMonsters = randInt(2, 5*(m_levelNumber+1)+1);
    int r = -1;
    int c = -1;
    for(int i = 0; i < m_numMonsters; i++)
    {
        char monsterSet[] = {'S', 'G', 'B', 'D'};
        int index;
        if(m_levelNumber == 1)
            index = 2;
        else if (m_levelNumber ==2)
            index = 3;
        else
            index = 4;
        int monsterTypes = randInt(0, index-1);
        switch(monsterSet[monsterTypes])
        {
            case 'B':
                monsters.push_back(new Bogeyman(this));
                break;
            case 'S':
                monsters.push_back(new SnakeWoman(this));
                break;
            case 'G':
                monsters.push_back(new Goblin(this));
                break;
            case 'D':
                monsters.push_back(new Dragon(this));
                break;
        }
        r = monsters[i]->getRowPos();
        c = monsters[i]->getColPos();
        maze[r][c] = monsterSet[monsterTypes];
    }
}


void Level::removeObjects(GameObject *g, int i)
{
    // adding a space on maze to delete objects
    int row; int col;
    row = g -> getRow();
    col = g -> getCol();
     maze[row][col] = ' ';

    // reducing the objects vector + number of objects on board
    auto index = objects.begin() + i;
    objects.erase(index);
    m_numObjectsOnBoard--;
}

// removed char c as a paramter
bool Level::monsterAttack(Monsters * m)
{
  if(m -> isPlayerCloseBy(getPlayer() -> getRowPos(), getPlayer() -> getColPos(), m -> getRowPos(), m -> getColPos())) 
    {
        getPlayer() -> applyWeaponDamage(m -> getWeapon(), m);
        return true;
    }
    return false;
}



    bool Level::reduceNumMonstersOnBoard(int reduceBy)
    {
        if(m_numMonsters - reduceBy > 0)
        {
            m_numMonsters -= reduceBy;
            return true;
        }
        return false;
    }

// leaves objects in places where monsters die according to their type
    void Level::addObjectsAfterMonstersDie(int row, int col, char monsterName)
    {
        if (maze[row][col] == ' ')
        {
            if(monsterName == 'B')
            {
                magicAxes *newObject = new magicAxes(this);
                objects.push_back(newObject);
                m_numObjectsOnBoard+= 1;
                newObject -> setObjectPosition(row, col);
                maze[row][col] = ')';
            }

            else if (monsterName == 'D')
            {
                ObjectStore choice = static_cast<ObjectStore>(randInt(IMPROVEARMORSCROLL, TELEPORTATIONSCROLL));
                if (choice == IMPROVEARMORSCROLL)
                {
                improveArmorScroll *newObject = new improveArmorScroll(this);
                objects.push_back(newObject);
                m_numObjectsOnBoard+= 1;
                newObject -> setObjectPosition(row, col);
                maze[row][col] = '?';
                }

                else if (choice == RAISESTRENGTHSCROLL)
                {
                raiseStrengthScroll *newObject = new raiseStrengthScroll(this);
                objects.push_back(newObject);
                m_numObjectsOnBoard+= 1;
                newObject -> setObjectPosition(row, col);
                maze[row][col] = '?';
                }

                else if (choice == ENHANCEHEALTHSCROLL)
                {
                enhanceHealthScroll *newObject = new enhanceHealthScroll(this);
                objects.push_back(newObject);
                m_numObjectsOnBoard+= 1;
                newObject -> setObjectPosition(row, col);
                maze[row][col] = '?';
                }

                else if (choice == ENHANCEDEXTERITYSCROLL)
                {
                enhanceDexterityScroll *newObject = new enhanceDexterityScroll(this);
                objects.push_back(newObject);
                m_numObjectsOnBoard+= 1;
                newObject -> setObjectPosition(row, col);
                maze[row][col] = '?';
                }

                else if (choice == TELEPORTATIONSCROLL)
                {
                teleportationScroll *newObject = new teleportationScroll(this);
                objects.push_back(newObject);
                m_numObjectsOnBoard+= 1;
                newObject -> setObjectPosition(row, col);
                maze[row][col] = '?';
                }

            }

            else if (monsterName == 'G')
            {
                if(trueWithProbability(0.33333))
                {
                ObjectStore choice = static_cast<ObjectStore>(randInt(MAGICAXES, MAGICFANGS));
                if(choice == MAGICAXES)
                    {
                        magicAxes *newObject = new magicAxes(this);
                        objects.push_back(newObject);
                        m_numObjectsOnBoard+= 1;
                        newObject -> setObjectPosition(row, col); 
                        maze[row][col] = ')';
                    }
                else if (choice == MAGICFANGS)
                    {
                        magicFangs *newObject = new magicFangs(this);
                        objects.push_back(newObject);
                        m_numObjectsOnBoard+= 1;
                        newObject -> setObjectPosition(row, col);  
                        maze[row][col] = ')';
                    }
                }
            }

            else if (monsterName == 'S')
            {
            
                if(trueWithProbability(0.3333))
                {
                    magicFangs *newObject = new magicFangs(this);
                    objects.push_back(newObject);
                    m_numObjectsOnBoard+= 1;
                    newObject -> setObjectPosition(row, col); 
                    maze[row][col] = ')';

                }

            }
        }
    }


 Level::~Level()
{
    for(int i = 0; i < m_rooms; i++)
    {
        delete rooms[i];
    }

    for(int i = 0; i < m_numObjectsOnBoard; i++)
    {
        delete objects[i];
    }

        for(int i = 0; i < monsters.size(); i++)
    {
        delete monsters[i];
    }

    delete m_player;
    delete m_stairs;
}

Stairs* Level::getStairs()
{
    return m_stairs;
}


void Level::addStairsToLevel()
{
    m_stairs = new Stairs(this);
    int r = m_stairs -> getRow();
    int c = m_stairs -> getCol();
    maze[r][c] = '>';
}

void Level::printStairs()
{
    maze[getStairs() -> getRow()][getStairs() -> getCol()] = '>';
}

int Level::getNumMonstersOnBoard() const
{
    return m_numMonsters;
}

Monsters* Level::getMonster(int index) const
{
    return monsters.at(index);
}


  void Level::eraseAMonster(int index)
 {
       if (index >= 0 && index < monsters.size()) {
        // delete monsters.at(index);
        monsters.erase(monsters.begin() + index);
        m_numMonsters--;
    }
 }

int Level::getNumberMonsters()
{
    return monsters.size();
}