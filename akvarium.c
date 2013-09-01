#include "akvarium.h"
#include "thing.h"
#include "plant.h"
#include <MT.h>

thing *new_spec_thing(AKVARIUM **ak, int typen, int x, int y, int z)
{
   thing **ppt;
   
   //kolla om det är ledigt där och skapa isf en sak där
   if(ak[x][y].th[z]==NULL)
   {
       ppt=&(ak[x][y].th[z]);
   
        *ppt=(thing *)calloc(1,sizeof(thing));
        (**ppt).typ=typen;
        
        (**ppt).max_vel=1;
        (**ppt).weight=300;
        (**ppt).energy=500;
        
    if(typen==0)
        (**ppt).indicate_col=POO;
    else if(typen==1)
        (**ppt).indicate_col=ENERGY_TO_MAKE_ROOT;
    else if(typen==2)
        (**ppt).indicate_col=ENERGY_TO_MAKE_PLANT*2;
    else if(typen==3)
        (**ppt).indicate_col=ENERGY_TO_MAKE_H;
    else if(typen==4)
        (**ppt).indicate_col=(int)(ENERGY_TO_MAKE_C);
    else if(typen==4)
        (**ppt).indicate_col=(int)(ENERGY_TO_MAKE_A);

        return *ppt;
   }
   else
       return NULL;
}

int puffa(AKVARIUM **ak,int x, int y, int z)
{
    //Gör utrymme genom att puffa upp saker ovanför där vi har tänkt göra så att det blir tomt!
    int i, j, k;
    int fe;
    int ny;

//       //Gör bmp svart
//       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
//       //Skriv ut text
//       textprintf_ex(bmp, font, 0, 12, makecol(0, 100, 243), -1,  "puffa %d %d %d",x,y,z);
//       //rita ut bilden på skärmen
//       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h); 

    //Leta först upp ett tomt utrymme ovanför koordinaterna
    fe=0;
    for(j=y;j>=0 && !fe;j--)
    {
        if(ak[x][j].th[z]==NULL)
        {
            fe=1;
            ny=j;
        }
    }

    //Om det fanns utrymme för att puffa
    if(fe!=0)
    {
          while(ny<y)
          {
              //Flytta saken nedanför hit.
              ak[x][ny].th[z]=ak[x][ny+1].th[z];
              ak[x][ny+1].th[z]=NULL;
              
              ny++;
          }
          return 1;
    }
    else
        return 0;
}             

void move_things(AKVARIUM **ak)
{
     //Gå igenom alla rutor och flytta saker
     
     int x,y,z;
     int vx,vy,vz;
     int i,j,k;
     thing *pt;
     int found;

     for(x=0;x<s_w;x++)
     {
         for(y=s_h-1;y>=0;y--)
         {
             for(z=0;z<DEPTH;z++)
             {
                 //Se om det finns nåt på den rutan
                 if(ak[x][y].th[z]!=NULL)
                 {
                     ak[x][y].th[z]->moved=0;
                 }
             }
         }
     }
     
     for(x=0;x<s_w;x++)
     {
         for(y=0;y<s_h;y++)
         {
             for(z=0;z<DEPTH;z++)
             {
                 //Se om det finns nåt på den rutan
                 pt=NULL;
                 if(ak[x][y].th[z]!=NULL)
                 {
                     pt=ak[x][y].th[z];
                     if(pt->moved==0)
                     {
                         pt->moved=1;

//       //Gör bmp svart
//       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
//       //Skriv ut text
//       textprintf_ex(bmp, font, 0, 12, makecol(0, 100, 243), -1,  "move thing %d", pt->typ);
//       //rita ut bilden på skärmen
//       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h); 
                         
                         if(pt->typ==0)
                         {
                             //Jord faller alltid neråt
                             pt->dy+=0.2;
                             pt->dx=wind;
                         }
                         else if(pt->typ==1 || pt->typ==2)
                         {
                              //Bara döda växter ska röra sig just här
                              //if(!pt->dead)
                                  //Växter har en massa hyss för sig! =)
                                  //move_plant(ak, pt, x, y, z);
                              if(pt->dead)
                              {
                                  pt->dy-=0.1;
                                  pt->dx+=wind;
                              }
                         }
                         else if(pt->typ>=3 && pt->dead)
                         {
                             //döda djur flyter
                             pt->dy-=0.2;
                             pt->dx=wind;
                         }
                         else if(pt->typ==3)
                         {
                             //växtätare äter gräs eller flyttar mot gräs eller från köttätare
                             move_herbivore(ak, pt, x, y, z);
                         }
                         else if(pt->typ==4)
                         {
                             //köttätare äter eller flyttar mot en växtätare som den kan se
                             move_carnivore(ak, pt, x, y, z);
                         }
                         else if(pt->typ==5)
                         {
                             //asätare äter eller flyttar mot en döing som den kan se
                             move_aseater(ak, pt, x, y, z);
                         }
                         else if(pt->typ==6)
                         {
                             //ägg flyter mest omkring
                             move_egg(ak, pt, x, y, z);
                         }
                         
//       //Gör bmp svart
//       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
//       //Skriv ut text
//       textprintf_ex(bmp, font, 0, 12, makecol(0, 100, 243), -1,  "about to move thing %d", pt->typ);
//       //rita ut bilden på skärmen
//       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h); 

                         move_thing(ak, &pt, x, y, z);
                         if(pt->typ>=3 && !pt->dead)
                         {
                             if(pt->typ!=6)
                                 make_poo(ak,pt,x,y,z);
                             pt->age++;
                         }
                         
                         //Rör på växter
                         move_plants( (*ak)->plants);
                         
                         //pyffa slumpmässigt
//                         puffa(ak,rand()%s_w,s_h-1,rand()%2);
//       //Gör bmp svart
//       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
//       //Skriv ut text
//       textprintf_ex(bmp, font, 0, 12, makecol(0, 100, 243), -1,  "moved thing %d", pt->typ);
//       //rita ut bilden på skärmen
//       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h); 
                     }
                 }
             }
         }
     }
}

