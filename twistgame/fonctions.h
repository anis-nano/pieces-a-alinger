
enum {E=6};
typedef struct
{
char ch[20];
}nomimage; //declaration global

SDL_Event event,event2,event3;
typedef struct
{SDL_Surface *img;
char noimg[6];
}rect;

SDL_Surface *menu=NULL,*background=NULL;
SDL_Surface *button_aide=NULL;
SDL_Surface *button_pause=NULL;
SDL_Surface *text=NULL;
enum {N=11};enum {M=12};
rect mat[N][M];rect mat2[N][M];

enum {H=6};





SDL_Surface *ecran=NULL;
int egalite();
void destroy();
void swap();
void fillrect();


//fonctions
void  initmat(nomimage tab[])
{
int i,j,k;SDL_Rect pos;

srand(time(NULL));
for(i=0;i<10;i++)
{for(j=0;j<11;j++)
{k=rand()%7; //gives a random number to k beetween 0 and 6;
mat[i][j].img=SDL_LoadBMP(tab[k].ch);
strcpy (mat[i][j].noimg,tab[k].ch);
}
}

i=0; j=0;pos.y=0;

for(i=0;i<10;i++)
{pos.x=0;
for(j=0;j<11;j++)
{
SDL_BlitSurface(mat[i][j].img,NULL,ecran,&pos);
pos.x=pos.x+80;
}
pos.y=pos.y+80;
}
SDL_Flip(ecran);


}




void  initmat2(nomimage tab[])
{int i,j,k;SDL_Rect pos;

srand(time(NULL));
for(i=0;i<10;i++)
{for(j=0;j<11;j++)
{k=rand()%7; //gives a random number to k beetween 0 and 6;
mat2[i][j].img=SDL_LoadBMP(tab[k].ch);
strcpy(mat2[i][j].noimg,tab[k].ch);
}
}

i=0; j=0;pos.y=0;
for(i=0;i<10;i++)
{pos.x=1020;
for(j=0;j<11;j++)
{
SDL_BlitSurface(mat2[i][j].img,NULL,ecran,&pos);
pos.x=pos.x+80;
}
pos.y=pos.y+80;
}
SDL_Flip(ecran);
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
{ SDL_FreeSurface(mat[csy2][csx2].img);
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
{void decalage();

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

decalage(csx2,csy2,x3,y3,x4,y4,tab);test(tab);

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
    decalage4(csx2,csy2,x3,y3,x4,y4,x5,y5,tab);test(tab);
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
    SDL_Rect pos2,pos3,pos4,pos5,pos6;
    fillrect(mat[y3][x3]); fillrect(mat[y4][x4]);
    printf("%d %d\n",csy2,csx2);
    printf("%s\n",mat[csy2][csx2].noimg);

    fillrect(mat[csy2][csx2]);
    fillrect(mat[y5][x5]);
    fillrect(mat[y6][x6]);

    pos3.x=x3*80;      pos2.x=csx2*80;
    pos3.y=y3*80;
                       pos2.y=csy2*80;
    pos4.y=y4*80;
    pos4.x=x4*80;
    pos5.x=x5*80;      pos5.y=y5*80; pos6.x=x6*80;  pos6.y=y6*80;

//blite with green

SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos3);
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos4);
SDL_BlitSurface(mat[y5][x5].img,NULL,ecran,&pos5);
SDL_BlitSurface(mat[y6][x6].img,NULL,ecran,&pos6);



i=recherche(mat[csy2][csx2].noimg,tab);

mat[csy2][csx2].img=SDL_LoadBMP(tab[i+14].ch); //why not like strcpy
 strcpy(mat[csy2][csx2].noimg,tab[i+14].ch);
//rahi tbadel ta3 mat[8][10] tanit -________________________-" c'régler

SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos2);
pos2.x=10*80;pos2.y=8*80;
SDL_BlitSurface(mat[8][10].img,NULL,ecran,&pos2);
SDL_Flip(ecran);
SDL_Delay(400);
   decalage5(csx2,csy2,x3,y3,x4,y4,x5,y5,x6,y6,tab); test(tab);
}

