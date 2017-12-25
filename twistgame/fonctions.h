

enum {E=6};
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

enum {H=6};






SDL_Surface *ecran=NULL;
int egalite();
void destroy();
void swap();
void fillrect();


//fonctions
void  initmat(nomimage tab[])
{int i,j,k;



srand(time(NULL));
for(i=0;i<10;i++)
{for(j=0;j<11;j++)
{k=rand()%7; //gives a random number to k beetween 0 and 6;
mat[i][j].img=SDL_LoadBMP(tab[k].ch);
strcpy (mat[i][j].noimg,tab[k].ch);
}

}
}

int egalite(int csy,int csx,int csy2,int csx2)
{
if(csy2<0 || csy2>9)return 0;
if(csx2<0 || csx2>10)return 0;
if(strcmp(mat[csy][csx].noimg,mat[csy2][csx2].noimg)==0) return 1;
return 0;
}

//GREEN
void fillrect(rect img)
{
SDL_FillRect(img.img,NULL,SDL_MapRGB(img.img->format,0,255,0));
}

//permutation entre la case sélectionne 1 et la cs2
void swap(int csy,int csx,int csx2,int csy2)
{char temp[20]; void change();
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

void swap_destroy(int csy,int csx,int csx2,int csy2)
{
char temp[20]; void change();
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


SDL_BlitSurface(mat[csy][csx].img,NULL,ecran,&pos1);
//destroy the second argument
fillrect(mat[csy2][csx2]);
SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos2);
SDL_Flip(ecran);
}


void reswap(int csy,int csx,int csx2,int csy2)
{
swap(csy,csx,csx2,csy2);

swap(csy2,csx2,csx,csy);

}

void decalage(int csx2,int csy2,int x3,int y3,int x4,int y4,nomimage tab[])
{int k;SDL_Rect pos;


int cy2=csy2,cy3=y3,cy4=y4,cx3=x3,cx2=csx2,cx4=x4; //copy of the cordi;
int sum=csy2+y3+y4;
//1 er cas décalage horizontal
if((csx2!=x3&&csx2!=x4)&&(csy2==y3&&csy2==y4))
{
while(csy2>0)
{  SDL_FreeSurface(mat[csy2][csx2].img);
  SDL_FreeSurface(mat[y3][x3].img);
  SDL_FreeSurface(mat[y4][x4].img);

mat[csy2][csx2].img=SDL_LoadBMP(mat[csy2-1][csx2].noimg); strcpy(mat[csy2][csx2].noimg,mat[csy2-1][csx2].noimg);
mat[y3][x3].img=SDL_LoadBMP(mat[y3-1][x3].noimg);        strcpy(mat[y3][x3].noimg,mat[y3-1][x3].noimg);
mat[y4][x4].img=SDL_LoadBMP(mat[y4-1][x4].noimg);       strcpy(mat[y4][x4].noimg,mat[y4-1][x4].noimg);

pos.x=csx2*80 ;pos.y=csy2*80;
SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos);

pos.x=x3*80 ;pos.y=y3*80;
SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80 ;pos.y=y4*80;
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos);

SDL_Flip(ecran);
SDL_Delay(400);


csy2--; y3--; y4--;


}


k=rand()%7;
mat[csy2][csx2].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat[csy2][csx2].noimg,tab[k].ch);
k=rand()%7;
mat[y3][x3].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat[y3][x3].noimg,tab[k].ch);
k=rand()%7;
mat[y4][x4].img=SDL_LoadBMP(tab[k].ch); strcpy(mat[y4][x4].noimg,tab[k].ch);

pos.x=csx2*80 ;pos.y=csy2*80;
SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos);

pos.x=x3*80 ;pos.y=y3*80;
SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80 ;pos.y=y4*80;
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos);


}
//2éme cas décalage vertical

else if(csx2==x3&&csx2==x4)
{int cy2=0,cy3=1,cy4=2,cx3=x3,cx2=csx2,cx4=x4; //copy of the cordi;

while(csy2>2||y3>2||y4>2)
{
  SDL_FreeSurface(mat[csy2][csx2].img);
  SDL_FreeSurface(mat[y3][x3].img);
  SDL_FreeSurface(mat[y4][x4].img);

mat[csy2][csx2].img=SDL_LoadBMP(mat[csy2-3][csx2].noimg);
strcpy(mat[csy2][csx2].noimg,mat[csy2-3][csx2].noimg);

mat[y3][x3].img=SDL_LoadBMP(mat[y3-3][x3].noimg);
strcpy(mat[y3][x3].noimg,mat[y3-3][x3].noimg);

mat[y4][x4].img=SDL_LoadBMP(mat[y4-3][x4].noimg);
strcpy(mat[y4][x4].noimg,mat[y4-3][x4].noimg);


pos.x=csx2*80 ;pos.y=csy2*80;
SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos);

pos.x=x3*80 ;pos.y=y3*80;
SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80 ;pos.y=y4*80;
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos);



