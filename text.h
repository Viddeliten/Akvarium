void printsome(char *texten)
{
    //G�r bmp svart
   rectfill(bmp, 0, 0, s_w-1, s_h-1, 0);   

   //Skriv ut text
   textprintf_centre_ex(bmp, font, s_w / 2, 120, makecol(0, 100, 243), -1,  "jord");
           
   //rita ut bilden p� sk�rmen
   blit(bmp, screen, 0, 0, 0, 0, s_w, s_h);              

}
