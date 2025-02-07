#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include "profilemenu.c"
#include "project.c"
#define FILE_NAME "usersdata.txt"
#define min(a,b) ((a<=b)? a:b)
#define max(a,b) ((a>=b)? a:b)
short int dirx[128]={0};
short int diry[128]={0};
char enem[5]="DFGSU";
char enemlives[10]="0510152030";



void initialize_arrs(){
   dirx['U']=-1;dirx['Y']=-1;dirx['H']=0;dirx['J']=-1;dirx['K']=1;dirx['L']=0;dirx['B']=1;dirx['N']=1;
diry['U']=-1;diry['Y']=1;diry['H']=-1;diry['J']=0;diry['K']=0;diry['L']=1;diry['B']=-1;diry['N']=1;
}

typedef struct{
    char username[50];
    int difficulty;
    int tajrobe1;
    int tajrobe2;
    Bazi* games;
}karbar;
Bazi wwwwwwwwwwww;
Bazi* bazi=&wwwwwwwwwwww;
karbar karbarr;
void init_karbar(){

karbarr.tajrobe1=0;
karbarr.tajrobe2=0;
karbarr.games=malloc(10*sizeof(Bazi));
}

void initialize_food(Player* player) {
    int food_elements = 10;
    
    for (int i = 0; i < 4; i++) {
        player->ghaza[i].tedad = 0;  
        player->ghaza[i].mande = malloc(food_elements * sizeof(int));
        if (!player->ghaza[i].mande) {
            fprintf(stderr, "Memory allocation failed for ghaza[%d].mande\n", i);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < food_elements; j++) {
            player->ghaza[i].mande[j] = -1;
        }
    }
}

int spell_activation;
void masiryab(int x1,int y1,int x2,int y2,int taraf,tabaghe* tt){
    srand(time(NULL));
    int o1=x2;
    int o2=y2;
    if(taraf){
        int r=1;
        int z=x1-x2;
        if(x1<x2){
            z=-z;
            r=-1;
        }
        else if(x1==x2){
            r=0;
        }
        int u=y1-y2-1;
        u--;
        o2++;
        tt->a[o1][o2]='#';
        while((0<u) && (z>0)){
            int f=rand()%2;
            if(f){
                z--;
                o1+=r;
                tt->a[o1][o2]='#';
            }
            else{
                u--;
                o2++;
                tt->a[o1][o2]='#';
            }
        }
        for(int i=0;i<z;i++){
            o1+=r;
            tt->a[o1][o2]='#';
        }
        for(int i=0;i<u;i++){
            o2++;
            tt->a[o1][o2]='#';
        }
    }
    else{
        int r=1;
        int z=y1-y2;
        if(y1<y2){
            z=-z;
            r=-1;
        }
        else if(y1==y2){
            r=0;
        }
        int u=x1-x2-1;
        u--;
        o1++;
        tt->a[o1][o2]='#';
        while((0<u) && (z>0)){
            int f=rand()%2;
            if(f){
                z--;
                o2+=r;
                if(tt->a[o1][o2]!=' '){
                    o2-=r;
                    z++;
                    continue;
                }
                tt->a[o1][o2]='#';
            }
            else{
                u--;
                o1++;
                if(tt->a[o1][o2]!=' '){
                    o1--;
                    u++;
                    continue;
                }
                tt->a[o1][o2]='#';
            }
        }
        for(int i=0;i<z;i++){
            o2+=r;
            if(tt->a[o1][o2]!=' '){
                    o2-=r;
                    i--;
                    continue;
                }
            tt->a[o1][o2]='#';
        }
        for(int i=0;i<u;i++){
            o1++;
            if(tt->a[o1][o2]!=' '){
                    o1--;
                    i++;
                    continue;
                }
            tt->a[o1][o2]='#';
        }
    }

}
void mplayer(Player* player){
   player->numtabaghe=1;
   player->level=1;
   player->gold=0;
   player->armor[0]=1;
   for(int i=1;i<5;i++){player->armor[i]=0;}
   player->hits=0;
   player->health=100;
   player->hunger=100;
   player->healing=1;
   player->ghodrat=0;player->soraat=0;for(int i=0;i<3;i++){player->spells[i]=0;}
   player->color=0;
   player->masterk=0;
   player->dour=-1;
   player->nazdik=0;
   player->selah_dardast=-1;
   initialize_food(player);
}

void initialize_tabaghe(tabaghe *t) {
   t->vojood_masterkey=0;
   
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            t->a[i][j] = ' ';
        }
    }
}