//tested
void decalage4_v(int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6,nomimage tab[])
{//decalage vertical
int cy3=0,cy4=1,cy5=2,cy6=3,cx3=x3,cx4=x4,cx5=x5,cx6=x6,k; //copy de cordonnes;
SDL_Rect pos;
int sum=y3+y4+y5+y6;
while((y3>3)||(y4>3)||(y5>3)||(y6>3))
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


y3=y3-4; y4=y4-4; y5=y5-4; y6=y6-4;

SDL_Delay(400);
printf("end of the decalage_v loop\n");
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
SDL_Rect pos;int k;void decalage4_v();
//1 er cas décalage horizontal
if((csx2!=x3&&csx2!=x4)&&(csy2==y3&&csy2==y4))
{
while(y3>0)
{ SDL_FreeSurface(mat[y5][x5].img);
  SDL_FreeSurface(mat[y3][x3].img);
  SDL_FreeSurface(mat[y6][x6].img);
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



swap_destroy(max,x3,csx2,csy2);//swap

SDL_Delay(4000);


if(max==y3) decalage4_v(csy2,csx2,x4,y4,x5,y5,x6,y6,tab);
else if(max==y4) decalage4_v(x3,y3,csx2,csy2,x5,y5,x6,y6,tab);
else if(max==y5) decalage4_v(x3,y3,x4,y4,csx2,csy2,x6,y6,tab);
else if(max==y6) decalage4_v(x3,y3,x4,y4,x5,y5,csx2,csy2,tab);

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

   if(egalite(csy,csx,csy2-4,csx2)==1)
   //5 cases
   {
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
     }
     else if(egalite(csy,csx,csy2,csx2-2)==1)
     {
     if(egalite(csy,csx,csy2,csx2-3)==1)
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


//
void destroy_type2(int csx,int csy,nomimage tab[])
{
    int k;
    SDL_Rect pos,pos2,pos3,pos4,pos5,pos6,pos7,pos8,pos9;void decalage();
    fillrect(mat[csy][csx]); pos.x=csx*80;   pos.y=csy*80; SDL_BlitSurface(mat[csy][csx].img,NULL,ecran,&pos);
if((csx-1)>=0)  {
 fillrect(mat[csy][csx-1]); pos2.x=(csx-1)*80;    pos2.y=csy*80;SDL_BlitSurface(mat[csy][csx-1].img,NULL,ecran,&pos2);
 if((csy-1)>=0) {fillrect(mat[csy-1][csx-1]); pos3.x=(csx-1)*80; pos3.y=(csy-1)*80;SDL_BlitSurface(mat[(csy-1)][csx-1].img,NULL,ecran,&pos3);}
 if((csy+1)<=10) {fillrect(mat[csy-1][csx+1]); pos4.x=(csx+1)*80;  pos4.y=(csy-1)*80;SDL_BlitSurface(mat[csy-1][csx+1].img,NULL,ecran,&pos4);}
		}

if((csx+1)<=9) {
 fillrect(mat[csy][csx+1]); pos5.x=(csx+1)*80;  pos5.y=csy*80;SDL_BlitSurface(mat[csy][csx+1].img,NULL,ecran,&pos5);
 if((csy-1)>=0) {fillrect(mat[csy+1][csx-1]); pos6.x=(csx-1)*80;  pos6.y=(csy+1)*80;SDL_BlitSurface(mat[csy+1][csx-1].img,NULL,ecran,&pos6);}
 if((csy+1)<=10) {fillrect(mat[csy+1][csx+1]); pos7.x=(csx+1)*80;  pos7.y=(csy+1)*80;SDL_BlitSurface(mat[csy+1][csx+1].img,NULL,ecran,&pos7);}
 		}


if((csy-1)>=0) {fillrect(mat[csy-1][csx]);pos8.x=csx*80;  pos8.y=(csy-1)*80;SDL_BlitSurface(mat[csy-1][csx].img,NULL,ecran,&pos8);}
if((csy+1)<=10) {fillrect(mat[csy+1][csx]);pos9.x=csx*80;  pos9.y=(csy+1)*80;SDL_BlitSurface(mat[csy+1][csx].img,NULL,ecran,&pos9);}

if(((csy-1)>=0)&&((csy+1)<=10))
{
  if(((csx-1)>=0)&&((csx+1)<=9))
   {
	SDL_Flip(ecran);
	SDL_Delay(400);
	decalage((csx),csy,(csx),(csy+1),(csx),(csy-1),tab);
	decalage((csx-1),csy,(csx-1),(csy+1),(csx-1),(csy-1),tab);
	decalage((csx+1),csy,(csx+1),(csy+1),(csx+1),(csy-1),tab);
   }
    else if((csx-1)>=0)
		{
	SDL_Flip(ecran);
	SDL_Delay(400);
	decalage((csx),csy,(csx),(csy+1),(csx),(csy-1),tab);
	decalage((csx-1),csy,(csx-1),(csy+1),(csx-1),(csy-1),tab);
		}
	else if((csx+1)<=9)
		{
		SDL_Flip(ecran);
		SDL_Delay(400);
		decalage((csx),csy,(csx),(csy+1),(csx),(csy-1),tab);
		decalage((csx+1),csy,(csx+1),(csy+1),(csx+1),(csy-1),tab);
		}

}
if((csy-1)<0)
{
	k=rand()%7;
	mat[csy][csx].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy][csx].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy][csx].img,NULL,ecran,&pos);
	k=rand()%7;
	mat[csy+1][csx].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy+1][csx].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy+1][csx].img,NULL,ecran,&pos9);

     if((csx-1)>=0)
	{
	k=rand()%7;
	mat[csy][csx-1].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy][csx-1].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy][csx-1].img,NULL,ecran,&pos2);
	k=rand()%7;
	mat[csy+1][csx-1].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy+1][csx-1].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy+1][csx-1].img,NULL,ecran,&pos6);
	}
     if((csx+1)<=9)
	{
	k=rand()%7;
	mat[csy][csx+1].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy][csx+1].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy][csx+1].img,NULL,ecran,&pos5);
	k=rand()%7;
	mat[csy+1][csx+1].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy+1][csx+1].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy+1][csx+1].img,NULL,ecran,&pos7);
	}
