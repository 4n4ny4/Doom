

#ifndef GameObject_hpp
#define GameObject_hpp
#include <string>

class Level;
class Player;
class GameObject
{
public:
    GameObject(Level* level);
    int getRow() const;
    int getCol() const;
    bool setObjectPosition(int row, int col);
    std::string getObjectName();
    virtual ~GameObject();
    
    
private:
    int m_row;
    int m_col;
    Level *m_level;
    std::string objectName;
    
};

class Weapon: public GameObject
{
public:
    // common weapon points-related functions
    Weapon(Level *level, int dexterity, int damage, std::string weaponName, std::string actionAndWeapon);
    int getDexterityBonus() const;
    int getDamageAmount() const;
    // weapon name-related functions
    std::string getWeaponName() const;
    std::string getWeaponAndActionName() const;
    virtual ~Weapon();
    
private:
    int m_dexterityBonus;
    int m_damageAmt;
    std::string m_WeaponName;
    std::string m_actioAndWeapon;
};


class Maces: public Weapon
{
public:
    Maces(Level *level);
};

class shortSwords: public Weapon
{
public:
    shortSwords(Level *level);
};

class longSwords: public Weapon
{
public:
    longSwords(Level *level);
};

class magicAxes: public Weapon
{
public:
    magicAxes(Level *level);
};

class magicFangs: public Weapon
{
public:
    magicFangs(Level *level);
private:
    int m_sleepTime;
};



//*********SCROLL FUNCTIONS*********

class Scroll: public GameObject

{
public:
    Scroll(Level *level, std::string scrollName);
    std::string getScrollName();
private:
    std::string m_scrollName;
};

class teleportationScroll: public Scroll{
public:
    teleportationScroll(Level *level);
};

class improveArmorScroll: public Scroll{
public:
    improveArmorScroll(Level *level);
};

class raiseStrengthScroll: public Scroll{
public:
    raiseStrengthScroll(Level *level);
};

class enhanceHealthScroll: public Scroll{
public:
    enhanceHealthScroll(Level *level);
};

class enhanceDexterityScroll: public Scroll{
public:
    enhanceDexterityScroll(Level *level);
};

class GoldenIdol: public GameObject
{
public:
    GoldenIdol(Level *l);
};

class Stairs: public GameObject
{
public:
    Stairs(Level *l);
};


#endif /* GameObject_hpp */
