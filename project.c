#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "profilemenu.c"
#define FILE_NAME "usersdata.dat"
void main_menu();
int main(){
    initscr();             
    noecho();              
    keypad(stdscr, TRUE);  
    cbreak(); 
    main_menu();
    endwin();
    return 0;
}

void upload(){
    clear();
    curs_set(0);
    echo();
    draw_rectangle(30,15);
    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);
    int start_x = (screen_width - 30) / 2 + 2;
    int start_y = (screen_height - 15) / 2 + 2;
    attron(A_BOLD);
    mvprintw(start_y,start_x+11,"ROGUE");
    refresh();
    napms(200);
    mvprintw(start_y+8,start_x-1,"............................");
    mvprintw(start_y+10,start_x+11,"0%c",'%');
    refresh();
    napms(1000);
    mvprintw(start_y+8,start_x-1,"#####");
    mvprintw(start_y+10,start_x+11,"17%c",'%');
    refresh();
    napms(2000);
    mvprintw(start_y+8,start_x-1,"##############");
    mvprintw(start_y+10,start_x+11,"50%c",'%');
    refresh();
    napms(3000);
    mvprintw(start_y+8,start_x-1,"#########################");
    mvprintw(start_y+10,start_x+11,"92%c",'%');
    refresh();
    napms(500);
    mvprintw(start_y+8,start_x-1,"############################");
    mvprintw(start_y+10,start_x+11,"100%c",'%');
    refresh();
    napms(300);
    attroff(A_BOLD);
}




void main_menu(){
    upload();
mainmengoto:
    int choice=-1;
    int highlight=0;
    while(1){
        clear();
        curs_set(0);
        draw_rectangle(50,30);
        int screen_height, screen_width;
        getmaxyx(stdscr, screen_height, screen_width);
        int start_x = (screen_width - 50) / 2 + 2;
        int start_y = (screen_height - 30) / 2 + 2;
        char choices[4][50]={"                1.start the game","                  2.scoreboard","                   3.settings","               4.exit the program"};
            init_pair(1,COLOR_RED,COLOR_BLACK);
            attron(COLOR_PAIR(1)); 
            attron(A_BOLD);
            mvprintw(start_y,start_x+14,"WELCOME TO THE ROGUE");
            attroff(COLOR_PAIR(1)); 
            attroff(A_BOLD);
        for(int i=0;i<4;i++){
                mvprintw(start_y+3+i,start_x,"%s",choices[i]);
        }
        refresh();
        noecho();
        char ch=getch();
        switch(ch){
            case '1':
                choice=0;
                break;
            case '2':
                choice=1;
                break;
            case '3':
                choice=2;
                break;
            case '4':
                choice=3;

        }
        if(choice>=0){
            break;
        }
    }
    switch(choice){
        case 0:
            profile_menu();
            break;
        case 1:
            
            break;
        case 2:
            if(!login_status){
                clear();
                mvprintw(1,1,"First you have to login from profile menu");
                mvprintw(2,1,"press any button to continue");

                refresh();
                getch();
                break;
            }
            settings_menu();
            break;
        case 3:
            
            while(1){
                clear();
            mvprintw(1,1,"Are you sure you want to exit?");
            mvprintw(2,1,"Y\\N");
                noecho();
                char cha=getch();
                mvprintw(1,1,"                              ");
                mvprintw(2,1,"     ");
                if(cha=='Y' || cha=='y'){
                    return;
                }
                else if(cha=='N' || cha=='n'){
                    break;
                }
            }
            break;
    }
    goto mainmengoto;
}

































void set_difficulty(){
    clear();
    curs_set(0);
    draw_rectangle(60,30);
    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);
    int start_x = (screen_width - 60) / 2 + 2;
    int start_y = (screen_height - 30) / 2 + 2;
    mvprintw(start_y+2,start_x,"set difficulty of the game");
    mvprintw(start_y+3,start_x,"(if you're looking for \"easy\",then we have no such thing here)");
    mvprintw(start_y+4,start_x,"1.normal");
    mvprintw(start_y+5,start_x,"2.hard");
    while(1){
        char ch=getch();
        if(ch=='1' || ch=='2'){
            int u[2]={1,2};
            which_user.difficulty=u[ch-'0'];
            break;
        }
    }
    FILE *file = fopen(FILE_NAME, "rb+");
        if (!file) {
            mvprintw(start_y + 10, start_x, "Error: Unable to open file.");
            refresh();
            getch();
            return;
        }
    User temp_user;User* userr=&which_user;
    while (fread(&temp_user, sizeof(User), 1, file)) {
            if (strcmp(temp_user.username, userr->username) == 0) {
                fseek(file, -sizeof(User), SEEK_CUR);
                fwrite(userr, sizeof(User), 1, file);
                break;
            }
        }
        fclose(file);
    return;
}


void change_hero_menu(){
    clear();
    curs_set(0);
    draw_rectangle(50,30);
    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);
    int start_x = (screen_width - 50) / 2 + 2;
    int start_y = (screen_height - 30) / 2 + 2;
    mvprintw(start_y+3,start_x,"choose the color of your hero");
    mvprintw(start_y+4,start_x,"1.yellow");
    mvprintw(start_y+5,start_x,"2.green");
    mvprintw(start_y+6,start_x,"3.blue");
while(1){
    char ch=getch();
    if(ch>'0' && ch<'4'){
        char characters[3]="YGB";
        which_user.character=characters[ch-'0'];
        break;
    }
}
    FILE *file = fopen(FILE_NAME, "rb+");
        if (!file) {
            mvprintw(start_y + 10, start_x, "Error: Unable to open file.");
            refresh();
            getch();
            return;
        }
    User temp_user;User* userr=&which_user;
    while (fread(&temp_user, sizeof(User), 1, file)) {
            if (strcmp(temp_user.username, userr->username) == 0) {
                fseek(file, -sizeof(User), SEEK_CUR);
                fwrite(userr, sizeof(User), 1, file);
                break;
            }
        }
        fclose(file);
    return;
}



void settings_menu(){
    settingmengoto:
    clear();
    curs_set(0);
    draw_rectangle(50,30);
    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);
    int start_x = (screen_width - 50) / 2 + 2;
    int start_y = (screen_height - 30) / 2 + 2;
    char u[4][30]={"1.change the hero","2.choose the difficulty","3.music","4.back"};
    for(int i=0;i<4;i++){
        mvprintw(start_y+i+2,start_x,"%s",u[i]);
    } 
    noecho();
    char ch=getch();
    switch(ch){
        case '1':
            change_hero_menu();
            break;
        case '2':
            set_difficulty();
            break;
        case '3':
            //music_menu();
            break;
        case '4':
            return;

    }
    goto settingmengoto;
    return;
}

