#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>
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
SDL_Surface *text=NULL,*text_2=NULL;
SDL_Surface *cover=NULL,*cover_2=NULL,*clock=NULL,*clock2=NULL,*clock3=NULL,*SCORE=NULL,*SCORE2=NULL;
Mix_Chunk* effect1;
Mix_Music* music;
TTF_Font *font2;


enum {N=11};enum {M=12};
rect mat[N][M];rect mat2[N][M];
int score=0,score_2=0,t,t2,time_since,start_time,m;
char s[20],s_2[20];
enum {H=6};

SDL_Rect pos_text,pos_text_2,pos_clock,pos_clock2,pos_clock3;
SDL_Color cl={255,255,255};



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

//srand(time(NULL));
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
if (mat[csy][csx].noimg[0]==mat[csy2][csx2].noimg[0]) return 1;
return 0;
}
int egalite_type3(int csy,int csx,int csy2,int csx2)
{
if(csy2<0 || csy2>9)return 0;
if(csx2<0 || csx2>10)return 0;
if (mat[csy][csx].noimg[2]=='3'||mat[csy2][csx2].noimg[2]=='3') return 1;
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

//SDL_Flip(ecran);



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



//SDL_Flip(ecran);






csy2=csy2-3;y3=y3-3;y4=y4-3;

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
char t1[10],t2[10],t3[10];

strcpy(t1,mat[csy2][csx2].noimg);
strcpy(t2,mat[y3][x3].noimg);
strcpy(t3,mat[y4][x4].noimg);

 if((mat[csy2][csx2].noimg[2]=='2')|| (mat[y3][x3].noimg[2]=='2')||
  (mat[y4][x4].noimg[2]=='2')) destroy_type2(csy2,csx2,y3,x3,y4,x4,tab);
else {

fillrect(mat[y3][x3]); fillrect(mat[y4][x4]);
fillrect(mat[csy2][csx2]);

pos.x=csx2*80; pos.y=csy2*80;
SDL_BlitSurface(mat[csy2][csx2].img,NULL,ecran,&pos);



pos.x=x3*80; pos.y=y3*80;
SDL_BlitSurface(mat[y3][x3].img,NULL,ecran,&pos);



pos.x=x4*80; pos.y=y4*80;
SDL_BlitSurface(mat[y4][x4].img,NULL,ecran,&pos);


// SDL_FillRect(text,NULL,SDL_MapRGB(text->format,0,255,0)); bug !

//SDL_FillRect(img.img,NULL,SDL_MapRGB(img.img->format,0,255,0));
//SDL_FillRect(test,ecran,test->format)

SDL_Flip(ecran);
SDL_BlitSurface(cover,NULL,ecran,&pos_text);
TTF_Font *sc=TTF_OpenFont("textform.TTF",64);
SDL_FreeSurface(text);
score=score+3;
sprintf(s,"%d",score);
text=TTF_RenderText_Blended(sc,s,cl);
SDL_BlitSurface(text,NULL,ecran,&pos_text);


SDL_Flip(ecran);
Mix_PlayChannel(-1,effect1,0);
SDL_Delay(300);
//TESTING

//apelle a la fonction decalage (delated)

decalage(csx2,csy2,x3,y3,x4,y4,tab);
SDL_Flip(ecran);
test(tab);

printf("%s\n",mat[csx2][csy2].noimg);
printf("%s\n",mat[y4][x4].noimg);
printf("%s\n",mat[y3][x4].noimg);

if(t1[2]=='3') destroy_type_3(t1,tab);
else if(t2[2]=='3')destroy_type_3(t2,tab);
else if(t3[2]=='3')destroy_type_3(t3,tab);

}
}




void destroy3(int csx2,int csy2,int x3,int y3,int x4,int y4,nomimage tab[])
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
SDL_Delay(300);
//TESTING

//apelle a la fonction decalage (delated)

decalage(csx2,csy2,x3,y3,x4,y4,tab);

printf("%s\n",mat[csx2][csy2].noimg);
printf("%s\n",mat[y4][x4].noimg);
printf("%s\n",mat[y3][x4].noimg);


}


void destroy3_t(int csx2,int csy2,int x3,int y3,int x4,int y4,nomimage tab[])
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
Mix_PlayChannel(-1,effect1,0);
SDL_Delay(300);
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
SDL_Delay(100);

if(max==y3)
decalage(csx2,csy2,x4,y4,x5,y5,tab);
else if(max==y4) decalage(csx2,csy2,x3,y3,x5,y5,tab);
else decalage(csx2,csy2,x3,y3,x4,y4,tab);

}



}
}


//still beta not tested yet
void destroy5(int csx2,int csy2,int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6,nomimage tab[])
{void decalage5();
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
Mix_PlayChannel(-1,effect1,0);

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

SDL_Delay(300);


if(max==y3) decalage4_v(csy2,csx2,x4,y4,x5,y5,x6,y6,tab);
else if(max==y4) decalage4_v(x3,y3,csx2,csy2,x5,y5,x6,y6,tab);
else if(max==y5) decalage4_v(x3,y3,x4,y4,csx2,csy2,x6,y6,tab);
else if(max==y6) decalage4_v(x3,y3,x4,y4,x5,y5,csx2,csy2,tab);

}

}


}


//cas de csy2-1 ,csy2+1
int verf_1_1(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
  if(egalite(csy,csx,csy2-2,csx2)==1)
   {

     if(egalite(csy,csx,csy2+2,csx2)==1)
   {
   swap(csy,csx,csx2,csy2);
   destroy5(csx2,csy2,csx2,csy2-1,csx2,csy2+1,
   csx2,csy2-2,csx2,csy+2,tab);
   return 1;
   }
   swap(csy,csx,csx2,csy2);
   destroy4(csx2,csy2,csx2,csy2-1,csx2,csy2+1,
   csx2,csy2-2,tab);
   return 1;

   }

   else if(egalite(csy,csx,csy2+2,csx2)==1)
   {
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
   if(egalite(csy,csx,csy2,csx2+1)==1)
  {
      if(egalite(csy,csx,csy2,csx2+2)==1)
      {
      swap(csy,csx,csx2,csy2);
      destroy5(csx2,csy2,csx2-1,csy2,csx2-2,csy2,csx2+1,csy2,
      csx2+2,csy2,tab);
      return 1;
      }
      swap(csy,csx,csx2,csy2);
      destroy4(csx2,csy2,csx2-1,csy2,csx2-2,csy2,csx2+1,csy2,tab);
      return 1;
  }else return 0;

}
//cas csy2-1,csy2-2
int verf_1_3(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
       // cas 4 cases
   if (egalite(csy,csx,csy2+1,csx2)==1)
   {

   if(egalite(csy,csx,csy2+2,csx2)==1)
   //5 cases
   {
   swap(csy,csx,csx2,csy2);
   destroy5(csx2,csy2,csx2,csy2-1,csx2,csy2-2,csx2,csy2+1,csx2
   ,csy2+2,tab);
   return 1;
   }
   swap(csy,csx,csx2,csy2);
   destroy4(csx2,csy2,csx2,csy2-1,csx2,csy2-2,csx2,csy2+1,tab);
   return 1;
   }else return 0;


}

//cas csy2+1,csy2+2
int verf_1_4(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
    if(egalite(csy,csx,csy2-1,csx2)==1)
    {if(egalite(csy,csx,csy2-2,csx2)==1)
    {//appele destroy 5
    swap(csy,csx,csx2,csy2);
    destroy5(csx2,csy2,csx2,csy2+1,csx2,csy2+2,csx2,csy2-1,csx2,
    csy2-2,tab);
    return 1;
    }else
    swap(csy,csx,csx2,csy2);
    destroy4(csx2,csy2,csx2,csy2+1,csx2,csy2+2,csx2,csy2-1,tab);
    return 1;
    }else return 0;

}

//cas csx2+1,csx2+2
int verf_1_5(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
 if(egalite(csy,csx,csy2,csx2-1)==1)
 {
    if(egalite(csy,csx,csy2,csx2-2)==1)
     {
     swap(csy,csx,csx2,csy2);
     destroy5(csx2,csy2,csx2+1,csy2,csx2+2,csy2,csx2-1,csy2,
     csx2-2,csy2,tab);
      return 1;
     }else
   { //apelle
    swap(csy,csx,csx2,csy2);
    destroy4(csx2,csy2,csx2+1,csy2,csx2+2,csy2,csx2-1,csy2,tab);
    return 1;
    }
 }else return 0;

}
//cas csx2+1,csx2-1
int verf_1_6(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
    if(egalite(csy,csx,csy2,csx2+2)==1)
     {if(egalite(csy,csx,csy2,csx2-2)==1)
     {
     swap(csy,csx,csx2,csy2);
     destroy5(csx2,csy2,csx2+1,csy2,csx2-1,csy2,csx2+2,
     csy2,csx2-2,csy2,tab);
     return 1;
     }
     swap(csy,csx,csx2,csy2);
     destroy4(csx2,csy2,csx2+1,csy2,csx2-1,csy2,csx2+2,
    csy2,tab);
    return 1;
     }
     else if(egalite(csy,csx,csy2,csx2-2)==1)
     {
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

if(csy2==csy&&csx2==csx-1)
     {
if((d==0)&&(egalite_type_3(csx,csy,csx2,csy2,tab)==1)){d=1;ok=1;}
else
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
        swap(csy,csx,csx2,csy2);
        destroy(csx2,csy2,csx2-1,csy2,csx2-2,csy2,tab);
  }else if((d==0)&&(i==1)) {reswap(csy,csx,csx2,csy2); score_down();}

}

//////////////////////2eme cas

if (csy2==csy&&csx2==csx+1)
{
if((d==0)&&(egalite_type_3(csx,csy,csx2,csy2,tab)==1)){d=1;ok=1;}
else
 if((d==0)&&(egalite(csy,csx,csy2+1,csx2)==1)
&&(egalite(csy,csx,csy2+2,csx2)==1))
   {ok=1;d=1;
               if(verf_1_4(csx,csy,csx2,csy2,tab)==0)
                { swap(csy,csx,csx2,csy2);
                    destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);
                }
                 }




 if((d==0)&&(egalite(csy,csx,csy2-1,csx2)==1)
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
     swap(csy,csx,csx2,csy2);
     destroy(csx2,csy2,csx2+1,csy2,csx2+2,csy2,tab);
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
  }else if((d==0)&&(i==1)) {reswap(csy,csx,csx2,csy2); score_down();}

}
////////////////////////3eme cas
 if (csy2==csy-1&&csx2==csx)
{if((d==0)&&(egalite_type_3(csx,csy,csx2,csy2,tab)==1)){d=1;ok=1;}
else

if((d==0)&&egalite(csy,csx,csy2,csx2+1)==1
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
       swap(csy,csx,csx2,csy2);
      destroy(csx2,csy2,csx2,csy2-1,csx2,csy2-2,tab);
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
  }else if((d==0)&&(i==1)){reswap(csy,csx,csx2,csy2); score_down();}


}
//////////////////////////// 4eme cas

 if ((csy2==(csy+1))&&(csx2==csx))
  {
  if((d==0)&&(egalite_type_3(csx,csy,csx2,csy2,tab)==1)){d=1;ok=1;}

else if((d==0)&&(egalite(csy,csx,csy2,csx2+1)==1)
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
      swap(csy,csx,csx2,csy2);
      destroy(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);

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
     }else if((d==0)&&(i==1)) {reswap(csy,csx,csx2,csy2); score_down();}

}

  if((d==0)&&(i==0)) verification_global(csx2,csy2,csx,csy,tab,1);



}