SDL_Flip(ecran);
}
if((csy+1)>10)
{
  if(((csx-1)>=0)&&((csx+1)<=9))
	{
	   SDL_Flip(ecran);
		SDL_Delay(400);
		decalage((csx-1),csy-1,(csx),(csy-1),(csx+1),(csy-1),tab);
		decalage((csx-1),csy,(csx),(csy),(csx+1),(csy),tab);
	}
  if((csx-1)<0)
	{
while(csy>1)
{ SDL_FreeSurface(mat[csy][csx].img);
  SDL_FreeSurface(mat[csy-1][csx].img);
  SDL_FreeSurface(mat[csy][csx+1].img);
  SDL_FreeSurface(mat[csy-1][csx+1].img);


mat[csy][csx].img=SDL_LoadBMP(mat[csy-2][csx].noimg);        strcpy(mat[csy][csx].noimg,mat[csy][csx].noimg);
mat[csy-1][csx].img=SDL_LoadBMP(mat[csy-3][csx].noimg);        strcpy(mat[csy-1][csx].noimg,mat[csy-3][csx].noimg);
mat[csy][csx+1].img=SDL_LoadBMP(mat[csy-2][csx+1].noimg);        strcpy(mat[csy][csx+1].noimg,mat[csy-2][csx+1].noimg);
mat[csy-1][csx+1].img=SDL_LoadBMP(mat[csy-3][csx+1].noimg);        strcpy(mat[csy-1][csx+1].noimg,mat[csy-3][csx+1].noimg);

SDL_BlitSurface(mat[csy][csx].img,NULL,ecran,&pos);
SDL_BlitSurface(mat[csy-1][csx].img,NULL,ecran,&pos8);
SDL_BlitSurface(mat[csy][csx+1].img,NULL,ecran,&pos5);
SDL_BlitSurface(mat[csy-1][csx+1].img,NULL,ecran,&pos4);
csy=csy-2;

pos.x=csx*80;  pos.y=csy*80;
pos8.x=csx*80;  pos8.y=(csy-1)*80;
pos5.x=(csx+1)*80;  pos5.y=csy*80;
pos4.x=(csx+1)*80;  pos4.y=(csy-1)*80;
SDL_Flip(ecran);
SDL_Delay(400);
}
	k=rand()%7;
	mat[csy][csx].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy][csx].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy][csx].img,NULL,ecran,&pos);
	k=rand()%7;
	mat[csy-1][csx].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy-1][csx].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy-1][csx].img,NULL,ecran,&pos8);

	k=rand()%7;
	mat[csy][csx+1].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy][csx+1].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy][csx+1].img,NULL,ecran,&pos5);
	k=rand()%7;
	mat[csy-1][csx+1].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy-1][csx+1].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy-1][csx+1].img,NULL,ecran,&pos4);
	}