SDL_Flip(ecran);






csy2=csy2-3;y3=y3-3;y4=y4-3;
SDL_Delay(400);
printf("%d\n",csy2);
printf("%d\n",y3);
printf("%d\n",y4);
}

if((sum%5==0)||(sum==6))
{
SDL_FreeSurface(mat[3][cx3].img);
mat[3][cx3].img=SDL_LoadBMP(mat[0][cx3].noimg);
strcpy(mat[3][cx3].noimg,mat[0][cx3].noimg);

pos.x=cx3*80 ;pos.y=3*80;
SDL_BlitSurface(mat[3][cx3].img,NULL,ecran,&pos);

}
else if((sum==18)||(sum==9))
{
SDL_FreeSurface(mat[4][cx3].img);
mat[4][cx3].img=SDL_LoadBMP(mat[1][cx3].noimg);
strcpy(mat[4][cx3].noimg,mat[1][cx3].noimg);


pos.x=cx3*80 ;pos.y=4*80;
SDL_BlitSurface(mat[4][cx3].img,NULL,ecran,&pos);

SDL_FreeSurface(mat[3][cx3].img);
mat[3][cx3].img=SDL_LoadBMP(mat[0][cx3].noimg);
strcpy(mat[3][cx3].noimg,mat[0][cx3].noimg);

pos.x=cx3*80 ;pos.y=3*80;
SDL_BlitSurface(mat[3][cx3].img,NULL,ecran,&pos);

}

  SDL_FreeSurface(mat[cy2][cx2].img);
  SDL_FreeSurface(mat[cy3][cx3].img);
  SDL_FreeSurface(mat[cy4][cx4].img);

k=rand()%7;
mat[cy2][cx2].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat[cy2][cx2].noimg,tab[k].ch);
k=rand()%7;
mat[cy3][cx3].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat[cy3][cx3].noimg,tab[k].ch);
k=rand()%7;
mat[cy4][cx4].img=SDL_LoadBMP(tab[k].ch); strcpy(mat[cy4][cx4].noimg,tab[k].ch);

pos.x=cx2*80 ;pos.y=cy2*80;
SDL_BlitSurface(mat[cy2][cx2].img,NULL,ecran,&pos);

pos.x=cx3*80 ;pos.y=cy3*80;
SDL_BlitSurface(mat[cy3][cx3].img,NULL,ecran,&pos);

pos.x=cx4*80 ;pos.y=cy4*80;
SDL_BlitSurface(mat[cy4][cx4].img,NULL,ecran,&pos);



}






SDL_Flip(ecran);


}


//détruire les 3 cases
void destroy(int csx2,int csy2,int x3,int y3,int x4,int y4,nomimage tab[])
{
SDL_Rect pos;void decalage();
//fill the destroyed cases with green

fillrect(mat[y3][x3]); fillrect(mat[y4][x4]);
fillrect(mat[csy2][csx2]);

pos.x=csx2*80; pos.y=csy2*80;
SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos);



pos.x=x3*80; pos.y=y3*80;
SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos);



pos.x=x4*80; pos.y=y4*80;
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos);


SDL_Flip(ecran);
SDL_Delay(400);
//TESTING

//apelle a la fonction decalage (delated)

decalage(csx2,csy2,x3,y3,x4,y4,tab);

printf("%s\n",mat[csx2][csy2].noimg);
printf("%s\n",mat[y4][x4].noimg);
printf("%s\n",mat[y3][x4].noimg);

}

int max3(int x, int y, int z)
{
  if(x > y)
  {
     if(x > z)
       return x;
     else
       return z;
  }
  else
  {
     if(y > z)
       return y;
     else
       return z;
  }
}


int max4(int x,int y,int z,int w)
{int m=max3(x,y,z);
if(m>w)return  m;
else return w;

}
int max5(int a,int b,int c,int d,int e)
{int m=max4(a,b,c,d);
if(m>e)return m;
return e;
}


