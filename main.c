#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

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
    Position position;
    int health;
    // Room* room;
} Player;

int screenSetUp();
Room** mapSetUp();
Player* playerSetUp();
int handleInput(int input, Player* user);
int checkPosition(int newY, int newX, Player* user);
int playerMove(int y, int x, Player* user);

/* room functions */
Room* createRoom(int y, int x, int height, int width);
int drawRoom(Room* room);

int main() {
    Player* user;
    int ch;

    screenSetUp();

    mapSetUp();

    user = playerSetUp();

    // main game loop
    while ((ch = getch()) != 'q') {
        handleInput(ch, user);
    }
    
    endwin();

    return 0;
}

int screenSetUp() {
    initscr();
    printw("Hello World!");
    noecho();
    refresh();
    srand(time(NULL));

    return 1;
}

Room** mapSetUp() {
    Room** rooms;
    rooms = malloc(sizeof(Room)*6);
    // mvprintw(13, 13, "--------");
    // mvprintw(14, 13, "|......|");
    // mvprintw(15, 13, "|......|");
    // mvprintw(16, 13, "|......|");
    // mvprintw(17, 13, "|......|");
    // mvprintw(18, 13, "--------");

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    // mvprintw(2, 40, "--------");
    // mvprintw(3, 40, "|......|");
    // mvprintw(4, 40, "|......|");
    // mvprintw(5, 40, "|......|");
    // mvprintw(6, 40, "|......|");
    // mvprintw(7, 40, "--------");

    rooms[1] = createRoom(2, 40, 6, 8);
    drawRoom(rooms[1]);

    // mvprintw(10, 40, "------------");
    // mvprintw(11, 40, "|..........|");
    // mvprintw(12, 40, "|..........|");
    // mvprintw(13, 40, "|..........|");
    // mvprintw(14, 40, "|..........|");
    // mvprintw(15, 40, "------------");

    rooms[2] = createRoom(10, 40, 6, 12);
    drawRoom(rooms[2]);

    return rooms;
}

Room* createRoom(int y, int x, int height, int width) {
    Room* newRoom = malloc(sizeof(Room));

    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;

    newRoom->doors = malloc(sizeof(Position) * 4);

    // top door
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->doors[0]->y = newRoom->position.y;

    // bottom door
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->doors[1]->y = newRoom->position.y + newRoom->height - 1;

    // left door
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->x = newRoom->position.x;
    newRoom->doors[2]->y = rand() % (height - 2) + newRoom->position.y + 1;

    // right door
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->x = newRoom->position.x + newRoom->width - 1;
    newRoom->doors[3]->y = rand() % (height - 2) + newRoom->position.y + 1;

    return newRoom;
}

int drawRoom(Room* room) {
    int x;
    int y;

    // draw top and bottom
    for (x = room->position.x; x < room->position.x + room->width; x++) {
        mvprintw(room->position.y, x, "-"); //top
        mvprintw(room->position.y + room->height - 1, x, "-"); //bottom
    }

    // draw floors and side walls
    for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
        // draw side walls
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");

        // draw floors
        for (x = room->position.x + 1; x < room->position.x + room-> width - 1; x++) {
            mvprintw(y, x, ".");
        }
    }

    // draw doors
    for (int i = 0; i < 4; i++) {
        mvprintw(room->doors[i]->y, room->doors[i]->x, "+");
    }

    return 1;
}

Player* playerSetUp() {
    Player* newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->position.y = 14;
    newPlayer->position.x = 14;
    newPlayer->health = 20;

    playerMove(newPlayer->position.y, newPlayer->position.x, newPlayer);

    return newPlayer;
}

int handleInput(int input, Player* user) {
    int newY;
    int newX;

    switch (input) {
        // move up
        case 'w':
        case 'W':
            newY = user->position.y - 1;
            newX = user->position.x;
            break;

        // move down
        case 's':
        case 'S':
            newY = user->position.y + 1;
            newX = user->position.x;
            break;

        // move left
        case 'a':
        case 'A':
            newY = user->position.y;
            newX = user->position.x - 1;
            break;

        // move right
        case 'd':
        case 'D':
            newY = user->position.y;
            newX = user->position.x + 1;
            break;

        default:
            break;
    }

    checkPosition(newY, newX, user);
}

// Check what is at next position
int checkPosition(int newY, int newX, Player* user) {
    int space;

    switch (mvinch(newY, newX)) {
        case '.':
            playerMove(newY, newX, user);
            break;
        default:
            move(user->position.y, user->position.x);
            break;
    }
}

int playerMove(int y, int x, Player* user) {
    mvprintw(user->position.y, user->position.x, ".");
    
    user->position.y = y;
    user->position.x = x;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x);
}