//

void score_down()
{
SDL_BlitSurface(cover,NULL,ecran,&pos_text);
TTF_Font *sc=TTF_OpenFont("textform.TTF",64);
SDL_FreeSurface(text);
if(score>0)score=score-1;
sprintf(s,"%d",score);
text=TTF_RenderText_Blended(sc,s,cl);
SDL_BlitSurface(text,NULL,ecran,&pos_text);
SDL_Flip(ecran);
}

void score_up_3()
{
SDL_BlitSurface(cover,NULL,ecran,&pos_text);
TTF_Font *sc=TTF_OpenFont("textform.TTF",64);
SDL_FreeSurface(text);
score=score+3;
sprintf(s,"%d",score);
text=TTF_RenderText_Blended(sc,s,cl);
SDL_BlitSurface(text,NULL,ecran,&pos_text);
SDL_Flip(ecran);
}

void score_up_3_2()
{
SDL_BlitSurface(cover_2,NULL,ecran,&pos_text_2);
TTF_Font *font=TTF_OpenFont("textform.TTF",64);
SDL_FreeSurface(text_2);
score_2=score_2+3;
sprintf(s_2,"%d",score_2);
text_2=TTF_RenderText_Blended(font,s_2,cl);
SDL_BlitSurface(text_2,NULL,ecran,&pos_text_2);
SDL_Flip(ecran);
}






void test(nomimage tab[])
{
	int j,i,b;
	j=0;
while(j<11)
{
i=0;b=0;
while((i<10)&&(b==0))
{
if((i<6)&&(egalite(j,i,j,i+1)==1)&&(egalite(j,i,j,i+2)==1)&&(egalite(j,i,j,i+3)==1)&&(egalite(j,i,j,i+4)==1))
{destroy5(i,j,i+1,j,i+2,j,i+3,j,i+4,j,tab);b=1;}
else
if((i<7)&&(egalite(j,i,j,i+1)==1)&&(egalite(j,i,j,i+2)==1)&&(egalite(j,i,j,i+3)==1))
{destroy4(i,j,i+1,j,i+2,j,i+3,j,tab);b=1;}
else
if((i<8)&&(egalite(j,i,j,i+1)==1)&&(egalite(j,i,j,i+2)==1))
{destroy3_t(i,j,i+1,j,i+2,j,tab);b=1;}
else
if((j<7)&&(egalite(j,i,j+1,i)==1)&&(egalite(j,i,j+2,i)==1)&&(egalite(j,i,j+3,i)==1)&&(egalite(j,i,j+4,i)==1))
{
destroy5(i,j,i,j+1,i,j+2,i,j+3,i,j+4,tab);b=1;}
else
if((j<8)&&(egalite(j,i,j+1,i)==1)&&(egalite(j,i,j+2,i)==1)&&(egalite(j,i,j+3,i)==1))
{destroy4(i,j,i,j+1,i,j+2,i,j+3,tab);b=1;}
else
if((j<9)&&(egalite(j,i,j+1,i)==1)&&(egalite(j,i,j+2,i)==1))
{destroy3_t(i,j,i,j+1,i,j+2,tab);b=1;}
else
i++;
}
if(b==1)
j=0;
else j++;
}
}