else if((csx+1)>9)
	{
while(csy>1)
{ SDL_FreeSurface(mat[csy][csx].img);
  SDL_FreeSurface(mat[csy-1][csx].img);
  SDL_FreeSurface(mat[csy][csx-1].img);
  SDL_FreeSurface(mat[csy-1][csx-1].img);


mat[csy][csx].img=SDL_LoadBMP(mat[csy-2][csx].noimg);        strcpy(mat[csy][csx].noimg,mat[csy][csx].noimg);
mat[csy-1][csx].img=SDL_LoadBMP(mat[csy-3][csx].noimg);        strcpy(mat[csy-1][csx].noimg,mat[csy-3][csx].noimg);
mat[csy][csx-1].img=SDL_LoadBMP(mat[csy-2][csx-1].noimg);        strcpy(mat[csy][csx-1].noimg,mat[csy-2][csx-1].noimg);
mat[csy-1][csx-1].img=SDL_LoadBMP(mat[csy-3][csx-1].noimg);        strcpy(mat[csy-1][csx-1].noimg,mat[csy-3][csx-1].noimg);

SDL_BlitSurface(mat[csy][csx].img,NULL,ecran,&pos);
SDL_BlitSurface(mat[csy-1][csx].img,NULL,ecran,&pos8);
SDL_BlitSurface(mat[csy][csx-1].img,NULL,ecran,&pos5);
SDL_BlitSurface(mat[csy-1][csx-1].img,NULL,ecran,&pos4);
csy=csy-2;

pos.x=csx*80;  pos.y=csy*80;
pos8.x=csx*80;  pos8.y=(csy-1)*80;
pos5.x=(csx-1)*80;  pos5.y=csy*80;
pos4.x=(csx-1)*80;  pos4.y=(csy-1)*80;
SDL_Flip(ecran);
SDL_Delay(400);
}
	k=rand()%7;
	mat[csy][csx].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy][csx].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy][csx].img,NULL,ecran,&pos);
	k=rand()%7;
	mat[csy-1][csx].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy-1][csx].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy-1][csx].img,NULL,ecran,&pos8);

	k=rand()%7;
	mat[csy][csx-1].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy][csx-1].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy][csx-1].img,NULL,ecran,&pos5);
	k=rand()%7;
	mat[csy-1][csx-1].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[csy-1][csx-1].noimg,tab[k].ch);
	SDL_BlitSurface(mat[csy-1][csx-1].img,NULL,ecran,&pos4);
	}

}
}