void move_thing(AKVARIUM **ak, thing **ppt, int x, int y, int z)
{
     int dx, dy, nx, ny;
     
//       //Gör bmp svart
//       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
//       //Skriv ut text
//       textprintf_ex(bmp, font, 0, 12, makecol(0, 100, 243), -1,  "move_thing");
//       //rita ut bilden på skärmen
//       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h); 
             

     //Kolla så att saken inte försöker röra sig fortare än max_vel
     while(sqrt((*ppt)->dx*(*ppt)->dx+(*ppt)->dy*(*ppt)->dy) > (*ppt)->max_vel)
     {
         (*ppt)->dx=(*ppt)->dx*0.9;
         (*ppt)->dy=(*ppt)->dy*0.9;
     }
     
     //Skaffa rörelse
    (*ppt)->mdx+=(*ppt)->dx;
    (*ppt)->mdy+=(*ppt)->dy;

     dx=(int)(*ppt)->mdx;
     dy=(int)(*ppt)->mdy;
     
     if(dy!=0 || dx!=0)
     {
         //Kolla så att det inte är något ivägen
         nx=x+dx;
         ny=y+dy;
         
         //Kolla kanter
         if(nx>=s_w-1)
         {
             nx=s_w-1;
             (*ppt)->dx=0;
         }
         else if(nx<=0)
         {
             nx=0;
             (*ppt)->dx=0;
         }
         if(ny>=s_h-1)
         {
             ny=s_h-1;
             (*ppt)->dy=0;
         }
         else if(ny<=0)
         {
             ny=0;
             (*ppt)->dy=0;
         }
         
         //Kolla så att det finns utrymme och flytta isf
         if(ak[nx][ny].th[0]==NULL)
         {
            (*ppt)->mdx-=dx;
            (*ppt)->mdy-=dy;
            ak[nx][ny].th[0]=*ppt; 
            ak[x][y].th[z]=NULL; 
         }
         else if(ak[nx][ny].th[1]==NULL)
         {
            (*ppt)->mdx-=dx;
            (*ppt)->mdy-=dy;
            ak[nx][ny].th[1]=*ppt;
            ak[x][y].th[z]=NULL; 
         }
         else
         {
             (*ppt)->dx=0;
             (*ppt)->dy=0;
             (*ppt)->mdx=0;
             (*ppt)->mdy=0;
         }
     }
     else
     {
         nx=x;
         ny=y;
     }
     
     if((*ppt)->typ!=6)
         energy_in_creature(ak,*ppt,x,y,z);

}

void move_egg(AKVARIUM **ak, thing *pt, int x, int y, int z)
{
     int found, i,j,k;
     
//     if((pt->gonnabe==3 && pt->age>pt->max_age_egg MAX_AGE_EGG_H) || (pt->gonnabe==5 && pt->age>MAX_AGE_EGG_A))
     if(pt->gonnabe==3 && pt->age>pt->max_age_egg)
     {
         pt->typ=pt->gonnabe;
         pt->age=0;
         if(pt->typ==5)
             pt->indicate_col=(int)(ENERGY_TO_MAKE_A);
         if(pt->typ==3)
             pt->indicate_col=(int)(ENERGY_TO_MAKE_H);
     }
     else
     {
         //Driv omkring om ägget inte ligger bredvid en växt
         found=0;
         
         for(i=-1;i<2;i++)
         {
             for(j=-1;j<2;j++)
             {
                 for(k=0;k<2;k++)
                 {
                     if(x+i>=0 && x+i<s_w && y+j>=0 && y+j<s_h && 
                     ak[x+i][y+j].th[k]!=NULL && 
                     (ak[x+i][y+j].th[k]->typ==1 || ak[x+i][y+j].th[k]->typ==2))
                         found=1;
                 }
             }
         }
         
         if(!found)
         {
             pt->dx+=wind;
         }
         else
         {
             pt->dx=0;
             pt->mdx=0;
         }
     }
}