//still beta not tested yet
void destroy4(int csx2,int csy2,int x3,int y3,int x4,int y4,int x5,int y5,nomimage tab[])
{
    int i;   int  recherche();void decalage4();
    SDL_Rect pos2,pos3,pos4,pos5;void decalage();
    fillrect(mat[y3][x3]); fillrect(mat[y4][x4]);
    fillrect(mat[csy2][csx2]); fillrect(mat[y5][x5]);

    pos3.x=x3*80;   pos3.y=y3*80;   pos4.x=x4*80;    pos4.y=y4*80;
    pos2.x=csx2*80; pos2.y=csy2*80;  pos5.x=x5*80;  pos5.y=y5*80;


SDL_BlitSurface(mat[y5][x5].img,NULL,ecran,&pos5);

SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos3);

SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos4);



i=recherche(mat[csy2][csx2].noimg,tab);
SDL_FreeSurface(mat[csy2][csx2].img);
mat[csy2][csx2].img=SDL_LoadBMP(tab[i+7].ch);  strcpy(mat[csy2][csx2].noimg,tab[i+7].ch);

SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos2);

SDL_Flip(ecran);
SDL_Delay(400);
    decalage4(csx2,csy2,x3,y3,x4,y4,x5,y5,tab);
}
int recherche(char ch[20],nomimage tab[])
{
    int i=0;
    for(i=0;i<=6;i++)
    {if(strcmp(ch,tab[i].ch)==0) return i;

    }


}



//Still in beta version not tested
void decalage4(int csx2,int csy2,int x3,int y3,int x4,int y4,int x5,int y5,nomimage tab[])
{int max=max4(csy2,y3,y4,y5);void decalage();
//1er cas decalage horizontal
printf("%d",max);
if((csx2!=x3&&csx2!=x4&&csx2!=x5)&&(csy2==y3&&csy2==y4&&csy2==y5)) decalage(x3,y3,x4,y4,x5,y5,tab);

else if((csx2==x3)&&(csx2==x4)&&(csx2==x5))
{SDL_Rect pos;

if(max==csy2) decalage(x3,y3,x4,y4,x5,y5,tab);
else
{

swap_destroy(max,x3,csx2,csy2);


SDL_Delay(1000);
if(max==y3)
decalage(csx2,csy2,x4,y4,x5,y5,tab);
else if(max==y4) decalage(csx2,csy2,x3,y3,x5,y5,tab);
else decalage(csx2,csy2,x3,y3,x4,y4,tab);

}



}
}


//still beta not tested yet
void destroy5(int csx2,int csy2,int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6,nomimage tab[])
{
    int i;
    SDL_Rect pos2,pos3,pos4,pos5,pos6;void decalage();
    fillrect(mat[y3][x3]); fillrect(mat[y4][x4]);
    fillrect(mat[csy2][csx2]); fillrect(mat[y5][x5]);fillrect(mat[x6][y6]);

    pos3.x=x3*80;   pos3.y=y3*80;   pos4.x=x4*80;    pos4.y=y4*80; pos6.y=y6*80;

    pos2.x=csx2*80; pos2.y=csy2*80;  pos5.x=x5*80;  pos5.y=y5*80; pos6.x=x6*80;

//blite with green
SDL_BlitSurface(mat[y5][x5].img,NULL,ecran,&pos5);
SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos3);
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos4);
SDL_BlitSurface(mat[x6][y6].img,NULL,ecran,&pos6);



i=recherche(mat[csy2][csx2].noimg,tab);

mat[csy2][csx2].img=SDL_LoadBMP(tab[i+14].ch);  strcpy(mat[csy2][csx2].noimg,tab[i+14].ch);

SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos2);

SDL_Flip(ecran);
SDL_Delay(400);
    decalage5(csx2,csy2,x3,y3,x4,y4,x5,y5,x6,y6,tab);
}

