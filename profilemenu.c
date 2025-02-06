#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE_NAME "usersdata.dat"
typedef struct{
    long int point;
    long int gold;
    char username[50];
    char pass[50];
    char email[50];
}User;

void save_user_data();
void sign_up();
int is_username_taken();
void draw_rectangle(int width, int height);
void random_pass();
int profile_menu();
int main(){
    initscr();             
    noecho();              
    keypad(stdscr, TRUE);  
    cbreak(); 
    profile_menu();
    endwin();
    return 0;
}
void save_user_data(User user) {
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file) {
        mvprintw(1, 1, "Error: Unable to open file for writing.");
        fclose(file);
        refresh();
        return;
    } User temp_user;User* userr=&user;
    while (fread(&temp_user, sizeof(User), 1, file)) {
            if (strcmp(temp_user.username, userr->username) == 0) {
                fseek(file, -sizeof(User), SEEK_CUR);
                fwrite(userr, sizeof(User), 1, file);
                break;
            }
        }
        fclose(file);
}

int is_username_taken(const char *username) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        return 0; // Assume no users if file doesn't exist
    }
    User temp;
    while (fread(&temp, sizeof(User), 1, file)) {
        if (strcmp(temp.username, username) == 0) {
            fclose(file);
            return 1; // Username exists
        }
    }
    fclose(file);
    return 0; // Username not found
}

int is_info_correct(User a){
     FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        return 0; // Assume no users if file doesn't exist
    }
    User temp;
    while (fread(&temp, sizeof(User), 1, file)) {
        if (strcmp(temp.username, a.username) == 0) {
            if(strcmp(temp.pass,a.pass)==0){
                fclose(file);
                return 1;
            }
            fclose(file);
            return 2; 
        }
    }
    fclose(file);
    return 0;
}

User* is_info_correct1(User a) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        return NULL; // در صورت عدم وجود فایل
    }

    User *matched_user = (User *)malloc(sizeof(User)); // تخصیص حافظه برای کاربر موردنظر
    User temp;

    while (fread(&temp, sizeof(User), 1, file)) {
        if (strcmp(temp.username, a.username) == 0 && strcmp(temp.email, a.email) == 0) {
            *matched_user = temp; // کپی اطلاعات کاربر
            fclose(file);
            return matched_user;
        }
    }
    fclose(file);
    free(matched_user); // آزادسازی حافظه در صورت عدم تطابق
    return NULL;
}


void sign_up() {
    clear();
    User user;
    draw_rectangle(50, 30);
    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);
    int start_x = (screen_width - 50) / 2 + 2;
    int start_y = (screen_height - 30) / 2 + 2;

    while (1) {
        mvprintw(start_y, start_x, "Enter Username: ");
        curs_set(1);
        refresh();
        echo();
        mvgetstr(start_y + 1, start_x, user.username); // Get username
        noecho();

        if (is_username_taken(user.username)) {
            curs_set(0);
            mvprintw(start_y + 2, start_x, "Username already taken! Try again.");
            mvprintw(start_y+1,start_x,"                                     ");
            refresh();
        } else {
            break;
        }
    }
    int highlight = 0;
    int cha;
while (1) {
    curs_set(0);
    echo();
        if (highlight == 0) {
            attron(A_REVERSE);
            mvprintw(start_y + 3, start_x, "Random Password");
            attroff(A_REVERSE);
            mvprintw(start_y + 3, start_x + 20, "Enter Password");
        } else {
            mvprintw(start_y + 3, start_x, "Random Password");
            attron(A_REVERSE);
            mvprintw(start_y + 3, start_x + 20, "Enter Password");
            attroff(A_REVERSE);
        }
        curs_set(0);
        refresh();
        noecho();
        cha = getch();
        mvprintw(start_y+3,start_x,"                                               ");
        if(cha==KEY_LEFT){
            highlight=(highlight==0)? 1 : 0;

        }
        else if(cha==KEY_RIGHT){
            highlight=(highlight==0)? 1 : 0;
        }
        else if(cha=='\n'){
            break;
        }
    }