void move_plant(AKVARIUM **ak, thing *pt, int x, int y, int z)
{
     int found_fall, found_plant, found_earth;
     int vx, vy, vz;
     int i,j,k;
     int nx, ny, nz;
     int nytyp;
     float e;
     thing *nv;
     
     //Växter och rötter faller neråt om de inte har några växtgrannar bredvid eller under sig
     found_fall=0;
     found_plant=0; //Växter vill göra mer grönt om det finns färre än 3 växter runt
     found_earth=0; //Växter vill göra mer rot om det finns färre än 4 växter runt samt jord någonstans runt
     
     vx=x-1;
     vy=y-1;
     vz=0;
     //Kolla vad som finns runtomkring
     for(i=-1;i<2;i++)
     {
         for(j=-1;j<2;j++)
         {
             for(k=0;k<2;k++)
             {
                 if(x+i>=0 && x+i<s_w
                 && y+j>=0 && y+j<s_h
                 && !(i==0 && j==0 && k==z))
                 {
                     if(ak[x+i][y+j].th[k]!=NULL
                     && !ak[x+i][y+j].th[k]->dead
                     && (ak[x+i][y+j].th[k]->typ==1
                     || ak[x+i][y+j].th[k]->typ==2))
                     {
                         
                         found_plant++; //Växt i anslutande ruta
                         if(j>0)
                            found_fall++; //Växt som förhindrar fall
                     }
                     if(ak[x+i][y+j].th[k]!=NULL
                     && ak[x+i][y+j].th[k]->typ==0)
                     {
                         found_earth++;
                         found_fall++;
                     }
                 }
             }
         }
     }

     //Växter blir rötter om de har en jord på sig
     k=(z+1)%2;
     if(ak[x][y].th[k]!=NULL && ak[x][y].th[k]->typ==0)
         pt->typ=1;

     if(!found_fall && y<s_h-1)
     {
         //Ramla neråt och gör inget annat
         pt->dy+=0.1;
         pt->dx=wind;
         pt->falling=20;

     }
     else
           pt->falling--;

     if(pt->falling<=0 && (found_plant>0 || found_earth>0))
     {
         //det finns lite grannar, så vi kan växa och sno energi
         //energi först, men bara om vi har dåligt med det!
         if(pt->energy<MIN_ENERGY)
         {
             for(i=-1;i<2;i++)
             {
                 for(j=-1;j<2;j++)
                 {
                     for(k=0;k<2;k++)
                     {
                         if(x+i>=0 && x+i<s_w
                         && y+j>=0 && y+j<s_h
                         && !(i==0 && j==0 && k==z))
                         {
                             if(ak[x+i][y+j].th[k]!=NULL)
                             {
                                 if(ak[x+i][y+j].th[k]->typ==1
                                 || (ak[x+i][y+j].th[k]->typ==2 && pt->typ==2))
                                 {
                                     //Ta lite energi från en växtgranne
                                     pt->energy+=ak[x+i][y+j].th[k]->energy/5;
                                     ak[x+i][y+j].th[k]->energy-=ak[x+i][y+j].th[k]->energy/5;
                                 }
                                 if(pt->typ==1 && ak[x+i][y+j].th[k]->typ==0)
                                 {
                                     //Ta lite energi från en jord bredvid
                                     e=ak[x+i][y+j].th[k]->energy/PLANT_DIVIDER;
                                     pt->energy+=e;
                                     ak[x+i][y+j].th[k]->energy-=e;
                                     
                                     if(ak[x+i][y+j].th[k]->energy<3)
                                     {
                                         //Döda jorden om det är för lite kvar
                                         free(ak[x+i][y+j].th[k]);
                                         ak[x+i][y+j].th[k]=NULL;
                                     }   
                                 }
                             }
                         }
                     }
                 }
             }
         }
         
         //Det kostar lite energi per vikt att existera
         pt->energy-=pt->weight/PLANT_COST;
         
         //Växa
         //Omvandla först lite energi till vikt!
         pt->weight+=pt->energy/100;
         pt->energy-=pt->energy/50;
         
         nytyp=0;
         //KOlla om vi vill göra en rot först
         if(found_plant<5 && found_earth && pt->energy>ENERGY_TO_MAKE_ROOT)
         {
             nytyp=1;
         }
         else if(found_plant<4 && pt->energy>ENERGY_TO_MAKE_PLANT)
         {
              nytyp=2;
         }
         
         if(nytyp!=0)
         {
             ny=y+(rand()%3)-1;
             nx=x+(rand()%3)-1;
             if(nx>=0 && nx<s_w
             && ny>=0 && ny<s_h)
             {
                 if((nytyp==2 &&  ak[nx][ny].th[z]==NULL) || (nytyp==1 && puffa(ak,nx,ny,z)))
                 {
                    nv=NULL;
                    //Skapa mer växt eller rot!
                    nv=new_spec_thing(ak,nytyp,nx,ny,z);
                    if(nv!=NULL)
                    {
    //       //Gör bmp svart
    //       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
    //       //Skriv ut text
    //       textprintf_ex(bmp, font, 0, 12, makecol(0, 100, 243), -1,  "plant grew %d",nytyp);
    //       //rita ut bilden på skärmen
    //       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h); 
                        nv->energy=pt->energy/2;
                        pt->energy/=2;
    
                        nv->weight=pt->weight/3;
                        pt->weight-=pt->weight/3;
    
                    }
                 }
             }
         }
    }   
    pt->moved=1;
}