//tested
void decalage4_v(int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6,nomimage tab[])
{//decalage vertical
int cy3=0,cy4=1,cy5=2,cy6=3,cx3=x3,cx4=x4,cx5=x5,cx6=x6,k; //copy of the cordi;
SDL_Rect pos;
int sum=y3+y4+y5+y6;
while(y3>3||y4>3||y5>3)
{
  SDL_FreeSurface(mat[y3][x3].img);
  SDL_FreeSurface(mat[y4][x4].img);
  SDL_FreeSurface(mat[y5][x5].img);
  SDL_FreeSurface(mat[y6][x6].img);

mat[y3][x3].img=SDL_LoadBMP(mat[y3-4][x3].noimg);
strcpy(mat[y3][x3].noimg,mat[y3-4][x3].noimg);

mat[y4][x4].img=SDL_LoadBMP(mat[y4-4][x4].noimg);
strcpy(mat[y4][x4].noimg,mat[y4-4][x4].noimg);

mat[y5][x5].img=SDL_LoadBMP(mat[y5-4][x5].noimg);
strcpy(mat[y5][x5].noimg,mat[y5-4][x5].noimg);

mat[y6][x6].img=SDL_LoadBMP(mat[y6-4][x6].noimg);
strcpy(mat[y6][x6].noimg,mat[y6-4][x6].noimg);


pos.x=x3*80 ;pos.y=y3*80;
SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80 ;pos.y=y4*80;
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos);

pos.x=x5*80 ;pos.y=y5*80;
SDL_BlitSurface(mat[y5][x5].img,NULL,ecran,&pos);

pos.x=x6*80 ;pos.y=y6*80;
SDL_BlitSurface(mat[y6][x6].img,NULL,ecran,&pos);

SDL_Flip(ecran);


y3=y3-4;y4=y4-4;y5=y5-4;y6=y6-4;
SDL_Delay(400);
printf("%d\n",y3);
printf("%d\n",y4);
printf("%d\n",y5);
printf("%d\n",y6);
}

if((sum==10)||(sum==26))
{
SDL_FreeSurface(mat[4][cx4].img);
mat[4][cx4].img=SDL_LoadBMP(mat[0][cx4].noimg);
strcpy(mat[4][cx4].noimg,mat[0][cx4].noimg);

pos.x=cx4*80 ;pos.y=4*80;
SDL_BlitSurface(mat[4][cx4].img,NULL,ecran,&pos);

}
else if((sum==14)||(sum==30))
{
SDL_FreeSurface(mat[5][cx4].img);
mat[5][cx4].img=SDL_LoadBMP(mat[1][cx4].noimg);
strcpy(mat[5][cx4].noimg,mat[1][cx4].noimg);


pos.x=cx4*80 ;pos.y=5*80;
SDL_BlitSurface(mat[5][cx4].img,NULL,ecran,&pos);



SDL_FreeSurface(mat[4][cx4].img);
mat[4][cx4].img=SDL_LoadBMP(mat[0][cx4].noimg);
strcpy(mat[4][cx4].noimg,mat[0][cx4].noimg);

pos.x=cx4*80 ;pos.y=4*80;
SDL_BlitSurface(mat[4][cx4].img,NULL,ecran,&pos);

}else if(sum==18)
{

SDL_FreeSurface(mat[6][cx4].img);
mat[6][cx4].img=SDL_LoadBMP(mat[2][cx4].noimg);
strcpy(mat[6][cx4].noimg,mat[2][cx4].noimg);


pos.x=cx4*80 ;pos.y=6*80;
SDL_BlitSurface(mat[6][cx4].img,NULL,ecran,&pos);



SDL_FreeSurface(mat[5][cx4].img);
mat[5][cx4].img=SDL_LoadBMP(mat[1][cx4].noimg);
strcpy(mat[5][cx4].noimg,mat[1][cx4].noimg);

pos.x=cx4*80 ;pos.y=5*80;
SDL_BlitSurface(mat[5][cx4].img,NULL,ecran,&pos);


SDL_FreeSurface(mat[4][cx4].img);
mat[4][cx4].img=SDL_LoadBMP(mat[0][cx4].noimg);
strcpy(mat[4][cx4].noimg,mat[0][cx4].noimg);

pos.x=cx4*80 ;pos.y=4*80;
SDL_BlitSurface(mat[4][cx4].img,NULL,ecran,&pos);

}
 //libérer l'espace mémoire de les 4 derniers cases
  SDL_FreeSurface(mat[cy3][cx3].img);
  SDL_FreeSurface(mat[cy4][cx4].img);
  SDL_FreeSurface(mat[cy5][cx5].img);
  SDL_FreeSurface(mat[cy6][cx6].img);
//affecter les 4 derniers cases au hasard
k=rand()%7;
mat[cy3][cx3].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat[cy3][cx3].noimg,tab[k].ch);
k=rand()%7;
mat[cy4][cx4].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat[cy4][cx4].noimg,tab[k].ch);
k=rand()%7;
mat[cy5][cx5].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat[cy5][cx5].noimg,tab[k].ch);
k=rand()%7;
mat[cy6][cx6].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat[cy6][cx6].noimg,tab[k].ch);






//affichier les images (les 4 derniers  cases)
pos.x=cx3*80 ;pos.y=cy3*80;
SDL_BlitSurface(mat[cy3][cx3].img,NULL,ecran,&pos);