void aide()
{
int i,j,b;
i=0;b=0;
while((i<10)&&(b==0))
{
j=0;
while((j<11)&&(b==0))
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
//TTF_CloseFont(font);
TTF_Quit();

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
     initmat(tab);
     test(tab);
     init_button_aide(); init_button_pause();
     test2(tab);
     SDL_Flip(ecran);
}
void init_bot(nomimage tab[])
{
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
initbackground(); initmat(tab);  initmat2(tab); test(tab);test_2(tab);
    init_button_aide(); init_button_pause();
    SDL_Flip(ecran);

}
void init_menu()
{SDL_Rect pos; pos.x=0; pos.y=0;
pos_text.x=250;pos_text_2.x=1700;
pos_text.y=825;pos_text_2.y=825;
pos_clock.y=825;pos_clock.x=960;
pos_clock2.y=825;pos_clock2.x=880;
pos_clock3.y=825;pos_clock3.x=940;


font2=TTF_OpenFont("textform.TTF",64);m=4;

SDL_WM_SetCaption("twist",NULL);
SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
ecran=SDL_SetVideoMode(1900,900,32,SDL_HWSURFACE);
menu=SDL_LoadBMP("menu.bmp");
SDL_BlitSurface(menu,NULL,ecran,&pos);
SDL_Flip(ecran);
}

void test_event(SDL_Event event,int i,int *csx,int *csy,int *csx2,int *csy2,int *p,nomimage tab[],
int bot,int *a)
{int x,y,ok;int si_aide();
          if (event.type==SDL_MOUSEBUTTONDOWN)
          {   x=event.button.x;y=event.button.y;
                  if(event.button.button==SDL_BUTTON_LEFT)
                       {
                       if(click_pause(x,y)==1)*p=-(*p);

                       if((*p>0)&&(click_matrice(x,y)==1))
                       {
                       (*csx)=(event.button.x)/80;//case selectionée
                       (*csy)=(event.button.y)/80;
                       printf("csy=%d    csx=%d \n",(*csy),(*csx));
                       printf("%s\n",mat[(*csy)][(*csx)].noimg);
                       }else if(((si_aide(x,y))==1)&&(*a>0)){*a=(*a)-1; aide();  }
                       }
                      else if((*p>0)&&(i!=0)&&(event.button.button==SDL_BUTTON_RIGHT)&&(click_matrice(x,y)==1))
                      {    i=0;ok=0;
                        (*csx2)=event.button.x/80;(*csy2)=event.button.y/80;


                         verification_global(*csx,*csy,*csx2,*csy2,tab,0);
                         test(tab);
                         if(bot==1) {aide2(tab); test_2(tab);}
                 }


          }
}



int si_aide(int x,int y)
{if((x>886)&&(x<1013)&&(y>255)&&(y<315))return 1;
return 0;
}

void init_tab(nomimage tab[])
{
strcpy(tab[0].ch,"1_1.bmp");strcpy(tab[7].ch,"1_2.bmp");strcpy(tab[14].ch,"1_3.bmp");
strcpy(tab[1].ch,"2_1.bmp");strcpy(tab[8].ch,"2_2.bmp");strcpy(tab[15].ch,"2_3.bmp");
strcpy(tab[2].ch,"3_1.bmp");strcpy(tab[9].ch,"3_2.bmp");strcpy(tab[16].ch,"3_3.bmp");
strcpy(tab[3].ch,"4_1.bmp");strcpy(tab[10].ch,"4_2.bmp");strcpy(tab[17].ch,"4_3.bmp");
strcpy(tab[4].ch,"5_1.bmp");strcpy(tab[11].ch,"5_2.bmp");strcpy(tab[18].ch,"5_3.bmp");
strcpy(tab[5].ch,"6_1.bmp");strcpy(tab[12].ch,"6_2.bmp");strcpy(tab[19].ch,"6_3.bmp");
strcpy(tab[6].ch,"7_1.bmp");strcpy(tab[13].ch,"7_2.bmp");strcpy(tab[20].ch,"7_3.bmp");
}

void destroy_type2(int y,int x,int y2,int x2,int y3,int x3,nomimage tab[])
{
    SDL_Rect pos,pos2,pos3,pos4,pos5,pos6,pos7,pos8,pos9;void decalage();

if(x==x2)
 {destroy3(x,y,x2,y2,x3,y3,tab);SDL_Flip(ecran);score_up_3();Mix_PlayChannel(-1,effect1,0);
 SDL_Flip(ecran);
 SDL_Delay(400);
   if(x==10)
	{destroy3(x-1,y,x2-1,y2,x3-1,y3,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
	}
   else if(x==0)
        { destroy3(x+1,y,x2+1,y2,x3+1,y3,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
	}
   else
        {
         destroy3(x+1,y,x2+1,y2,x3+1,y3,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
         destroy3(x-1,y,x2-1,y2,x3-1,y3,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
        }
 }

else

if(y==y2)
 {
   if(y==0)
	{
	destroy3(x,y,x2,y2,x3,y3,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
    destroy3(x,y+1,x2,y2+1,x3,y3+1,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
        }
   else if(y==9)
	{
	   destroy3(x,y-1,x2,y2-1,x3,y3-1,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
       destroy3(x,y,x2,y2,x3,y3,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
        }
   else
	{
	   destroy3(x,y-1,x2,y2-1,x3,y3-1,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
       destroy3(x,y,x2,y2,x3,y3,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
       destroy3(x,y+1,x2,y2+1,x3,y3+1,tab);score_up_3();SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
        }
 }

SDL_Flip(ecran);


 	  }



void destroy_type_3(char ch[],nomimage tab[])
{
int i,j,k;
SDL_Rect pos;

for(i=0;i<10;i++)
{for(j=0;j<11;j++)
{
 if(mat[i][j].noimg[0]==ch[0]) destroy1(i,j,tab);

}
}
}

// csy,csx
void destroy1(int i,int j,nomimage tab[])
{int k;SDL_Rect pos;
pos.x=j*80;  pos.y=i*80;

fillrect(mat[i][j]);
SDL_BlitSurface(mat[i][j].img,NULL,ecran,&pos);
SDL_Flip(ecran);
Mix_PlayChannel(-1,effect1,0);
SDL_Delay(300);

     SDL_FreeSurface(mat[i][j].img);
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
	SDL_BlitSurface(cover,NULL,ecran,&pos_text);
    TTF_Font *sc=TTF_OpenFont("textform.TTF",64);
    SDL_FreeSurface(text);
    score=score+1;
    sprintf(s,"%d",score);
    text=TTF_RenderText_Blended(sc,s,cl);
    SDL_BlitSurface(text,NULL,ecran,&pos_text);
       SDL_Flip(ecran);
}


void init_score()
{
  sprintf(s, "%d", score);
cover=SDL_LoadBMP("cover.bmp");

TTF_Font *font=TTF_OpenFont("textform.TTF",64);

text=TTF_RenderText_Blended(font,s,cl);

SCORE=TTF_RenderText_Blended(font,"SCORE :",cl);

SDL_Rect pos;
pos.x=10;   pos.y=825;

SDL_BlitSurface(text,NULL,ecran,&pos_text);
SDL_BlitSurface(SCORE,NULL,ecran,&pos);
SDL_Flip(ecran);
}

void init_score_2()
{
  sprintf(s_2, "%d", score_2);
cover_2=SDL_LoadBMP("cover.bmp");
SDL_Rect pos;
pos.x=1300; pos.y=825;
SCORE2=TTF_RenderText_Blended(font2,"BOT_SCORE :",cl);
TTF_Font *font=TTF_OpenFont("textform.TTF",64);
text_2=TTF_RenderText_Blended(font,s_2,cl);

SDL_BlitSurface(text_2,NULL,ecran,&pos_text_2);
SDL_BlitSurface(SCORE2,NULL,ecran,&pos);
SDL_Flip(ecran);
}





//still beta

int click_pause(int x,int y)
{

{if((x>886&&x<1011)&&(y>350&&y<415))
return 1;
}

}

//fontions for bot

void swap2(int csy,int csx,int csx2,int csy2)
{char temp[20]; void change();
SDL_Rect pos1,pos2;

pos2.y=csy2*80; pos1.y=csy*80;
pos2.x=(csx2*80)+1020; pos1.x=(csx*80)+1020;

strcpy(temp,mat2[csy2][csx2].noimg);
SDL_FreeSurface(mat2[csy2][csx2].img);

mat2[csy2][csx2].img=SDL_LoadBMP(mat2[csy][csx].noimg);

strcpy(mat2[csy2][csx2].noimg,mat2[csy][csx].noimg);
SDL_FreeSurface(mat2[csy][csx].img);

mat2[csy][csx].img=SDL_LoadBMP(temp);
strcpy(mat2[csy][csx].noimg,temp);

SDL_BlitSurface(mat2[csy2][csx2].img,NULL,ecran,&pos2);
SDL_BlitSurface(mat2[csy][csx].img,NULL,ecran,&pos1);

SDL_Flip(ecran);
SDL_Delay(500);
}

int egalite_type_3(int csx,int csy,int csx2,int csy2,nomimage tab[])
{char t[10];
if(mat[csy][csx].noimg[2]=='3')
{
swap(csy,csx,csx2,csy2);
strcpy(t,mat[csy2][csx2].noimg);
destroy1(csy2,csx2,tab);
destroy_type_3(t,tab);
return 1;
}
if(mat[csy2][csx2].noimg=='3')
{
swap(csy,csx,csx2,csy2);
strcpy(t,mat[csy][csx].noimg);
destroy1(csy,csx,tab);
destroy_type_3(mat[csy][csx].noimg,tab);
return 1;
}
}
int egalite_type_3_2(int csx,int csy,int csx2,int csy2,nomimage tab[])
{char t[10];
if(mat2[csy][csx].noimg[2]=='3')
{
swap(csy,csx,csx2,csy2);
strcpy(t,mat2[csy2][csx2].noimg);
destroy1_2(csy2,csx2,tab);
destroy_type_3_2(t,tab);
return 1;
}
if(mat2[csy2][csx2].noimg=='3')
{
swap(csy,csx,csx2,csy2);
strcpy(t,mat2[csy][csx].noimg);
destroy1_2(csy,csx,tab);
destroy_type_3_2(mat2[csy][csx].noimg,tab);
return 1;
}
}



void inser_score()
{


}





//
                                   ///////BOT fonctions section////////




void destroy1_2(int i,int j,nomimage tab[])
{int k;SDL_Rect pos;
pos.x=j*80+1020;  pos.y=i*80;

fillrect(mat2[i][j]);
SDL_BlitSurface(mat2[i][j].img,NULL,ecran,&pos);
SDL_Flip(ecran);
Mix_PlayChannel(-1,effect1,0);
SDL_Delay(300);
SDL_FreeSurface(mat2[i][j].img);
	if(i==0)
	{
	 k=rand()%7;
	mat2[i][j].img=SDL_LoadBMP(tab[k].ch);
	strcpy (mat2[i][j].noimg,tab[k].ch);
	pos.x=j*80+1020;  pos.y=i*80;
	SDL_BlitSurface(mat2[i][j].img,NULL,ecran,&pos);
	}

	else
	{
	  k=i;
	  while(k>0)
		{
		  mat2[k][j].img=SDL_LoadBMP(mat2[k-1][j].noimg);
		  strcpy (mat2[k][j].noimg,mat2[k-1][j].noimg);
		  pos.x=j*80+1020;  pos.y=k*80;
		  SDL_BlitSurface(mat2[k][j].img,NULL,ecran,&pos);
		  k--;
		}
	 k=rand()%7;
	 mat2[0][j].img=SDL_LoadBMP(tab[k].ch);
	 strcpy (mat2[0][j].noimg,tab[k].ch);
	 pos.x=j*80+1020;  pos.y=0;
	 SDL_BlitSurface(mat2[0][j].img,NULL,ecran,&pos);
	}

       SDL_Flip(ecran);


}

void destroy_type2_2(int y,int x,int y2,int x2,int y3,int x3,nomimage tab[])
{
    SDL_Rect pos,pos2,pos3,pos4,pos5,pos6,pos7,pos8,pos9;void decalage();

if(x==x2)
 {destroy3_2(x,y,x2,y2,x3,y3,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
 SDL_Flip(ecran);
 SDL_Delay(400);
   if(x==10)
	{destroy3_2(x-1,y,x2-1,y2,x3-1,y3,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
	}
   else if(x==0)
        { destroy3_2(x+1,y,x2+1,y2,x3+1,y3,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
	}
   else
        {
         destroy3_2(x+1,y,x2+1,y2,x3+1,y3,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
         destroy3_2(x-1,y,x2-1,y2,x3-1,y3,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
        }
 }

else

if(y==y2)
 {
   if(y==0)
	{
	destroy3_2(x,y,x2,y2,x3,y3,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
    destroy3_2(x,y+1,x2,y2+1,x3,y3+1,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
        }
   else if(y==9)
	{
	   destroy3_2(x,y-1,x2,y2-1,x3,y3-1,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
       destroy3_2(x,y,x2,y2,x3,y3,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
        }
   else
	{
	   destroy3_2(x,y-1,x2,y2-1,x3,y3-1,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
       destroy3_2(x,y,x2,y2,x3,y3,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
       destroy3_2(x,y+1,x2,y2+1,x3,y3+1,tab);SDL_Flip(ecran);Mix_PlayChannel(-1,effect1,0);
        }
 }

SDL_Flip(ecran);


 	  }



void destroy3_2(int csx2,int csy2,int x3,int y3,int x4,int y4,nomimage tab[])
{void decalage_2();

SDL_Rect pos;
//fill the destroyed cases with green


fillrect(mat2[y3][x3]); fillrect(mat2[y4][x4]);
fillrect(mat2[csy2][csx2]);

pos.x=csx2*80+1020; pos.y=csy2*80;
SDL_BlitSurface(mat2[csy2][csx2].img,NULL,ecran,&pos);



pos.x=x3*80+1020; pos.y=y3*80;
SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos);



pos.x=x4*80+1020; pos.y=y4*80;
SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos);

SDL_Flip(ecran);
SDL_Delay(300);
//TESTING

//apelle a la fonction decalage (delated)

decalage_2(csx2,csy2,x3,y3,x4,y4,tab);

printf("%s\n",mat2[csx2][csy2].noimg);
printf("%s\n",mat2[y4][x4].noimg);
printf("%s\n",mat2[y3][x4].noimg);


}

void destroy3_2_t(int csx2,int csy2,int x3,int y3,int x4,int y4,nomimage tab[])
{void decalage_2();

SDL_Rect pos;
//fill the destroyed cases with green


fillrect(mat2[y3][x3]); fillrect(mat2[y4][x4]);
fillrect(mat2[csy2][csx2]);

pos.x=csx2*80+1020; pos.y=csy2*80;
SDL_BlitSurface(mat2[csy2][csx2].img,NULL,ecran,&pos);



pos.x=x3*80+1020; pos.y=y3*80;
SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos);



pos.x=x4*80+1020; pos.y=y4*80;
SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos);

SDL_Flip(ecran);

//TESTING

//apelle a la fonction decalage (delated)

decalage_2(csx2,csy2,x3,y3,x4,y4,tab);

printf("%s\n",mat2[csx2][csy2].noimg);
printf("%s\n",mat2[y4][x4].noimg);
printf("%s\n",mat2[y3][x4].noimg);


}

/*
void aide2()
{
int i,j,b;
i=0;b=0;
while((i<10)&&(b==0))
{
j=0;
while((j<11)&&(b==0))
{
if((j<8)&&(i>0)&&(egalite2(i,j,i-1,j+1)==1)&&(egalite2(i,j,i-1,j+2)==1))
{swap2(i,j,j,i-1);b=1;}
else if((j<8)&&(i<10)&&(egalite2(i,j,i+1,j+1)==1)&&(egalite2(i,j,i+1,j+2)==1))
{swap2(i,j,j,i+1);b=1;}
else if((j<9)&&(i>0)&&(egalite2(i,j,i-1,j+1)==1)&&(egalite2(i,j,i-1,j-1)==1))
{swap2(i,j,j,i-1);b=1;}
else if((j<9)&&(i<10)&&(egalite2(i,j,i+1,j+1)==1)&&(egalite2(i,j,i+1,j-1)==1))
{swap2(i,j,j,i+1);b=1;}
else if((j>1)&&(i>0)&&(egalite2(i,j,i-1,j-1)==1)&&(egalite2(i,j,i-1,j-2)==1))
{swap2(i,j,j,i-1);b=1;}
else if((j>1)&&(i<10)&&(egalite2(i,j,i+1,j-1)==1)&&(egalite2(i,j,i+1,j-2)==1))
{swap2(i,j,j,i+1);b=1;}
else if((j>0)&&(j<9)&&(i>0)&&(egalite2(i,j,i-1,j-1)==1)&&(egalite2(i,j,i-1,j+1)==1))
{swap2(i,j,j,i-1);b=1;}
else if((j>0)&&(j<9)&&(i<9)&&(egalite2(i,j,i+1,j-1)==1)&&(egalite2(i,j,i+1,j+1)==1))
{swap2(i,j,j,i+1);b=1;}
else if((j>0)&&(i>1)&&(egalite2(i,j,i-1,j-1)==1)&&(egalite2(i,j,i-2,j-1)==1))
{swap2(i,j,j-1,i);b=1;}
else if((j>0)&&(i<9)&&(egalite2(i,j,i+1,j-1)==1)&&(egalite2(i,j,i+2,j-1)==1))
{swap2(i,j,j-1,i);b=1;}
else if((j>0)&&(i>0)&&(i<10)&&(egalite2(i,j,i-1,j-1)==1)&&(egalite2(i,j,i+1,j-1)==1))
{swap2(i,j,j-1,i);b=1;}
else if((j<10)&&(i>0)&&(i<10)&&(egalite2(i,j,i-1,j+1)==1)&&(egalite2(i,j,i+1,j+1)==1))
{swap2(i,j,j+1,i);b=1;}
else if((j<9)&&(i>1)&&(egalite2(i,j,i-1,j+1)==1)&&(egalite2(i,j,i-2,j+1)==1))
{swap2(i,j,j+1,i);b=1;}
else if((j<9)&&(i<9)&&(egalite2(i,j,i+1,j+1)==1)&&(egalite2(i,j,i+2,j+1)==1))
{swap2(i,j,j+1,i);b=1;}
if((j<7)&&(egalite2(i,j,i,j+2)==1)&&(egalite2(i,j,i,j+3)==1))
{swap2(i,j,j+1,i);b=1;}
else if((j>2)&&(egalite2(i,j,i,j-2)==1)&&(egalite2(i,j,i,j-3)==1))
{swap2(i,j,j-1,i);b=1;}
else if((i<8)&&(egalite2(i,j,i+2,j)==1)&&(egalite2(i,j,i+3,j)==1))
{swap2(i,j,j,i+1);b=1;}
else if((i>2)&&(egalite2(i,j,i-2,j)==1)&&(egalite2(i,j,i-3,j)==1))
{swap2(i,j,j,i-1);b=1;}
else j++;
}
if(b==0)
i++;
}
}
*/





int egalite2(int csy,int csx,int csy2,int csx2)
{
if(csy2<0 || csy2>9)return 0;
if(csx2<0 || csx2>10)return 0;
if (mat2[csy][csx].noimg[0]==mat2[csy2][csx2].noimg[0]) return 1;
return 0;
}




void destroy_type_3_2(char ch[],nomimage tab[])
{
int i,j,k;
SDL_Rect pos;

for(i=0;i<10;i++)
{for(j=0;j<11;j++)
{
 if(mat2[i][j].noimg[0]==ch[0]) destroy1_2(i,j,tab);

}
}
}



//détruire les 3 cases

void destroy_2(int csx2,int csy2,int x3,int y3,int x4,int y4,nomimage tab[])

{
void score_up_3_2();

void decalage_2();

SDL_Rect pos;
//fill the destroyed cases with green
char t1[10],t2[10],t3[10];

strcpy(t1,mat2[csy2][csx2].noimg);
strcpy(t2,mat2[y3][x3].noimg);
strcpy(t3,mat2[y4][x4].noimg);

 if((mat2[csy2][csx2].noimg[2]=='2')|| (mat2[y3][x3].noimg[2]=='2')||
  (mat2[y4][x4].noimg[2]=='2')) destroy_type2_2(csy2,csx2,y3,x3,y4,x4,tab);
else {

fillrect(mat2[y3][x3]); fillrect(mat2[y4][x4]);
fillrect(mat2[csy2][csx2]);

pos.x=csx2*80+1020; pos.y=csy2*80;
SDL_BlitSurface(mat2[csy2][csx2].img,NULL,ecran,&pos);



pos.x=x3*80+1020; pos.y=y3*80;
SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos);



pos.x=x4*80+1020; pos.y=y4*80;
SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos);

SDL_Flip(ecran);


SDL_Flip(ecran);
score_up_3_2();
Mix_PlayChannel(-1,effect1,0);
SDL_Delay(300);

decalage_2(csx2,csy2,x3,y3,x4,y4,tab);
test_2(tab);

printf("%s\n",mat2[csx2][csy2].noimg);
printf("%s\n",mat2[y4][x4].noimg);
printf("%s\n",mat2[y3][x4].noimg);

if(t1[2]=='3') destroy_type_3_2(t1,tab);
else if(t2[2]=='3')destroy_type_3_2(t2,tab);
else if(t3[2]=='3')destroy_type_3_2(t3,tab);

}
}

void decalage_2(int csx2,int csy2,int x3,int y3,int x4,int y4,nomimage tab[])
{int k;SDL_Rect pos;


int cy2=csy2,cy3=y3,cy4=y4,cx3=x3,cx2=csx2,cx4=x4; //copy of the cordi;
int sum=csy2+y3+y4;
//1 er cas décalage horizontal
if((csx2!=x3&&csx2!=x4)&&(csy2==y3&&csy2==y4))
{
while(csy2>0)
{ SDL_FreeSurface(mat2[csy2][csx2].img);
  SDL_FreeSurface(mat2[y3][x3].img);
  SDL_FreeSurface(mat2[y4][x4].img);

mat2[csy2][csx2].img=SDL_LoadBMP(mat2[csy2-1][csx2].noimg); strcpy(mat2[csy2][csx2].noimg,mat2[csy2-1][csx2].noimg);
mat2[y3][x3].img=SDL_LoadBMP(mat2[y3-1][x3].noimg);        strcpy(mat2[y3][x3].noimg,mat2[y3-1][x3].noimg);
mat2[y4][x4].img=SDL_LoadBMP(mat2[y4-1][x4].noimg);       strcpy(mat2[y4][x4].noimg,mat2[y4-1][x4].noimg);

pos.x=csx2*80+1020 ;pos.y=csy2*80;
SDL_BlitSurface(mat2[csy2][csx2].img,NULL,ecran,&pos);

pos.x=x3*80+1020 ;pos.y=y3*80;
SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80+1020 ;pos.y=y4*80;
SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos);

//SDL_Flip(ecran);



csy2--; y3--; y4--;


}


k=rand()%7;
mat2[csy2][csx2].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat2[csy2][csx2].noimg,tab[k].ch);
k=rand()%7;
mat2[y3][x3].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat2[y3][x3].noimg,tab[k].ch);
k=rand()%7;
mat2[y4][x4].img=SDL_LoadBMP(tab[k].ch); strcpy(mat2[y4][x4].noimg,tab[k].ch);

pos.x=csx2*80+1020 ;pos.y=csy2*80;
SDL_BlitSurface(mat2[csy2][csx2].img,NULL,ecran,&pos);

pos.x=x3*80+1020 ;pos.y=y3*80;
SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80+1020 ;pos.y=y4*80;
SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos);


}
//2éme cas décalage vertical

else if(csx2==x3&&csx2==x4)
{int cy2=0,cy3=1,cy4=2,cx3=x3,cx2=csx2,cx4=x4; //copy of the cordi;

while(csy2>2||y3>2||y4>2)
{
  SDL_FreeSurface(mat2[csy2][csx2].img);
  SDL_FreeSurface(mat2[y3][x3].img);
  SDL_FreeSurface(mat2[y4][x4].img);

mat2[csy2][csx2].img=SDL_LoadBMP(mat2[csy2-3][csx2].noimg);
strcpy(mat2[csy2][csx2].noimg,mat2[csy2-3][csx2].noimg);

mat2[y3][x3].img=SDL_LoadBMP(mat2[y3-3][x3].noimg);
strcpy(mat2[y3][x3].noimg,mat2[y3-3][x3].noimg);

mat2[y4][x4].img=SDL_LoadBMP(mat2[y4-3][x4].noimg);
strcpy(mat2[y4][x4].noimg,mat2[y4-3][x4].noimg);


pos.x=csx2*80+1020 ;pos.y=csy2*80;
SDL_BlitSurface(mat2[csy2][csx2].img,NULL,ecran,&pos);

pos.x=x3*80+1020 ;pos.y=y3*80;
SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80+1020 ;pos.y=y4*80;
SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos);



//SDL_Flip(ecran);






csy2=csy2-3;y3=y3-3;y4=y4-3;

printf("%d\n",csy2);
printf("%d\n",y3);
printf("%d\n",y4);
}

if((sum%5==0)||(sum==6))
{
SDL_FreeSurface(mat2[3][cx3].img);
mat2[3][cx3].img=SDL_LoadBMP(mat2[0][cx3].noimg);
strcpy(mat2[3][cx3].noimg,mat2[0][cx3].noimg);

pos.x=cx3*80+1020 ;pos.y=3*80;
SDL_BlitSurface(mat2[3][cx3].img,NULL,ecran,&pos);

}
else if((sum==18)||(sum==9))
{
SDL_FreeSurface(mat2[4][cx3].img);
mat2[4][cx3].img=SDL_LoadBMP(mat2[1][cx3].noimg);
strcpy(mat2[4][cx3].noimg,mat2[1][cx3].noimg);


pos.x=cx3*80+1020 ;pos.y=4*80;
SDL_BlitSurface(mat2[4][cx3].img,NULL,ecran,&pos);

SDL_FreeSurface(mat2[3][cx3].img);
mat2[3][cx3].img=SDL_LoadBMP(mat2[0][cx3].noimg);
strcpy(mat2[3][cx3].noimg,mat2[0][cx3].noimg);

pos.x=cx3*80+1020 ;pos.y=3*80;
SDL_BlitSurface(mat2[3][cx3].img,NULL,ecran,&pos);

}

  SDL_FreeSurface(mat2[cy2][cx2].img);
  SDL_FreeSurface(mat2[cy3][cx3].img);
  SDL_FreeSurface(mat2[cy4][cx4].img);

k=rand()%7;
mat2[cy2][cx2].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat2[cy2][cx2].noimg,tab[k].ch);
k=rand()%7;
mat2[cy3][cx3].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat2[cy3][cx3].noimg,tab[k].ch);
k=rand()%7;
mat2[cy4][cx4].img=SDL_LoadBMP(tab[k].ch); strcpy(mat2[cy4][cx4].noimg,tab[k].ch);

pos.x=cx2*80+1020 ;pos.y=cy2*80;
SDL_BlitSurface(mat2[cy2][cx2].img,NULL,ecran,&pos);

pos.x=cx3*80+1020 ;pos.y=cy3*80;
SDL_BlitSurface(mat2[cy3][cx3].img,NULL,ecran,&pos);

pos.x=cx4*80+1020 ;pos.y=cy4*80;
SDL_BlitSurface(mat2[cy4][cx4].img,NULL,ecran,&pos);

}


SDL_Flip(ecran);


}

void swap_destroy_2(int csy,int csx,int csx2,int csy2)
{
char temp[20]; void change();
SDL_Rect pos1,pos2;

pos2.y=csy2*80; pos1.y=csy*80;
pos2.x=csx2*80+1020; pos1.x=csx*80+1020;

strcpy(temp,mat2[csy2][csx2].noimg);


strcpy(mat2[csy2][csx2].noimg,mat2[csy][csx].noimg);

SDL_FreeSurface(mat2[csy][csx].img);

mat2[csy][csx].img=SDL_LoadBMP(temp);
strcpy(mat2[csy][csx].noimg,temp);


SDL_BlitSurface(mat2[csy][csx].img,NULL,ecran,&pos1);
//destroy the second argument
fillrect(mat2[csy2][csx2]);
SDL_BlitSurface(mat2[csy2][csx2].img,NULL,ecran,&pos2);
SDL_Flip(ecran);
}

void destroy4_2(int csx2,int csy2,int x3,int y3,int x4,int y4,int x5,int y5,nomimage tab[])
{
    int i;   int  recherche();void decalage4();
    SDL_Rect pos2,pos3,pos4,pos5;void decalage();
    fillrect(mat2[y3][x3]); fillrect(mat2[y4][x4]);
    fillrect(mat2[csy2][csx2]); fillrect(mat2[y5][x5]);

    pos3.x=x3*80+1020;   pos3.y=y3*80;   pos4.x=x4*80+1020;    pos4.y=y4*80;
    pos2.x=csx2*80+1020; pos2.y=csy2*80;  pos5.x=x5*80+1020;  pos5.y=y5*80;


SDL_BlitSurface(mat2[y5][x5].img,NULL,ecran,&pos5);

SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos3);

SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos4);



i=recherche(mat2[csy2][csx2].noimg,tab);
SDL_FreeSurface(mat2[csy2][csx2].img);
mat2[csy2][csx2].img=SDL_LoadBMP(tab[i+7].ch);  strcpy(mat2[csy2][csx2].noimg,tab[i+7].ch);

SDL_BlitSurface(mat2[csy2][csx2].img,NULL,ecran,&pos2);

SDL_Flip(ecran);
SDL_Delay(300);
    decalage4_2(csx2,csy2,x3,y3,x4,y4,x5,y5,tab);
}



void decalage4_2(int csx2,int csy2,int x3,int y3,int x4,int y4,int x5,int y5,nomimage tab[])
{int max=max4(csy2,y3,y4,y5);void decalage_2();
//1er cas decalage horizontal
printf("%d",max);
if((csx2!=x3&&csx2!=x4&&csx2!=x5)&&(csy2==y3&&csy2==y4&&csy2==y5))
 decalage_2(x3,y3,x4,y4,x5,y5,tab);
else if((csx2==x3)&&(csx2==x4)&&(csx2==x5))
{SDL_Rect pos;

if(max==csy2) decalage_2(x3,y3,x4,y4,x5,y5,tab);
else
{

swap_destroy_2(max,x3,csx2,csy2);


SDL_Delay(1000);
if(max==y3)
decalage_2(csx2,csy2,x4,y4,x5,y5,tab);
else if(max==y4) decalage_2(csx2,csy2,x3,y3,x5,y5,tab);
else decalage_2(csx2,csy2,x3,y3,x4,y4,tab);

}

}
}

//still beta not tested yet
void destroy5_2(int csx2,int csy2,int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6,nomimage tab[])
{void decalage5();
    int i;
    SDL_Rect pos2,pos3,pos4,pos5,pos6;
    fillrect(mat2[y3][x3]); fillrect(mat2[y4][x4]);
    fillrect(mat2[csy2][csx2]);
    fillrect(mat2[y5][x5]);
    fillrect(mat2[y6][x6]);

    pos3.x=x3*80+1020;      pos2.x=csx2*80+1020;
    pos3.y=y3*80;
                            pos2.y=csy2*80;
    pos4.y=y4*80;
    pos4.x=x4*80+1020;
    pos5.x=x5*80+1020;      pos5.y=y5*80; pos6.x=x6*80+1020;  pos6.y=y6*80;

//blite with green

SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos3);
SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos4);
SDL_BlitSurface(mat2[y5][x5].img,NULL,ecran,&pos5);
SDL_BlitSurface(mat2[y6][x6].img,NULL,ecran,&pos6);



i=recherche(mat2[csy2][csx2].noimg,tab);

mat2[csy2][csx2].img=SDL_LoadBMP(tab[i+14].ch);
 strcpy(mat2[csy2][csx2].noimg,tab[i+14].ch);


SDL_BlitSurface(mat2[csy2][csx2].img,NULL,ecran,&pos2);
pos2.x=10*80+1020;pos2.y=8*80;
SDL_BlitSurface(mat2[8][10].img,NULL,ecran,&pos2);
SDL_Flip(ecran);
SDL_Delay(300);
   decalage5_2(csx2,csy2,x3,y3,x4,y4,x5,y5,x6,y6,tab); test_2(tab);
}





void decalage5_2(int csx2,int csy2,int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6,nomimage tab[])
{
SDL_Rect pos;int k;void decalage4_v_2();
//1 er cas décalage horizontal
if((csx2!=x3&&csx2!=x4)&&(csy2==y3&&csy2==y4))
{
while(y3>0)
{ SDL_FreeSurface(mat2[y5][x5].img);
  SDL_FreeSurface(mat2[y3][x3].img);
  SDL_FreeSurface(mat2[y6][x6].img);
  SDL_FreeSurface(mat2[y4][x4].img);


mat2[y3][x3].img=SDL_LoadBMP(mat2[y3-1][x3].noimg);        strcpy(mat2[y3][x3].noimg,mat2[y3-1][x3].noimg);
mat2[y4][x4].img=SDL_LoadBMP(mat2[y4-1][x4].noimg);        strcpy(mat2[y4][x4].noimg,mat2[y4-1][x4].noimg);
mat2[y5][x5].img=SDL_LoadBMP(mat2[y5-1][x5].noimg);        strcpy(mat2[y5][x5].noimg,mat2[y5-1][x5].noimg);
mat2[y6][x6].img=SDL_LoadBMP(mat2[y6-1][x6].noimg);        strcpy(mat2[y6][x6].noimg,mat2[y6-1][x6].noimg);


//affichage des images dans l'ecran
pos.x=x3*80+1020 ;pos.y=y3*80;
SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80+1020 ;pos.y=y4*80;
SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos);

pos.x=x5*80+1020 ;pos.y=y5*80;
SDL_BlitSurface(mat2[y5][x5].img,NULL,ecran,&pos);

pos.x=x6*80+1020 ;pos.y=y6*80;
SDL_BlitSurface(mat2[y6][x6].img,NULL,ecran,&pos);



SDL_Flip(ecran);



 y3--; y4--; y5--; y6--;


}
//affections les  4 derniers cases
k=rand()%7;
mat2[y3][x3].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat2[y3][x3].noimg,tab[k].ch);
k=rand()%7;
mat2[y4][x4].img=SDL_LoadBMP(tab[k].ch); strcpy(mat2[y4][x4].noimg,tab[k].ch);
k=rand()%7;
mat2[y5][x5].img=SDL_LoadBMP(tab[k].ch); strcpy(mat2[y5][x5].noimg,tab[k].ch);
k=rand()%7;
mat2[y6][x6].img=SDL_LoadBMP(tab[k].ch); strcpy(mat2[y6][x6].noimg,tab[k].ch);

//affichage des images dans l'ecran
pos.x=x3*80+1020 ;pos.y=y3*80;
SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80+1020 ;pos.y=y4*80;
SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos);



pos.x=x5*80+1020 ;pos.y=y5*80;
SDL_BlitSurface(mat2[y5][x5].img,NULL,ecran,&pos);

pos.x=x6*80+1020 ;pos.y=y6*80;
SDL_BlitSurface(mat2[y6][x6].img,NULL,ecran,&pos);
SDL_Flip(ecran);

}

//2éme cas decalage vertical
else
{int max=max5(csy2,y3,y4,y5,y6);SDL_Rect pos,pos2;
if (max==csy2) decalage4_v( x3, y3, x4, y4, x5,  y5, x6, y6, tab);
else{



swap_destroy_2(max,x3,csx2,csy2);//swap

SDL_Delay(300);


if(max==y3) decalage4_v(csy2,csx2,x4,y4,x5,y5,x6,y6,tab);
else if(max==y4) decalage4_v_2(x3,y3,csx2,csy2,x5,y5,x6,y6,tab);
else if(max==y5) decalage4_v_2(x3,y3,x4,y4,csx2,csy2,x6,y6,tab);
else if(max==y6) decalage4_v_2(x3,y3,x4,y4,x5,y5,csx2,csy2,tab);

}

}


}
void decalage4_v_2(int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6,nomimage tab[])
{//decalage vertical
int cy3=0,cy4=1,cy5=2,cy6=3,cx3=x3,cx4=x4,cx5=x5,cx6=x6,k; //copy de cordonnes;
SDL_Rect pos;
int sum=y3+y4+y5+y6;
while((y3>3)||(y4>3)||(y5>3)||(y6>3))
{
  SDL_FreeSurface(mat2[y3][x3].img);
  SDL_FreeSurface(mat2[y4][x4].img);
  SDL_FreeSurface(mat2[y5][x5].img);
  SDL_FreeSurface(mat2[y6][x6].img);

mat2[y3][x3].img=SDL_LoadBMP(mat2[y3-4][x3].noimg);
strcpy(mat2[y3][x3].noimg,mat2[y3-4][x3].noimg);

mat2[y4][x4].img=SDL_LoadBMP(mat2[y4-4][x4].noimg);
strcpy(mat2[y4][x4].noimg,mat2[y4-4][x4].noimg);

mat2[y5][x5].img=SDL_LoadBMP(mat2[y5-4][x5].noimg);
strcpy(mat2[y5][x5].noimg,mat2[y5-4][x5].noimg);

mat2[y6][x6].img=SDL_LoadBMP(mat2[y6-4][x6].noimg);
strcpy(mat2[y6][x6].noimg,mat2[y6-4][x6].noimg);


pos.x=x3*80+1020 ;pos.y=y3*80;
SDL_BlitSurface(mat2[y3][x3].img,NULL,ecran,&pos);

pos.x=x4*80+1020 ;pos.y=y4*80;
SDL_BlitSurface(mat2[y4][x4].img,NULL,ecran,&pos);

pos.x=x5*80+1020 ;pos.y=y5*80;
SDL_BlitSurface(mat2[y5][x5].img,NULL,ecran,&pos);

pos.x=x6*80+1020 ;pos.y=y6*80;
SDL_BlitSurface(mat2[y6][x6].img,NULL,ecran,&pos);

SDL_Flip(ecran);


y3=y3-4; y4=y4-4; y5=y5-4; y6=y6-4;

}

if((sum==10)||(sum==26))
{
SDL_FreeSurface(mat2[4][cx4].img);
mat2[4][cx4].img=SDL_LoadBMP(mat2[0][cx4].noimg);
strcpy(mat2[4][cx4].noimg,mat2[0][cx4].noimg);

pos.x=cx4*80+1020 ;pos.y=4*80;
SDL_BlitSurface(mat2[4][cx4].img,NULL,ecran,&pos);

}
else if((sum==14)||(sum==30))
{
SDL_FreeSurface(mat2[5][cx4].img);
mat2[5][cx4].img=SDL_LoadBMP(mat2[1][cx4].noimg);
strcpy(mat2[5][cx4].noimg,mat2[1][cx4].noimg);


pos.x=cx4*80+1020 ;pos.y=5*80;
SDL_BlitSurface(mat2[5][cx4].img,NULL,ecran,&pos);



SDL_FreeSurface(mat2[4][cx4].img);
mat2[4][cx4].img=SDL_LoadBMP(mat2[0][cx4].noimg);
strcpy(mat2[4][cx4].noimg,mat2[0][cx4].noimg);

pos.x=cx4*80+1020 ;pos.y=4*80;
SDL_BlitSurface(mat2[4][cx4].img,NULL,ecran,&pos);

}else if(sum==18)
{

SDL_FreeSurface(mat2[6][cx4].img);
mat2[6][cx4].img=SDL_LoadBMP(mat2[2][cx4].noimg);
strcpy(mat2[6][cx4].noimg,mat2[2][cx4].noimg);


pos.x=cx4*80+1020 ;pos.y=6*80;
SDL_BlitSurface(mat2[6][cx4].img,NULL,ecran,&pos);



SDL_FreeSurface(mat2[5][cx4].img);
mat2[5][cx4].img=SDL_LoadBMP(mat2[1][cx4].noimg);
strcpy(mat2[5][cx4].noimg,mat2[1][cx4].noimg);

pos.x=cx4*80+1020 ;pos.y=5*80;
SDL_BlitSurface(mat2[5][cx4].img,NULL,ecran,&pos);


SDL_FreeSurface(mat2[4][cx4].img);
mat2[4][cx4].img=SDL_LoadBMP(mat2[0][cx4].noimg);
strcpy(mat2[4][cx4].noimg,mat2[0][cx4].noimg);

pos.x=cx4*80+1020 ;pos.y=4*80;
SDL_BlitSurface(mat2[4][cx4].img,NULL,ecran,&pos);

}
 //libérer l'espace mémoire de les 4 derniers cases
  SDL_FreeSurface(mat2[cy3][cx3].img);
  SDL_FreeSurface(mat2[cy4][cx4].img);
  SDL_FreeSurface(mat2[cy5][cx5].img);
  SDL_FreeSurface(mat2[cy6][cx6].img);
//affecter les 4 derniers cases au hasard
k=rand()%7;
mat2[cy3][cx3].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat2[cy3][cx3].noimg,tab[k].ch);
k=rand()%7;
mat2[cy4][cx4].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat2[cy4][cx4].noimg,tab[k].ch);
k=rand()%7;
mat2[cy5][cx5].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat2[cy5][cx5].noimg,tab[k].ch);
k=rand()%7;
mat2[cy6][cx6].img=SDL_LoadBMP(tab[k].ch);  strcpy(mat2[cy6][cx6].noimg,tab[k].ch);






