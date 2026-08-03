#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password.h"
#include "menu.h"
#include "generator.h"
#include <conio.h>
static user *head = NULL;

static void appendnode(user *node)
{
    if (head == NULL)
    {
        head = node;
    }
    else
    {
        user *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
    }
}

void addpassword()
{
    int choice2, choice3, length;
    user *confirm = head;

    user *node;
    node = malloc(sizeof(user));
    if (node == NULL)
        return;
    clearinput();
    printf("Website : ");
    fgets(node->website, sizeof(node->website), stdin);

    node->website[strcspn(node->website, "\n")] = '\0';

    printf("\nUsername: ");
    fgets(node->username, sizeof(node->username), stdin);
    node->username[strcspn(node->username, "\n")] = '\0';
    while (confirm != NULL)
    {
        if (strcmp(node->website, confirm->website) == 0 && strcmp(node->username, confirm->username) == 0)
        {
            printf("This account is already exist !\n \n");
            printf("website: %s\n \n", node->website);
            printf("username: %s\n", node->username);
            printf("You can update the password instead.\n");
            free(node);
            return;
        }
        confirm = confirm->next;
    }
    node->username[strcspn(node->username, "\n")] = '\0';
    printf("\nPassword:\n ");
    menugenerator();
    do
    {
        scanf("%d", &choice2);
    } while (choice2 != 1 && choice2 != 2);
    switch (choice2)
    {
    case 1:
        printf("Enter Password:\n");
        getchar();
        fgets(node->pw, sizeof(node->pw), stdin);
        node->pw[strcspn(node->pw, "\n")] = '\0';
        break;
    case 2:
        printf("Enter password length (8~20) :\n");
        do
        {
            scanf("%d", &length);
        } while (length < 8 || length > 20);

        do
        {
            generate(node->pw, length);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("  Generated password:%s\n", node->pw);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            do
            {
                printf("Use this password?\n1-Yes\n2-Generate another\n");
                scanf("%d", &choice3);
            } while (choice3 != 1 && choice3 != 2);
        } while (choice3 == 2);

        break;
    }
    node->next = NULL;
    printf("So..\n");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n Website : %s\n", node->website);
    printf("\n Username: %s\n", node->username);
    printf("\n Password: %s\n", node->pw);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    appendnode(node);
    savetofile();
}

void searchpassword()
{

    user *search = head;
    if (search == NULL)
        return;

    char website[50];
    printf("Enter the website:\n");

    fgets(website, sizeof(website), stdin);
    website[strcspn(website, "\n")] = '\0';
    while (search != NULL)
    {
        if (strcmp(search->website, website) == 0)
        {
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("   Website: %s\n", search->website);
            printf("   Username: %s\n", search->username);
            printf("   Password:%s\n", search->pw);
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            break;
        }
        search = search->next;
    }
    if (search == NULL)
    {
        printf("Website NOT FOUND!\n ");
    }
}

void showpasswords()
{
    if (head == NULL)
    {
        printf("No passwords Saved YET!\n");
        return;
    }
    user *current = head;
    while (current != NULL)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf(" Website : %s\n", current->website);
        printf(" Username: %s\n", current->username);
        printf(" Password: %s\n", current->pw);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        current = current->next;
    }
}

void deletepassword()
{
    char website[50];
    int confirm;

    user *previous = NULL;
    user *current = head;

    if (head == NULL)
    {
        printf("There are no passwords saved!\n");
        return;
    }
    clearinput();
    printf("Enter the website to delete:\n ");

    fgets(website, sizeof(website), stdin);
    website[strcspn(website, "\n")] = '\0';

    while (current != NULL)
    {
        if (strcmp(current->website, website) == 0)
        {
            printf("\nWebsite : %s\n", current->website);
            printf("Username: %s\n", current->username);
            printf("Password: %s\n", current->pw);
            printf("\nAre you sure you want to delete this password?\n");
            printf("1 - Yes\n");
            printf("2 - No\n");

            do
            {
                scanf("%d", &confirm);
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            } while (confirm != 1 && confirm != 2);
            if (confirm == 2)
            {
                printf("Deletion cancelled.\n");
                return;
            }

            if (previous == NULL)
                head = current->next;
            else
                previous->next = current->next;

            free(current);

            savetofile();

            printf("Password deleted successfully!\n");

            return;
        }

        previous = current;
        current = current->next;
    }

    printf("Website NOT FOUND!\n");
}

void savetofile()
{
    FILE *f;
    user *current = head;
    f = fopen("password.dat", "wb");
    if (f == NULL)
    {
        printf("ERROR Opening File !\n");
        return;
    }
    while (current != NULL)
    {

        user tmp = *current;
        tmp.next = NULL;
        encrypt(tmp.pw);
        fwrite(&tmp, sizeof(user), 1, f);
        current = current->next;
    }
    fclose(f);
}

void loadfromfile()
{
    FILE *f = fopen("password.dat", "rb");

    if (f == NULL)
        return;

    while (1)
    {
        user *node = malloc(sizeof(user));

        if (node == NULL)
            break;

        if (fread(node, sizeof(user), 1, f) != 1)
        {
            free(node);
            break;
        }

        encrypt(node->pw);

        node->next = NULL;

        appendnode(node);
    }

    fclose(f);
}

void updatepassword()
{
    user *current = head;
    if (current == NULL)
    {
        printf("No passwords saved\n");
        return;
    }
    clearinput();
    char website[50];
    printf("Enter the website:\n");

    fgets(website, sizeof(website), stdin);
    website[strcspn(website, "\n")] = '\0';
    while (current != NULL)
    {
        if (strcmp(current->website, website) == 0)
        {
            printf("The current password is:%s\n", current->pw);
            printf("Enter the NEW password:\n");
            fgets(current->pw, sizeof(current->pw), stdin);
            current->pw[strcspn(current->pw, "\n")] = '\0';

            savetofile();
            printf("Password changed Successfully!\n");
            break;
        }
        current = current->next;
    }
    if (current == NULL)
    {
        printf("Website NOT FOUND\n");
    }
}

void encrypt(char *password)
{
    char key = 'P';
    int i = 0;
    while (password[i] != '\0')
    {
        password[i] = password[i] ^ key;
        i++;
    }
}

void inputpassword(char password[])
{
    char ch;
    int i = 0;

    while ((ch = _getch()) != '\r')
    {
        password[i++] = ch;
        printf("*");
    }

    password[i] = '\0';
}

void clearinput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
void clearall()
{
    if (head == NULL)
    {
        printf("No passwords to delete.\n");
        return;
    }

    int confirm;

    printf("\n---------------------------------------\n");
    printf("            <!> WARNING <!>\n");
    printf("\n----------------------------------------\n");
    printf("This action will permanently delete\n");
    printf("aLL saved passwords.\n\n");
    printf("Are you sure you want to continue?\n\n");
    printf("1 - Yes\n");
    printf("2 - No\n");
    printf("Choice: ");

    do
    {
        scanf("%d", &confirm);
    }
    while(confirm != 1 && confirm != 2);

    if(confirm == 2)
    {
        printf("Operation cancelled.\n");
        return;
    }

    user *current = head;

    while(current != NULL)
    {
        user *temp = current;
        current = current->next;
        free(temp);
    }

    head = NULL;

    savetofile();

    printf("All passwords deleted successfully!\n");
}