pos.x=cx4*80 ;pos.y=cy4*80;
SDL_BlitSurface(mat[cy4][cx4].img,NULL,ecran,&pos);

pos.x=cx5*80 ;pos.y=cy5*80;
SDL_BlitSurface(mat[cy5][cx5].img,NULL,ecran,&pos);

pos.x=cx6*80 ;pos.y=cy6*80;
SDL_BlitSurface(mat[cy6][cx6].img,NULL,ecran,&pos);


//mise a jour l'ecran
SDL_Flip(ecran);



}







//beta not tested yet

void decalage5(int csx2,int csy2,int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6,nomimage tab[])
{
SDL_Rect pos;int k;
//1 er cas décalage horizontal
if((csx2!=x3&&csx2!=x4)&&(csy2==y3&&csy2==y4))
{
while(y3>0)
{ SDL_FreeSurface(mat[y5][x5].img);
  SDL_FreeSurface(mat[y3][x3].img);       SDL_FreeSurface(mat[y6][x6].img);
  SDL_FreeSurface(mat[y4][x4].img);


mat[y3][x3].img=SDL_LoadBMP(mat[y3-1][x3].noimg);        strcpy(mat[y3][x3].noimg,mat[y3-1][x3].noimg);
mat[y4][x4].img=SDL_LoadBMP(mat[y4-1][x4].noimg);        strcpy(mat[y4][x4].noimg,mat[y4-1][x4].noimg);
mat[y5][x5].img=SDL_LoadBMP(mat[y5-1][x5].noimg);        strcpy(mat[y5][x5].noimg,mat[y5-1][x5].noimg);
mat[y6][x6].img=SDL_LoadBMP(mat[y6-1][x6].noimg);        strcpy(mat[y6][x6].noimg,mat[y6-1][x6].noimg);


//affichage des images dans l'ecran
pos.x=x3*80 ;pos.y=y3*80;
SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80 ;pos.y=y4*80;
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos);

pos.x=x5*80 ;pos.y=y5*80;
SDL_BlitSurface(mat[y5][x5].img,NULL,ecran,&pos);

pos.x=x6*80 ;pos.y=y6*80;
SDL_BlitSurface(mat[y6][x6].img,NULL,ecran,&pos);



SDL_Flip(ecran);
SDL_Delay(400);


 y3--; y4--; y5--; y6--;


}
//affections les  4 derniers cases
k=rand()%7;
mat[y3][x3].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat[y3][x3].noimg,tab[k].ch);
k=rand()%7;
mat[y4][x4].img=SDL_LoadBMP(tab[k].ch); strcpy(mat[y4][x4].noimg,tab[k].ch);
k=rand()%7;
mat[y5][x5].img=SDL_LoadBMP(tab[k].ch); strcpy(mat[y5][x5].noimg,tab[k].ch);
k=rand()%7;
mat[y6][x6].img=SDL_LoadBMP(tab[k].ch); strcpy(mat[y6][x6].noimg,tab[k].ch);

//affichage des images dans l'ecran
pos.x=x3*80 ;pos.y=y3*80;
SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80 ;pos.y=y4*80;
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos);



pos.x=x5*80 ;pos.y=y5*80;
SDL_BlitSurface(mat[y5][x5].img,NULL,ecran,&pos);

pos.x=x6*80 ;pos.y=y6*80;
SDL_BlitSurface(mat[y6][x6].img,NULL,ecran,&pos);
SDL_Flip(ecran);

}

//2éme cas decalage vertical
else
{int max=max5(csy2,y3,y4,y5,y6);SDL_Rect pos,pos2;
if (max==csy2) decalage4_v( x3, y3, x4, y4, x5,  y5, x6, y6, tab);
else{



swap_destroy(max,x3,csx2,csy2);

SDL_Delay(4000);


if(max==y3) decalage4_v(csy2,csx2,x4,y4,x5,y5,x6,y6,tab);
else if(max==y4) decalage4_v(x3,y3,csx2,csy2,x5,y5,x6,y6,tab);
else if(max==y5) decalage4_v(x3,y3,x4,y4,csx2,csy2,x6,y6,tab);
else if(max==y6) decalage4_v(x3,y3,x4,y4,x5,y5,csy2,csx2,tab);

}

}

}

