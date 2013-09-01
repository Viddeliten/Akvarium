#ifndef THING_H
#define THING_H
#include "akvarium.h"
#include <allegro.h>

typedef struct thing
{
       int typ; //0=jord 1=rot 2=v�xt 3=v�xt�tare 4=k�tt�tare 5=as�tare 6=�gg
       int dead;
       int age;
       float dx, dy;
       float mdx, mdy;
       float max_vel;
       float weight;
       float energy; //G�r denna ner till noll d�r prylen 1% av massan blir energi hela tiden
       float min_weight;
       float poo; //1% av massan blir bajs hela tiden
       float max_age;
       float max_age_egg;
       
       int falling;
       
       int gonnabe;       
       int indicate_col;
       
       int moved;
       
} thing;

typedef struct thing_list
{
        int x, y, z;
        thing_list *previous;
        thing_list *next;
} thing_list;

thing *new_thing(struct AKVARIUM **ak, int typen, int start_e, int x, int y, int z);

#endif
