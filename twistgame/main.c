#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<string.h>

typedef struct
{
char ch[20];
}nomimage;


int main(int argc,char *argv[])
{nomimage tab[6];
strcpy(tab[0].ch,"1_1.bmp");
strcpy(tab[1].ch,"2_1.bmp");
strcpy(tab[2].ch,"3_1.bmp");
strcpy(tab[3].ch,"4_1.bmp");
strcpy(tab[4].ch,"5_1.bmp");
strcpy(tab[5].ch,"6_1.bmp");
strcpy(tab[6].ch,"7_1.bmp");


SDL_Surface *ecran=NULL;
SDL_Surface *mat[10][11]={NULL}; int i,j,k;
SDL_Rect pos;
pos.x=0; pos.y=0;

srand(time(NULL));
for(i=0;i<=10;i++)
{for(j=0;j<=11;j++)
{k=rand()%7; //gives a random number to k beetween 0 and 6;
mat[i][j]=SDL_LoadBMP(tab[k].ch);
}
}
SDL_Init(SDL_INIT_VIDEO);
ecran=SDL_SetVideoMode(880,800,32,SDL_HWSURFACE);
SDL_WM_SetCaption("twist",NULL);i=0; j=0;
for(i=0;i<=10;i++)
{pos.x=0;
for(j=0;j<=11;j++)
{k=rand()%8;
SDL_BlitSurface(mat[i][j],NULL,ecran,&pos);
pos.x=pos.x+80;
}
pos.y=pos.y+80;
}
SDL_Flip(ecran);

pause();

    return 0;
}