//still beta not tested
//cas de csy2-1 ,csy2+1
int verf_1_1(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
  if(egalite(csy,csx,csy2-2,csx2)==1)
   {  if(egalite(csy,csx,csy2-3,csx2)==1)
   {
   swap(csy,csx,csx2,csy2);
   destroy5(csx2,csy2,csx2,csy2-1,csx2,csy2+1,
   csx2,csy2-2,csx2,csy-3,tab);
   return 1;
   }
   swap(csy,csx,csx2,csy2);
   destroy4(csx2,csy2,csx2,csy2-1,csx2,csy2+1,
   csx2,csy2-2,tab);
   return 1;
   }else if(egalite(csy,csx,csy2+2,csx2)==1)
   {if(egalite(csy,csx,csy2+3,csx2)==1)
   {swap(csy,csx,csx2,csy2);
   destroy5(csx2,csy2,csx2,csy2-1,csx2,csy2+1,
   csx2,csy2+2,csx2,csy+3,tab);
   return 1;
   }
   swap(csy,csx,csx2,csy2);
   destroy4(csx2,csy2,csx2,csy2-1,csx2,csy2+1,
   csx2,csy2+2,tab);
   return 1;
   }
   return 0;

}
//cas csx2-1 ,csx2-2
int verf_1_2(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
   if(egalite(csy,csx,csy2,csx2-3)==1)
  {
      if(egalite(csy,csx,csy2,csx2-4)==1)
      {
      swap(csy,csx,csx2,csy2);
      destroy5(csx2,csy2,csx2-1,csy2,csx2-2,csy2,csx2-3,csy2,
      csx2-4,csy2,tab);
      return 1;
      }
      swap(csy,csx,csx2,csy2);
      destroy4(csx2,csy2,csx2-1,csy2,csx2-2,csy2,csx2-3,csy2,tab);
      return 1;
  }else return 0;

}
//cas csy2-1,csy2-2
int verf_1_3(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
       // cas 4 cases
   if (egalite(csy,csx,csy2-3,csx2)==1)
   {
   {if(egalite(csy,csx,csy2-4,csx2)==1)
   //5 cases
   swap(csy,csx,csx2,csy2);
   destroy5(csx2,csy2,csx2,csy2-1,csx2,csy2-2,csx2,csy2-3,csx2
   ,csy2-4,tab);

   return 1;
   }
   swap(csy,csx,csx2,csy2);
   destroy4(csx2,csy2,csx2,csy2-1,csx2,csy2-2,csx2,csy2-3,tab);
   return 1;
   }else return 0;


}

//cas csy2+1,csy2+2
int verf_1_4(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
    if(egalite(csy,csx,csy2+3,csx2)==1)
    {if(egalite(csy,csx,csy2+4,csx2)==1)
    {//appele destroy 5
    swap(csy,csx,csx2,csy2);
    destroy5(csx2,csy2,csx2,csy2+1,csx2,csy2+2,csx2,csy2+3,csx2,
    csy2+4,tab);
    return 1;
    }else
    swap(csy,csx,csx2,csy2);
    destroy4(csx2,csy2,csx2,csy2+1,csx2,csy2+2,csx2,csy2+3,tab);
    return 1;
    }else return 0;

}

//cas csx2+1,csx2+2
int verf_1_5(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
 if(egalite(csy,csx,csy2,csx2+3)==1)
 {
    if(egalite(csy,csx,csy2,csx2+4)==1)
     {
     swap(csy,csx,csx2,csy2);
     destroy5(csx2,csy2,csx2+1,csy2,csx2+2,csy2,csx2+3,csy2,
     csx2+4,csy2,tab);
      return 1;
     }else
   { //apelle
    swap(csy,csx,csx2,csy2);
    destroy4(csx2,csy2,csx2+1,csy2,csx2+2,csy2,csx2+3,csy2,tab);
    return 1;
    }
 }else return 0;

}
//cas csx2+1,csx2-1
int verf_1_6(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
    if(egalite(csy,csx,csy2,csx2+2)==1)
     {if(egalite(csy,csx,csy2,csx2+3)==1)
     {
     swap(csy,csx,csx2,csy2);
     destroy5(csx2,csy2,csx2+1,csy2,csx2-1,csy2,csx2+2,
     csy2,csx2+3,csy2,tab);
     return 1;
     }
     swap(csy,csx,csx2,csy2);
     destroy4(csx2,csy2,csx2+1,csy2,csx2-1,csy2,csx2+2,
    csy2,tab);
    return 1;
     }else if(egalite(csy,csx,csy2,csx2-2)==1)
     {if(egalite(csy,csx,csy2,csx2-3)==1)
     {
     swap(csy,csx,csx2,csy2);
     destroy5(csx2,csy2,csx2+1,csy2,csx2-1,csy2,csx2-2,
     csy2,csx2-3,csy2,tab);
     return 1;
     }
     swap(csy,csx,csx2,csy2);
     destroy4(csx2,csy2,csx2+1,csy2,csx2-1,csy2,csx2-2,csy2,tab);
     return 1;
     }
return 0;


}


