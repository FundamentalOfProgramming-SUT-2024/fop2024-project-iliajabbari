#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FILE_NAME "usersdata.dat"
#define min(a,b) ((a<=b)? a:b)
#define max(a,b) ((a>=b)? a:b)
short int dirx[128]={0};
short int diry[128]={0};
dirx['U']=-1;dirx['Y']=-1;dirx['H']=0;dirx['J']=-1;dirx['K']=1;dirx['L']=0;dirx['B']=1;dirx['N']=1;
dirx['U']=-1;dirx['Y']=1;dirx['H']=-1;dirx['J']=0;dirx['K']=0;dirx['L']=1;dirx['B']=-1;dirx['N']=1;
typedef struct{
    int numtabaghe;
    int xplayer;
    int yplayer;
    char befplayer;
}Player;
Player* player;

void locate_player(){
    /////////////////////////////////
}


void taghir_naghshe(tabaghe* t,tabaghe* tnam,char c){
    char e=t->a[player->xplayer+dirx[c]][player->yplayer+diry[c]];

    if(e==)
}

void evaluate_move(tabaghe* t,char c){
    char q=t->a[player->xplayer+dirx[c]][player->yplayer+diry[c]];
    if(strchr("_ |O",q)!=NULL){
        return 0;
    }
    if(q==//enemy){
        return 0;
    }
    return 1;
}

void display_game(tabaghe* t,tabaghe* tnam,){
    clear();
    int height,width;
    getmaxyx(stdscr,height,width);
    char c;
    while(1){
         c=getch();
        if(strchr("YyUuHhJjKkLlBbNn",c)!=NULL){
            break;
        }
    }
    while(1){
        if(strchr("YyUuHhJjKkLlBbNn",c)!=NULL){
          if(c>96){
            c-=32;
          }
          if(evaluate_move(t,c)){
            if(player->befplayer==){player->befplayer='.';}
            t->a[player->xplayer][player->yplayer]=player->befplayer;
            player->befplayer=t->a[player->xplayer][player->yplayer];
            player->xplayer+=dirx[c];
            player->yplayer+=diry[c];
        }
        else{
          message();
        }
        }
        if(c=='f'){
          c=getch();
          if(strchr("YyUuHhJjKkLlBbNn",c)!=NULL){
            while(evaluate_move(t,c)){
              if(player->befplayer==){player->befplayer='.';}
              t->a[player->xplayer][player->yplayer]=player->befplayer;
              player->befplayer=t->a[player->xplayer][player->yplayer];
              player->xplayer+=dirx[c];
              player->yplayer+=diry[c];
            }
          }
        }
        else if(c=='g'){
          c=getch();
          if(strchr("YyUuHhJjKkLlBbNn",c)!=NULL){
          while(evaluate_move(t,c)){
            if(t->a[player->xplayer+=dirx[c]][player->yplayer+=diry[c]]==){
              t->a[player->xplayer][player->yplayer]=player->befplayer;
              player->befplayer=t->a[player->xplayer][player->yplayer];
              break;
            }
          }
        }
        }
        else if(c=='s'){
          int u=player->xplayer,b=player->yplayer;
          int f1=max(u-5,0),f2=min(u+5,width);
          int g1=max(b-5,0),g2=min(b+5,height);
          for(int i=f1;i<=f2;i++){
            if(t->a[i][b]=='+'){
                tnam->a[i][b]='+';
            }
          }
          for(int i=g1;i<=g2;i++){
            if(t->a[u][i]=='+'){
                tnam->a[u][i]='+';
            }
          }

        }
        else if(c=='>'){
          
        }
        else if(c=='<'){
          
        }
        c=getch();
    }
}

int main(){
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    cbreak();
    int sc_height, sc_width;
    getmaxyx(stdscr, sc_height, sc_width);
}