//affichier les images (les 4 derniers  cases)
pos.x=cx3*80+1020 ;pos.y=cy3*80;
SDL_BlitSurface(mat2[cy3][cx3].img,NULL,ecran,&pos);

pos.x=cx4*80+1020 ;pos.y=cy4*80;
SDL_BlitSurface(mat2[cy4][cx4].img,NULL,ecran,&pos);

pos.x=cx5*80+1020 ;pos.y=cy5*80;
SDL_BlitSurface(mat2[cy5][cx5].img,NULL,ecran,&pos);

pos.x=cx6*80+1020 ;pos.y=cy6*80;
SDL_BlitSurface(mat2[cy6][cx6].img,NULL,ecran,&pos);


//mise a jour l'ecran
SDL_Flip(ecran);

}


void test_2(nomimage tab[])
{
	int j,i,b;
	j=0;
while(j<11)
{
i=0;b=0;
while((i<10)&&(b==0))
{
if((i<6)&&(egalite2(j,i,j,i+1)==1)&&(egalite2(j,i,j,i+2)==1)&&(egalite2(j,i,j,i+3)==1)&&(egalite2(j,i,j,i+4)==1))
{destroy5_2(i,j,i+1,j,i+2,j,i+3,j,i+4,j,tab);b=1;}
else
if((i<7)&&(egalite2(j,i,j,i+1)==1)&&(egalite2(j,i,j,i+2)==1)&&(egalite2(j,i,j,i+3)==1))
{destroy4_2(i,j,i+1,j,i+2,j,i+3,j,tab);b=1;}
else
if((i<8)&&(egalite2(j,i,j,i+1)==1)&&(egalite2(j,i,j,i+2)==1))
{destroy3_2_t(i,j,i+1,j,i+2,j,tab);b=1;}
else
if((j<7)&&(egalite2(j,i,j+1,i)==1)&&(egalite2(j,i,j+2,i)==1)&&(egalite2(j,i,j+3,i)==1)&&(egalite2(j,i,j+4,i)==1))
{
destroy5_2(i,j,i,j+1,i,j+2,i,j+3,i,j+4,tab);b=1;}
else
if((j<8)&&(egalite2(j,i,j+1,i)==1)&&(egalite2(j,i,j+2,i)==1)&&(egalite2(j,i,j+3,i)==1))
{destroy4_2(i,j,i,j+1,i,j+2,i,j+3,tab);b=1;}
else
if((j<9)&&(egalite2(j,i,j+1,i)==1)&&(egalite2(j,i,j+2,i)==1))
{destroy3_2_t(i,j,i,j+1,i,j+2,tab);b=1;}
else
i++;
}
if(b==1)
j=0;
else j++;
}

}