void test(nomimage tab[])
{
	int i,j,b;
	i=0;
while(i<11)
{
j=0;b=0;
while((j<10)&&(b==0))
{
if((j<6)&&(egalite(i,j,i,j+1)==1)&&(egalite(i,j,i,j+2)==1)&&(egalite(i,j,i,j+3)==1)&&(egalite(i,j,i,j+4)==1))
{destroy5(j,i,j+1,i,j+2,i,j+3,i,j+4,i,tab);b=1;}
else
if((j<7)&&(egalite(i,j,i,j+1)==1)&&(egalite(i,j,i,j+2)==1)&&(egalite(i,j,i,j+3)==1))
{destroy4(j,i,j+1,i,j+2,i,j+3,i,tab);b=1;}
else
if((j<8)&&(egalite(i,j,i,j+1)==1)&&(egalite(i,j,i,j+2)==1))
{destroy(j,i,j+1,i,j+2,i,tab);b=1;}
else
if((i<7)&&(egalite(i,j,i+1,j)==1)&&(egalite(i,j,i+2,j)==1)&&(egalite(i,j,i+3,j)==1)&&(egalite(i,j,i+4,j)==1))
{
destroy5(j,i,j,i+1,j,i+2,j,i+3,j,i+4,tab);b=1;}
else
if((i<8)&&(egalite(i,j,i+1,j)==1)&&(egalite(i,j,i+2,j)==1)&&(egalite(i,j,i+3,j)==1))
{destroy4(j,i,j,i+1,j,i+2,j,i+3,tab);b=1;}
else
if((i<9)&&(egalite(i,j,i+1,j)==1)&&(egalite(i,j,i+2,j)==1))
{destroy(j,i,j,i+1,j,i+2,tab);b=1;}
else
j++;
}
if(b==1)
i=0;
else i++;
}
}



void aide()
{
int i,j,b;
i=0;b=0;
while((i<11)&&(b==0))
{
j=0;
while((j<10)&&(b==0))
{
if((j<8)&&(i>0)&&(egalite(i,j,i-1,j+1)==1)&&(egalite(i,j,i-1,j+2)==1))
{reswap(i,j,j,i-1);b=1;}
else if((j<8)&&(i<10)&&(egalite(i,j,i+1,j+1)==1)&&(egalite(i,j,i+1,j+2)==1))
{reswap(i,j,j,i+1);b=1;}
else if((j<9)&&(i>0)&&(egalite(i,j,i-1,j+1)==1)&&(egalite(i,j,i-1,j-1)==1))
{reswap(i,j,j,i-1);b=1;}
else if((j<9)&&(i<10)&&(egalite(i,j,i+1,j+1)==1)&&(egalite(i,j,i+1,j-1)==1))
{reswap(i,j,j,i+1);b=1;}
else if((j>1)&&(i>0)&&(egalite(i,j,i-1,j-1)==1)&&(egalite(i,j,i-1,j-2)==1))
{reswap(i,j,j,i-1);b=1;}
else if((j>1)&&(i<10)&&(egalite(i,j,i+1,j-1)==1)&&(egalite(i,j,i+1,j-2)==1))
{reswap(i,j,j,i+1);b=1;}
else if((j>0)&&(j<9)&&(i>0)&&(egalite(i,j,i-1,j-1)==1)&&(egalite(i,j,i-1,j+1)==1))
{reswap(i,j,j,i-1);b=1;}
else if((j>0)&&(j<9)&&(i<9)&&(egalite(i,j,i+1,j-1)==1)&&(egalite(i,j,i+1,j+1)==1))
{reswap(i,j,j,i+1);b=1;}
else if((j>0)&&(i>1)&&(egalite(i,j,i-1,j-1)==1)&&(egalite(i,j,i-2,j-1)==1))
{reswap(i,j,j-1,i);b=1;}
else if((j>0)&&(i<9)&&(egalite(i,j,i+1,j-1)==1)&&(egalite(i,j,i+2,j-1)==1))
{reswap(i,j,j-1,i);b=1;}
else if((j>0)&&(i>0)&&(i<10)&&(egalite(i,j,i-1,j-1)==1)&&(egalite(i,j,i+1,j-1)==1))
{reswap(i,j,j-1,i);b=1;}
else if((j<10)&&(i>0)&&(i<10)&&(egalite(i,j,i-1,j+1)==1)&&(egalite(i,j,i+1,j+1)==1))
{reswap(i,j,j+1,i);b=1;}
else if((j<9)&&(i>1)&&(egalite(i,j,i-1,j+1)==1)&&(egalite(i,j,i-2,j+1)==1))
{reswap(i,j,j+1,i);b=1;}
else if((j<9)&&(i<9)&&(egalite(i,j,i+1,j+1)==1)&&(egalite(i,j,i+2,j+1)==1))
{reswap(i,j,j+1,i);b=1;}
if((j<7)&&(egalite(i,j,i,j+2)==1)&&(egalite(i,j,i,j+3)==1))
{reswap(i,j,j+1,i);b=1;}
else if((j>2)&&(egalite(i,j,i,j-2)==1)&&(egalite(i,j,i,j-3)==1))
{reswap(i,j,j-1,i);b=1;}
else if((i<8)&&(egalite(i,j,i+2,j)==1)&&(egalite(i,j,i+3,j)==1))
{reswap(i,j,j,i+1);b=1;}
else if((i>2)&&(egalite(i,j,i-2,j)==1)&&(egalite(i,j,i-3,j)==1))
{reswap(i,j,j,i-1);b=1;}
else j++;
}
if(b==0)
i++;
}
}