void make_floor(tabaghe *t) {
    srand(time(NULL));
    int ted_ot = rand() % 4 + 6;
    if(ted_ot==7){
        ted_ot=8;
    }
    t->tedad=ted_ot;
    t->otagh=malloc(ted_ot*sizeof(room));
    int sc_height, sc_width;
    getmaxyx(stdscr, sc_height, sc_width);

   
    for (int i = 0; i <= sc_width; i++) {
        t->a[i][0] = '_';
        t->a[i][sc_height - 1] = '_';
    }
    for (int i = 1; i < sc_height; i++) {
        t->a[0][i] = '|';
        t->a[sc_width - 1][i] = '|';
    }



    int y = sc_height / 3;
    int x = sc_width / 3;

    for (int o = 0; o < 9; o++) {
        if (ted_ot == o) break;

        int i = o / 3;
        int j = o % 3;

  
        int x1 = rand() % (x - 12) + 1 + (i * x)+1;
        int y1 = rand() % (y - 12) + 1 + (j * y)+1;
        int x2 = rand() % (x - (x1 - (i * x)) - 5) + 5;
        int y2 = rand() % (y - (y1 - (j * y)) - 5) + 5;
        t->otagh[o].x1=x1;
        t->otagh[o].y2=y2;
        t->otagh[o].x2=x2;
        t->otagh[o].y1=y1;
        t->otagh[o].enemies=malloc(50*sizeof(enemyy));
        t->otagh[o].type=rand()%20;
        if (x1 + x2 >= sc_width - 1) x2 = sc_width - x1 - 2;
        if (y1 + y2 >= sc_height - 1) y2 = sc_height - y1 - 2;
        int tedad=rand()%2 + 1;
   
        for (int p = 0; p <= x2; p++) {
            t->a[x1 + p][y1] = '_';
            t->a[x1 + p][y1 + y2] = '_';
        }
        for (int p = 1; p < y2; p++) {
            t->a[x1][y1 + p] = '|';
            t->a[x1 + x2][y1 + p] = '|';
        }
        t->a[x1][y1+y2] = '|';
        t->a[x1+x2][y1+y2] = '|';
        for (int p = 1; p < x2; p++) {
            for (int u = 1; u < y2; u++) {
                t->a[x1 + p][y1 + u] = '.';
            }
        }
        int ll=rand()%3;
        if(ll==0){
            int u[4][2]={{x1+1,y1+1},{x1+1,y1+y2-1},{x1+x2-1,y1+1},{x1+x2-1,y1+y2-1}};
            int r=rand()%4;
            t->a[u[r][0]][u[r][1]]='&';
            while(1){
                int q1=x1+2+rand()%(x2-4);
                int q2=y1+2+rand()%(y2-4);
                if(t->a[q1][q2]=='.'){
                    t->a[q1][q2]='@';
                    break;
                }
        }
        }
        ll=rand()%3+1;
        for(int i=0;i<ll;i++){
            int q1=x1+2+rand()%(x2-4);
            int q2=y1+2+rand()%(y2-4);
            if(t->a[q1][q2]=='.'){
                t->a[q1][q2]='O';
            }
            
        }
        int oo=rand()%8;
        int failn;
        if(oo>0){
         failn=0;
            while(1){
               if(failn>3){break;}
                int x=x1+2+rand()%(x2-4);
                int y=y1+2+rand()%(y2-4);
                if(t->a[x][y]=='.'){
                    t->a[x][y]='T';//trap
                    break;
                }
                else{failn++;}
            }
        }
        oo=rand()%5;
        if(oo>0){
            while(1){
               if(failn>15){break;}
                int x=x1+2+rand()%(x2-4);
                int y=y1+2+rand()%(y2-4);
                if(t->a[x][y]=='.'){
                    t->a[x][y]='R';//secret
                    break;
                }
                else{failn++;}
            }
        }
        if(t->vojood_masterkey==0){
            failn=0;
        while(1){
         if(failn>20){break;}
         int x=x1+2+rand()%(x2-4);
         int y=y1+2+rand()%(y2-4);
         if(t->a[x][y]=='.' && t->a[x+1][y]=='.'){
            t->a[x][y]=0x25B3;//bastani
            t->a[x+1][y]==0;
            t->vojood_masterkey=1;
            break;
         }
         else{
            failn++;
         }
         }
        }
         oo=rand()%4;
        if(oo>0){
            failn=0;
            while(1){
                if(failn>10){
                    break;
                }
                int x=x1+2+rand()%(x2-4);
                int y=y1+2+rand()%(y2-4);
                if(t->a[x][y]=='.' && t->a[x+1][y]=='.'){
                    int u=rand()%4 + 1;
                    if(u==0){t->a[x][y]=weapon[0];}//weapon
                    if(u==1){t->a[x][y]=weapon[1];}
                    if(u==2){t->a[x][y]=weapon[2];}
                    if(u==3){t->a[x][y]=weapon[3];}
                    if(u==4){t->a[x][y]=weapon[4];}
                    t->a[x+1][y]==0;
                    //t->a[x][y]=weapon[0];
                    
                    break;
                }
                else{
                    failn++;
                }
            }
            
        }
        oo=rand()%6;
        
        if(oo>0){
            
            failn=0;
            while(1){
                if(failn>15){
                    break;
                }
                int x=x1+2+rand()%(x2-4);
                int y=y1+2+rand()%(y2-4);
                if(t->a[x][y]=='.' && t->a[x+1][y]=='.'){
                    int u=rand()%3;
                    t->a[x][y]=spell[u];//spell
                    t->a[x+1][y]==0;
                    break;
                }
                else{
                    failn++;
                }
            }
            oo--;
        
        }
        oo=rand()%4;
        if(oo==3){
            failn=0;
            while(1){
                if(failn>15){
                    break;
                }
                int x=x1+2+rand()%(x2-4);
                int y=y1+2+rand()%(y2-4);
                if(t->a[x][y]=='.' && t->a[x+1][y]=='.'){
                    //food
                    int u=rand()%4;
                    if(u==1 || u==0){t->a[x][y]=0x1F34E;}
                    else if(u==2){t->a[x][y]=0x1F34A;}
                    else if(u==3){t->a[x][y]=0x1F349;}
                    t->a[x+1][y]==u;
                    break;
                }
                else{
                    failn++;
                }
            }
        }
        failn=0;
        while(1){
         if(failn>15){break;}
         int x=x1+2+rand()%(x2-4);
         int y=y1+2+rand()%(y2-4);
         if(t->a[x][y]=='.' && t->a[x+1][y]=='.'){
            t->a[x][y]=0x1F4B0;//gold
            t->a[x+1][y]==0;
            break;
         }
         else{
            failn++;
         }
        }
        for(int i=0;i<1;i++){
            room* ee=&t->otagh[o];
            failn=0;
            while(1){
                if(failn>15){ee->enemies[i].vojood=0;break;}
                int x=rand()%ee->x2;
                int y=rand()%ee->y2;
                if(t->a[ee->x1+x][ee->y1+y]=='.'){
                    ee->enemies[i].xplayer=ee->x1+x;ee->enemies[i].yplayer=ee->y1+y;
                    int t=rand()%5;
                    ee->enemies[i].esm=enem[t];
                    ee->enemies[i].lives=enemlives[t];
                    ee->enemies[i].vojood=1;
                    break;
                }
                else{failn++;}
            }
            
            
        }
        
         if(0<o && o<3){
        if (j != 0) {
    room *aa = t->otagh + o;
    room *bb = t->otagh + o - 1;

    int x_a = aa->x1 +1+ (rand() % (aa->x2-2));
    int y_a = aa->y1;
    int x_b = bb->x1 + 1+(rand() % (bb->x2-2));
    int y_b = bb->y1 + bb->y2;
    t->a[x_a][y_a] = '+';
    t->a[x_b][y_b] = '+';
    masiryab(x_a, y_a, x_b, y_b, 1, t);
}
         }
         

if (i != 0) {
    room *aa = t->otagh + o;
    room *bb = t->otagh + o - 3;

    int y_a = aa->y1 + (rand() % (aa->y2-2))+1;
    int x_a = aa->x1;
    int y_b = bb->y1 + (rand() % (bb->y2-2))+1;
    int x_b = bb->x1 + bb->x2;

    t->a[x_a][y_a] = '+';
    t->a[x_b][y_b] = '+';

   masiryab(x_a, y_a, x_b, y_b, 0, t);
}  
   }
   //initialize_player(t);
}

