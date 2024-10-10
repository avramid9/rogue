#ifndef MONSTER_H
#define MONSTER_H

#include "position.h"

typedef struct Monster {
    char string[2];
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    int pathfinding;
    int alive;
    Position* position;
} Monster;

// monster functions
Monster* selectMonster(int level);
Monster* createMonster(char symbol, int health, int attack, int speed, int defence, int pathfinding);
int pathFindingSeek(Position* start, Position* destination);
int pathFindingRandom(Position* position);
Monster* getMonsterAt(Position* position, Monster** monsters);
int killMonster(Monster* monster);
void drawMonster(Monster* monster);

#endif