//tester c'le il y'pas d'jeux
void test2(nomimage tab[])
{
int i,j,b,k;
SDL_Rect pos;
pos.x=0; pos.y=0;
i=0;b=0;
while((i<11)&&(b==0))
{
j=0;
while((j<10)&&(b==0))
{
if((j<8)&&(i>0)&&(egalite(i,j,i-1,j+1)==1)&&(egalite(i,j,i-1,j+2)==1))
{b=1;}
else if((j<8)&&(i<10)&&(egalite(i,j,i+1,j+1)==1)&&(egalite(i,j,i+1,j+2)==1))
{b=1;}
else if((j<9)&&(i>0)&&(egalite(i,j,i-1,j+1)==1)&&(egalite(i,j,i-1,j-1)==1))
{b=1;}
else if((j<9)&&(i<10)&&(egalite(i,j,i+1,j+1)==1)&&(egalite(i,j,i+1,j-1)==1))
{b=1;}
else if((j>1)&&(i>0)&&(egalite(i,j,i-1,j-1)==1)&&(egalite(i,j,i-1,j-2)==1))
{b=1;}
else if((j>1)&&(i<10)&&(egalite(i,j,i+1,j-1)==1)&&(egalite(i,j,i+1,j-2)==1))
{b=1;}
else if((j>0)&&(j<9)&&(i>0)&&(egalite(i,j,i-1,j-1)==1)&&(egalite(i,j,i-1,j+1)==1))
{b=1;}
else if((j>0)&&(j<9)&&(i<9)&&(egalite(i,j,i+1,j-1)==1)&&(egalite(i,j,i+1,j+1)==1))
{b=1;}
else if((j>0)&&(i>1)&&(egalite(i,j,i-1,j-1)==1)&&(egalite(i,j,i-2,j-1)==1))
{b=1;}
else if((j>0)&&(i<9)&&(egalite(i,j,i+1,j-1)==1)&&(egalite(i,j,i+2,j-1)==1))
{b=1;}
else if((j>0)&&(i>0)&&(i<10)&&(egalite(i,j,i-1,j-1)==1)&&(egalite(i,j,i+1,j-1)==1))
{b=1;}
else if((j<9)&&(i>0)&&(i<10)&&(egalite(i,j,i-1,j+1)==1)&&(egalite(i,j,i+1,j+1)==1))
{b=1;}
else if((j<9)&&(i>1)&&(egalite(i,j,i-1,j+1)==1)&&(egalite(i,j,i-2,j+1)==1))
{b=1;}
else if((j<9)&&(i<9)&&(egalite(i,j,i+1,j+1)==1)&&(egalite(i,j,i+2,j+1)==1))
{b=1;}
if((j<7)&&(egalite(i,j,i,j+2)==1)&&(egalite(i,j,i,j+3)==1))
{b=1;}
else if((j>2)&&(egalite(i,j,i,j-2)==1)&&(egalite(i,j,i,j-3)==1))
{b=1;}
else if((i<8)&&(egalite(i,j,i+2,j)==1)&&(egalite(i,j,i+3,j)==1))
{b=1;}
else if((i>2)&&(egalite(i,j,i-2,j)==1)&&(egalite(i,j,i-3,j)==1))
{b=1;}
else j++;
}
if(b==0)
i++;
}

if(b==0)
for(i=0;i<11;i++)
{for(j=0;j<10;j++)
{k=rand()%7;
SDL_FreeSurface(mat[i][j].img);
mat[i][j].img=SDL_LoadBMP(tab[k].ch);
strcpy (mat[i][j].noimg,tab[k].ch);
SDL_BlitSurface(mat[i][j].img,NULL,ecran,&pos);
pos.x=pos.x+80;
}
pos.y=pos.y+80;
}
SDL_Flip(ecran);




}