void move_aseater(AKVARIUM **ak, thing *pt, int x, int y, int z)
{
     int ez;
     int found;
     int fdy, fdx, nfdy, nfdx;
     int i, j, k;
     MTRand mtrand1;
     thing *nt;

     
     ez=(z+1)%2;
     if(pt->age>pt->max_age)
     {
        pt->dead=1;
     }
     else if(ak[x][y].th[ez]!=NULL
     && ak[x][y].th[ez]->typ>=2
     && ak[x][y].th[ez]->dead) //Se om vi kan äta ett offer
     {
         //ta dens massa!
         pt->weight+=ak[x][y].th[ez]->weight*ENERGY_LOSS;
         pt->weight+=ak[x][y].th[ez]->poo*ENERGY_LOSS;
                  
         //Döda
         free(ak[x][y].th[ez]);
         ak[x][y].th[ez]=NULL;
         
         //Har vi stannat för att äta får vi stå still
         ak[x][y].th[z]->dx=0;
         ak[x][y].th[z]->dy=0;
         ak[x][y].th[z]->mdx=0;
         ak[x][y].th[z]->mdy=0;
     }
     else if(pt->energy>ENERGY_TO_MAKE_A && ak[x][y].th[(z+1)%2]==NULL)
     {
          //Om vi har en massa överskottsenergi och det finns plats förökar vi oss
          nt=new_spec_thing(ak,6,x,y,(z+1)%2);
          if(nt!=NULL)
          {
              nt->weight=pt->weight/2;
              pt->weight=pt->weight/2;
              nt->energy=pt->energy/2;
              pt->energy=pt->energy/2;
              
                            nt->max_age=pt->max_age;
              nt->max_age_egg=nt->max_age_egg;
              if(mtrand1.randInt(400)<10)
              {
                  nt->max_age=nt->max_age+(mtrand1.randInt(200)-100)/100;
              }
              if(mtrand1.randInt(400)<10)
              {
                  nt->max_age_egg=nt->max_age_egg+(mtrand1.randInt(200)-100)/100;
              }

              nt->gonnabe=pt->typ;
              nt->indicate_col=(int)(nt->energy);
          }
     }
     else if(pt->weight<MIN_WEIGHT_A*2)
     {
         //Leta efter mat.
         found=0;
         for(i=-SIGHT;i<SIGHT;i++)
         {
             for(j=-SIGHT;j<SIGHT;j++)
             {
                 for(k=0;k<2;k++)
                 {
                     if(x+i>=0 && x+i<s_w
                     && y+j>=0 && y+j<s_h 
                     && !(i==0 && j==0 && k==z)
                     && ak[x+i][y+j].th[k]!=NULL 
                     && ak[x+i][y+j].th[k]->typ>=2
                     && ak[x+i][y+j].th[k]->dead)
                     {
                         //Hittat en! Undrar hur långt bort den är!
                         found++;
                         nfdx=i;
                         nfdy=j;
                         if(found>1)
                         {
                             if(sqrt(nfdy*nfdy+nfdx*nfdx)<sqrt(fdy*fdy+fdx*fdx))
                             {
                                 fdx=i;
                                 fdy=j;
                             }
                         }
                         else
                         {
                             fdx=i;
                             fdy=j;
                         }
                     }
                 }
             }
         }
         if(found>0)
         {
             //Accelrera mot maten
             if(fdx!=0)
                 pt->dx+=ACCX;
             else if(pt->dx>0)
                 pt->dx--;
             else if(pt->dx<0)
                 pt->dx++;
             if(fdy!=0)
                 pt->dy+=ACCY;
             else if(pt->dy>0)
                 pt->dy--;
             else if(pt->dy<0)
                 pt->dy++;
         }
         else
         {
//       //Gör bmp svart
//       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
//       //Skriv ut text
//       textprintf_ex(bmp, font, 0, 12, makecol(0, 100, 243), -1,  "move_carnivore");
//       textprintf_ex(bmp, font, 0, 20, makecol(0, 100, 243), -1,  "irra runt");
//       //rita ut bilden på skärmen
//       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              

             //Ändra lite slumpmässig riktning
             pt->dx=(rand()%3)-1;
             pt->dy=(rand()%4)-2;
         }
     }
}

