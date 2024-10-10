#ifndef ITEM_H
#define ITEM_H

#include "position.h"
#include "weapon.h"
// #include "potion.h"

typedef enum {WEAPON_TYPE, POTION_Type} ItemType;

typedef struct Item {
    ItemType type;
    Position* position;

    union {
        Weapon* weapon;
        // Potion* potion;
    } item;

    char string[256];
} Item;

// item factory
Item* createSword(int attack, int health);

#endif