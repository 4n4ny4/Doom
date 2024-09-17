
// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "Level.h"
#include "Actors.h"
#include "globals.h"
#include "GameObject.h"
#include <iostream>
using namespace std;



// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance): currLevelNum(0)
{
    m_goblinSmellDistance = goblinSmellDistance;
}

// displays the stats of the game
void Game::displayStats()
{
    int hitPts = l[currLevelNum] -> getPlayer() -> getHitPts();
    int armor = l[currLevelNum] -> getPlayer() -> getArmorPts();
    int strength = l[currLevelNum] -> getPlayer() -> getStrengthPts();
    int dexterity = l[currLevelNum] -> getPlayer() -> getDexterityPts();
    cout << "Level: " << currLevelNum  << " Hit points: " << hitPts << " Armor: " << armor << " Strength: " << strength << " Dexterity: " << dexterity << endl;
}

void Game::play()
{
    //start the game
    l[currLevelNum] = new Level(1);
    l[currLevelNum] -> addObjectsToLevel();
    l[currLevelNum] -> addMonsterToLevel();
    l[currLevelNum] -> addStairsToLevel();
    l[currLevelNum] -> addPlayerToLevel();
    l[currLevelNum] -> printLevel();
    displayStats();

    
    while(!l[currLevelNum]->getPlayer() -> hasLost() && currLevelNum < 5) {
        if(trueWithProbability(0.1))
        {
             l[currLevelNum] -> getPlayer() -> increaseHitPts(l[currLevelNum] -> getPlayer());
        }
       clearScreen();
        if(currLevelNum < 4)
        {
            l[currLevelNum] -> printStairs();
        }
       
        l[currLevelNum] -> printObjects();
        l[currLevelNum] -> printPlayer(l[currLevelNum] -> getPlayer() -> getRowPos(), l[currLevelNum] -> getPlayer() -> getColPos());
        l[currLevelNum] -> printLevel();

        displayStats();

        // reduces sleep time 
        if(l[currLevelNum]-> getPlayer() -> isAsleep())
        {
            if(l[currLevelNum] -> getPlayer() -> getSleepTime() > 0)
            {
                l[currLevelNum]-> getPlayer() -> reduceSleepTime();
            }
        }

        // displaying action strings 
        cout << l[currLevelNum] -> getPlayer() -> getActionString() << endl;

        for(int i = 0; i < l[currLevelNum] -> getNumMonstersOnBoard(); i++)
        {
            cout << l[currLevelNum] -> getMonster(i) -> getActionString() << endl;
        }

        // setting action strings back to empty strings
         l[currLevelNum] -> getPlayer() -> setActionString("");
           for(int i = 0; i < l[currLevelNum] -> getNumMonstersOnBoard(); i++)
        {
            l[currLevelNum] -> getMonster(i) -> setActionString("");
        }

        char input = getCharacter();
       // char input = 'h';
        switch(input)
        {
            case 'i':
            if(l[currLevelNum] -> getPlayer() -> getSleepTime() > 0)
                {
                    monstersMove();
                    break;
                }
                clearScreen();
                l[currLevelNum] -> getPlayer() -> displayInventory();
                cin.get();
                clearScreen();
                // monsters move
                monstersMove();
                l[currLevelNum] -> printLevel();
                displayStats();
                break;
                
            case 'w':
            {
                if(l[currLevelNum] -> getPlayer() -> getSleepTime() > 0)
                {
                    monstersMove();
                    break;
                }
                l[currLevelNum] -> getPlayer() -> displayInventory();
                l[currLevelNum] -> getPlayer() -> switchWeapon(getCharacter());
               // monsters move
               monstersMove();
               
                break;
            }
                
            case 'c':
            {
                if(l[currLevelNum] -> getPlayer() -> getSleepTime() > 0)
                {
                    monstersMove();
                    break;
                }
                l[currLevelNum] -> getPlayer() -> cheat(l[currLevelNum] -> getPlayer());
                // monsters move
                monstersMove();
                break;
            }
                
            case 'q':
                exit(0);
                break;
            case 'g':
            {
                if(l[currLevelNum] -> getPlayer() -> getSleepTime() > 0)
                {
                    monstersMove();
                    break;
                }
                l[currLevelNum] -> getPlayer() -> pickUpGameObject(l[currLevelNum]);
                monstersMove();
                break;
            }
                
            case '>':
            {
                int stairRow = l[currLevelNum] -> getStairs() -> getRow();
                int stairCol = l[currLevelNum] -> getStairs() -> getCol();
                if(stairRow == l[currLevelNum] -> getPlayer() -> getRowPos() && stairCol == l[currLevelNum] -> getPlayer() -> getColPos())
                {
                    currLevelNum++;
                       if(currLevelNum < 4)
                        {
                            clearScreen();
                            l[currLevelNum] = new Level(currLevelNum);
                            l[currLevelNum] -> addObjectsToLevel();
                            l[currLevelNum] -> movePlayerToNextLevel(l[currLevelNum - 1] -> getPlayer(), l[currLevelNum]);
                             l[currLevelNum] -> addMonsterToLevel();
                            l[currLevelNum] -> addStairsToLevel();
                        }
                        else{
                            l[currLevelNum] = new Level(currLevelNum);
                            l[currLevelNum] -> addObjectsToLevel();
                            l[currLevelNum] -> movePlayerToNextLevel(l[currLevelNum - 1] -> getPlayer(), l[currLevelNum]);
                            l[currLevelNum] -> addMonsterToLevel();
                            }
                    l[currLevelNum] -> printLevel();
                    displayStats();
                    }
                    break;
                }
              
            case 'r':
            {
                if(l[currLevelNum] -> getPlayer() -> getSleepTime() > 0)
                {
                    monstersMove();
                    break;
                }
                l[currLevelNum] -> getPlayer() -> displayInventory();
                l[currLevelNum] -> getPlayer() -> readScroll(getCharacter());
                // monsters move
                monstersMove();
                break;
            }
             case ARROW_UP:
             case ARROW_DOWN:
             case ARROW_LEFT:
             case ARROW_RIGHT:

            {
                 if(l[currLevelNum] -> getPlayer() -> getSleepTime() > 0)
                {
                    monstersMove();
                    break;
                }
                //get player's current coordinates
                int currentRow = l[currLevelNum]->getPlayer()->getRowPos();
                int currentCol = l[currLevelNum]->getPlayer()->getColPos();
                
                int monsterCoord[2] = {-1,-1};
                //hits a wall
                if(l[currLevelNum]->getPlayer()->getCoordinatesForMove(input,currentRow, currentCol, monsterCoord) == -1)
                {
                    // monsters move
                    monstersMove();
                    break;
                }
                
                // hits a monster
                else if(l[currLevelNum]->getPlayer()->getCoordinatesForMove(input,currentRow, currentCol, monsterCoord) ==  0)
                {
                    // player hits monster
                    int monsterRow = monsterCoord[0];
                    int monsterCol = monsterCoord[1];

                  // applies damage to defender
                    for(int i = 0; i < l[currLevelNum] -> getNumberMonsters(); i++)
                    {
                        if(l[currLevelNum] -> getMonster(i) -> getRowPos() == monsterRow && l[currLevelNum] -> getMonster(i) -> getColPos() == monsterCol)
                        {
                           l[currLevelNum] -> getMonster(i) -> applyWeaponDamage(l[currLevelNum] -> getPlayer() -> getWeapon(), l[currLevelNum] -> getPlayer());
                           if(l[currLevelNum] -> getMonster(i) -> getHitPts() <= 0)
                                {
                                    l[currLevelNum] -> getMonster(i) -> hasLost(monsterRow, monsterCol, l[currLevelNum] -> getMonster(i), i);
                                }
                            // monsters move
                            monstersMove();
                            break;
                        }
                    } 
                    
                }
                
                // enters new space
                else if(l[currLevelNum]->getPlayer()->getCoordinatesForMove(input,currentRow, currentCol, monsterCoord) ==  1)
                {
                    clearScreen();
                    int newRow = l[currLevelNum]->getPlayer()->getRowPos();
                    int newCol = l[currLevelNum]->getPlayer()->getColPos();
                    l[currLevelNum]->setMaze(currentRow,currentCol,' ');
                    l[currLevelNum]->setMaze(newRow,newCol,'@');
                    // monsters move
                    monstersMove();
                    l[currLevelNum] -> printLevel();
                    displayStats();
                    break;
                }
                
            }
        }  
    }
}  

