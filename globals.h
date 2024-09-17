
#ifndef globals_h
#define globals_h

const int LEVELROWS = 18;
const int LEVELCOLS = 70;
const int MAXINVENTORYSIZE = 25;
const int MAXLEVELS = 5;

enum ObjectStore{
    MACES = 0,
    SHORTSWORDS = 1,
    LONGSWORDS = 2,
    IMPROVEARMORSCROLL = 3,
    RAISESTRENGTHSCROLL = 4,
    ENHANCEHEALTHSCROLL = 5,
    ENHANCEDEXTERITYSCROLL = 6,
    TELEPORTATIONSCROLL = 7,
    MAGICFANGS = 8,
    MAGICAXES = 9,
    GOLDENIDOL = 10
};

enum MonstersStore{
    SNAKEWOMAN = 0,
    GOBLINS = 1,
    BOGEYMEN = 2,
    DRAGONS = 3,
};
#endif /* globals_h */
