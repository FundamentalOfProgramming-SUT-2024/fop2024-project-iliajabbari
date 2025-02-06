#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

#define FILE_NAME "usersdata.dat"
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
    int x1;int x2;int y1;int y2;
    int type;//1-10 normal 11-14 enchant 15-18 nightmare 19-20 treasure
}room;
typedef struct{
    int tedad;
    int mande;
}food;
typedef struct{

}dareramz;

typedef struct{
    char esm;
    int lives;
    int xplayer;
    int yplayer;
    int soraat;
    int vojood;
}enemyy;
wchar_t weapon[5]={0x2692,0x1F5E1,0x1FA84,0x27B3,0x2694};
wchar_t spell[3]={0x1F5F2,0x1F9EA,0x1F4A3};
typedef struct{
    int numtabaghe;
    int xplayer;
    int yplayer;
    int level;
    int gold;
    int armor[5];
    food ghaza[4];
    int spells[3];
    int masterk;
    int hits;
    int health;
    int hunger;
    char spells_activated[3];
    int color;
}Player;
typedef struct {
    wchar_t a[300][300];
    int tedad;
    room* otagh;
    int vojood_masterkey;
   // int mal_kam;//maloum ya kamel
    int chand;//t1-t2-t3-t4
    enemyy* enemies;
   // unsigned char passdoor[9][];
} tabaghe;


void display_map(tabaghe *t, int sc_height, int sc_width);

int* initialize_player(tabaghe* t);
typedef struct {
    tabaghe t1;
    tabaghe t2;
    tabaghe t3;
    tabaghe t4;
    tabaghe maloum;
    int vaziatmaloum;
    Player player;
    
} Bazi;
Bazi wwwwwwwwwwww;
Bazi* bazi=&wwwwwwwwwwww;
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
   for(int i=0;i<5;i++){player->armor[i]=0;}
   player->hits=0;
   player->health=100;
   player->hunger=100;
}

void initialize_tabaghe(tabaghe *t) {
   t->vojood_masterkey=0;
   t->enemies=calloc(50,sizeof(Player));
    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 300; j++) {
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
                    t->a[x][y]=0x1F34E;//food
                    t->a[x+1][y]==0;
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
   initialize_player(t);
}

