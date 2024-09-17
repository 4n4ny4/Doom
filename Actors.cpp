
#include "Actors.h"
#include "globals.h"
#include "utilities.h"
#include "Level.h"
#include "GameObject.h"
#include <iostream>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class Weapon;

Actor::Actor(int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, int sleepTime, int maxHitPoints, Weapon * weapon, Level *l, string name)
{
    //set level + weapon pointers
    m_level = l;
    m_weapon = weapon;

    //set poisiton
    int r = randInt(1,LEVELROWS - 1);
    int c = randInt(1, LEVELCOLS - 1);
    while(! m_level -> isInBounds(r, c))
    {
        r = randInt(1,LEVELROWS - 1);
        c = randInt(1, LEVELCOLS - 1);
    }

    // set position
    m_row = r;
    m_col = c;
    
    // set game points
    m_dexterityPts = dexterityPoints;
    m_hitPoints = hitPoints;
    m_armorPts = armorPoints;
    m_strengthPts = strengthPoints;
    m_sleepTime = sleepTime;
    m_maxHitPts = maxHitPoints;

    // set strings
    m_actorName = name;
  
}

//checks if actor is asleep
bool Actor::isAsleep()
{
    if (getSleepTime()> 0)
        return true;
    else
        return false;
}

// reduces actor's hit points
bool Actor::reduceHitPoints(int reduceBy)
{
    m_hitPoints -= reduceBy;
    return true;

}

void Actor::applyWeaponDamage(Weapon *otherActorWeapon, Actor *otherActor)
{
    // calcaulate damage amount 
    int attackerPoints = otherActor -> getDexterityPts() + otherActor -> getWeapon() -> getDexterityBonus();
    int defenderPoints = getDexterityPts() + getWeapon() -> getDexterityBonus();

    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints))
    {
        int damagePoints = randInt(0, otherActor -> getStrengthPts() + otherActorWeapon -> getDamageAmount() - 1);
        m_hitPoints -= damagePoints;

        // if player is still alive even after getting hit
        if(m_hitPoints > 0)
        {
            // puts to sleep if weapon is magic fangs of sleep
            if (trueWithProbability(0.20))
            {
                if(setSleepTime(otherActor -> getWeapon()))
                {
                    otherActor -> setActionString(otherActor -> getActorName() + otherActor -> getWeapon() -> getWeaponAndActionName() + "and hits putting " +  getActorName() + " to sleep.");
                    return;
                }
            }
            otherActor -> setActionString(otherActor -> getActorName() + otherActor -> getWeapon() -> getWeaponAndActionName() +  getActorName() +  " and hits.");
        }
        // else if player dies from getting hit, include in action string
        else if (m_hitPoints <= 0)
         {
             if(setSleepTime(otherActor -> getWeapon()))
                {
                    otherActor -> setActionString(otherActor -> getActorName() + otherActor -> getWeapon() -> getWeaponAndActionName() + " putting " +  getActorName() + " to sleep, dealing a final blow.");
                }
            otherActor -> setActionString(otherActor -> getActorName() + otherActor -> getWeapon() -> getWeaponAndActionName() + getActorName() +  " and hits, dealing a final blow.");
         }
         return;
    }
    otherActor -> setActionString(otherActor -> getActorName() + otherActor -> getWeapon() -> getWeaponAndActionName() + getActorName() + " and misses.");
}


// reduces sleep time (used after hit by magic fangs)
void Actor::reduceSleepTime()
{
    if(m_sleepTime - 1 >= 0)
    {
        m_sleepTime -= 1;
    }
}


// getters
int Actor::getSleepTime() const
{
    return m_sleepTime;
}
int Actor::getDexterityPts() const
{
    return m_dexterityPts;
}
int Actor::getStrengthPts() const
{
    return m_strengthPts;
}
int Actor::getArmorPts() const
{
    return m_armorPts;
}

Weapon* Actor::getWeapon()
{
    return m_weapon;
}

Level* Actor::getLevel() const{
    return m_level;
}