void move_carnivore(AKVARIUM **ak, thing *pt, int x, int y, int z)
{
     int ez;
     int found;
     int fdy, fdx, nfdy, nfdx, nx, ny;
     int i, j, k;
     MTRand mtrand1;
     thing *nt;

//       //Gör bmp svart
//       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
//       //Skriv ut text
//       textprintf_ex(bmp, font, 0, 12, makecol(0, 100, 243), -1,  "move_carnivore");
//       //rita ut bilden på skärmen
//       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              

     //Se om vi kan äta ett offer
     ez=(z+1)%2;
     if(pt->age>pt->max_age)
     {
        pt->dead=1;
     }
     else if(ak[x][y].th[ez]!=NULL && ak[x][y].th[ez]->typ==3)
     {
         //ta dens massa!
         pt->weight+=ak[x][y].th[ez]->weight*ENERGY_LOSS;
         pt->poo+=ak[x][y].th[ez]->poo;
         pt->energy+=ak[x][y].th[ez]->energy*ENERGY_LOSS;
                  
         //Döda
         free(ak[x][y].th[ez]);
         ak[x][y].th[ez]=NULL;
         
         //Har vi stannat för att äta får vi stå still
         ak[x][y].th[z]->dx=0;
         ak[x][y].th[z]->dy=0;
         ak[x][y].th[z]->mdx=0;
         ak[x][y].th[z]->mdy=0;
     }
     else if(pt->energy>ENERGY_TO_MAKE_C && ak[x][y].th[(z+1)%2]==NULL)
     {
          //Om vi har en massa överskottsenergi och det finns plats förökar vi oss
          nt=new_spec_thing(ak,pt->typ,x,y,(z+1)%2);
          if(nt!=NULL)
          {
              nt->weight=pt->weight/2;
              pt->weight=pt->weight/2;
              nt->energy=pt->energy/2;
              pt->energy=pt->energy/2;
              
              nt->max_age=pt->max_age;
              nt->max_age_egg=nt->max_age_egg;
              if(mtrand1.randInt(400)<10)
              {
                  nt->max_age=nt->max_age+(mtrand1.randInt(200)-100)/100;
              }
              if(mtrand1.randInt(400)<10)
              {
                  nt->max_age_egg=nt->max_age_egg+(mtrand1.randInt(200)-100)/100;
              }
          }
     }
     else if(pt->weight<MIN_WEIGHT*6)
     {
         //Leta efter mat.
         found=0;
         for(i=-SIGHT;i<SIGHT;i++)
         {
             for(j=-SIGHT;j<SIGHT;j++)
             {
                 for(k=0;k<2;k++)
                 {
                     if(x+i>=0 && x+i<s_w
                     && y+j>=0 && y+j<s_h 
                     && !(i==0 && j==0 && k==z)
                     && ak[x+i][y+j].th[k]!=NULL 
                     && ak[x+i][y+j].th[k]->typ==3)
                     {
                         //Hittat en! Undrar hur långt bort den är!
                         found++;
                         nfdx=i;
                         nfdy=j;
                         if(found>1)
                         {
                             if(sqrt(nfdy*nfdy+nfdx*nfdx)<sqrt(fdy*fdy+fdx*fdx))
                             {
                                 fdx=i;
                                 fdy=j;
                             }
                         }
                         else
                         {
                             fdx=i;
                             fdy=j;
                         }
                     }
                 }
             }
         }
         if(found>0)
         {
             //Accelrera mot maten
             if(fdx!=0)
                 pt->dx+=ACCX;
             else if(pt->dx>0)
                 pt->dx--;
             else if(pt->dx<0)
                 pt->dx++;
             if(fdy!=0)
                 pt->dy+=ACCY;
             else if(pt->dy>0)
                 pt->dy--;
             else if(pt->dy<0)
                 pt->dy++;
                 
             //Se om vi kan äta nåt framför oss!!!
             if(pt->dx>0)
                 nx=x+1;
             else if(pt->dx<0)
                 nx=x-1;
             else
                 nx=x;
             if(pt->dy>0)
                 ny=y+1;
             else if(pt->dy<0)
                 ny=y-1;
             else
                 ny=y;
             if(nx>=0 && nx<s_w && ny>=0 && ny<s_h &&
             ak[nx][ny].th[0]!=NULL && (ak[nx][ny].th[0]->typ==3))
             { //Om vi kan äta en växtätare framför oss
                 //ta dens massa!
                 pt->weight+=ak[nx][ny].th[0]->weight*ENERGY_LOSS;
                 pt->poo+=ak[nx][ny].th[0]->poo;
                 pt->energy+=ak[nx][ny].th[0]->energy;
                 
                 //Döda
                 free(ak[nx][ny].th[0]);
                 ak[nx][ny].th[0]=NULL;
             }

         }
         else
         {
             //Ändra lite slumpmässig riktning
             pt->dx+=((rand()%3)-1)*0.25;
             pt->dy+=((rand()%3)-1)*0.25;
         }
     }

     //Ändra lite slumpmässig riktning
     pt->dx+=((rand()%3)-1)*0.25;
     pt->dy+=((rand()%3)-1)*0.25;
}

