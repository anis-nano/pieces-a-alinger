#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<string.h>
#include "fonctions.h"
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>
#include <sys/time.h>

int main(int argc,char *argv[])
{


Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
effect1=Mix_LoadWAV("Pickup_Coin8.wav");
music=Mix_LoadMUS("Magic-Clock-Shop.mp3");


nomimage tab[21];//pour les noms des images
init_tab(tab);
int i,j,k,dl,ok=0; int csx,csy,csx2,csy2;//cs:case seléctionnée 1 et 2,
int a=5; //pour aide 5 fois max
int x,y;
int d,a1,x1,y1;
t2=59;
SDL_Rect pos,posev1;

TTF_Init();
init_menu();
int cn=1,p=1;//p:pour pause cn:continue
pos.x=0; pos.y=0;
while(cn)
{
SDL_WaitEvent(&event2);
if(event2.type==SDL_QUIT)cn =0;
if(event2.type==SDL_MOUSEBUTTONDOWN)
{start_time=(SDL_GetTicks());
 printf("time ====== %d ========\n",start_time);
  x=event2.button.x;
  y=event2.button.y;
 //1) play_butoon
if(play_button(x,y)==1)
     { Mix_PlayMusic(music,-1);init_play(tab);
      init_score();

      while(cn)
     {
  aff_clock(&cn);
             d=0;
           SDL_PollEvent(&event);
           if(event.type==SDL_QUIT)   cn=0;
             test_event(event,i,&csx,&csy,&csy2,&csx2,&p,tab,0,&a);  i++;


    }
    }
//start player_vs_bot button
else if(vs_bot_button(x,y)==1)
    {   Mix_PlayMusic(music,-1);
    init_bot(tab);init_score();init_score_2();

     while(cn)
     {
      d=0;aff_clock(&cn);
            SDL_PollEvent(&event3);
              if(event3.type==SDL_QUIT)   cn=0;
           test_event(event3,i,&csx,&csy,&csx2,&csy2,&p,tab,1,&a); i++;
     }
     }
}
}

free_surfaces();


Mix_FreeChunk(effect1);

Mix_CloseAudio();
return EXIT_SUCCESS;
}

void aff_clock(int *cn)
{char m2[3],s[3];


  time_since=(SDL_GetTicks()-start_time)/1000;
  if(t2-time_since==-1)
  {t2=t2+59;m=m-1;
  SDL_BlitSurface(cover,NULL,ecran,&pos_clock2);
  }
  printf("======%d====\n",t2-time_since);

 sprintf(s,"%02d",t2-time_since);
 sprintf(m2,"%02d",m);

  clock=TTF_RenderText_Blended(font2,s,cl);
  clock2=TTF_RenderText_Blended(font2,m2,cl);
  clock3=TTF_RenderText_Blended(font2,":",cl);

  SDL_BlitSurface(cover,NULL,ecran,&pos_clock);
  SDL_BlitSurface(clock,NULL,ecran,&pos_clock);
  SDL_BlitSurface(clock2,NULL,ecran,&pos_clock2);
  SDL_BlitSurface(clock3,NULL,ecran,&pos_clock3);
  SDL_Flip(ecran);
  if(t-1==0&&m==0) *cn=0;

}

