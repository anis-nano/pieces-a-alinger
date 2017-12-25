
#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<string.h>
#include"fonctions.h"


//the MAIN
int main(int argc,char *argv[])
{

nomimage tab[14];
strcpy(tab[0].ch,"1_1.bmp");strcpy(tab[7].ch,"1_2.bmp");strcpy(tab[14].ch,"1_3.bmp");
strcpy(tab[1].ch,"2_1.bmp");strcpy(tab[8].ch,"2_2.bmp");strcpy(tab[15].ch,"2_3.bmp");
strcpy(tab[2].ch,"3_1.bmp");strcpy(tab[9].ch,"3_2.bmp");strcpy(tab[16].ch,"3_3.bmp");
strcpy(tab[3].ch,"4_1.bmp");strcpy(tab[10].ch,"4_2.bmp");strcpy(tab[17].ch,"4_3.bmp");
strcpy(tab[4].ch,"5_1.bmp");strcpy(tab[11].ch,"5_2.bmp");strcpy(tab[18].ch,"5_3.bmp");
strcpy(tab[5].ch,"6_1.bmp");strcpy(tab[12].ch,"6_2.bmp");strcpy(tab[19].ch,"6_3.bmp");
strcpy(tab[6].ch,"7_1.bmp");strcpy(tab[13].ch,"7_2.bmp");strcpy(tab[20].ch,"7_3.bmp");


SDL_Surface *depimage=NULL;
 int i,j,k,dl,ok=0; int csx,csy,csx2,csy2;
int d;

SDL_Rect pos,posev1;
pos.x=0; pos.y=0;
initmat(tab);


SDL_WM_SetCaption("twist",NULL);
SDL_Init(SDL_INIT_VIDEO);
ecran=SDL_SetVideoMode(880,800,32,SDL_HWSURFACE);


i=0; j=0;
for(i=0;i<10;i++)
{pos.x=0;
for(j=0;j<11;j++)
{k=rand()%8;
SDL_BlitSurface(mat[i][j].img,NULL,ecran,&pos);
pos.x=pos.x+80;
}
pos.y=pos.y+80;
}
i=0;
SDL_Flip(ecran);
int cn=1;



//testing

while(cn)
{ d=0;
   SDL_WaitEvent(&event);
              if(event.type==SDL_QUIT)   cn=0;
              ////////////////////////
if (event.type==SDL_MOUSEBUTTONDOWN)
{              if(event.button.button==SDL_BUTTON_LEFT)
                   {
                       csx=(event.button.x)/80;//case selectionée
                       csy=(event.button.y)/80;
                    printf("csy=%d    csx=%d \n",csy,csx);
                        }
                    else if((i!=0)&&(event.button.button==SDL_BUTTON_RIGHT))
                  {i=0;ok=0;
                 csx2=event.button.x/80;csy2=event.button.y/80;
                printf("csy2=%d    csx2=%d \n",csy2,csx2);
verification_global(csx,csy,csx2,csy2,tab,0);

                        }
}

i++;
}





return EXIT_SUCCESS;

}




