void destroy_type_3(int y,int x,nomimage tab[])
{
int i,j,k;
SDL_Rect pos;
char ch[10];
strcpy(ch,mat[y][x].noimg);
for(i=0;i<11;i++)
{for(j=0;j<10;j++)
{
 if(mat[i][j].noimg[0]==ch[0])
    {  SDL_FreeSurface(mat[i][j].img);
	if(i==0)
	{
	 k=rand()%7;
	mat[i][j].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat[i][j].noimg,tab[k].ch);
	pos.x=j*80;  pos.y=i*80;
	SDL_BlitSurface(mat[i][j].img,NULL,ecran,&pos);
	}

	else
	{
	  k=i;
	  while(k>0)
		{
		  mat[k][j].img=SDL_LoadBMP(mat[k-1][j].noimg);
		  strcpy (mat[k][j].noimg,mat[k-1][j].noimg);
		  pos.x=j*80;  pos.y=k*80;
		  SDL_BlitSurface(mat[k][j].img,NULL,ecran,&pos);
		  k--;
		}
	 k=rand()%7;
	 mat[0][j].img=SDL_LoadBMP(tab[k].ch);
	 strcpy (mat[0][j].noimg,tab[k].ch);
	 pos.x=j*80;  pos.y=0;
	 SDL_BlitSurface(mat[0][j].img,NULL,ecran,&pos);
	}
       SDL_Flip(ecran);
   }
}
}
}
int play_button(int x,int y)
{if((x>=703)&&(x<=1177)&&(y>=380)&&(y<=522)) return 1;
return 0;
}
int vs_bot_button(int x,int y)
{if((x>=516)&&(x<=1362)&&(y>=560)&&(y<=762)) return 1;
return 0;
}
int scores_button(int x,int y)
{if((x>=699)&&(x<=1172)&&(y>=741)&&(y<=884)) return 1;
return 0;
}