void namayesh_naghshe(Bazi* bazi){
    if(bazi->vaziatmaloum==0){
        bazi->vaziatmaloum=1;
    }
    else if(bazi->vaziatmaloum==1){
        bazi->vaziatmaloum=0;
    }
}
tabaghe* ff(Bazi* bazi,int h){if(h==1){return &bazi->t1;}
if(h==2){return &bazi->t2;}
if(h==3){return &bazi->t3;}
if(h==4){return &bazi->t4;}}

int evaluate_move(char c,tabaghe* t,Player player){
    int x=player.xplayer+dirx[c];
    int y=player.yplayer+diry[c];
    wchar_t b=t->a[x][y];
    if(b==' ' || b=='O' || b=='_' || b=='|' || b=='D' || b=='F' || b=='G' || b=='S' || b=='U') {
        return 0;
    }
    if(t->a[x-1][y]>127){
       t->a[x][y]='.';
       wchar_t h=t->a[x-1][y];
       t->a[x-1][y]='.';
       return h;

    }
    if(b>127){
        wchar_t h=t->a[x][y];
        t->a[x][y]='.';
        t->a[x-1][y]='.';
        return h;
    }
    return 1;
}


 void weapon_menu(Bazi* bazi);
  void partabe_tir(Bazi* bazi);
  void enem_move(tabaghe* t,Player* player);

int otaghenabard(Player* player){
    clear();int x,y;
    getmaxyx(stdscr,y,x);
    x/=3;y/=3;
    tabaghe* t;
    enemyy enemy;
    char a[500][500];
    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            a[i][j]='E';
        }
    }
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            a[i+x][j+y]='.';
        }
    }
    for(int i=0;i<x;i++){a[i+x][y]='_';a[i+x][2*y]='_';}
    for(int i=0;i<y;i++){a[x][i+y]='|';a[2*x][i+y]='|';}
    a[x][y]='_';a[2*x][y]='_';a[x][2*y]='|';a[2*x][2*y]='|';
    int o=rand()%5;
    enemy.esm=enem[o];enemy.xplayer=x+1;enemy.yplayer=y+1;enemy.vojood=1;enemy.lives=(enemlives[2*o]-48)*10+(enemlives[2*o+1]-48);
   player->xplayer=2*x-1;player->yplayer=2*y-1;
    while(1){
        if(enemy.vojood==0){
            return 1;
        }
        if(player->health<=0){return 0;}
        for(int i=0;i<x+1;i++){
            for(int j=0;j<y+1;j++){
                mvprintw(y+j,x+i,"%c",a[i+x][j+y]);
            }
        }
        
            mvprintw(enemy.yplayer,enemy.xplayer,"%c",enemy.esm);
        
        attron(COLOR_PAIR(player->color));
        mvprintw(player->yplayer,player->xplayer,"P");
        attroff(COLOR_PAIR(player->color));
        char c=getch();
        if(c=='q'){break;}//temp
        if(c=='Y' || c=='y' || c=='U' || c=='u' || c=='H' || c=='h' || c=='J' || c=='j' || c=='K' || c=='k' || c=='L' || c=='l' || c=='B' || c=='b' || c=='N' || c=='n'){
            initialize_arrs();
            if(c>96){c-=32;}
            if(!((player->xplayer+dirx[c]==enemy.xplayer && player->yplayer+diry[c]==enemy.yplayer) || (player->xplayer+dirx[c]==enemy.xplayer && player->yplayer+diry[c]==enemy.yplayer) || (player->xplayer+dirx[c]==enemy.xplayer && player->yplayer+diry[c]==enemy.yplayer) ||a[player->xplayer+dirx[c]][player->yplayer+diry[c]]=='|' || a[player->xplayer+dirx[c]][player->yplayer+diry[c]]=='_')){
                player->xplayer+=dirx[c];
                
                player->yplayer+=diry[c];
            }//
            int x1=player->xplayer,y1=player->yplayer;
            if(x1-1<=enemy.xplayer && x1+1>=enemy.xplayer){
        if(y1-1<=enemy.yplayer && y1+1>=enemy.yplayer){
            int i;
            for(i=0;i<5;i++){if(enem[i]==enemy.esm){break;}}
            player->health-=10;
        }
    }
    if(enemy.yplayer>y1){
        enemy.yplayer--;
        
    
        
    }
    else if(enemy.yplayer<y1){
     
       
        enemy.yplayer++;
        
      
        
    }
    else if(enemy.yplayer==y1){
    if(enemy.xplayer>x1){
    
        enemy.xplayer--;
        
        
        
    }
    else if(enemy.xplayer<x1){
        
        enemy.xplayer++;
        
        
        
    }
    }

        }
        else if(c=='I' || c=='i'){
            weapon_menu(bazi);
            continue;
        }
        else if(c=='W'){
            player->selah_dardast=-1;
        }
        else if(c==' '){
            partabe_tir(bazi);
            enem_move(t,player);
        }
        
    }
    
}