if(highlight){
  getpass:
    mvprintw(start_y + 4, start_x, "Enter Password: ");
    
    refresh();
    echo();
    mvgetstr(start_y+5,start_x,user.pass);
    int upper=0,lower=0,num=0,len=strlen(user.pass);
    for(int i=0;i<len;i++){
        if(user.pass[i]>='A' && user.pass[i]<='Z'){
            upper++;
        }
        else if(user.pass[i]>='a' && user.pass[i]<='z'){
            lower++;
        }
        else if(user.pass[i]>='0' && user.pass[i]<='9'){
            num++;
        }
    }
    if(!(num && lower && upper && (len>=7))){
         mvprintw(start_y + 6, start_x, "Invalid password");
    mvprintw(start_y+7,start_x,"(it mustcontain uppercase lowercase and number)");
    mvprintw(start_y+5,start_x,"                                               ");
     goto getpass;
    }
}
else{
    int len;
    getpass1:
    len =rand()%20 + 7;
    random_pass(user.pass,len);
     int upper=0,lower=0,num=0,leng=strlen(user.pass);
    for(int i=0;i<leng;i++){
        if(user.pass[i]>='A' && user.pass[i]<='Z'){
            upper++;
        }
        else if(user.pass[i]>='a' && user.pass[i]<='z'){
            lower++;
        }
        else if(user.pass[i]>='0' && user.pass[i]<='9'){
            num++;
        }
    }
    if(!(num && lower && upper && (leng>=7))){
     goto getpass1;
    }
    mvprintw(start_y+5,start_x,"Your password is:");
    mvprintw(start_y+6,start_x,"%s",user.pass);
    getch();
    }
   
getemail:
echo();
mvprintw(start_y+6,start_x,"                               ");
    mvprintw(start_y+7,start_x,"Enter Email:                                   ");
    curs_set(1);
    refresh();
    mvgetstr(start_y + 8, start_x, user.email);
    int yyyyy=0,zzzzzzz=0,fffffff=1;
    for(int i=0;i<50;i++){
        if(user.email[i]==0){
            break;
        }
        if(user.email[i]=='.'){
            if(yyyyy){
                fffffff=0;
                break;
            }
            else{
                yyyyy=i;
            }
        }
        if(user.email[i]=='@'){
            if(zzzzzzz){
                fffffff=0;
                break;
            }
            else{
                zzzzzzz=i;
            }
        }
    }
    if(fffffff){
        if(yyyyy>zzzzzzz+1){

        }
         else{
        mvprintw(start_y + 9, start_x, "Invlaid Email(must be of the form xx@yy.zz) ");
        mvprintw(start_y+8,start_x,"                                           ");
        goto getemail;
    }
    }
    else{
        mvprintw(start_y + 9, start_x, "Invlaid Email(must be of the form xx@yy.zz) ");
        mvprintw(start_y+8,start_x,"                                           ");
        goto getemail;
    }
    // Initialize user data
    user.point = 0;
    user.gold = 0;

    save_user_data(user);
    mvprintw(start_y + 9, start_x, "User registered successfully!               ");
    refresh();
    getch();
    return;
}

void forgetpass() {
    

    while (1) {
        clear();
    int attempt = 0;
        echo();
         User temp;
        draw_rectangle(50, 30);
        int screen_height, screen_width;
        getmaxyx(stdscr, screen_height, screen_width);
        int start_x = (screen_width - 50) / 2 + 2;
        int start_y = (screen_height - 30) / 2 + 2;

        if (attempt > 0) {
            mvprintw(start_y+1, start_x, "Invalid username or email. Try again.");
        }
        mvprintw(start_y + 2, start_x, "Enter Username:");
        mvgetstr(start_y + 3, start_x, temp.username);
        mvprintw(start_y + 4, start_x, "Enter Email:");
        mvgetstr(start_y + 5, start_x, temp.email);
        User *matched_user = is_info_correct1(temp);
        if (matched_user==NULL) {
            attempt++;
            continue; 
        }
        char new_password[50];
    set_new_password:
        mvprintw(start_y + 7, start_x, "Enter New Password:");
        echo();
        mvgetstr(start_y + 8, start_x, new_password);
        int upper = 0, lower = 0, digit = 0, len = strlen(new_password);
        for (int i = 0; i < len; i++) {
            if (new_password[i] >= 'A' && new_password[i] <= 'Z') upper++;
            else if (new_password[i] >= 'a' && new_password[i] <= 'z') lower++;
            else if (new_password[i] >= '0' && new_password[i] <= '9') digit++;
        }

        if (!(upper && lower && digit && len >= 7)) {
            mvprintw(start_y + 9, start_x, "Invalid password! Must include uppercase, lowercase, and a number.");
            refresh();
            getch();
            mvprintw(start_y + 8, start_x, "                                            ");
            goto set_new_password;
        }
        strcpy(matched_user->pass, new_password);
        FILE *file = fopen(FILE_NAME, "rb+");
        if (!file) {
            mvprintw(start_y + 10, start_x, "Error: Unable to open file.");
            refresh();
            getch();
            break;
        }

        User temp_user;
        while (fread(&temp_user, sizeof(User), 1, file)) {
            if (strcmp(temp_user.username, matched_user->username) == 0) {
                fseek(file, -sizeof(User), SEEK_CUR);
                fwrite(matched_user, sizeof(User), 1, file);
                break;
            }
        }
        fclose(file);
        free(matched_user);

        mvprintw(start_y + 10, start_x, "Password updated successfully!");
        refresh();
        getch();
        break; // خروج از حلقه
    }
}