void free_surfaces()
{int i,j;
for(i=0;i<10;i++)
{
for(j=0;j<11;j++)
{
SDL_FreeSurface(mat[i][j].img);
}
}


for(i=0;i<10;i++)
{
for(j=0;j<11;j++)
{
SDL_FreeSurface(mat2[i][j].img);
}
}

SDL_FreeSurface(ecran);SDL_FreeSurface(menu);
SDL_FreeSurface(background);SDL_FreeSurface(text);
}

void initbackground()
{SDL_Rect pos;pos.x=0; pos.y=0;
background=SDL_LoadBMP("background.bmp");
SDL_BlitSurface(background,NULL,ecran,&pos);
SDL_Flip(ecran);
}
int click_matrice(int x,int y)
{
if((x>0)&&(x<=879)&&(y>0)&&(y>0)&&(y<=799)) return 1;
return 0;
}
void init_button_aide()
{
SDL_Rect pos; pos.x=886; pos.y=255;
button_aide=SDL_LoadBMP("button_aide.bmp");
 SDL_BlitSurface(button_aide,NULL,ecran,&pos);
 SDL_Flip(ecran);
}
void init_button_pause()
{SDL_Rect pos;pos.x=886; pos.y=350;
button_pause=SDL_LoadBMP("button_pause.bmp");
SDL_BlitSurface(button_pause,NULL,ecran,&pos);
SDL_Flip(ecran);
}
void init_play(nomimage tab[])
{    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
     SDL_Flip(ecran);
     initbackground();
     initmat(tab); test(tab);
     init_button_aide(); init_button_pause();
     test2(tab);
     SDL_Flip(ecran);
}
void init_bot(nomimage tab[])
{
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
initbackground(); initmat(tab);  initmat2(tab); test(tab);
    init_button_aide(); init_button_pause();
    SDL_Flip(ecran);
}
void init_menu()
{SDL_Rect pos; pos.x=0; pos.y=0;
SDL_WM_SetCaption("twist",NULL);
SDL_Init(SDL_INIT_VIDEO);
ecran=SDL_SetVideoMode(1900,900,32,SDL_HWSURFACE);
menu=SDL_LoadBMP("menu.bmp");
SDL_BlitSurface(menu,NULL,ecran,&pos);
SDL_Flip(ecran);

}
void test_event(SDL_Event event,int i,int *csx,int *csy,int *csx2,int *csy2,nomimage tab[])
{int x,y,ok;int si_aide();
          if (event.type==SDL_MOUSEBUTTONDOWN)
          {   x=event.button .x;y=event.button.y;
                  if(event.button.button==SDL_BUTTON_LEFT)
                       {
                       if(click_matrice(x,y)==1)
                       {
                       (*csx)=(event.button.x)/80;//case selectionée
                       (*csy)=(event.button.y)/80;
                       printf("csy=%d    csx=%d \n",(*csy),(*csx));
                       printf("%s\n",mat[(*csy)][(*csx)].noimg);
                       }else if(si_aide(x,y)==1) aide();
                       }
                      else if((i!=0)&&(event.button.button==SDL_BUTTON_RIGHT)&&(click_matrice(x,y)==1))
                      {    i=0;ok=0;
                        (*csx2)=event.button.x/80;(*csy2)=event.button.y/80;
                         printf("csy2=%d    csx2=%d \n",(*csy2),(*csx2));
                         verification_global(*csx,*csy,*csx2,*csy2,tab,0);

                 }


          }
}

/*rana m3AHA sdl_ttf hadi -"
void init_score()
{
SDL_Color cl={255,255,255};
TTF_Font* font=TTF_OpenFont("Gaeil1.ttf",32);
text=TTF_RenderText_Solid(font,"test_sdl",cl);
SDL_Rect pos_text;
pos_text.x=250;
pos_text.y=900;
SDL_BlitSurface(text,NULL,ecran,&pos_text);
SDL_Flip(ecran);
}
*/
int si_aide(int x,int y)
{if((x>886)&&(x<1013)&&(y>255)&&(y<315))return 1;
return 0;
}

