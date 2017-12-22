#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<string.h>
#include"fonctions.h"


//the MAIN
int main(int argc,char *argv[])
{
nomimage tab[6];
strcpy(tab[0].ch,"1_1.bmp");
strcpy(tab[1].ch,"2_1.bmp");
strcpy(tab[2].ch,"3_1.bmp");
strcpy(tab[3].ch,"4_1.bmp");
strcpy(tab[4].ch,"5_1.bmp");
strcpy(tab[5].ch,"6_1.bmp");
strcpy(tab[6].ch,"7_1.bmp");

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

///////////////////////1er cas
if(csy2==csy&&csx2==abs(csx-1))
     {
if((d==0)&&(egalite(mat[csy][csx],mat[csy2-1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+1][csx2])==1))
    {ok=1;d=1;

                   swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2-1,csx2,csy2+1,tab);

     }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2+1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+2][csx2])==1))
    {ok=1;d=1;

                   swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);

    }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2-1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2-2][csx2])==1))
   {ok=1;d=1;

                  swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2-1,csx2,csy2-2,tab);

   }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2][csx2-1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2-2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2-1,csy2,csx2-2,csy2,tab);

  }else reswap(csy,csx,csx2,csy2);

}
//////////////////////2eme cas

if (csy2==csy&&csx2==abs(csx+1))
{ if((d==0)&&(egalite(mat[csy][csx],mat[csy2+1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+2][csx2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);

  }

else if((d==0)&&(egalite(mat[csy][csx],mat[csy2-1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2-2][csx2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2-1,csx2,csy2-2,tab);


  }

else if((d==0)&&(egalite(mat[csy][csx],mat[csy2][csx2+1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2+2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2+1,csy2,csx2+2,csy2,tab);

  }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2-1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+1][csx2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2-1,csx2,csy2+1,tab);

  }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2+1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+2][csx2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);

  }else reswap(csy,csx,csx2,csy2);

}
////////////////////////3eme cas
if (csy2==abs(csy-1)&&csx2==csx)
{if((d==0)&&egalite(mat[csy][csy],mat[csy2][csx2+1])==1
&&(egalite(mat[csy][csy],mat[csy2][csx2-1])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2+1,csy2,csx2-1,csy2,tab);

  }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2-1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2-2][csx2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2-1,csx2,csy2-2,tab);

  }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2][csx2+1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2+2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2+1,csy2,csx2+2,csy2,tab);

  }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2][csx2-1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2-2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2-1,csy2,csx2-2,csy2,tab);

  }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2][csx2-1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2+1])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2-1,csy2,csx2+1,csy2,tab);

  }else reswap(csy,csx,csx2,csy2);


}
//////////////////////////// 4eme cas
if (csy2==csy+1&&csx2==csx)
  {
   if((d==0)&&(egalite(mat[csy][csy],mat[csy2][csx2+1])==1)
   &&(egalite(mat[csy][csy],mat[csy2][csx2-1])==1))
    {ok=1;d=1;

                   swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2+1,csy2,csx2-1,csy2,tab);

    }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2+1][csx2])==1)
&&(egalite(mat[csy][csx],mat[csy2+2][csx2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);

  }//not responding -___- in top left botton
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2][csx2+1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2+2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
destroy(csx2,csy2,csx2+1,csy2,csx2+2,csy2,tab);

  }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2][csx2-1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2-2])==1))
  {ok=1;d=1;

                 swap(csy,csx,csx2,csy2);
        destroy(csx2,csy2,csx2-1,csy2,csx2-2,csy2,tab);

  }
else if((d==0)&&(egalite(mat[csy][csx],mat[csy2][csx2-1])==1)
&&(egalite(mat[csy][csx],mat[csy2][csx2+1])==1))
  {ok=1;
d=1;
                 swap(csy,csx,csx2,csy2);
     destroy(csx2,csy2,csx2-1,csy2,csx2+1,csy2+1,tab);
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

return EXIT_SUCCESS;

}