void food_menu(Bazi* bazi){
    clear();
    Player* player=&bazi->player;
    int x,y;
    getmaxyx(stdscr,y,x);
    x/=3;y/=3;
    curs_set(0);
    for(int i=0;i<=x;i++){
        mvprintw(y,i+x,"_");
        mvprintw(2*y,i+x,"_");
    }
    for(int j=0;j<=y;j++){
        mvprintw(j+y,x,"|");
        mvprintw(j+y,2*x,"|");
    }
    mvprintw(y,x,"_");mvprintw(y,2*x,"_");
    mvprintw(y+1,x+1,"FOOD");
    for(int i=0;i<x-11;i++){mvprintw(y+1,x+5+i,".");}
    mvprintw(y+1,2*x-6,"AMOUNT");
    mvprintw(y+2,x+1,"NORMAL FOOD");
    for(int i=0;i<x-14;i++){mvprintw(y+2,x+12+i,".");}
    mvprintw(y+2,2*x-2,"%d",player->ghaza[0].tedad+player->ghaza[3].tedad);
    mvprintw(y+3,x+1,"SUPER FOOD");
    for(int i=0;i<x-13;i++){mvprintw(y+3,x+11+i,".");}
    mvprintw(y+3,2*x-2,"%d",player->ghaza[1].tedad);
    mvprintw(y+4,x+1,"MAGICAL FOOD");
    for(int i=0;i<x-15;i++){mvprintw(y+4,x+13+i,".");}
    mvprintw(y+4,2*x-2,"%d",player->ghaza[2].tedad);
    mvprintw(y+9,x+x/2-5,"HUNGER LEVEL");
    
    for(int i=7;i<x-8;i++){mvprintw(y+10,x+i,"_");mvprintw(y+12,x+i,"_");}
    mvprintw(y+11,x+7,"|");mvprintw(y+12,x+7,"|");mvprintw(y+11,2*x-9,"|");mvprintw(y+12,2*x-9,"|");
    int a=player->hunger;
    a=(a*(x-16))/100;
    for(int i=0;i<a-1;i++){mvprintw(y+11,x+8+i,"#");}
    int s=0;char c;
    while(1){
        c=getch();
        if(c=='1'){
            int i=0;
            while(player->ghaza[0].mande[i]==-1){i++;}
            if(player->ghaza[0].mande[i]>120){
                player->health-=15;
                player->ghaza[0].mande[i]=-1;
            }
            else{
                player->hunger=min(100,player->hunger+15);
                player->ghaza[0].mande[i]=-1;
            }
            break;
        }
        else if(c=='2'){
            int i=0;
            while(player->ghaza[1].mande[i]==-1){i++;}
            if(player->ghaza[1].mande[i]>120){
                player->hunger=min(100,player->hunger+15);
                
                player->ghaza[1].mande[i]=-1;
            }
            else{
                player->hunger=min(100,player->hunger+15);
                player->soraat=1;
                player->ghaza[1].mande[i]=-1;
            }
            break;
        }
        else if(c=='3'){
            int i=0;
            while(player->ghaza[1].mande[i]==-1){i++;}
            if(player->ghaza[1].mande[i]>120){
                player->hunger=min(100,player->hunger+15);
                
                player->ghaza[1].mande[i]=-1;
            }
            else{
                player->hunger=min(100,player->hunger+15);
                player->ghodrat=1;
                player->ghaza[1].mande[i]=-1;
            }
            break;
        }
        else if(c=='Q' || c=='q'){break;}
    }
   /* while(1){
        if(s==20){break;}
    napms(500);
    s++;
    mvprintw(y+11,x+6+a," ");
    refresh();
    napms(500);
    mvprintw(y+11,x+6+a,"#");
    refresh();
    
    }*/
    
    
}


void weapon_menu(Bazi* bazi){
    clear();
    Player* player=&bazi->player;
    int x,y;
    getmaxyx(stdscr,y,x);
    x/=3;y/=3;
    curs_set(0);
    for(int i=0;i<=x;i++){
        mvprintw(y,i+x,"_");
        mvprintw(2*y,i+x,"_");
    }
    for(int j=0;j<=y;j++){
        mvprintw(j+y,x,"|");
        mvprintw(j+y,2*x,"|");
    }
    mvprintw(y,x,"_");mvprintw(y,2*x,"_");
    mvprintw(y+1,x+1,"WEAPON");
    for(int i=0;i<x-12;i++){mvprintw(y+1,x+7+i,".");}
    mvprintw(y+1,2*x-5,"COUNT");
    mvprintw(y+2,x+1,"MACE");
    for(int i=0;i<x-8;i++){mvprintw(y+2,x+5+i,".");}
    mvprintw(y+2,2*x-3,"inf");
    mvprintw(y+3,x+1,"DAGGER");
    for(int i=0;i<x-10;i++){mvprintw(y+3,x+7+i,".");}
    mvprintw(y+3,2*x-3,"%d",player->armor[1]);
    mvprintw(y+4,x+1,"MAGIC WAND");
    for(int i=0;i<x-14;i++){mvprintw(y+4,x+11+i,".");}
    mvprintw(y+4,2*x-3,"%d",player->armor[2]);
    mvprintw(y+5,x+1,"NORMAL ARROW");
    for(int i=0;i<x-16;i++){mvprintw(y+5,x+13+i,".");}
    mvprintw(y+5,2*x-3,"%d",player->armor[3]);
    mvprintw(y+6,x+1,"SWORD");
    for(int i=0;i<x-7;i++){mvprintw(y+6,x+6+i,".");}
    mvprintw(y+6,2*x-3,"%d",player->armor[4]);
    char ww[5][15]={"MACE","DAGGER","MAGIC WAND","NORMAL ARROW","SWORD"};
    if(player->selah_dardast>=0){
    mvprintw(y+8,x+x/2-8,"DEFAULT: %s",ww[player->selah_dardast]);}
    else{mvprintw(y+8,x+x/2-8,"DEFAULT: %s",ww[0]);}
    while(1){
        char c=getch();
        if(c=='1' || c=='5'){
            if(player->armor[c-49]==0){
                attron(COLOR_PAIR(1));mvprintw(0,0,"NO SUCH ARMOR EXISTS");attroff(COLOR_PAIR(1));
                napms(3000);
                break;
            }
            if(player->selah_dardast!=(-1)){
                attron(COLOR_PAIR(1));mvprintw(0,0,"FIRST PUT AWAY THE ARMOR IN YOUR HANDS");attroff(COLOR_PAIR(1));
                napms(3000);
                break;
            }
                player->selah_dardast=c-49;
                break;
            
        }
        else if(c=='2' || c=='3' || c=='4'){
            player->selah_dardast=c-49;
            break;
        }
        else if(c=='Q' || c=='q'){break;}
        else{attron(COLOR_PAIR(1));mvprintw(0,0,"INVALID COMMAND");attroff(COLOR_PAIR(1));}
        refresh();
        napms(3000);
        mvprintw(0,0,"               ");
        
    }
}