int login_status;
User which_user;
void sign_in() {
    while (1) {
        clear();
        echo();
        curs_set(1);
        draw_rectangle(60, 20);
        int screen_height, screen_width;
        getmaxyx(stdscr, screen_height, screen_width);
        int start_x = (screen_width - 60) / 2 + 2;
        int start_y = (screen_height - 20) / 2 + 2;
        echo();
        User temp;
        mvprintw(start_y, start_x, "Enter Username: ");
        mvgetstr(start_y + 1, start_x, temp.username);

        mvprintw(start_y + 3, start_x, "Enter Password: ");
        mvgetstr(start_y+4,start_x,temp.pass);

        // Navigation for Submit and Forget Password
        int pointer = 0; // 0: Submit, 1: Forget Password
        char cha;int highlight=0;
        
       while (1) {
    curs_set(0);
    noecho();
        
            
            mvprintw(start_y + 7, start_x, "1.SUBMIT");
            
            mvprintw(start_y + 8, start_x , "2.forget password?");
            mvprintw(start_y+9,start_x,"3.Back to profile menu");
        
        curs_set(0);
        refresh();
        noecho();
        cha = getch();
        if(cha=='1'){
            pointer=0;
            break;
        }
        else if(cha=='2'){
            pointer=1;
            break;
        }
        else if(cha=='3'){
            pointer=2;
            break;
        }
    }

        if (pointer == 0) { // Submit selected
            int u = is_info_correct(temp);
            if (u == 0) {
                mvprintw(start_y + 10, start_x, "User with such a username doesn't exist");
                refresh();
                getch();
                continue; // Restart the login process
            } else if (u == 2) {
                mvprintw(start_y + 10, start_x, "Wrong Password!");
                refresh();
                getch();
                continue; // Restart the login process
            } else if (u == 1) {
                mvprintw(start_y + 10, start_x, "Login successful! Welcome, %s.", temp.username);
                refresh();
                which_user=temp;
                login_status=1;
                getch();
                break; // Exit the function after successful login
            }
        } else if (pointer == 1) { // Forget Password selected
            forgetpass();
            refresh();
            getch();
        }
        else if(pointer==2){
            return;
        }
    }
    return;
}




int profile_menu() {
    profmenu:
    login_status=0;
    // Define menu options
    char choices[4][30]={"Sign Up","Sign In","BACK"};
    
     int highlight = 0;
    int choice = -1;
    int ch;

    while (1) {
        curs_set(0);
        clear();
        draw_rectangle(50, 30);
        int screen_height, screen_width;
        getmaxyx(stdscr, screen_height, screen_width);
        int start_x = (screen_width - 50) / 2 + 2;
        int start_y = (screen_height - 30) / 2 + 2;
        mvprintw(start_y + 1, start_x + 12, "=== PROFILE MENU ===");
        for (int i = 0; i <3; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
                mvprintw(start_y + 2 * i + 3, start_x, "%s", choices[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(start_y + 2 * i + 3, start_x, "%s", choices[i]);
            }
        }

        ch = getch();
        switch (ch) {
            case KEY_UP:
                highlight = (highlight == 0) ? 2 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == 2) ? 0 : highlight + 1;
                break;
                
        }
        if(ch=='\n'){
            choice=highlight;
            break;
        }
    }

    // Take action based on the user's choice
    switch (choice) {
        case 0: // Sign Up
            sign_up();
            break;
        case 1: // Sign In
            // sign_in(); // Implement this function
            sign_in();
            if(login_status==1){
                return 1;
            }
            
            break;
        case 2: // Forgot Password
            // forgot_password(); // Implement this function
            return 0;
            refresh();
            
            break;
    }
    goto profmenu;
}


void draw_rectangle(int width, int height) {
    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    int start_x = (screen_width - width) / 2;
    int start_y = (screen_height - height) / 2;

    // Draw borders
    for (int i = 0; i < width; i++) {
        mvprintw(start_y, start_x + i, "-");
        mvprintw(start_y + height - 1, start_x + i, "-");
    }
    for (int i = 0; i < height; i++) {
        mvprintw(start_y + i, start_x, "|");
        mvprintw(start_y + i, start_x + width - 1, "|");
    }

    // Draw corners
    mvprintw(start_y, start_x, "+");
    mvprintw(start_y, start_x + width - 1, "+");
    mvprintw(start_y + height - 1, start_x, "+");
    mvprintw(start_y + height - 1, start_x + width - 1, "+");
}
void random_pass(char *pass, int len) {
    for (int i = 0; i < len; i++) {
        pass[i] = rand() % 93 + 33; // Random printable ASCII character
    }
    pass[len] = '\0'; // Null-terminate the string
}