void reswap2(int csy,int csx,int csx2,int csy2)
{
swap2(csy,csx,csx2,csy2);
swap2(csy2,csx2,csx,csy);
}

//cas de csy2-1 ,csy2+1
int verf_1_1_2(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
  if(egalite2(csy,csx,csy2-2,csx2)==1)
   {

     if(egalite2(csy,csx,csy2+2,csx2)==1)
   {
   swap2(csy,csx,csx2,csy2);
   destroy5_2(csx2,csy2,csx2,csy2-1,csx2,csy2+1,
   csx2,csy2-2,csx2,csy+2,tab);
   return 1;
   }
   swap2(csy,csx,csx2,csy2);
   destroy4_2(csx2,csy2,csx2,csy2-1,csx2,csy2+1,
   csx2,csy2-2,tab);
   return 1;

   }

   else if(egalite2(csy,csx,csy2+2,csx2)==1)
   {
   swap2(csy,csx,csx2,csy2);
   destroy4_2(csx2,csy2,csx2,csy2-1,csx2,csy2+1,
   csx2,csy2+2,tab);
   return 1;
   }
   return 0;

}
//cas csx2-1 ,csx2-2
int verf_1_2_2(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
   if(egalite2(csy,csx,csy2,csx2+1)==1)
  {
      if(egalite2(csy,csx,csy2,csx2+2)==1)
      {
      swap2(csy,csx,csx2,csy2);
      destroy5_2(csx2,csy2,csx2-1,csy2,csx2-2,csy2,csx2+1,csy2,
      csx2+2,csy2,tab);
      return 1;
      }
      swap2(csy,csx,csx2,csy2);
      destroy4_2(csx2,csy2,csx2-1,csy2,csx2-2,csy2,csx2+1,csy2,tab);
      return 1;
  }else return 0;

}
//cas csy2-1,csy2-2
int verf_1_3_2(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
       // cas 4 cases
   if (egalite2(csy,csx,csy2+1,csx2)==1)
   {

   if(egalite2(csy,csx,csy2+2,csx2)==1)
   //5 cases
   {
   swap2(csy,csx,csx2,csy2);
   destroy5_2(csx2,csy2,csx2,csy2-1,csx2,csy2-2,csx2,csy2+1,csx2
   ,csy2+2,tab);
   return 1;
   }
   swap2(csy,csx,csx2,csy2);
   destroy4_2(csx2,csy2,csx2,csy2-1,csx2,csy2-2,csx2,csy2+1,tab);
   return 1;
   }else return 0;


}