//
void verification_global(int csx,int csy,int csx2,int csy2,nomimage tab[],int i)
{int d=0,ok;
///////////////////////1er cas
if(csy2==csy&&csx2==abs(csx-1))
     {
if((d==0)&&(egalite(csy,csx,csy2-1,csx2)==1)
&&(egalite(csy,csx,csy2+1,csx2)==1))
    {ok=1;d=1;
                if(verf_1_1(csx,csy,csx2,csy2,tab)==0)
               {swap(csy,csx,csx2,csy2);
                destroy(csx2,csy2,csx2,csy2-1,csx2,csy2+1,tab);
               }
}
else if((d==0)&&(egalite(csy,csx,csy2+1,csx2)==1)
&&(egalite(csy,csx,csy2+2,csx2)==1))
    {ok=1;d=1;
       if(verf_1_4(csx,csy,csx2,csy2,tab)==0)
      {
      swap(csy,csx,csx2,csy2);
      destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);
      }
    }
else if((d==0)&&(egalite(csy,csx,csy2-1,csx2)==1)
&&(egalite(csy,csx,csy2-2,csx2)==1))
   {ok=1;d=1;
   if(verf_1_3(csx,csy,csx2,csy2,tab)==0)
     {
     swap(csy,csx,csx2,csy2);
     destroy(csx2,csy2,csx2,csy2-1,csx2,csy2-2,tab);
     }
   }
else if((d==0)&&(egalite(csy,csx,csy2,csx2-1)==1)
&&(egalite(csy,csx,csy2,csx2-2)==1))
  {ok=1;d=1;
        if(verf_1_2(csx,csy,csx2,csy2,tab)==0)
        {
        swap(csy,csx,csx2,csy2);
        destroy(csx2,csy2,csx2-1,csy2,csx2-2,csy2,tab);
        }
  }else if(i==1) reswap(csy,csx,csx2,csy2);

}

//////////////////////2eme cas

if (csy2==csy&&csx2==abs(csx+1))
{ if((d==0)&&(egalite(csy,csx,csy2+1,csx2)==1)
&&(egalite(csy,csx,csy2+2,csx2)==1))
   {ok=1;d=1;
               if(verf_1_4(csx,csy,csx2,csy2,tab)==0)
                { swap(csy,csx,csx2,csy2);
                    destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);
                }
                                                                     }




else if((d==0)&&(egalite(csy,csx,csy2-1,csx2)==1)
&&(egalite(csy,csx,csy2-2,csx2)==1))
  {ok=1;d=1;
         if(verf_1_3(csx,csy,csx2,csy2,tab)==0)
           { swap(csy,csx,csx2,csy2);
                     destroy(csx2,csy2,csx2,csy2-1,csx2,csy2-2,tab);
           }
  }



else if((d==0)&&(egalite(csy,csx,csy2,csx2+1)==1)
&&(egalite(csy,csx,csy2,csx2+2)==1))
  {ok=1;d=1;
if(verf_1_5(csx,csy,csx2,csy2,tab)==0)
     {
     swap(csy,csx,csx2,csy2);
     destroy(csx2,csy2,csx2+1,csy2,csx2+2,csy2,tab);
     }
  }
else if((d==0)&&(egalite(csy,csx,csy2-1,csx2)==1)
&&(egalite(csy,csx,csy2+1,csx2)==1))
  {ok=1;d=1;
   if(verf_1_1(csx,csy,csx2,csy2,tab)==0)
   {  swap(csy,csx,csx2,csy2);
    destroy(csx2,csy2,csx2,csy2-1,csx2,csy2+1,tab);
   }

  }
