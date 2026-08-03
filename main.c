#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"menu.h"
#include"password.h"
#include "master.h"

int main(){
    int choice1;
     setupmaster();
     if(!verifymaster()){
        printf("Wrong Password \n");
        return 0;
     }


    loadfromfile();
    
    do{
    printf("\n");
    showmenu();   
    scanf("%d",&choice1);
    
    switch (choice1)
    {
    case 1:
     addpassword();
     
     break;
    case 2:
      searchpassword();
     break;
    case 3: 
     
     showpasswords();
     break; 
    case 4:
     deletepassword();
     
     break;
    case 5:
     updatepassword(); 
     break;
    case 6:
      clearall();
      break;
    case 7:
     printf("BaBye!");
     break;
    default:
     printf("ERROR !>.< \n");
        break;
    }
    }while(choice1!=7);
    
    return 0;
}



