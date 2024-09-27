#ifndef ROGUE_H
#define ROGUE_H

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct Level {
    char** tiles;
    int level;
    int numberOfRooms;
    struct Room** rooms;
    struct Monster** monsters;
    int numberOfMonsters;
    struct Player* user;
} Level;

typedef struct Position {
    int x;
    int y;
    // TILE_TYPE tile;
} Position;

typedef struct Room {
    Position position;
    int height;
    int width;

    Position** doors;
    // Monter** monsters;
    // Item** items;
} Room;

typedef struct Player {
    Position* position;
    int health;
    int attack;
    // Room* room;
} Player;

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

int screenSetUp();

// level functions
Level* createLevel(int level);
Room** roomsSetUp();
char** saveLevelPositions();

// player functions
Player* playerSetUp();
Position* handleInput(int input, Player* user);
int checkPosition(Position* newPosition, Level* level);
int playerMove(Position* newPosition, Player* user, char** level);

// room functions
Room* createRoom(int y, int x, int height, int width);
int drawRoom(Room* room);
int connectDoors(Position* doorOne, Position* doorTwo);

// monster functions
int addMonsters(Level* level);
Monster* selectMonster(int level);
Monster* createMonster(char symbol, int health, int attack, int speed, int defence, int pathfinding);
int setStartingPosition(Monster* monster, Room* room);
int moveMonsters(Level* level);
int pathFindingSeek(Position* start, Position* destination);
int pathFindingRandom(Position* position);
Monster* getMonsterAt(Position* position, Monster** monsters);
int killMonster(Monster* monster);


int combat(Player* player, Monster* monster, int order);

#endif