void move_herbivore(AKVARIUM **ak, thing *pt, int x, int y, int z)
{
     int ez;
     int found;
     int fdy, fdx, fdz, nfdy, nfdx;
     int i, j, k;
     thing *nt;
     int nx,ny,nz;
     MTRand mtrand1;
     
     //Se om vi kan äta en växt
     ez=(z+1)%2;
     if(pt->age>pt->max_age)
     {
        pt->dead=1;
     }
     else if(ak[x][y].th[ez]!=NULL && !ak[x][y].th[ez]->dead && (ak[x][y].th[ez]->typ==1 || ak[x][y].th[ez]->typ==2))
     {
         //ta dens massa!
         pt->weight+=ak[x][y].th[ez]->weight*ENERGY_LOSS;
         pt->poo+=ak[x][y].th[ez]->poo;
         pt->energy+=ak[x][y].th[ez]->energy*ENERGY_LOSS;
         
         //Döda
         free(ak[x][y].th[ez]);
         ak[x][y].th[ez]=NULL;
         
         //Har vi stannat för att äta får vi stå still
         ak[x][y].th[z]->dx=0;
         ak[x][y].th[z]->dy=0;
         ak[x][y].th[z]->mdx=0;
         ak[x][y].th[z]->mdy=0;
     }
     else if(pt->energy>ENERGY_TO_MAKE_H && ak[x][y].th[(z+1)%2]==NULL)
     {
          //Om vi har en massa överskottsenergi och det finns plats förökar vi oss
          nt=new_spec_thing(ak,6,x,y,(z+1)%2);
          if(nt!=NULL)
          {
              nt->weight=pt->weight/2;
              pt->weight=pt->weight/2;
              nt->energy=pt->energy/2;
              pt->energy=pt->energy/2;
              nt->gonnabe=pt->typ;
              nt->indicate_col=(int)(nt->energy);
              
              nt->max_age=pt->max_age;
              nt->max_age_egg=nt->max_age_egg;
              if(mtrand1.randInt(400)<10)
              {
                  nt->max_age=nt->max_age+(mtrand1.randInt(200)-100)/100;
              }
              if(mtrand1.randInt(400)<10)
              {
                  nt->max_age_egg=nt->max_age_egg+(mtrand1.randInt(200)-100)/100;
              }

              nt->gonnabe=pt->typ;
              nt->indicate_col=(int)(nt->energy);
          }
     }
     else
     {
         //Leta efter mat eller fiender.
         found=0;
         for(i=-SIGHT;i<SIGHT;i++)
         {
             for(j=-SIGHT;j<SIGHT;j++)
             {
                 for(k=0;k<2;k++)
                 {
                     if(x+i>0 && x+i<s_w
                     && y+j>0 && y+j<s_h 
                     && !(i==0 && j==0 && k==z)
                     && ak[x+i][y+j].th[k]!=NULL 
                     && !ak[x+i][y+j].th[k]->dead
                     && (ak[x+i][y+j].th[k]->typ==4
                     || (pt->weight<MIN_WEIGHT*3 && (ak[x+i][y+j].th[k]->typ==1
                     || ak[x+i][y+j].th[k]->typ==2))))
                     {
                         //Hittat en! Undrar hur långt bort den är!
                         found++;
                         nfdx=i;
                         nfdy=j;
                         if(found>1)
                         {
                             if(sqrt(nfdy*nfdy+nfdx*nfdx)<sqrt(fdy*fdy+fdx*fdx))
                             {
                                 fdx=i;
                                 fdy=j;
                                 fdz=k;
                             }
                         }
                         else
                         {
                             fdx=i;
                             fdy=j;
                             fdz=k;
                         }
                     }
                 }
             }
         }
         
         if(found>0)
         {
             if(ak[x+fdx][y+fdy].th[fdz]->typ==4)
             {
                 //Akta sig för farliga saker!
                 if(fdx!=0)
                     pt->dx-=HACCX;
                 else if(pt->dx>0)
                     pt->dx-=SIGHT;
                 else if(pt->dx<0)
                     pt->dx+=SIGHT;

                 if(fdy!=0)
                     pt->dy-=HACCY;
                 else if(pt->dy>0)
                     pt->dy-=SIGHT;
                 else if(pt->dy<0)
                     pt->dy+=SIGHT;
             }
             else if(ak[x+fdx][y+fdy].th[fdz]->typ<3)
             {
                 //Accelrera mot maten
                 if(fdx!=0)
                     pt->dx+=ACCX;
                 else if(pt->dx>0)
                     pt->dx-=ACCX;
                 else if(pt->dx<0)
                     pt->dx+=ACCX;
                 if(fdy!=0)
                     pt->dy+=ACCY;
                 else if(pt->dy>0)
                     pt->dy-=ACCY;
                 else if(pt->dy<0)
                     pt->dy+=ACCY;
             }
             
             //Se om vi kan äta nåt framför oss!!!
             if(pt->dx>0)
                 nx=x+1;
             else if(pt->dx<0)
                 nx=x-1;
             else
                 nx=x;
             if(pt->dy>0)
                 ny=y+1;
             else if(pt->dy<0)
                 ny=y-1;
             else
                 ny=y;
//       //Gör bmp svart
//       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
//       //Skriv ut text
//       textprintf_ex(bmp, font, 0, 12, makecol(0, 100, 243), -1,  "x y mdx mdy nx ny");
//       textprintf_ex(bmp, font, 0, 20, makecol(0, 100, 243), -1,  "%d %d %f %f %d %d",x, y, pt->mdx, pt->mdy, nx, ny);
//       //rita ut bilden på skärmen
//       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);     
//       //vänta
//       while(!key[KEY_SPACE]);      
//       while(key[KEY_SPACE]);      

             if(nx>=0 && nx<s_w && ny>=0 && ny<s_h &&
             ak[nx][ny].th[0]!=NULL && !ak[nx][ny].th[0]->dead &&(ak[nx][ny].th[0]->typ==1 || ak[nx][ny].th[0]->typ==2))
             { //Om vi kan äta en växt framför oss
                 //ta dens massa!
                 pt->weight+=ak[nx][ny].th[0]->weight*ENERGY_LOSS;
                 pt->poo+=ak[nx][ny].th[0]->poo;
                 pt->energy+=ak[nx][ny].th[0]->energy*ENERGY_LOSS;
                 
                 //Döda
                 free(ak[nx][ny].th[0]);
                 ak[nx][ny].th[0]=NULL;
             }

         }
         else
         {
             //Ändra lite slumpmässig riktning
             if(pt->dx==0)
                 pt->dx=((rand()%3)-1)*0.5;
             if(pt->dy==0)
                 pt->dy=((rand()%3)-1)*2;
         }
     }

     //Ändra lite slumpmässig riktning
     pt->dx+=((rand()%3)-1)*0.1;
     pt->dy+=((rand()%3)-1)*0.1;
     pt->dx+=wind/5;
}