void spell_menu(Bazi* bazi){
    clear();
    Player* player=&bazi->player;
    int x,y;
    getmaxyx(stdscr,y,x);
    x/=3;y/=3;
    curs_set(0);
    for(int i=0;i<=x;i++){
        mvprintw(y,i+x,"_");
        mvprintw(2*y,i+x,"_");
    }
    for(int j=0;j<=y;j++){
        mvprintw(j+y,x,"|");
        mvprintw(j+y,2*x,"|");
    }
    mvprintw(y,x,"_");mvprintw(y,2*x,"_");
    mvprintw(y+1,x+1,"SPELL");
    for(int i=0;i<x-11;i++){mvprintw(y+1,x+6+i,".");}
    mvprintw(y+1,2*x-5,"COUNT");
    mvprintw(y+2,x+1,"HEALTH");
    for(int i=0;i<x-9;i++){mvprintw(y+2,x+7+i,".");}
    mvprintw(y+2,2*x-2,"%d",player->spells[1]);
    mvprintw(y+3,x+1,"SPEED");
    for(int i=0;i<x-8;i++){mvprintw(y+3,x+6+i,".");}
    mvprintw(y+3,2*x-2,"%d",player->spells[0]);
    mvprintw(y+4,x+1,"DAMAGE");
    for(int i=0;i<x-8;i++){mvprintw(y+4,x+6+i,".");}
    mvprintw(y+4,2*x-2,"%d",player->spells[2]);
    while(1){
        char c=getch();
        if(player->spells_activated[0] || player->spells_activated[1] || player->spells_activated[2]){
            attron(COLOR_PAIR(1));mvprintw(0,0,"YOU CAN'T ACTIVATE TWO SPELLS AT THE SAME TIME");attroff(COLOR_PAIR(1));
            napms(3000);
            break;
        }
        if(c=='1'){
            spell_activation=0;
            player->spells[1]--;
            player->healing++;

            break;
        }
        else if(c=='2'){
            spell_activation=0;
            player->spells[0]--;
            player->soraat=1;
            break;
        }
        else if(c=='3'){
            spell_activation=0;
            player->spells[2]--;
            player->ghodrat=1;
            break;
        }
        else if(c=='Q' || c=='q'){
            break;
        }

    }
}

int find_otagh(tabaghe* t,int x,int y){
    for(int i=0;i<t->tedad;i++){
        if(t->otagh[i].x1<=x && x<=t->otagh[i].x1+t->otagh[i].x2){
            if(t->otagh[i].y1<=y && y<=t->otagh[i].y1+t->otagh[i].y2){
                return i;
            }
        }
    }
    return -1;
}

int damages[5]={5,12,15,5,10};
void evaluate_armor_move(char c,room* otagh,int x,int y,int arnum,tabaghe* t){
    int q,w;
    initialize_arrs();
    getmaxyx(stdscr,q,w);
    while(1){
        display_map(t,q,w);
        if(t->a[x+dirx[c]][y+diry[c]]=='O' || t->a[x+dirx[c]][y+diry[c]]=='+' || t->a[x+dirx[c]][y+diry[c]]=='_' || t->a[x+dirx[c]][y+diry[c]]=='|'){
            attron(COLOR_PAIR(1));mvprintw(0,0,"MOVE NOT ALLOWED");attroff(COLOR_PAIR(1));
            t->a[x][y]='W';
            refresh();
            napms(3000);
            mvprintw(0,0,"________________");
            refresh();
            break;
        }
        else{
            x+=dirx[c];
            y+=diry[c];
            mvprintw(y,x,"%lc",weapon[arnum]);
            refresh();
            napms(100);
        }
        for(int i=0;i<3;i++){
            if(otagh->enemies[i].xplayer>=x-1 && otagh->enemies[i].xplayer<=x+1){
                if(otagh->enemies[i].yplayer>=y-1 && otagh->enemies[i].yplayer<=y+1){
                    otagh->enemies[i].lives-=damages[arnum];
                    if(otagh->enemies[i].lives<=0){otagh->enemies[i].vojood=0;}
                    break;
                }
            }
        }
    }
}
void partabe_tir(Bazi* bazi){
    Player* player=&bazi->player;
    tabaghe* t;
    if(player->numtabaghe==1){t=&bazi->t1;}
    if(player->numtabaghe==2){t=&bazi->t2;}
    if(player->numtabaghe==3){t=&bazi->t3;}
    if(player->numtabaghe==4){t=&bazi->t4;}
    int d=find_otagh(t,player->xplayer,player->yplayer);
    room* ott;
    if(player->selah_dardast==-1){
        attron(COLOR_PAIR(1));
        mvprintw(0,0,"CHOOSE ARMOR(PRESS \"E\" BUTTON)");attroff(COLOR_PAIR(1));
        refresh();
        napms(3000);
        mvprintw(0,0,"________________________________");
        refresh();
    }
    if(d>=0){
        ott=&t->otagh[d];

    if(player->selah_dardast==4){
        player->armor[player->selah_dardast]--;
        if(!player->armor[player->selah_dardast]){
            player->selah_dardast=-1;
        }
        for(int i=0;i<3;i++){
            int x=player->xplayer,y=player->yplayer;
            if(ott->enemies[i].xplayer>=x-1 && ott->enemies[i].xplayer<=x+1){
                if(ott->enemies[i].yplayer>=y-1 && ott->enemies[i].yplayer<=y+1){
                    ott->enemies[i].lives-=10;
                    if(ott->enemies[i].lives<=0){ott->enemies[i].vojood=0;}
                }
            }
        }
    }
    else if(player->selah_dardast==1 || player->selah_dardast==2 || player->selah_dardast==3){
        char c=getch();
        player->armor[player->selah_dardast]--;
        if(!player->armor[player->selah_dardast]){
            player->selah_dardast=-1;
        }
        if(c>96){c-=32;}
        if(c=='H' || c=='J' || c=='K' || c=='L' || c=='Y' || c=='U' || c=='B' || c=='N'){
        evaluate_armor_move(c,ott,player->xplayer,player->yplayer,player->selah_dardast,t);
        }
    }
    if(player->selah_dardast==0){
        for(int i=0;i<3;i++){
            int x=player->xplayer,y=player->yplayer;
            if(ott->enemies[i].xplayer>=x-1 && ott->enemies[i].xplayer<=x+1){
                if(ott->enemies[i].yplayer>=y-1 && ott->enemies[i].yplayer<=y+1){
                    ott->enemies[i].lives-=5;
                    if(ott->enemies[i].lives<=0){ott->enemies[i].vojood=0;}
                }
            }
        }
    }
    }
}