std::string Actor::getActionString()
{
    return m_action;
}

std::string Actor::getActorName()
{
    return m_actorName;
}

int Actor::getHitPts()
{
    return m_hitPoints;
}

int Actor::getRowPos()
{
    return m_row;
}

int Actor::getColPos(){
    return m_col;
}



// setters
bool Actor::setSleepTime(Weapon *otherWeapon)
{
    magicFangs* isMagicFangs = dynamic_cast<magicFangs*>(otherWeapon);
    if (isMagicFangs != nullptr)
    {
        if(isAsleep())
            m_sleepTime = std::max(getSleepTime(), randInt(2,6));
        else
            m_sleepTime = randInt(2,6);
        return true;
    }
    return false;
}

void Actor::setWeapon(Weapon *newWeapon)
{
    m_weapon = newWeapon;
}

void Actor::setLevel(Level * l) 
{
    m_level = l;
}

bool Actor::setHitPoints(int reduceHitPointsBy, Actor *a)
{
       Player* isPlayer = dynamic_cast<Player*>(a);
    if (isPlayer != nullptr) {
        if(m_hitPoints - reduceHitPointsBy < 0)
        {
            m_hitPoints = reduceHitPointsBy;
            // hasLost();
            return true; // necessary??
        }
        m_hitPoints -= reduceHitPointsBy;
        return true;
    }
    return false;
}
bool Actor::setDexterityPts(int toAdd, Actor *a)
{
    Player* isPlayer = dynamic_cast<Player*>(a);
    if (isPlayer != nullptr)
    {
        if (m_dexterityPts + toAdd > 90)
        {
            m_dexterityPts = 90;
            return true;
        }
        m_dexterityPts += toAdd;
        return true;
    }
    return false;
}
bool Actor::setStrengthPts(int toAdd, Actor *a)
{
    Player* isPlayer = dynamic_cast<Player*>(a);
    if (isPlayer != nullptr)
    {
        if(m_strengthPts + toAdd > 90)
        {
            m_strengthPts = 90;
            return true;
        }
        m_strengthPts += toAdd;
        return true;
    }
    return false;
}

bool Actor::setArmorPts(int toAdd, Actor *a)
{
    Player* isPlayer = dynamic_cast<Player*>(a);
    if (isPlayer != nullptr)
    {
        if(m_armorPts + toAdd > 90)
        {
            m_armorPts = 90;
            return true;
        }
        m_armorPts += toAdd;
        return true;
    }
    return false;
}

void Actor::strengthPointsTo(int num)
{
    m_strengthPts = num;
}
void Actor::setActionString(std::string a)
{
    m_action = a;
}

//setters

void Actor::setRowPos(int newRowPos)
{
    m_row = newRowPos;
}

void Actor::setColPos(int newColPos){
    m_col = newColPos;
}


// desetructor for actor 
Actor::~Actor()
{
}

// sets max hit points from enhancing health
bool Actor::enhanceHealthMaxHitPts(Actor *a)
{
    Player* isPlayer = dynamic_cast<Player*>(a);
    if (isPlayer != nullptr)
    {
        m_maxHitPts += randInt(3,8);
        return true;
    }
    return false;
}

// for debugging purposes
bool Actor::cheat(Actor *a)
{
    
    Player* isPlayer = dynamic_cast<Player*>(a);
    if (isPlayer != nullptr)
    {
        isPlayer->setHitPoints(50, a);
        isPlayer->strengthPointsTo(9);
        return true;
    }
    return false;
}

int Actor::getMaxHitPts()
{
    return m_maxHitPts;
}

//**********PLAYER FUNCTIONS***************/


Player::Player(Weapon * weapon, Level *l): Actor(20, 2, 2, 2, 0, 20, weapon, l, "player")
{
   addToInventory(weapon);
}

void Actor::increaseHitPts(Actor *a)
{
     Player* isPlayer = dynamic_cast<Player*>(a);
     if(isPlayer != nullptr)
     {
        if(getHitPts() + 1 <= getMaxHitPts())
            {
                m_hitPoints += 1;
            }
     }
}