//cas csy2+1,csy2+2
int verf_1_4_2(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
    if(egalite2(csy,csx,csy2-1,csx2)==1)
    {if(egalite2(csy,csx,csy2-2,csx2)==1)
    {//appele destroy 5
    swap2(csy,csx,csx2,csy2);
    destroy5_2(csx2,csy2,csx2,csy2+1,csx2,csy2+2,csx2,csy2-1,csx2,
    csy2-2,tab);
    return 1;
    }else
    swap2(csy,csx,csx2,csy2);
    destroy4_2(csx2,csy2,csx2,csy2+1,csx2,csy2+2,csx2,csy2-1,tab);
    return 1;
    }else return 0;

}

//cas csx2+1,csx2+2
int verf_1_5_2(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
 if(egalite2(csy,csx,csy2,csx2-1)==1)
 {
    if(egalite2(csy,csx,csy2,csx2-2)==1)
     {
     swap2(csy,csx,csx2,csy2);
     destroy5_2(csx2,csy2,csx2+1,csy2,csx2+2,csy2,csx2-1,csy2,
     csx2-2,csy2,tab);
      return 1;
     }else
   { //apelle
    swap2(csy,csx,csx2,csy2);
    destroy4_2(csx2,csy2,csx2+1,csy2,csx2+2,csy2,csx2-1,csy2,tab);
    return 1;
    }
 }else return 0;

}
//cas csx2+1,csx2-1
int verf_1_6_2(int csx,int csy,int csx2,int csy2,nomimage tab[])
{
    if(egalite2(csy,csx,csy2,csx2+2)==1)
     {if(egalite2(csy,csx,csy2,csx2-2)==1)
     {
     swap2(csy,csx,csx2,csy2);
     destroy5_2(csx2,csy2,csx2+1,csy2,csx2-1,csy2,csx2+2,
     csy2,csx2-2,csy2,tab);
     return 1;
     }
     swap2(csy,csx,csx2,csy2);
     destroy4_2(csx2,csy2,csx2+1,csy2,csx2-1,csy2,csx2+2,
    csy2,tab);
    return 1;
     }
     else if(egalite2(csy,csx,csy2,csx2-2)==1)
     {
     swap2(csy,csx,csx2,csy2);
     destroy4_2(csx2,csy2,csx2+1,csy2,csx2-1,csy2,csx2-2,csy2,tab);
     return 1;
     }
return 0;


}


