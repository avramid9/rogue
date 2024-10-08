#ifndef ROOM_H
#define ROOM_H

#include "monster.h"
#include "player.h"
#include "position.h"
#include "door.h"

typedef struct Room {
    Position position;
    int height;
    int width;

    struct Door** doors;
    int numberOfDoors;
    // Monter** monsters;
    // Item** items;
} Room;

// room functions
Room* createRoom(int grid, int numberOfDoors);
int drawRoom(Room* room);

int placePlayer(Room** rooms, Player* user);
int setStartingPosition(Monster* monster, Room* room);

#endif