bool Player::switchWeapon(char input)
{
    int objectNum = input - 'a' + 1;
    //find object that user chooses in Inventory
    if(objectNum <= m_inventorySize)
    {
        // stores object of choice in temp variable
        GameObject *temp = inventory.at(objectNum - 1);
        //store weapon player was holding into vector
        inventory.at(objectNum -1) = getWeapon();
        Weapon* isWeapon = dynamic_cast<Weapon*>(temp);
        if(isWeapon != nullptr) {
            setWeapon(isWeapon);
            setActionString("You are now wielding " + isWeapon -> getWeaponName());
            return true;
        }
    }
    cout << "Please choose the right weapon to wield. " << endl;
    return false;
}

bool Player::addToInventory(GameObject *g)
{
    if(m_inventorySize < MAXINVENTORYSIZE)
    {
    inventory.push_back(g);
    // check if weapon
    Weapon* isWeapon = dynamic_cast<Weapon*>(g);
    if (isWeapon!= nullptr)
    {
        setActionString("You've picked up a " + isWeapon -> getWeaponName());
        m_inventorySize++;
    }
    Scroll* isScroll = dynamic_cast<Scroll*>(g);
    if (isScroll!= nullptr)
   // if not weapon, check if scroll
    {
        setActionString("You've picked up a " + isScroll -> getScrollName());
        m_inventorySize++;
    }
     return true;
    }
    else
        return false;
}

// helps player pick up game objects (scrolls and weapons)
bool Player::pickUpGameObject(Level *l)
{
    if(l -> getNumObjectsOnBoard() == 0)
        return false;
    for(int i = 0; i < l -> getNumObjectsOnBoard(); i++)
    {
        // if player picks up golden idol, end the game
        GoldenIdol* isGoldenObject = dynamic_cast<GoldenIdol*>(l -> getObject(i));
        if (isGoldenObject != nullptr)
            {
                hasWon();
                return true;
            }
        GameObject* g = l -> getObject(i);
        // if object coordinates match one of objects stored in objects vector, add it to inventory
        if(g -> getRow() == getRowPos() && g-> getCol() == getColPos())
        {
            addToInventory(g);
            l -> removeObjects(g, i);
            return true;
        }
    }
    return false;
}

// used when playor has gotten golden idol
void Player::hasWon()
{
    cout << "Congrats! You''ve won! Press q to quit";
     char input = getCharacter();
    do {
        std::cin >> input;
        } while (input != 'q');
    exit(0);
}



bool Player::readScroll(char input)
{
    getLevel() -> printLevel();
    // convert user input to objectNum
    int objectNum = input - 'a' + 1;
    //find node previous to scroll of interest
    if(m_inventorySize == 1) // assuming only short swords is in there
    {
        cout << "no scrolls found" << endl;
        return false;
    }
    
    // if edge cases don't apply, check if scroll type and delete it if so
    if(objectNum <= m_inventorySize)
    {
        GameObject *g = inventory.at(objectNum -1);
          if(readScrollHelper(g))
        {
            
            m_inventorySize--;
            delete g;
            inventory.erase(inventory.begin() + objectNum - 1);
            return true;
        }
           else
        {
            cout << "sorry, we couldn't find the scroll" << endl;
            return false;
        }
    }
    return false;
}
        

   // helps read scroll and perofrm corresponding actions according to scroll type           