void verification_global_2(int csx,int csy,int csx2,int csy2,nomimage tab[],int i)
{int d=0,ok;
///////////////////////1er cas

if(csy2==csy&&csx2==csx-1)
     {
if((d==0)&&(egalite_type_3_2(csx,csy,csx2,csy2,tab)==1)){d=1;ok=1;}
else
if((d==0)&&(egalite2(csy,csx,csy2-1,csx2)==1)
&&(egalite2(csy,csx,csy2+1,csx2)==1))
    {ok=1;d=1;
                if(verf_1_1_2(csx,csy,csx2,csy2,tab)==0)
               {swap2(csy,csx,csx2,csy2);
                destroy_2(csx2,csy2,csx2,csy2-1,csx2,csy2+1,tab);
               }
}
else if((d==0)&&(egalite2(csy,csx,csy2+1,csx2)==1)
&&(egalite2(csy,csx,csy2+2,csx2)==1))
    {ok=1;d=1;
       if(verf_1_4_2(csx,csy,csx2,csy2,tab)==0)
      {
      swap2(csy,csx,csx2,csy2);
      destroy_2(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);
      }
    }
else if((d==0)&&(egalite2(csy,csx,csy2-1,csx2)==1)
&&(egalite2(csy,csx,csy2-2,csx2)==1))
   {ok=1;d=1;
   if(verf_1_3_2(csx,csy,csx2,csy2,tab)==0)
     {
     swap2(csy,csx,csx2,csy2);
     destroy_2(csx2,csy2,csx2,csy2-1,csx2,csy2-2,tab);
     }
   }
else if((d==0)&&(egalite2(csy,csx,csy2,csx2-1)==1)
&&(egalite2(csy,csx,csy2,csx2-2)==1))
  {ok=1;d=1;
        swap2(csy,csx,csx2,csy2);
        destroy_2(csx2,csy2,csx2-1,csy2,csx2-2,csy2,tab);
  }else if((d==0)&&(i==1)) {reswap2(csy,csx,csx2,csy2);}

}

//////////////////////2eme cas

if (csy2==csy&&csx2==csx+1)
{
if((d==0)&&(egalite_type_3_2(csx,csy,csx2,csy2,tab)==1)){d=1;ok=1;}
else
 if((d==0)&&(egalite2(csy,csx,csy2+1,csx2)==1)
&&(egalite2(csy,csx,csy2+2,csx2)==1))
   {ok=1;d=1;
               if(verf_1_4_2(csx,csy,csx2,csy2,tab)==0)
                { swap2(csy,csx,csx2,csy2);
                    destroy_2(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);
                }
                 }




 if((d==0)&&(egalite2(csy,csx,csy2-1,csx2)==1)
&&(egalite2(csy,csx,csy2-2,csx2)==1))
  {ok=1;d=1;
         if(verf_1_3_2(csx,csy,csx2,csy2,tab)==0)
           { swap2(csy,csx,csx2,csy2);
            destroy_2(csx2,csy2,csx2,csy2-1,csx2,csy2-2,tab);
           }
  }



else if((d==0)&&(egalite2(csy,csx,csy2,csx2+1)==1)
&&(egalite2(csy,csx,csy2,csx2+2)==1))
  {ok=1;d=1;
     swap2(csy,csx,csx2,csy2);
     destroy_2(csx2,csy2,csx2+1,csy2,csx2+2,csy2,tab);
  }
else if((d==0)&&(egalite2(csy,csx,csy2-1,csx2)==1)
&&(egalite2(csy,csx,csy2+1,csx2)==1))
  {ok=1;d=1;
   if(verf_1_1_2(csx,csy,csx2,csy2,tab)==0)
   {  swap2(csy,csx,csx2,csy2);
    destroy_2(csx2,csy2,csx2,csy2-1,csx2,csy2+1,tab);
   }

  }
else if((d==0)&&(egalite2(csy,csx,csy2+1,csx2)==1)
&&(egalite2(csy,csx,csy2+2,csx2)==1))
  {ok=1;d=1;
if(verf_1_4_2(csx,csy,csx2,csy2,tab)==0)
 {
    swap2(csy,csx,csx2,csy2);
    destroy_2(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);
  }
  }else if((d==0)&&(i==1)) {reswap2(csy,csx,csx2,csy2);}

}
////////////////////////3eme cas
 if (csy2==csy-1&&csx2==csx)
{if((d==0)&&(egalite_type_3_2(csx,csy,csx2,csy2,tab)==1)){d=1;ok=1;}
else

if((d==0)&&egalite2(csy,csx,csy2,csx2+1)==1
&&(egalite2(csy,csx,csy2,csx2-1)==1))
  {ok=1;d=1;
if(verf_1_6_2(csx,csy,csx2,csy2,tab)==0)
   {
    swap2(csy,csx,csx2,csy2);
    destroy_2(csx2,csy2,csx2+1,csy2,csx2-1,csy2,tab);
    }
  }
else if((d==0)&&(egalite2(csy,csx,csy2-1,csx2)==1)
&&(egalite2(csy,csx,csy2-2,csx2)==1))
  {ok=1;d=1;
       swap2(csy,csx,csx2,csy2);
      destroy_2(csx2,csy2,csx2,csy2-1,csx2,csy2-2,tab);
  }
else if((d==0)&&(egalite2(csy,csx,csy2,csx2+1)==1)
&&(egalite2(csy,csx,csy2,csx2+2)==1))
  {ok=1;d=1;
if(verf_1_5_2(csx,csy,csx2,csy2,tab)==0)
      {   swap2(csy,csx,csx2,csy2);
          destroy_2(csx2,csy2,csx2+1,csy2,csx2+2,csy2,tab);
      }
  }
else if((d==0)&&(egalite2(csy,csx,csy2,csx2-1)==1)
&&(egalite2(csy,csx,csy2,csx2-2)==1))
  {ok=1;d=1;
if(verf_1_2_2(csx,csy,csx2,csy2,tab)==0)
       {swap2(csy,csx,csx2,csy2);
        destroy_2(csx2,csy2,csx2-1,csy2,csx2-2,csy2,tab);
        }
  }
else if((d==0)&&(egalite2(csy,csx,csy2,csx2-1)==1)
&&(egalite2(csy,csx,csy2,csx2+1)==1))
  {ok=1;d=1;
        if(verf_1_6_2(csx,csy,csx2,csy2,tab)==0)
           {  swap2(csy,csx,csx2,csy2);
              destroy_2(csx2,csy2,csx2-1,csy2,csx2+1,csy2,tab);
           }
  }else if((d==0)&&(i==1)){reswap2(csy,csx,csx2,csy2); }


}
//////////////////////////// 4eme cas

 if ((csy2==(csy+1))&&(csx2==csx))
  {
  if((d==0)&&(egalite_type_3_2(csx,csy,csx2,csy2,tab)==1)){d=1;ok=1;}

else if((d==0)&&(egalite2(csy,csx,csy2,csx2+1)==1)
   &&(egalite2(csy,csx,csy2,csx2-1)==1))
    {ok=1;d=1;
          if(verf_1_6_2(csx,csy,csx2,csy2,tab)==0)
            {
            swap2(csy,csx,csx2,csy2);
            destroy_2(csx2,csy2,csx2+1,csy2,csx2-1,csy2,tab);
            }
    }
else if((d==0)&&(egalite2(csy,csx,csy2+1,csx2)==1)
&&(egalite2(csy,csx,csy2+2,csx2)==1))
  {ok=1;d=1;
      swap2(csy,csx,csx2,csy2);
      destroy_2(csx2,csy2,csx2,csy2+1,csx2,csy2+2,tab);

  }
else if((d==0)&&(egalite2(csy,csx,csy2,csx2+1)==1)
&&(egalite2(csy,csx,csy2,csx2+2)==1))
  {ok=1;d=1;
    if(verf_1_5_2(csx,csy,csx2,csy2,tab)==0)
    {
     swap2(csy,csx,csx2,csy2);
     destroy_2(csx2,csy2,csx2+1,csy2,csx2+2,csy2,tab);
    }
  }
else if((d==0)&&(egalite2(csy,csx,csy2,csx2-1)==1)
&&(egalite2(csy,csx,csy2,csx2-2)==1))
  {ok=1;d=1;
if(verf_1_2_2(csx,csy,csx2,csy2,tab)==0)
       {swap2(csy,csx,csx2,csy2);
        destroy_2(csx2,csy2,csx2-1,csy2,csx2-2,csy2,tab);
                                                       }
  }
else if((d==0)&&(egalite2(csy,csx,csy2,csx2-1)==1)
&&(egalite2(csy,csx,csy2,csx2+1)==1))
   {ok=1; d=1;
       if(verf_1_6_2(csx,csy,csx2,csy2,tab)==0)
         {swap2(csy,csx,csx2,csy2);
          destroy_2(csx2,csy2,csx2-1,csy2,csx2+1,csy2+1,tab);
                                                            }
     }else if((d==0)&&(i==1)) {reswap2(csy,csx,csx2,csy2);}

}

  if((d==0)&&(i==0)) verification_global_2(csx2,csy2,csx,csy,tab,1);



}