void namayesh_naghshe(Bazi* bazi){
    if(bazi->vaziatmaloum==0){
        bazi->vaziatmaloum=1;
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


void otaghenabard(Player* player){
    clear();int x,y;
    getmaxyx(stdscr,y,x);
    x/=3;y/=3;
    enemyy en[3];
    char a[300][300];
    for(int i=0;i<300;i++){
        for(int j=0;j<300;j++){
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
    en[0].esm=enem[o];en[0].xplayer=x+1;en[0].yplayer=y+1;en[0].vojood=1;en[0].soraat=1;en[0].lives=(enemlives[2*o]-48)*10+(enemlives[2*o+1]-48);
    o=rand()%5;
    en[1].esm=enem[o];en[1].xplayer=2*x-1;en[1].yplayer=y+1;en[1].vojood=1;en[1].soraat=1;en[1].lives=(enemlives[2*o]-48)*10+(enemlives[2*o+1]-48);
    o=rand()%5;
    en[2].esm=enem[o];en[2].xplayer=x+1;en[2].yplayer=2*y-1;en[2].vojood=1;en[2].soraat=1;en[2].lives=(enemlives[2*o]-48)*10+(enemlives[2*o+1]-48);
    player->xplayer=2*x-1;player->yplayer=2*y-1;
    while(1){
        for(int i=0;i<x+1;i++){
            for(int j=0;j<y+1;j++){
                mvprintw(y+j,x+i,"%c",a[i+x][j+y]);
            }
        }
        for(int i=0;i<3;i++){
            mvprintw(en[i].yplayer,en[i].xplayer,"%c",en[i].esm);
        }
        attron(COLOR_PAIR(player->color));
        mvprintw(player->yplayer,player->xplayer,"P");
        attroff(COLOR_PAIR(player->color));
        char c=getch();
        if(c=='q'){break;}//temp
        if(c=='Y' || c=='y' || c=='U' || c=='u' || c=='H' || c=='h' || c=='J' || c=='j' || c=='K' || c=='k' || c=='L' || c=='l' || c=='B' || c=='b' || c=='N' || c=='n'){
            initialize_arrs();
            if(c>96){c-=32;}
            if(!((player->xplayer+dirx[c]==en[0].xplayer && player->yplayer+diry[c]==en[0].yplayer) || (player->xplayer+dirx[c]==en[1].xplayer && player->yplayer+diry[c]==en[1].yplayer) || (player->xplayer+dirx[c]==en[2].xplayer && player->yplayer+diry[c]==en[2].yplayer) ||a[player->xplayer+dirx[c]][player->yplayer+diry[c]]=='|' || a[player->xplayer+dirx[c]][player->yplayer+diry[c]]=='_')){
                player->xplayer+=dirx[c];
                
                player->yplayer+=diry[c];
            }
            

        }
    }
    
}

void food_menu(Bazi* bazi){
    clear();
    Player* player=&bazi->player;
    int x,y;
    getmaxyx(stdscr,y,x);
    x/=3;y/=3;
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
            int o=rand()%2;
            if(o){
                if(player->ghaza[0].tedad==0){o=0;}
                else{
                    player->ghaza[0].tedad-=1;
                    
                }
            }
            break;
        }
        else if(c=='2'){

            break;
        }
        else if(c=='3'){

            break;
        }
    }
   /* while(1){
        if(s==20){break;}
    napms(300);
    s++;
    mvprintw(y+11,x+6+a," ");
    refresh();
    napms(300);
    mvprintw(y+11,x+6+a,"#");
    refresh();
    
    }*/
    
    getch();
}


void keym(Bazi* bazi){
    int x,y;
    getmaxyx(stdscr,y,x);
    Player* player=&bazi->player;
    int nt=player->numtabaghe;
    while(1){
        tabaghe* t=&bazi->t1;//should be fixed
        if(bazi->vaziatmaloum==0){display_map(t,y,x);}
        else if(bazi->vaziatmaloum==1){display_map(t,y,x);}
        char c=getch();
        if(c=='Q' || c=='q'){break;}
        else if(c=='M' || c=='m'){namayesh_naghshe(bazi);continue;}
        else if(c=='Y' || c=='y' || c=='U' || c=='u' || c=='H' || c=='h' || c=='J' || c=='j' || c=='K' || c=='k' || c=='L' || c=='l' || c=='B' || c=='b' || c=='N' || c=='n'){
            initialize_arrs();
            if(c>96){c-=32;}
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
                if(k==0x1F34E){int u=rand()% 4; player->ghaza[u].tedad++;}
                if(k==0x1F4B0){player->gold++;}
            }

        }
        else if(c=='E' || c=='e'){
            food_menu(bazi);
            continue;
        }
        else if(c=='I' || c=='i'){
            //weapon_manu(bazi);
            continue;
        }
        else if(c=='V' || c=='v'){
            //spell_menu(bazi);
            continue;
        }
        else if(c=='<'){
            if(t->a[player->xplayer][player->yplayer]=='<'){

            }
        }
        else if(c=='>'){
            if(t->a[player->xplayer][player->yplayer]=='<'){

            }
        }
        if(t->a[player->xplayer][player->yplayer]=='T'){
            t->a[player->xplayer][player->yplayer]='t';
            Player player2=*player;
            otaghenabard(&player2);
        }
        if(t->a[player->xplayer][player->yplayer]=='@'){}//dareramzdar();}
        if(t->a[player->xplayer][player->yplayer]=='&'){}//ramzedardar();}
        if(t->a[player->xplayer][player->yplayer]=='R'){t->a[player->xplayer][player->yplayer]='?';}//daremakh();}

        
    }
        
    clear();
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
            else if(t->a[i][j]=='P' || t->a[i][j]=='t'){wchar_t e='.';mvprintw(j, i,"%lc", e);}
            else{mvprintw(j, i,"%lc", t->a[i][j]);}
            if(t->a[i][j]>127){
               i++;
            }
        }
    }
    mvprintw(y,x,"P");
    refresh();
}

// Main function
int main() {
   srand(time(NULL));
    
   setlocale(LC_ALL, "");
    // Initialize ncurses
   initscr();
   noecho();
   keypad(stdscr, TRUE);
   cbreak();
   curs_set(0);
   start_color();
   make_bazi(bazi);
   keym(bazi);
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
        