else if((d==0)&&(egalite(csy,csx,csy2+1,csx2)==1)
&&(egalite(csy,csx,csy2+2,csx2)==1))
  {ok=1;d=1;
if(verf_1_4(csx,csy,csx2,csy2,tab)==0)
 {
    swap(csy,csx,csx2,csy2);
    destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);
  }
  }else if(i==1) reswap(csy,csx,csx2,csy2);

}
////////////////////////3eme cas
if (csy2==abs(csy-1)&&csx2==csx)
{if((d==0)&&egalite(csy,csx,csy2,csx2+1)==1
&&(egalite(csy,csx,csy2,csx2-1)==1))
  {ok=1;d=1;
if(verf_1_6(csx,csy,csx2,csy2,tab)==0)
   {
    swap(csy,csx,csx2,csy2);
    destroy(csx2,csy2,csx2+1,csy2,csx2-1,csy2,tab);
    }
  }
else if((d==0)&&(egalite(csy,csx,csy2-1,csx2)==1)
&&(egalite(csy,csx,csy2-2,csx2)==1))
  {ok=1;d=1;
if(verf_1_3(csx,csy,csx2,csy2,tab)==0)
    {    swap(csy,csx,csx2,csy2);
         destroy(csx2,csy2,csx2,csy2-1,csx2,csy2-2,tab);
    }
  }
else if((d==0)&&(egalite(csy,csx,csy2,csx2+1)==1)
&&(egalite(csy,csx,csy2,csx2+2)==1))
  {ok=1;d=1;
if(verf_1_5(csx,csy,csx2,csy2,tab)==0)
      {   swap(csy,csx,csx2,csy2);
          destroy(csx2,csy2,csx2+1,csy2,csx2+2,csy2,tab);
      }
  }
else if((d==0)&&(egalite(csy,csx,csy2,csx2-1)==1)
&&(egalite(csy,csx,csy2,csx2-2)==1))
  {ok=1;d=1;
if(verf_1_2(csx,csy,csx2,csy2,tab)==0)
       {swap(csy,csx,csx2,csy2);
        destroy(csx2,csy2,csx2-1,csy2,csx2-2,csy2,tab);
        }
  }
else if((d==0)&&(egalite(csy,csx,csy2,csx2-1)==1)
&&(egalite(csy,csx,csy2,csx2+1)==1))
  {ok=1;d=1;
        if(verf_1_6(csx,csy,csx2,csy2,tab)==0)
           {  swap(csy,csx,csx2,csy2);
              destroy(csx2,csy2,csx2-1,csy2,csx2+1,csy2,tab);
           }
  }else if(i==1)reswap(csy,csx,csx2,csy2);


}
//////////////////////////// 4eme cas
if (csy2==csy+1&&csx2==csx)
  {
   if((d==0)&&(egalite(csy,csx,csy2,csx2+1)==1)
   &&(egalite(csy,csx,csy2,csx2-1)==1))
    {ok=1;d=1;
          if(verf_1_6(csx,csy,csx2,csy2,tab)==0)
            {
            swap(csy,csx,csx2,csy2);
            destroy(csx2,csy2,csx2+1,csy2,csx2-1,csy2,tab);
            }
    }
else if((d==0)&&(egalite(csy,csx,csy2+1,csx2)==1)
&&(egalite(csy,csx,csy2+2,csx2)==1))
  {ok=1;d=1;
    if(verf_1_4(csx,csy,csx2,csy2,tab)==0)
    {  swap(csy,csx,csx2,csy2);
     destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);
    }
  }//not responding -___- in top left botton
else if((d==0)&&(egalite(csy,csx,csy2,csx2+1)==1)
&&(egalite(csy,csx,csy2,csx2+2)==1))
  {ok=1;d=1;
    if(verf_1_5(csx,csy,csx2,csy2,tab)==0)
    {
     swap(csy,csx,csx2,csy2);
     destroy(csx2,csy2,csx2+1,csy2,csx2+2,csy2,tab);
    }
  }
else if((d==0)&&(egalite(csy,csx,csy2,csx2-1)==1)
&&(egalite(csy,csx,csy2,csx2-2)==1))
  {ok=1;d=1;
if(verf_1_2(csx,csy,csx2,csy2,tab)==0)
       {swap(csy,csx,csx2,csy2);
        destroy(csx2,csy2,csx2-1,csy2,csx2-2,csy2,tab);
                                                       }
  }
else if((d==0)&&(egalite(csy,csx,csy2,csx2-1)==1)
&&(egalite(csy,csx,csy2,csx2+1)==1))
   {ok=1; d=1;
       if(verf_1_6(csx,csy,csx2,csy2,tab)==0)
         {swap(csy,csx,csx2,csy2);
          destroy(csx2,csy2,csx2-1,csy2,csx2+1,csy2+1,tab);
                                                            }

     }else if(i==1) reswap(csy,csx,csx2,csy2);

}

  if((d==0)&&(i==0)) verification_global(csx2,csy2,csx,csy,tab,1);



}