int move_eachenemy(int x1, int y1,enemyy* enemy,tabaghe* t){
    if(enemy->vojood==0){return 0;}
    if(x1-1<=enemy->xplayer && x1+1>=enemy->xplayer){
        if(y1-1<=enemy->yplayer && y1+1>=enemy->yplayer){
            return 1;
        }
    }
    if(enemy->yplayer>y1){
        char c=t->a[enemy->yplayer-1][enemy->xplayer];
        if(c!='_' && c!='O' && c!='|'){
        enemy->yplayer--;
        return 0;
        }
        
    }
    if(enemy->yplayer<y1){
        char c=t->a[enemy->yplayer+1][enemy->xplayer];
        if(c!='_' && c!='O' && c!='|'){
        enemy->yplayer++;
        return 0;
        }
        
    }
    if(enemy->xplayer>x1){
        char c=t->a[enemy->yplayer][enemy->xplayer-1];
        if(c!='_' && c!='O' && c!='|'){
        enemy->xplayer--;
        return 0;
        }
        
    }
    if(enemy->xplayer<x1){
        char c=t->a[enemy->yplayer][enemy->xplayer+1];
        if(c!='_' && c!='O' && c!='|'){
        enemy->xplayer++;
        return 0;
        }
        
    }
return 0;
}


void enem_move(tabaghe* t,Player* player){
    int u=find_otagh(t,player->xplayer,player->yplayer);
    if(u!=(-1)){
    room* e=&t->otagh[u];
    for(int i=0;i<3;i++){
        int k=move_eachenemy(player->xplayer,player->yplayer,&e->enemies[i],t);
        if(k){
            int j;
            for(j=0;j<5;j++){if(e->enemies[i].esm==enem[j]){break;}}
            player->health-=10;

        }
    }
    }
}

void make_naghse_shorou(tabaghe* t,tabaghe* tnam,int x,int y){
    int h=find_otagh(t,x,y);
    *tnam=*t;
    room* d=&t->otagh[h];
    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            tnam->a[i][j]=' ';
        }
    }
    for(int i=0;i<3;i++){
        tnam->otagh[h].enemies[i].vojood=0;
    }
    for(int i=0;i<=d->x2;i++){
        for(int j=0;j<=d->y2;j++){
            tnam->a[i+d->x1][j+d->y1]=t->a[i+d->x1][j+d->y1];
        }
    }
    
    
    int sc_height, sc_width;
    getmaxyx(stdscr, sc_height, sc_width);

   
    for (int i = 0; i <= sc_width; i++) {
        tnam->a[i][0] = '_';
        tnam->a[i][sc_height - 1] = '_';
    }
    for (int i = 1; i < sc_height; i++) {
        tnam->a[0][i] = '|';
        tnam->a[sc_width - 1][i] = '|';
    }

}
void lose_game();