bool Player::readScrollHelper(GameObject *g)
    {
        Scroll* isScroll = dynamic_cast<Scroll*>(g);
        if(isScroll == nullptr)
        {
            cout << "Not a scroll. Please reselect" << endl;
            return false;
        }
        //teleportation scroll
        teleportationScroll* telepScroll = dynamic_cast<teleportationScroll*>(g);
        if(telepScroll)
        {
            int row = randInt(1, LEVELROWS - 1);
            int col = randInt (1, LEVELCOLS - 1);
            while(!getLevel() -> isInBounds(row, col))
            {
                row = randInt(1, LEVELROWS - 1);
                col = randInt (1, LEVELCOLS - 1);
            }
            // sets a new position for player
            getLevel() -> setMaze(getRowPos(), getColPos(), ' ');
            setRowPos(row);
            setColPos(col);
            getLevel() -> setMaze(row, col, '@');
            setActionString("You read a scroll of teleportation. You feel your body wrenched in space and time.");
            cout << getActionString();
            return true;
        }
    
        // improve armor scroll
        improveArmorScroll* improveArmor = dynamic_cast<improveArmorScroll*>(g);
    
        if(improveArmor)
        {
            if (getArmorPts() >= 99 || getArmorPts() <= 0)
                return false;
            else(setArmorPts(randInt(1,3),this));
           setActionString("You read a scroll of enhance armor. Your armor glows blue.");
           cout << getActionString();
            return true;
        }
    
        //raise strength scroll
        raiseStrengthScroll* strength = dynamic_cast<raiseStrengthScroll*>(g);
    
        if(strength)
        {
            if (getStrengthPts() >= 99 || getStrengthPts() <= 0)
                return false;
            else(setStrengthPts(randInt(1,3),this));
            setActionString("You read a scroll of raise strength. Your muscles bulge");
            cout << getActionString();
            return true;
        }
    
        // enhance health scroll
        enhanceHealthScroll* health = dynamic_cast<enhanceHealthScroll*>(g);
        if(health)
        {
            enhanceHealthMaxHitPts(this);
            setActionString("You read a scroll of enhance health. You feel your heart beating stronger.");
            cout << getActionString();
            return true;
        }
    
        //enhanced dexterity scroll
        enhanceDexterityScroll* dexterity= dynamic_cast<enhanceDexterityScroll*>(g);
        if(dexterity)
        {
            setDexterityPts(1,this);
            setActionString("You read a scroll of enhance dexterity. You feel like less of a klutz.");
            cout << getActionString();
            return true;
        }
    
    return false;
    }

// destructs all objects in inventory
Player::~Player()
{
    for(int i = 0; i < m_inventorySize; i++)
    {
        delete inventory.at(i);
    }
}

// displays inventory and numbers it
void Player::displayInventory()
{
    clearScreen();
    char objectNum = 'a';
    cout << "Inventory:" << endl;
    for(int i = 0; i < m_inventorySize; i++)
    {
        cout << objectNum << ". ";
          Scroll* isScroll = dynamic_cast<Scroll*>(inventory.at(i));
             if (isScroll != nullptr)
             {
                 string scrollName = isScroll -> getScrollName();
                 cout << scrollName << endl;
             }
              else{
                Weapon* isWeapon = dynamic_cast<Weapon*>(inventory.at(i));
                if (isWeapon != nullptr)
                {
                    string weaponName = isWeapon -> getWeaponName();
                    cout << weaponName << endl;
                }
            }
            objectNum++;
    }
}

// takes in user input and applies to find next coordinate 
int Player::getCoordinatesForMove(char input, int row, int col, int monsterCoord[2]) {
    int newRow = row;
    int newCol = col;
    switch (input) {
        case ARROW_UP:
            newRow--;
            break;
        case ARROW_DOWN:
            newRow++;
            break;
        case ARROW_LEFT:
            newCol--;
            break;
        case ARROW_RIGHT:
            newCol++;
            break;
        default:
            break;
    }
    //check if the movement is within bounds
    if (newRow >= 0 && newRow < LEVELROWS && newCol >= 0 && newCol < LEVELCOLS)
    {
        if(getLevel()->getMaze(newRow, newCol) == '#')
        {
            return -1;
        }
        
        // hitting a monster or player
        if(getLevel() -> getMaze(newRow, newCol) == 'S' || getLevel() -> getMaze(newRow, newCol) == 'D' || getLevel() -> getMaze(newRow, newCol) == 'B' || getLevel() -> getMaze(newRow, newCol) == 'G' || getLevel() -> getMaze(newRow, newCol) == '@')
        {
            monsterCoord[0] = newRow;
            monsterCoord[1] = newCol;
            return 0;
        }
         
        // moving to a new empty space
        else{
            setColPos(newCol);
            setRowPos(newRow);
            return 1;
        }
    }
    // none of the above conditions (invalid move)
    return -1;
}

