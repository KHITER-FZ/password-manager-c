#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include<time.h>
#include "generator.h"

void generate(char *password,int length){
    const char charset[]="ABCDEFJHIGKLMNOPQRSTUVWXYZ"
                          "abcdefjhigklmnopqrstuvwxyz"
                          "1234567890"
                          "!@#$^&*-";
 int charsetsize=strlen(charset);
 int i;
 for(i=0;i<length;i++){
    password[i]=charset[rand()%charsetsize];
 }
 password[length]='\0';

}