int keym(Bazi* bazi){
    int x,y;
    getmaxyx(stdscr,y,x);
    Player* player=&bazi->player;
    int nt=player->numtabaghe;
    make_naghse_shorou(&bazi->t1,&bazi->maloum,player->xplayer,player->yplayer);
    time_t beginloop=time(NULL);
    time_t endloop=time(NULL);
    time_t duration;
    int bord=0;
    int soratt=1;
    while(1){
        if(endloop!=beginloop){
            double d=difftime(endloop,beginloop);
            mvprintw(0,0,"%lf",d);
            for(int i=0;i<4;i++){
                if(player->ghaza[i].tedad>0){
                player->ghaza[i].mande+=(int)d/player->ghaza[i].tedad;}
            }
            player->health=min(100,player->health+(d/0.1)*player->healing);
            spell_activation+=d;
            if(d>30){soratt=1;player->soraat=0;player->healing=1;}
            karbarr.tajrobe2+=d;
            beginloop=endloop;
        }
        tabaghe* t;
        if(player->numtabaghe==1){t=&bazi->t1;}
        if(player->numtabaghe==2){t=&bazi->t2;}
        if(player->numtabaghe==3){t=&bazi->t3;}
        if(player->numtabaghe==4){t=&bazi->t4;}
        if(bazi->vaziatmaloum==0){display_map(&bazi->maloum,y,x);}
        
        else if(bazi->vaziatmaloum==1){display_map(t,y,x);}
        init_pair(4,COLOR_RED,COLOR_BLACK);
        attron(COLOR_PAIR(4));
        getmaxyx(stdscr,y,x);
        mvprintw(y-1,x/2-18,"HEALTH: %d   Level: %d/4     Gold: %d",player->health,player->level,player->gold);
        refresh();
        attroff(COLOR_PAIR(4));
        char c=getch();
        if(c=='Q' || c=='q'){bord=2;break;}
        else if(c=='M'){namayesh_naghshe(bazi);continue;}
        else if(c=='Y' || c=='y' || c=='U' || c=='u' || c=='H' || c=='h' || c=='J' || c=='j' || c=='K' || c=='k' || c=='L' || c=='l' || c=='B' || c=='b' || c=='N' || c=='n'){
            initialize_arrs();
            if(c>96){c-=32;}
            for(int i=0;i<soratt;i++){
            int k=evaluate_move(c,t,*player);
            if(k){
                player->xplayer+=dirx[c];
                player->yplayer+=diry[c];
                if(k==weapon[1]){player->armor[1]++;}
                if(k==weapon[2]){player->armor[2]++;}
                if(k==weapon[3]){player->armor[3]++;}
                if(k==weapon[4]){player->armor[4]++;}
                if(k==spell[0]){player->spells[0]++;}
                if(k==spell[1]){player->spells[1]++;}
                if(k==spell[2]){player->spells[2]++;}
                if(k==0x25B3){player->masterk++;}
                if(k==0x1F34E){int u=rand()% 2;int y[2]={0,3}; player->ghaza[y[u]].tedad++;}
                if(k==0x1F34A){ player->ghaza[1].tedad++;}
                if(k==0x1F349){player->ghaza[2].tedad++;}
                if(k==0x1F4B0){player->gold++;}
            }
            if(t->a[player->xplayer][player->yplayer]=='+' || t->a[player->xplayer][player->yplayer]=='#'){
                for(int i=-1;i<2;i++){
                    for(int j=-1;j<2;j++){
                        if(t->a[player->xplayer+i][player->yplayer+j]=='#' || t->a[player->xplayer+i][player->yplayer+j]=='+'){
                        bazi->maloum.a[player->xplayer+i][player->yplayer+j]=t->a[player->xplayer+i][player->yplayer+j];}
                    }
                }
            }
            bazi->maloum.a[player->xplayer][player->yplayer]=t->a[player->xplayer][player->yplayer];
            if(t->a[player->xplayer][player->yplayer]=='+'){
                int u=find_otagh(t,player->xplayer,player->yplayer);
                if(u!=(-1)){
                    room q=t->otagh[u];
                    for(int i=0;i<=q.x2;i++){
                        for(int j=0;j<=q.y2;j++){
                            bazi->maloum.a[i+q.x1][j+q.y1]=t->a[i+q.x1][j+q.y1];
                        }
                    }
                }
            }
            
            
            }
            for(int i=0;i<which_user.difficulty;i++){
                enem_move(t,player);
            }
            

        }
        else if(c=='P'){
            if(soratt==2){soratt=1;}
            else if(soratt==1){if(player->soraat){soratt=2;}}
        }
        else if(c=='E' ){
            food_menu(bazi);
            continue;
        }
        else if(c=='I' || c=='i'){
            weapon_menu(bazi);
            continue;
        }
        else if(c=='V' || c=='v'){
            spell_menu(bazi);
            continue;
        }
        else if(c=='<'){
            if(t->a[player->xplayer][player->yplayer]=='<'){
                if(player->numtabaghe==4){bord=1;}
                player->numtabaghe++;
                player->level=max(player->numtabaghe+1,player->level);
                if(player->numtabaghe==2){
                make_naghse_shorou(&bazi->t2,&bazi->maloum,player->xplayer,player->yplayer);
                bazi->t2.a[player->xplayer][player->yplayer]='>';}
                if(player->numtabaghe==3){
                make_naghse_shorou(&bazi->t3,&bazi->maloum,player->xplayer,player->yplayer);
                bazi->t3.a[player->xplayer][player->yplayer]='>';}
                if(player->numtabaghe==4){
                make_naghse_shorou(&bazi->t4,&bazi->maloum,player->xplayer,player->yplayer);
                bazi->t4.a[player->xplayer][player->yplayer]='>';}
            }
            
        }
        else if(c=='>'){
            if(t->a[player->xplayer][player->yplayer]=='>'){
                player->numtabaghe--;
                if(player->numtabaghe==1){bazi->maloum=bazi->t1;}
                if(player->numtabaghe==2){bazi->maloum=bazi->t2;}
                if(player->numtabaghe==3){bazi->maloum=bazi->t3;}
            }
        }
        
        else if(c=='W'){
            player->selah_dardast=-1;
        }
        else if(c==' '){
            partabe_tir(bazi);
            enem_move(t,player);
        }
        else if(c=='a'){if(player->armor[3]>0){player->selah_dardast=3;} else{attron(COLOR_PAIR(1));mvprintw(0,0,"YOU DON'T HAVE SUCH AN ARMOR");refresh();attroff(COLOR_PAIR(1));napms(3000);mvprintw(0,0,"___________________________________");}}
        else if(c=='s'){if(player->armor[4]>0){player->selah_dardast=4;} else{attron(COLOR_PAIR(1));mvprintw(0,0,"YOU DON'T HAVE SUCH AN ARMOR");refresh();attroff(COLOR_PAIR(1));napms(3000);mvprintw(0,0,"___________________________________");}}
        else if(c=='d'){if(player->armor[1]>0){player->selah_dardast=1;} else{attron(COLOR_PAIR(1));mvprintw(0,0,"YOU DON'T HAVE SUCH AN ARMOR");refresh();attroff(COLOR_PAIR(1));napms(3000);mvprintw(0,0,"___________________________________");}}
        else if(c=='m'){if(player->armor[0]>0){player->selah_dardast=0;} else{attron(COLOR_PAIR(1));mvprintw(0,0,"YOU DON'T HAVE SUCH AN ARMOR");refresh();attroff(COLOR_PAIR(1));napms(3000);mvprintw(0,0,"___________________________________");}}
        else if(c=='w'){if(player->armor[2]>0){player->selah_dardast=2;} else{attron(COLOR_PAIR(1));mvprintw(0,0,"YOU DON'T HAVE SUCH AN ARMOR");refresh();attroff(COLOR_PAIR(1));napms(3000);mvprintw(0,0,"___________________________________");}}
        if(t->a[player->xplayer][player->yplayer]=='T'){
            t->a[player->xplayer][player->yplayer]='t';
            Player player2=*player;
            int s=otaghenabard(&player2);
            if(!s){return 0;}
        }
        if(t->a[player->xplayer][player->yplayer]=='@'){}//dareramzdar();}
        if(t->a[player->xplayer][player->yplayer]=='&'){}//ramzedardar();}
        if(t->a[player->xplayer][player->yplayer]=='R'){t->a[player->xplayer][player->yplayer]='?';}//daremakh();}
        //////
        int u=find_otagh(t,player->xplayer,player->yplayer);
        if(u!=(-1)){
            room* e=&t->otagh[u];
            for(int i=0;i<3;i++){
                if(e->enemies[i].lives<0){e->enemies[i].vojood=0;}
            }
        }
        if(player->health<=0){

            return 0;
        }
        
        endloop=time(NULL);
    }
    
    if(bord==0){
        lose_game();
        return 0;
    }
    if(bord==1){
        return 1;
    }
    if(bord==2){
        int i=0;
        while(which_user.games[i].t1.a[2][2]!=0){i++;}
        which_user.games[i]=*bazi;
        return 0;
    }
        
    clear();
}