// when player has lost, prints level and sets action string to quit game
bool Player::hasLost()
{
    if (getHitPts() <= 0)
    {
        clearScreen();
        if(getLevel() -> getLevelNum() < 4)
        {
            getLevel() -> printStairs();
        }
        getLevel() -> printMonsters();
        getLevel() -> printObjects();
        getLevel() -> printPlayer(getLevel() -> getPlayer() -> getRowPos(), getLevel() -> getPlayer() -> getColPos());
        getLevel() -> printLevel();

        cout << "Level: " << getLevel() -> getLevelNum()  << " Hit points: " << getHitPts() << " Armor: " << getArmorPts() << " Strength: " << getStrengthPts() << " Dexterity: " << getDexterityPts() << endl;

        setActionString("press q to exit the game.");
        cout << getActionString() << endl;
        char input = getCharacter();
        while (input != 'q')
        {
            input = getCharacter();
        }
        //user has pressed char q
        exit(0);
        return true;
    }
    else
        return false;
}
 

//**********MONSTER FUNCTIONS***************

Monsters::Monsters(int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, int maxHitPoints, Weapon * weapon, Level *l, string name): Actor(hitPoints, armorPoints, strengthPoints, dexterityPoints, 0, maxHitPoints, weapon, l, name)
{
 
}

// checks if spot of next move is blocked by another thing
bool Monsters::isSafeToMove(int row, int col)
{
    if(getLevel() -> getMaze(row, col) != 'S' && getLevel() -> getMaze(row, col) != 'B' &&
                getLevel() -> getMaze(row, col) != 'D' && getLevel() -> getMaze(row, col) != 'G' && 
                getLevel() -> getMaze(row, col) != '#')
                return true;
    return false;
    
}

// checks if player is next to monster
bool Monsters::isPlayerCloseBy(int playerR, int playerC, int monsterR, int monsterC)
{
    int distance = abs(playerR - monsterR) + abs(playerC - monsterC);
    return (distance <= 1);
}


// calculates the sum of the difference in row distance and coloumn distance to find distance to player
bool Monsters::canReachPlayer(int playerR, int playerC, int monsterR, int monsterC, int numberOfMovesSoFar, int maxNumberOfMoves)
{
    int distance = abs(playerR - monsterR) + abs(playerC - monsterC);
    return (distance <= maxNumberOfMoves);
}

Monsters::~Monsters()
{

}

// move monsters according to where their positioned relative to player
bool Monsters::move(int playerR, int playerC, int numberOfMovesSoFar, int maxNumberOfMoves, char c, Monsters* m)
{
    if(getSleepTime() > 0)
        return false;
    if(getLevel() -> monsterAttack(m))
        {
        return false;
        }
    int monsterR = m -> getRowPos();
    int monsterC = m -> getColPos();
    if(canReachPlayer(playerR, playerC, monsterR, monsterC, numberOfMovesSoFar, maxNumberOfMoves))
		{
			if (playerR > monsterR)
            {
                // checks if spot is safe to move before moving into it
				if(isSafeToMove(monsterR + 1, monsterC))
                {
                    getLevel() -> setMaze(getRowPos(), getColPos(), ' ');
                    setRowPos(monsterR + 1);
                    setColPos(monsterC);
					getLevel() -> setMaze(getRowPos(), getColPos(), c);
					return true;
                }
            }

            if (playerC > monsterC)
            {
				if(isSafeToMove(monsterR, monsterC + 1))
                {
                    getLevel() -> setMaze(getRowPos(), getColPos(), ' ');
                    setRowPos(monsterR);
                    setColPos(monsterC + 1);
					getLevel() -> setMaze(getRowPos(), getColPos(), c);
					return true;
                }
            }

            if (monsterR > playerR)
            {
				if(isSafeToMove(monsterR - 1, monsterC))
                {
                    getLevel() -> setMaze(getRowPos(), getColPos(), ' ');
                    setRowPos(monsterR - 1);
                    setColPos(monsterC);
					getLevel() -> setMaze(getRowPos(), getColPos(), c);
					return true;
                }
            }

            if (monsterC > playerC)
            {
				if(isSafeToMove(monsterR, monsterC - 1))
                {
                    getLevel() -> setMaze(getRowPos(), getColPos(), ' ');
                    setRowPos(monsterR);
                    setColPos(monsterC - 1);
					getLevel() -> setMaze(getRowPos(), getColPos(), c);
					return true;
                }
            }   
        }
    return false;
}


