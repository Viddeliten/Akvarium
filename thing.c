#include "akvarium.h"
#include "thing.h"

#include <MT.h>

thing *new_thing(struct AKVARIUM **ak, int typen, int start_e, int x, int y, int z)
{
   int nx, ny, nz, empty;
   thing **ppt;
   MTRand mtrand1;          

   
   empty=0;
   while(!empty)
   {
       //Skaffa random koordinater
       x=mtrand1.randInt(s_w-1);
       y=mtrand1.randInt(s_h-1);
       
  
       for(z=0;z<DEPTH && !empty;z++)
       {
           //kolla om det är ledigt där och skapa isf en sak där
           if(ak[x][y].th[z]==NULL)
           {
               ppt=&(ak[x][y].th[z]);
               empty=1;
           }
       }
   }
   
   *ppt=(thing *)calloc(1,sizeof(thing));
   (**ppt).typ=typen;
   
    (**ppt).max_vel=2;
    (**ppt).weight=START_WEIGHT;
    (**ppt).energy=start_e;
    
    if(typen==0)
        (**ppt).indicate_col=POO;
    else if(typen==1)
        (**ppt).indicate_col=ENERGY_TO_MAKE_ROOT;
    else if(typen==2)
        (**ppt).indicate_col=ENERGY_TO_MAKE_PLANT*2;
    else if(typen==3)
    {   
        (**ppt).indicate_col=ENERGY_TO_MAKE_H;
        (**ppt).max_age=MAX_AGE_H;
        (**ppt).max_age_egg=MAX_AGE_EGG_H;
    }
    else if(typen==4)
    {   
        (**ppt).indicate_col=(int)(ENERGY_TO_MAKE_C);
        (**ppt).max_age=MAX_AGE_C;
    }
    else if(typen==5)
    {   
        (**ppt).indicate_col=(int)(ENERGY_TO_MAKE_A);
        (**ppt).max_age=MAX_AGE_A;
        (**ppt).max_age_egg=MAX_AGE_EGG_A;
    }
    
    return *ppt;
}