void draw_things(AKVARIUM **ak)
{
     int x, y;
     int rgb[3];
     thing *pt;
     float e;
     
     for(x=0;x<s_w;x++)
     {
         for(y=0;y<s_h;y++)
         {
             if(ak[x][y].th[0]!=NULL)
             { 
                pt=ak[x][y].th[0];                     
             }
             else if(ak[x][y].th[1]!=NULL)
             {
                  pt=ak[x][y].th[1];
             }
             else
                 pt=NULL;                 
                                     
             if(pt!=NULL)
             {                
                e=0.6+0.4*pt->energy/pt->indicate_col;
                if(e>1)
                    e=1;
                if(e<0.6)
                    e=0.6;
                rgb[0] = (int)(pal[pt->typ].r*e);
                rgb[1] = (int)(pal[pt->typ].g*e);
                rgb[2] = (int)(pal[pt->typ].b*e);

                //rita ut en pixel i färgen på plats x,y
                 putpixel(bmp, x, y, makecol(rgb[0], rgb[1], rgb[2]));
             }
//             else if(ak[x][y].th[1]!=NULL)
//             {
//                rgb[0] = pal[ak[x][y].th[1]->typ].r;
//                rgb[1] = pal[ak[x][y].th[1]->typ].g;
//                rgb[2] = pal[ak[x][y].th[1]->typ].b;
//
//                //rita ut en pixel i färgen på plats x,y
//                 putpixel(bmp, x, y, makecol(rgb[0], rgb[1], rgb[2]));
//             }
         }
     }
}

void energy_in_creature(AKVARIUM **ak,thing *pt, int x, int y, int z)
{
     int i;
     int sol;
     
     //Om det är ett levande djur som rör sig kostar det energi
     if(pt->typ>=3 && pt->dead==0)
     {
         //om det rör sig
         if(pt->dx!=0 || pt->dy!=0)
                  pt->energy-=sqrt(pt->dx*pt->dx+pt->dy*pt->dy)*MOVE_E;
         else
             pt->energy-=STILL_E;
     }
     
     //Om det är en växt som inte har något ovanför sig så får den energi (av solen, typ)
     if(pt->typ==2 && !pt->dead)
     {
         sol=0;
         
         if(y==0)
             sol=3;
         else
         {
             for(i=-1;i<2;i++)
             {
                 if(y-1>0 && y-1<s_h
                 && x+i>=0 && x+i<s_w)
                 {
                     if(ak[x+i][y-1].th[0]==NULL)
                         sol++;
                     if(ak[x+i][y-1].th[1]==NULL)
                         sol++;
                 }
                 else
                     sol+=2;
             }
         }
         //Ge energi från sol (max 6 solar)
         pt->energy+=sol*SOL_E;
     }
     
     //döda om slut på energi
     if(pt->energy<=0)
     {
         pt->dead=1;
         pt->energy=pt->weight;
     }
     //Döda rötter omvandlas till jord
     if(pt->dead && pt->typ==1)
     {
         pt->typ=0;
         pt->energy+=pt->weight;
     }
}