void lose_game(){
    int x,y;
    getmaxyx(stdscr,y,x);
    mvprintw(y/2,x/2-5,"YOU LOST THE GAME");
    mvprintw(y/2+1,x/2-10,"PRESS ANY BUTTON TO END THE GAME");
}


int* doshman(char c,tabaghe* t){
   int* result=malloc(4*sizeof(int));
   int validot=1;
   room q;
   int i;
   while(1){
   validot=1;
    i=rand()%(t->tedad);
    q=t->otagh[i];
    for(int j=0;j<q.x2;j++){
      for(int k=0;k<q.y2;k++){
         if(t->a[q.x1+j][q.y1+k]=='P'){
            validot=0;
         }
      }
    }
    if(validot){
      break;
    }
   }
    
    int j=(i+t->tedad-1)%t->tedad;
    room w=t->otagh[j];
    int failn=0;
    while(1){
      int fl=0;
      for(int x=3;x<q.x2-1;x++){
         for(int y=3;y<q.y2-1;y++){
        if(t->a[q.x1+x][q.y1+y]=='.'){
            t->a[q.x1+x][q.y1+y]=c;
            result[0]=q.x1+x;
            result[1]=q.y1+y;
            fl=1;
            break;
        }
         }
         if(fl){break;}
      }
        if(fl){break;}
    }
   return result;
}


int* initialize_player(tabaghe* t){
   int* result=malloc(4*sizeof(int));
   int validot=1;
   room q;
   int i;
   while(1){
   validot=1;
    i=rand()%(t->tedad);
    q=t->otagh[i];
    for(int j=0;j<q.x2;j++){
      for(int k=0;k<q.y2;k++){
         if(t->a[q.x1+j][q.y1+k]==0x25B3){
            validot=0;
         }
      }
    }
    if(validot){
      break;
    }
   }
    
    int j=(i+t->tedad-1)%t->tedad;
    room w=t->otagh[j];
    int failn=0;
    while(1){
      int fl=0;
      for(int x=1;x<q.x2;x++){
         for(int y=1;y<q.y2;y++){
        if(t->a[q.x1+x][q.y1+y]=='.'){
            t->a[q.x1+x][q.y1+y]='P';
            result[0]=q.x1+x;
            result[1]=q.y1+y;
            fl=1;
            break;
        }
         }
         if(fl){break;}
      }
        if(fl){break;}
    }
    failn=0;
    while(1){
      int fl=0;
      for(int x=1;x<w.x2-1;x++){
         for(int y=1;y<w.y2-1;y++){
        if(t->a[w.x1+x][w.y1+y]=='.'){
            t->a[w.x1+x][w.y1+y]='<';
            result[2]=w.x1+x;
            result[3]=w.y1+y;
            fl=1;
            break;
        }
         }
         if(fl){break;}
      }
      if(fl){break;}
    }
   return result;
}


void make_bazi(Bazi* bazi){
   initialize_tabaghe(&bazi->t1);initialize_tabaghe(&bazi->t2);initialize_tabaghe(&bazi->t3);initialize_tabaghe(&bazi->t4);initialize_tabaghe(&bazi->maloum);
   make_floor(&bazi->t1);make_floor(&bazi->t2);make_floor(&bazi->t3);make_floor(&bazi->t4);
   
   bazi->vaziatmaloum=0;
   mplayer(&bazi->player);
   int* u=initialize_player(&bazi->t1);
   bazi->player.xplayer=u[0];
   bazi->player.yplayer=u[1];

}


void display_map(tabaghe *t, int sc_height, int sc_width) {
   clear();
   Player player=bazi->player;
   int x=player.xplayer;int y=player.yplayer;
    for (int j = 0; j < sc_height; j++) {
         for (int i = 0; i < sc_width; i++) {
            if(t->a[i][j]==0x25B3){
               init_pair(1, COLOR_YELLOW, COLOR_BLACK);
               attron(COLOR_PAIR(1));
               mvprintw(j, i,"%lc", t->a[i][j]);
               attroff(COLOR_PAIR(1));
            }
            
            else if(t->a[i][j]=='P' || t->a[i][j]=='t' || t->a[i][j]=='T' || t->a[i][j]=='R'){wchar_t e='.';mvprintw(j, i,"%lc", e);}
            else{mvprintw(j, i,"%lc", t->a[i][j]);}
            if(bazi->vaziatmaloum){if(t->a[i][j]=='T' || t->a[i][j]=='R'){mvprintw(j, i,"%lc", t->a[i][j]);}}
            if(t->a[i][j]>127){
               i++;
            }

        }
    }
    mvprintw(y,x,"P");
    int u=find_otagh(t,x,y);
    if(u!=(-1)){
        room g=t->otagh[u];
        for(int i=0;i<3;i++){
            if(g.enemies[i].vojood){
            mvprintw(g.enemies[i].yplayer,g.enemies[i].xplayer,"%c",g.enemies[i].esm);
            }
        }
    }
    refresh();
}


void game(){
    main_menu();
    if(login_status){
    make_bazi(bazi);
    int c=keym(bazi);
    if(c==1){
        which_user.gold=bazi->player.gold;
    }
    save_user_data(which_user);
    }
}
// Main function
int main() {
    init_karbar();
   srand(time(NULL));
    init_pair(1,COLOR_YELLOW,COLOR_BLACK);
   setlocale(LC_ALL, "");
    // Initialize ncurses
   initscr();
   noecho();
   keypad(stdscr, TRUE);
   cbreak();
   curs_set(0);
   start_color();
   which_user.games=malloc(sizeof(bazi)*10);
   which_user.tajrobe1=0;
   which_user.tajrobe2=0;
   which_user.difficulty=1;
   which_user.character='Y';
   game();
   int sc_height, sc_width;
   getmaxyx(stdscr, sc_height, sc_width);
  // display_map(&bazi->t1,sc_height,sc_width);

   //tabaghe k;
   //initialize_tabaghe(&k);
   //make_floor(&k);

   // Display the generated map
   //display_map(&k, sc_height, sc_width);

   getch(); // Wait for user input
   endwin(); // End ncurses mode
   return 0;
}
        