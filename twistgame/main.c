#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<string.h>
#include"fonctions.h"
//#include<SDL/SDL_ttf.h>

//the MAIN
int main(int argc,char *argv[])
{

nomimage tab[20];
strcpy(tab[0].ch,"1_1.bmp");strcpy(tab[7].ch,"1_2.bmp");strcpy(tab[14].ch,"1_3.bmp");strcpy(tab[1].ch,"2_1.bmp");strcpy(tab[8].ch,"2_2.bmp");strcpy(tab[15].ch,"2_3.bmp");strcpy(tab[2].ch,"3_1.bmp");strcpy(tab[9].ch,"3_2.bmp");strcpy(tab[16].ch,"3_3.bmp");strcpy(tab[3].ch,"4_1.bmp");strcpy(tab[10].ch,"4_2.bmp");strcpy(tab[17].ch,"4_3.bmp");strcpy(tab[4].ch,"5_1.bmp");strcpy(tab[11].ch,"5_2.bmp");strcpy(tab[18].ch,"5_3.bmp");strcpy(tab[5].ch,"6_1.bmp");strcpy(tab[12].ch,"6_2.bmp");strcpy(tab[19].ch,"6_3.bmp");strcpy(tab[6].ch,"7_1.bmp");strcpy(tab[13].ch,"7_2.bmp");strcpy(tab[20].ch,"7_3.bmp");

int i,j,k,dl,ok=0; int csx,csy,csx2,csy2; int x,y;
int d,a1;

SDL_Rect pos,posev1;

TTF_Init();
init_menu();

int cn=1;
pos.x=0; pos.y=0;
while(cn)
{
SDL_WaitEvent(&event2);
if (event2.type==SDL_QUIT)cn =0;
if(event2.type==SDL_MOUSEBUTTONDOWN)
{ x=event2.button.x;
  y=event2.button.y;
if(play_button(x,y)==1) //1) play_butoon
     {init_play(tab);
      while(cn)
     {
      d=0;
      SDL_WaitEvent(&event);
              if(event.type==SDL_QUIT)   cn=0;


             test_event(event,i,&csx,&csy,&csy2,&csx2,tab);  i++;

    }
    }
//end of play button
else if(vs_bot_button(x,y)==1)
    {init_bot(tab);

     while(cn)
     {
      d=0;
             SDL_WaitEvent(&event3);

              if(event3.type==SDL_QUIT)   cn=0;
           test_event(event3,i,&csx,&csy,&csx2,&csy2,tab); i++;
     }
     }
}


}
//end of while
free_surfaces();
return EXIT_SUCCESS;

}








