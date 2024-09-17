
#include "GameObject.h"
#include "globals.h"
#include "utilities.h"
#include "Level.h"
#include "Actors.h"
#include <iostream>

using namespace std;

GameObject::GameObject(Level *level): m_row(randInt(1,LEVELCOLS - 1)), m_col(randInt(1,LEVELCOLS - 1)), m_level(level)
{
    if (level == nullptr)
    {
        cout << "The game object must be created in some level!" << endl;
        exit(1);
    }
    
    // checking if game object in bounds
    while(!level -> isInBounds(m_row, m_col))
    {
        m_row = randInt(1,LEVELCOLS - 1);
        m_col = randInt(1,LEVELCOLS - 1);
    }
}

int GameObject::getRow() const
{
    return m_row;
}

int GameObject::getCol() const
{
    return m_col;
}

std::string GameObject::getObjectName()
{
    return objectName;
}


// setters have checks to make sure its put in a valid state (in bounds of maze)
 bool GameObject::setObjectPosition(int row, int col)
 {
    if (m_level -> isInBounds(row, col))  
    {
          m_row = row;
          m_col = col;
          return true;
    }  
    return false;
 }


GameObject::~GameObject()
{

}

// ******WEAPONS******

Weapon::Weapon(Level *level, int dexterity, int damage, std::string weaponName,std::string weaponAndAction):GameObject(level),m_dexterityBonus(dexterity), m_damageAmt(damage), m_WeaponName(weaponName), m_actioAndWeapon(weaponAndAction)
{
}

string Weapon::getWeaponAndActionName() const
{
    return m_actioAndWeapon;
}

int Weapon::getDexterityBonus() const
{
    return m_dexterityBonus;
}

int Weapon::getDamageAmount() const{
    return m_damageAmt;
}

std::string Weapon::getWeaponName() const
{
    return m_WeaponName;
}

Weapon::~Weapon()
{}


// WEAPON TYPES (constructors)
Maces::Maces(Level *level):Weapon(level, 0, 2, "a Mace", " swings mace at ")
{
}
shortSwords::shortSwords(Level *level):Weapon(level, 0, 2, "a short sword", " slashes short sword at ")
{
}

longSwords::longSwords(Level *level):Weapon(level, 2, 4, "a long sword", " swings long sword at ")
{
}

magicAxes::magicAxes(Level *level): Weapon(level, 5, 5, "a magic axe", " chops magic axe at ")
{
}

magicFangs::magicFangs(Level *level): Weapon(level, 3, 2, "a magic fang", " strikes magic fangs at ")
{
}


// *****SCROLLS*********

Scroll::Scroll(Level *level, std::string scrollName): GameObject(level), m_scrollName(scrollName)
{

}

std::string Scroll::getScrollName()
{
    return m_scrollName;
}
//teleporation Scroll Functions
teleportationScroll::teleportationScroll(Level *level):Scroll(level, "scroll of teleportation")
{
}


// Improve Armor Scroll Functions
improveArmorScroll::improveArmorScroll(Level *level):Scroll(level, "scroll of enhance armor" )
{
    
}


//raise Strength Scroll Functions
raiseStrengthScroll::raiseStrengthScroll(Level *level):Scroll(level, "scroll of strength")
{}


// enhance Health Scroll Functions
enhanceHealthScroll::enhanceHealthScroll(Level *level): Scroll(level, "scroll of enhance health")
{}



// enhance dexterity Scroll Functions
enhanceDexterityScroll::enhanceDexterityScroll(Level *level): Scroll(level, "scroll of enhance dexterity")
{}


//*************GOLDEN IDOL******************
GoldenIdol::GoldenIdol(Level *l): GameObject(l)
{
    
}

//*************STAIRS******************

Stairs::Stairs(Level *l): GameObject(l)
{
}

























