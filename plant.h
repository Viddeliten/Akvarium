#ifndef PLANT_H
#define PLANT_H

typedef struct plant
{
        thing_list *green;
        thing_list *root;
}plant;

typedef struct plant_list
{
    plant *p;
    plant_list *next;
}plant_list;

void new_plant(AKVARIUM **ak);
void move_plants(plant_list *pp);
void plant_grow(plant *p);
void plant_fall(plant *p);

#endif