//BOGEYMAN

Bogeyman::Bogeyman(Level *l):Monsters(randInt(5,10), 2, randInt(2,3), randInt(2,3), 10, new shortSwords(l), l, "Bogeyman")
{
}

// drops weapon if allowed and deletes boogeyman
bool Bogeyman::hasLost(int row, int col, Monsters* m, int index)
{
    if(m -> getHitPts() > 0)
    {
        return false;
    }
    // set maze to empty space to remove monster
    getLevel() -> setMaze(row, col, ' ');
    // remove monster from store
    getLevel() -> eraseAMonster(index);
    // // drop a weapon if allowed
    getLevel() -> addObjectsAfterMonstersDie(row, col, 'B');
    return true;

}



//SNAKEWOMAN

SnakeWoman::SnakeWoman(Level *l):Monsters(randInt(3,6), 3, 2, 3, 6, new magicFangs(l), l, "Snakewoman")
{
    
}

// drops weapon if allowed and deletes snakewoman

bool SnakeWoman::hasLost(int row, int col, Monsters* m, int index)
{
     if(m -> getHitPts() > 0)
        return false;
    // set maze to empty space to remove monster
    getLevel() -> setMaze(row, col, ' ');
    // remove monster from store
    getLevel() -> eraseAMonster(index);
    // // drop a weapon if allowed
    getLevel() -> addObjectsAfterMonstersDie(row, col, 'S');
    return true;

}


//DRAGON

Dragon::Dragon(Level *l):Monsters(randInt(20,25), 4, 4, 4, 25, new longSwords(l), l, "Dragon")
{
    
}

// drops weapon if allowed and deletes dragon

bool Dragon::hasLost(int row, int col, Monsters* m, int index)
{
     if(m -> getHitPts() > 0)
        return false;
    // set maze to empty space to remove monster
    getLevel() -> setMaze(row, col, ' ');
    // remove monster from store
    getLevel() -> eraseAMonster(index);
    // // drop a weapon if allowed
    getLevel() -> addObjectsAfterMonstersDie(row, col, 'D');
    return true;

}


//GOBLIN

Goblin::Goblin(Level *l):Monsters(randInt(15,20), 1, 3, 1, 20, new shortSwords(l), l, "Goblin")
{
    
}

// drops weapon if allowed and deletes goblin

bool Goblin::hasLost(int row, int col, Monsters* m, int index)
{
     if(m -> getHitPts() > 0)
        return false;
    // set maze to empty space to remove monster
    getLevel() -> setMaze(row, col, ' ');
    // remove monster from store
    getLevel() -> eraseAMonster(index);
    // // drop a weapon if allowed
    getLevel() -> addObjectsAfterMonstersDie(row, col, 'G');
    return true;

}

// prints maze (for debugging purposes)
void Goblin::printTemplateMaze()
{
for(int i = 0; i < LEVELROWS; i++)
    {
        for(int j = 0; j < LEVELCOLS; j++)
        {

            cout << tempMaze[i][j];

        }
    cout << endl;
    }
}

// generates template maze to check goblin's movements
void Goblin::generateTemplateMaze()
{

    for (int i = 0; i < LEVELROWS;i++)
    {
        for(int j = 0; j < LEVELCOLS; j++)
        {
            tempMaze[i][j] = '.';
        }
    }
}

