#include "akvarium.h"
#include "plant.h"

void new_plant(AKVARIUM **ak)
{
     plant **ppt;
     plant_list **ppl;
     int x,y,z;
     
     //Skapa en planta
     *ppt=(plant *)calloc(1,sizeof(plant));

     //l�gg in en lista f�r gr�nt.
     (*ppt)->green=(thing_list *)calloc(1,sizeof(thing_list));

     //Skapa en gr�n d�r.
     x=rand()%s_w;
     y=rand()%s_h;
     z=rand()%DEPTH;

     new_thing(ak, 2, START_ENERGY_PLANT, x, y, z);
     
     (*ppt)->green->x=x;
     (*ppt)->green->y=y;
     (*ppt)->green->z=z;
     
     //l�gg in en lista f�r rot.
     (*ppt)->root=NULL;

     //L�gg till i akvariet
     ppl=&(*ak)->plants;
     while(*ppl!=NULL)
         ppl=&((*ppl)->next);

     *ppl=(plant_list *)calloc(1,sizeof(plant_list));
     (*ppl)->p=*ppt;
     (*ppl)->next=NULL;
     
       //G�r bmp svart
       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
       //Skriv ut text
       textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Creating plant... 7");
       //rita ut bilden p� sk�rmen
       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              
       //V�nta p� knapptryckning
           while(!key[KEY_ESC] && !key[KEY_SPACE]);
           while(!key[KEY_ESC] && key[KEY_SPACE]);    
}

void move_plants(plant_list *pp)
{
     if(pp!=NULL)
     {
              plant_grow(pp->p);
              plant_fall(pp->p);
              move_plants(pp->next);
     }
}

void plant_grow(AKVARIUM *ak, plant *p)
{
     thing_list **tpp;
     //Kolla om vi har alla pixlar
     tpp=&(p->green);
     while(*tpp!=NULL)
     {
         if(ak[(*tpp)->x][(*tpp)->y]->th[(*tpp)->z]==NULL || ak[(*tpp)->x][(*tpp)->y]->th[(*tpp)->z]->typ!=2)
         {
             //Det �r inte en v�xt d�r det borde
             plant_breakoff(tpp);
         }
     }
}

void plant_fall(plant *p)
{
}