void aide2(nomimage tab[])
{
int i,j,b;
i=0;b=0;

while((i<10)&&(b==0))
{
j=0;
while((j<11)&&(b==0))
{
if((j<8)&&(i>0)&&(egalite2(i,j,i-1,j+1)==1)&&(egalite2(i,j,i-1,j+2)==1))
{verification_global_2(j,i,j,i-1,tab,0);b=1; test_2(tab);}

else if((j<8)&&(i<10)&&(egalite2(i,j,i+1,j+1)==1)&&(egalite2(i,j,i+1,j+2)==1))
{verification_global_2(j,i,j,i+1,tab,0);b=1;test_2(tab);}

else if((j<9)&&(i>0)&&(egalite2(i,j,i-1,j+1)==1)&&(egalite2(i,j,i-1,j-1)==1))
{verification_global_2(j,i,j,i-1,tab,0);b=1;test_2(tab);}

else if((j<9)&&(i<10)&&(egalite2(i,j,i+1,j+1)==1)&&(egalite2(i,j,i+1,j-1)==1))
{verification_global_2(j,i,j,i+1,tab,0);b=1;test_2(tab);}

else if((j>1)&&(i>0)&&(egalite2(i,j,i-1,j-1)==1)&&(egalite2(i,j,i-1,j-2)==1))
{verification_global_2(j,i,j,i-1,tab,0);b=1;test_2(tab);}

else if((j>1)&&(i<10)&&(egalite2(i,j,i+1,j-1)==1)&&(egalite2(i,j,i+1,j-2)==1))
{verification_global_2(j,i,j,i+1,tab,0);b=1;test_2(tab);}

else if((j>0)&&(j<9)&&(i>0)&&(egalite2(i,j,i-1,j-1)==1)&&(egalite2(i,j,i-1,j+1)==1))
{verification_global_2(j,i,j,i-1,tab,0);b=1;test_2(tab);}

else if((j>0)&&(j<9)&&(i<9)&&(egalite2(i,j,i+1,j-1)==1)&&(egalite2(i,j,i+1,j+1)==1))
{verification_global_2(j,i,j,i+1,tab,0);b=1;test_2(tab);}

else if((j>0)&&(i>1)&&(egalite2(i,j,i-1,j-1)==1)&&(egalite2(i,j,i-2,j-1)==1))
{verification_global_2(j,i,j-1,i,tab,0);b=1;test_2(tab);}

else if((j>0)&&(i<9)&&(egalite2(i,j,i+1,j-1)==1)&&(egalite2(i,j,i+2,j-1)==1))
{verification_global_2(j,i,j-1,i,tab,0);b=1;test_2(tab);}

else if((j>0)&&(i>0)&&(i<10)&&(egalite2(i,j,i-1,j-1)==1)&&(egalite2(i,j,i+1,j-1)==1))
{verification_global_2(j,i,j-1,i,tab,0);b=1;test_2(tab);}

else if((j<10)&&(i>0)&&(i<10)&&(egalite2(i,j,i-1,j+1)==1)&&(egalite2(i,j,i+1,j+1)==1))
{verification_global_2(j,i,j+1,i,tab,0);b=1;test_2(tab);}

else if((j<9)&&(i>1)&&(egalite2(i,j,i-1,j+1)==1)&&(egalite2(i,j,i-2,j+1)==1))
{verification_global_2(j,i,j+1,i,tab,0);b=1;test_2(tab);}

else if((j<9)&&(i<9)&&(egalite2(i,j,i+1,j+1)==1)&&(egalite2(i,j,i+2,j+1)==1))
{verification_global_2(j,i,j+1,i,tab,0);b=1;test_2(tab);}

if((j<7)&&(egalite2(i,j,i,j+2)==1)&&(egalite2(i,j,i,j+3)==1))
{verification_global_2(j,i,j+1,i,tab,0);b=1;test_2(tab);}

else if((j>2)&&(egalite2(i,j,i,j-2)==1)&&(egalite2(i,j,i,j-3)==1))
{verification_global_2(j,i,j-1,i,tab,0);b=1;test_2(tab);}

else if((i<8)&&(egalite2(i,j,i+2,j)==1)&&(egalite2(i,j,i+3,j)==1))
{verification_global_2(j,i,j,i+1,tab,0);b=1;test_2(tab);}

else if((i>2)&&(egalite2(i,j,i-2,j)==1)&&(egalite2(i,j,i-3,j)==1))
{verification_global_2(j,i,j,i-1,tab,0);b=1;test_2(tab);}
else j++;
}
if(b==0)
i++;
}
}