// finds distance regardless of what's around (even if another object is blocking)
int Goblin::shortestDistanceToPlayer(int playerR, int playerC, int monsterR, int monsterC)
{
    return abs(playerR - monsterR) + abs(playerC - monsterC);
}



bool Goblin::canReachPlayer(int gobRow, int gobCol, int playerRow, int playerCol, int numberOfMovesSoFar, int maxDistance)
{
    // Base case: Goblin reaches player or exceeds max distance
    if (playerCol == gobCol && playerRow == gobRow)
        return true;
    if ((numberOfMovesSoFar + shortestDistanceToPlayer(playerRow, playerCol, gobRow, gobCol)) > maxDistance)
        return false;

    int rowDiff = playerRow - gobRow;
    int colDiff = playerCol - gobCol;

    // calcualte direction of movement
    int rowMove = (rowDiff > 0) ? 1 : (rowDiff < 0) ? -1: 0;
    int colMove = (colDiff > 0) ? 1 : (colDiff < 0) ? -1: 0;

    // we try to move closer to player
    if (rowMove != 0 && isSafeToMove(gobRow + rowMove, gobCol) && tempMaze[gobRow + rowMove][gobCol] != 'O')
    {
        tempMaze[gobRow + rowMove][gobCol] = 'O';
        path.push_back(Coord(gobRow + rowMove, gobCol));
        return canReachPlayer(gobRow + rowMove, gobCol, playerRow, playerCol, numberOfMovesSoFar + 1,  maxDistance);
    }
    else if (colMove != 0 && isSafeToMove(gobRow, gobCol + colMove) && tempMaze[gobRow][gobCol + colMove] != 'O')
    {
        tempMaze[gobRow][gobCol + colMove] = 'O';
        path.push_back(Coord(gobRow, gobCol + colMove));
        return canReachPlayer(gobRow, gobCol + colMove, playerRow, playerCol, numberOfMovesSoFar + 1, maxDistance);
    }

    // else we move away from the player (possible roundabout way of getting to player in < 15 steps)

    else if (rowMove != 0 && isSafeToMove(gobRow + (rowMove*-1), gobCol) && tempMaze[gobRow + (rowMove*-1)][gobCol] != 'O')
    {
        tempMaze[gobRow + (rowMove*-1)][gobCol] = 'O';
        path.push_back(Coord(gobRow + (rowMove*-1), gobCol));
        return canReachPlayer(gobRow + (rowMove*-1), gobCol, playerRow, playerCol,numberOfMovesSoFar + 1,  maxDistance);

    }

    else if (colMove != 0 && isSafeToMove(gobRow, gobCol + (colMove*-1)) && tempMaze[gobRow][gobCol + colMove] != 'O')
    {
        tempMaze[gobRow][gobCol + (colMove*-1)] = 'O';
        path.push_back(Coord(gobRow, gobCol + (colMove*-1)));
        return canReachPlayer(gobRow, gobCol + (colMove*-1), playerRow, playerCol, numberOfMovesSoFar + 1, maxDistance);
    }

    return false;
}

// controls goblin movement
bool Goblin::move(int playerR, int playerC, int numberOfMovesSoFar, int maxNumberOfMoves, char c, Monsters* m)
{
    // if sleep time is greater than zero, don't move
    if(getSleepTime() > 0)
        return false;
    // if player is near monster, then attack but don't move to new spot
    if(getLevel() -> monsterAttack(m))
        {
        return false;
        }
    // else we move to a new spot
    if (canReachPlayer(m -> getRowPos(), m -> getColPos(), playerR, playerC, 0, maxNumberOfMoves))
    {
        getLevel() -> setMaze(getRowPos(), getColPos(), ' ');
        int rowPosition = path.at(0).getRow();
        int colPosition = path.at(0).getCol();
        setRowPos(rowPosition);
        setColPos(colPosition);
        getLevel() -> setMaze(getRowPos(), getColPos(), c);
        return true;
    }
    return false;
}


// resets path vector so possible path can be found in next call
 void Goblin::clearPath()
 {
    path.clear();
 }