// move the monsters according to their type (using dynamic casting)
void Game::monstersMove()
{
     for(int i = 0; i < l[currLevelNum] -> getNumMonstersOnBoard(); i++)
     {
         Bogeyman* isBogey = dynamic_cast<Bogeyman*>(l[currLevelNum] -> getMonster(i));
         if (isBogey != nullptr)
         {
             isBogey -> move(l[currLevelNum] -> getPlayer() -> getRowPos(), l[currLevelNum] ->
                             getPlayer() -> getColPos(), 0, 5, 'B', isBogey);
         }
         
         SnakeWoman* isSnakeWoman = dynamic_cast<SnakeWoman*>(l[currLevelNum] -> getMonster(i));
         if (isSnakeWoman != nullptr)
         {
             isSnakeWoman -> move(l[currLevelNum] -> getPlayer() -> getRowPos(), l[currLevelNum] ->
                                  getPlayer() -> getColPos(), 0, 3, 'S', isSnakeWoman);
         }
         
         Dragon* isDragon = dynamic_cast<Dragon*>(l[currLevelNum] -> getMonster(i));
         if (isDragon != nullptr)
         {
             l[currLevelNum] -> monsterAttack(isDragon);
         }
         
         Goblin* isGoblin = dynamic_cast<Goblin*>(l[currLevelNum] -> getMonster(i));
         if(isGoblin != nullptr) {
             isGoblin -> generateTemplateMaze();
             isGoblin -> move(l[currLevelNum] -> getPlayer() -> getRowPos(), l[currLevelNum] ->
                              getPlayer() -> getColPos(), 0, m_goblinSmellDistance, 'G', isGoblin);
             isGoblin ->clearPath();
         }
     }
}

// deleting levels
Game::~Game()
{
    for(int i = 0; i <= 5; i++)
    {
        delete l[i];
    }
}    
        
        
        
        
        
        
    