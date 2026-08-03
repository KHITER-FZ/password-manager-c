#include<stdio.h>
#include"password.h"
#include<string.h>

void setupmaster()
{
    FILE *f = fopen("master.dat","rb");

    if(f != NULL)
    {
        fclose(f);
        return;
    }

    char master[30];

    printf("Create Password:\n");

    //fgets(master,sizeof(master),stdin);
    //master[strcspn(master,"\n")] = '\0';
    inputpassword(master);
    encrypt(master);

    f = fopen("master.dat","wb");

    if(f == NULL)
        return;

    fwrite(master,sizeof(char),strlen(master)+1,f);

    fclose(f);

    printf("Password created successfully!\n");
}

int verifymaster(){
    char master[30] ,input[30];

    FILE *f=fopen("master.dat","rb");
    if(f==NULL)
     return 0;
    fread(master,sizeof(char),sizeof(master),f);
    encrypt(master);
    printf("Enter Password:\n");
    //fgets(input,sizeof(input),stdin);
    //input[strcspn(input,"\n")]='\0';
    inputpassword(input);

    if(strcmp(master,input)==0){
        return 1;
    }else{
        printf("Wrong Master Password \n");
        return 0;
    }
 fclose(f);
}