void make_poo(AKVARIUM **ak, thing *pt, int x, int y, int z)
{
     thing *poo;
     int p;
     
     if(pt->weight>MIN_WEIGHT || (pt->typ==5 && pt->weight>MIN_WEIGHT_A))
     {
         //Gör om lite vikt till bajs
         p=(int)((pt->weight/100)*POO_PERCENT);
         pt->weight-=p;
         pt->poo+=p;
     }
     //Gör om lite vikt till energi
     if(pt->weight>MIN_WEIGHT || (pt->typ==5 && pt->weight>MIN_WEIGHT_A))
     {
         p=(int)(pt->weight/100);
         pt->weight-=p;
         pt->energy+=(p*WEIGHT_TO_ENERGY);
     }
          
     //kolla om vi ska bajsa
     if(pt->poo>POO)
     {
         //Kolla att det finns plats
         if(ak[x][y].th[(z+1)%2]==NULL)
         {
             poo=new_spec_thing(ak,0,x,y,(z+1)%2);
             if(poo!=NULL)
             {
                 pt->poo-=POO;
                 poo->energy=POO;
                 poo->weight=POO;
             }
         }
     }
}

           //Kolla så att allt finns
void check_things(AKVARIUM **ak)
{
      int x,y,z,i;
      int found2,found3,found4,found5;
      
      found2=0;
      found3=0;
      found4=0;
      found5=0;
      for(x=0;x<s_w;x++)
      {
          for(y=0;y<s_h;y++)
          {
              for(z=0;z<2;z++)
              {
                  if(ak[x][y].th[z]!=NULL)
                  {
                      if(ak[x][y].th[z]->typ==1 || ak[x][y].th[z]->typ==2)
                          found2++;
                      if((ak[x][y].th[z]->typ==6 && ak[x][y].th[z]->gonnabe==3) || (ak[x][y].th[z]->typ==3 && !ak[x][y].th[z]->dead))
                          found3++;
                      if(ak[x][y].th[z]->typ==4 && !ak[x][y].th[z]->dead)
                          found4++;
                      if((ak[x][y].th[z]->typ==6 && ak[x][y].th[z]->gonnabe==5) || (ak[x][y].th[z]->typ==5 && !ak[x][y].th[z]->dead))
                          found5++;                      
                  }
              }
          }
      }

       if(found2<1)
       {
           //Skriv ut text
           textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Creating new plants");        
           //rita ut bilden på skärmen
           blit(bmp, screen, 0, 0, 0, 0, s_w, s_h); 
           //Vänta på knapptryckning
//           while(!key[KEY_ESC] && !key[KEY_SPACE]);
//           while(!key[KEY_ESC] && key[KEY_SPACE]);                
       
           for(i=0;i<ANT_PLANT;i++)
               new_plant(ak);
       }
       
       if(found3<1)
       {
           //Skriv ut text
           textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Creating new herbivores");        
           //rita ut bilden på skärmen
           blit(bmp, screen, 0, 0, 0, 0, s_w, s_h); 
           //Vänta på knapptryckning
//           while(!key[KEY_ESC] && !key[KEY_SPACE]);
//           while(!key[KEY_ESC] && key[KEY_SPACE]);                

           for(i=0;i<ANT_PL_EATER;i++)
               new_thing(ak, 3, START_ENERGY_H,-1,-1,-1);
       }
       if(found4<1)
       {
           //Skriv ut text
           textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Creating new carnivores");        
           //rita ut bilden på skärmen
           blit(bmp, screen, 0, 0, 0, 0, s_w, s_h); 
           //Vänta på knapptryckning
//           while(!key[KEY_ESC] && !key[KEY_SPACE]);
//           while(!key[KEY_ESC] && key[KEY_SPACE]);                

           for(i=0;i<ANT_EATER;i++)
               new_thing(ak, 4, START_ENERGY,-1,-1,-1);
       }

       if(found5<1)
       {
           //Skriv ut text
           textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Creating new deatheaters");        
           //rita ut bilden på skärmen
           blit(bmp, screen, 0, 0, 0, 0, s_w, s_h); 
           //Vänta på knapptryckning
//           while(!key[KEY_ESC] && !key[KEY_SPACE]);
//           while(!key[KEY_ESC] && key[KEY_SPACE]);                

           for(i=0;i<ANT_ASEATER;i++)
               new_thing(ak, 5, START_ENERGY_AS,-1,-1,-1);
       }
}
