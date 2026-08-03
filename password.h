#ifndef PASSWORD_H
#define PASSWORD_H

typedef struct user{
 char website[50] ;
 char username[50];
 char pw[20];
 struct user *next;
}user;
void addpassword();
void showpasswords();
void searchpassword();
void deletepassword();
void savetofile();
void loadfromfile();
void updatepassword();
void encrypt(char *password);
void inputpassword(char password[]);
void clearinput();
void clearall();
#endif