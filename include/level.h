#ifndef LEVEL_H
#define LEVEL_H

#include "position.h"
#include "monster.h"
#include "player.h"
#include "room.h"

typedef struct Level {
    char** tiles;
    int level;
    int numberOfRooms;
    struct Room** rooms;
    struct Monster** monsters;
    int numberOfMonsters;
    struct Player* user;
} Level;

// level functions
Level* createLevel(int level);
void drawLevel(Level* level);
Room** roomsSetUp();
char** saveLevelPositions();
void connectDoors(Level* level);

int addMonsters(Level* level);
int moveMonsters(Level* level);

int checkPosition(Position* newPosition, Level* level);

#endif
