
#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<string.h>

typedef struct
{
char ch[20];
}nomimage; //declaration global

SDL_Event event;
typedef struct
{SDL_Surface *img;
char noimg[20];
}rect;

rect mat[9][10];
SDL_Surface *ecran=NULL;
int egalite();
void destroy();
void swap();
void fillrect();
int main(int argc,char *argv[])
{

SDL_Surface *depimage=NULL;
 int i,j,k,dl,ok=0; int csx,csy,csx2,csy2;
nomimage tab[6];


SDL_Rect pos,posev1;
pos.x=0; pos.y=0;
initmat(tab);


SDL_Init(SDL_INIT_VIDEO);
ecran=SDL_SetVideoMode(880,800,32,SDL_HWSURFACE);
SDL_WM_SetCaption("twist",NULL);i=0; j=0;
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
while(cn)
{    SDL_WaitEvent(&event);
              if(event.type==SDL_QUIT)   cn=0;
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
   //1er cas
if(csy2==csy&&csx2==abs(csx-1))
     {
if((egalite(mat[csy][csx],mat[csy2-1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+1][csx2])==1))
    {ok=1;

                   swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2-1,csx2,csy2+1);

     }
else if((egalite(mat[csy][csx],mat[csy2+1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+2][csx2])==1))
    {ok=1;

                   swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2);

    }
else if((egalite(mat[csy][csx],mat[csy2-1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2-2][csx2])==1))
   {ok=1;

                  swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2-1,csx2,csy2-2);

   }
else if((egalite(mat[csy][csx],mat[csy2][csx2-1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2-2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2-1,csy2,csx2-2,csy2);

  }else reswap(csy,csx,csx2,csy2);

}
//2eme cas
if (csy2==csy&&csx2==abs(csx+1))
{ if((egalite(mat[csy][csx],mat[csy2+1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+2][csx2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2);

  }

else if((egalite(mat[csy][csx],mat[csy2-1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2-2][csx2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2-1,csx2,csy2-2);


  }

else if((egalite(mat[csy][csx],mat[csy2][csx2+1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2+2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2+1,csy2,csx2+2,csy2);

  }
else if((egalite(mat[csy][csx],mat[csy2-1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+1][csx2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2-1,csx2,csy2+1);

  }
else if((egalite(mat[csy][csx],mat[csy2+1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+2][csx2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2);

  }else reswap(csy,csx,csx2,csy2);

}
//3eme cas
if (csy2==abs(csy-1)&&csx2==csx)
{if(egalite(mat[csy][csy],mat[csy2][csx2+1])==1
&&(egalite(mat[csy][csy],mat[csy2][csx2-1])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2+1,csy2,csx2-1,csy2);

  }
else if((egalite(mat[csy][csx],mat[csy2-1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2-2][csx2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2-1,csx2,csy2-2);

  }
else if((egalite(mat[csy][csx],mat[csy2][csx2+1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2+2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2+1,csy2,csx2+2,csy2);

  }
else if((egalite(mat[csy][csx],mat[csy2][csx2-1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2-2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2-1,csy2,csx2-2,csy2);

  }
else if((egalite(mat[csy][csx],mat[csy2][csx2-1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2+1])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2-1,csy2,csx2+1,csy2);

  }else reswap(csy,csx,csx2,csy2);


}
// 4eme cas
if (csy2==csy+1&&csx2==csx)
  {
   if((egalite(mat[csy][csy],mat[csy2][csx2+1])==1)
   &&(egalite(mat[csy][csy],mat[csy2][csx2-1])==1))
    {ok=1;

                   swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2+1,csy2,csx2-1,csy2);

    }
else if((egalite(mat[csy][csx],mat[csy2+1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+2][csx2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2);

  }//not responding -___- in top left botton
else if((egalite(mat[csy][csx],mat[csy2][csx2+1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2+2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2+1,csy2,csx2+2,csy2);

  }
else if((egalite(mat[csy][csx],mat[csy2][csx2-1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2-2])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
        destroy(csx2,csy2,csx2-1,csy2,csx2-2,csy2);

  }
else if((egalite(mat[csy][csx],mat[csy2][csx2-1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2+1])==1))
  {ok=1;

                 swap(csy,csx,csx2,csy2);
     destroy(csx2,csy2,csx2-1,csy2,csx2+1,csy2+1);
  }else reswap(csy,csx,csx2,csy2);

}

if(ok==1){
               printf("you can do it \n");

               /*
                SDL_FillRect(mat[csy2][csx2].img,NULL,SDL_MapRGB(mat[csy2][csx2].img->format,0,255,0));
                pos.x=csx2*80;pos.y=csy2*80;
                SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos);
                */

                                }
                        }
}

i++;
}
return 0;
}




//fonctions
void  initmat(nomimage tab[])
{int i,j,k;

strcpy(tab[0].ch,"1_1.bmp");
strcpy(tab[1].ch,"2_1.bmp");
strcpy(tab[2].ch,"3_1.bmp");
strcpy(tab[3].ch,"4_1.bmp");
strcpy(tab[4].ch,"5_1.bmp");
strcpy(tab[5].ch,"6_1.bmp");
strcpy(tab[6].ch,"7_1.bmp");

srand(time(NULL));
for(i=0;i<10;i++)
{for(j=0;j<11;j++)
{k=rand()%7; //gives a random number to k beetween 0 and 6;
mat[i][j].img=SDL_LoadBMP(tab[k].ch);
strcpy (mat[i][j].noimg,tab[k].ch);
}

}
}

int egalite(rect img,rect img2)
{
if(strcmp(img.noimg,img2.noimg)==0) return 1;
return 0;
}

//GREEN
void fillrect(rect img)
{
SDL_FillRect(img.img,NULL,SDL_MapRGB(img.img->format,0,255,0));
}



//permutation entre la case sélectionne 1 et la cs2
void swap(int csy,int csx,int csx2,int csy2)
{char temp[20];
SDL_Rect pos1,pos2;

pos2.y=csy2*80; pos1.y=csy*80;
pos2.x=csx2*80; pos1.x=csx*80;

strcpy(temp,mat[csy2][csx2].noimg);
SDL_FreeSurface(mat[csy2][csx2].img);

mat[csy2][csx2].img=SDL_LoadBMP(mat[csy][csx].noimg);

strcpy(mat[csy2][csx2].noimg,mat[csy][csx].noimg);
SDL_FreeSurface(mat[csy][csx].img);

mat[csy][csx].img=SDL_LoadBMP(temp);
strcpy(mat[csy][csx].noimg,temp);

SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos2);
SDL_BlitSurface(mat[csy][csx].img,NULL,ecran,&pos1);
SDL_Flip(ecran);
SDL_Delay(500);
}



//détruire les 3 cases
void destroy(int csx2,int csy2,int x3,int y3,int x4,int y4)
{SDL_Rect pos3,pos4,pos2;
fillrect(mat[y3][x3]); fillrect(mat[y4][x4]);
fillrect(mat[csy2][csx2]);
pos3.x=x3*80;   pos3.y=y3*80;   pos4.x=x4*80;    pos4.y=y4*80;
pos2.x=csx2*80; pos2.y=csy2*80;

SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos2);

SDL_BlitSurface(mat[y3][x4].img,NULL,ecran,&pos3);
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos4);
SDL_Flip(ecran);

}
void reswap(int csy,int csx,int csx2,int csy2)
{
swap(csy,csx,csx2,csy2);

swap(csy2,csx2,csx,csy);

}



