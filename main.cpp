#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <allegro.h>
#include <MT.h>

#include "thing.h"
#include "akvarium.h"
#include "plant.h"
#include "main.h"


using namespace std;

PALETTE pal;
BITMAP *bmp;
int s_w, s_h;
float wind;

int main(int argc, char *argv[])
{
   uintptr_t address;
   int i, j, k, x, y, antal;
   int color;
   int check;
   MTRand mtrand1;
   AKVARIUM **akvarium;
   
   //Det ska finnas v�xter, rovdjur, v�xt�tare och jord
   
    //K�r ig�ng allegro
    if(!install_allegro(SYSTEM_AUTODETECT, &errno, atexit))
    {
       ///skaffa tangentbord
       install_keyboard(); 
       //starta fullsk�rm
       s_w=320;
       s_h=200;
       if (set_gfx_mode(GFX_AUTODETECT, s_w, s_h, 0, 0) != 0)
       {
           s_w=640;
           s_h=480;
           if (set_gfx_mode(GFX_AUTODETECT, s_w, s_h, 0, 0) != 0)
           {
//               s_w=160;
//               s_h=100;
               s_w=800;
               s_h=600;
               if (set_gfx_mode(GFX_AUTODETECT, s_w, s_h, 0, 0) != 0)
               {
    	          allegro_message("Error setting graphics mode\n%s\n", allegro_error);
    	          return 1;
               }
           }
        }
        
        //Fixa lite f�rger
        //jord
        pal[0].r = 100;
        pal[0].g = 100;
        pal[0].b = 0;
        //r�tter
        pal[1].r = 200;
        pal[1].g = 200;
        pal[1].b = 200;
        //v�xter
        pal[2].r = 0;
        pal[2].g = 255;
        pal[2].b = 0;
        //v�xt�tare
        pal[3].r = 0;
        pal[3].g = 0;
        pal[3].b = 255;
        //k�tt�tare
        pal[4].r = 255;
        pal[4].g = 0;
        pal[4].b = 0;
        //as�tare
        pal[5].r = 255;
        pal[5].g = 0;
        pal[5].b = 255;
        //�gg
        pal[6].r = 255;
        pal[6].g = 255;
        pal[6].b = 128;
        
        
       //matris f�r sk�rmen
       akvarium=(AKVARIUM **)calloc(s_w,sizeof(AKVARIUM *));
       for(i=0;i<s_w;i++)
       {
           akvarium[i]=(AKVARIUM *)calloc(s_h,sizeof(AKVARIUM));
           for(j=0;j<s_h;j++)
           {
               for(k=0;k<2;k++)
               {
                   akvarium[i][j].th[k]=NULL;
               }
           }
       }
           
       //Skapa en bild som �r svart
       bmp=create_bitmap(s_w, s_h);

       //G�r bmp svart
       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
       
       //Skriv ut text
       textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Commencing creation...");
               
       //rita ut bilden p� sk�rmen
       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              
               
       //Skapa jord
       antal=ANT_JORD;

       //G�r bmp svart
       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);      
       //Skriv ut text
       textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Creating %d jord...",antal);
       //rita ut bilden p� sk�rmen
       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              

       //V�nta p� knapptryckning
//           while(!key[KEY_ESC] && !key[KEY_SPACE]);
//           while(!key[KEY_ESC] && key[KEY_SPACE]);                

       for(i=0;i<antal;i++)
       {
         new_thing(akvarium, 0, 0, -1, -1, -1);
  
       }

       //Skapa v�xter
       antal=ANT_PLANT;
       //G�r bmp svart
       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
   
       //Skriv ut text
       textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Creating %d plants...",antal);
               
       //rita ut bilden p� sk�rmen
       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              
               
       //V�nta p� knapptryckning
//           while(!key[KEY_ESC] && !key[KEY_SPACE]);
//           while(!key[KEY_ESC] && key[KEY_SPACE]);                

       for(i=0;i<antal;i++)
           new_thing(akvarium, 2, START_ENERGY_PLANT,-1,-1,-1);

       //skapa v�xt�tare
       antal=ANT_PL_EATER;
       //G�r bmp svart
       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
   
       //Skriv ut text
       textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Creating %d vegans...",antal);
               
       //rita ut bilden p� sk�rmen
       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              
               
       for(i=0;i<antal;i++)
           new_thing(akvarium, 3, START_ENERGY_H,-1,-1,-1);

       //Skapa k�tt�tare
       antal=ANT_EATER;
       //G�r bmp svart
       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
   
       //Skriv ut text
       textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Creating %d carnisar...",antal);
               
       //rita ut bilden p� sk�rmen
       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              
               
       for(i=0;i<antal;i++)
           new_thing(akvarium, 4,START_ENERGY,-1,-1,-1);

       //Skapa as�tare
       antal=ANT_ASEATER;
       //G�r bmp svart
       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
   
       //Skriv ut text
       textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Creating %d asar...",antal);
               
       //rita ut bilden p� sk�rmen
       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              
               
       for(i=0;i<antal;i++)
           new_thing(akvarium, 5,START_ENERGY_AS,-1,-1,-1);
                
       //G�r bmp svart
       rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   
       
       //Skriv ut text
       textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Done creating!");
               
       //rita ut bilden p� sk�rmen
       blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);     
       
       //vind
       wind=0;  
       check=0;       
               
        while(!key[KEY_ESC])
        {
           while(key[KEY_N]);
           if(key[KEY_P])
           {
               while(key[KEY_P]);
               new_plant(akvarium);
           }
           if(key[KEY_H])
           {
               while(key[KEY_H]);
               new_thing(akvarium, 3, START_ENERGY_H,-1,-1,-1);
           }
           if(key[KEY_C])
           {
               while(key[KEY_C]);
               new_thing(akvarium, 4, START_ENERGY,-1,-1,-1);
           }
           if(key[KEY_A])
           {
               while(key[KEY_A]);
               new_thing(akvarium, 5, START_ENERGY_AS,-1,-1,-1);
           }
               
           wind+=((rand()%3)-1)*0.2;
           while(wind!=0 && wind*wind>=sqrt(1))
               wind*=0.9;
           
           check++;
           if(check>500)
           {
               //Kolla s� att allt finns
              check_things(akvarium);
              check=0;
          }

           //G�r bmp bl�
           rectfill(bmp, 0, 0, s_w-1, s_h-1, makecol(0, 50, 100));
           
           //varelsar har sin turn
           move_things(akvarium);

             //Rita ut saker
             draw_things(akvarium);
               
//            //Skriv ut text
//            textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "Press ESC to exit");
               
          //rita ut bilden p� sk�rmen
          blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              
               
           //V�nta p� knapptryckning
//           while(!key[KEY_ESC] && !key[KEY_SPACE]);
//           while(!key[KEY_ESC] && key[KEY_SPACE]);                

        }

        for(i=0;i<s_w;i++)
            free(akvarium[i]);
        free(akvarium);

        get_palette(pal);
        save_bmp("dump.bmp", bmp, pal);

        destroy_bitmap(bmp);
        return 0;
    }
    else
    {

        printf("Allegro funkar inte");
    
        system("PAUSE");
        return EXIT_SUCCESS;
    }
}

END_OF_MAIN()
