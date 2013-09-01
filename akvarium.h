#ifndef AKVARIUM_H
#define AKVARIUM_H
#include "thing.h"
#include "main.h"

typedef struct AKVARIUM {
        struct thing *th[DEPTH]; //DEPTH antal saker får plats på varje ruta
        struct plant_list *plants;
}AKVARIUM;

void check_things(AKVARIUM **ak);
void move_things(AKVARIUM **ak);
void draw_things(AKVARIUM **ak);
void move_thing(AKVARIUM **ak, thing **ppt, int x, int y, int z);
void move_aseater(AKVARIUM **ak, thing *pt, int x, int y, int z);
void move_carnivore(AKVARIUM **ak, thing *pt, int x, int y, int z);
void move_herbivore(AKVARIUM **ak, thing *pt, int x, int y, int z);
void move_plant(AKVARIUM **ak, thing *pt, int x, int y, int z);
void energy_in_creature(AKVARIUM **ak,thing *pt, int x, int y, int z);
void make_poo(AKVARIUM **ak, thing *pt, int x, int y, int z);
void move_egg(AKVARIUM **ak, thing *pt, int x, int y, int z);
void new_plant(AKVARIUM **ak);

#endif
