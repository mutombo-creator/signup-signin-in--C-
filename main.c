#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//definition of my constant variables
#define MAX_NAME 100
#define MAX_USERNAME 100
#define MAX_PASSWORD 8
#define MAX_EMAIL 100
#define MAX_LOCATION 100


struct Account{
    char fullName[MAX_NAME];
    char userName[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char email[MAX_EMAIL];
    char location[MAX_LOCATION];
    int age;
};

int main()
{
    printf("Loading: \n");
    int option;
    system("color 27");
    loader();

    while(option != 3)
    {

        printf("\t\t\t\t\t****************************************************\n");
        printf("\t\t\t\t\t*             Welcome to Speech Therapy system      *\n");
        printf("\t\t\t\t\t****************************************************\n\n");
        printf("Menu!\n");
        printf("1:login \n");
        printf("2:signUp \n");
        printf("3:Exit \n");

        scanf("%d",&option);
        switch(option)
        {
            case 1:
                system("cls");
                printf("\t\t\t\t\t*****************************\n");
                printf("\t\t\t\t\t*** LOGIN HERE ***\n");
                Login();
                break;

            case 2:
                system("cls");
                printf("\t\t\t\t\t*****************************\n");
                printf("\t\t\t\t\t****Create Account****\n");
                CreateAccount();
                break;

            case 3:
                return 0;
                break;

            default:
                printf("Invalid Option");
                break;
        }
    }
    return 0;
}

void CreateAccount()
{
    FILE *userfile;
    userfile = fopen("account.txt","a+");

    if(userfile == NULL)
    {
         perror("Failed: ");
    }
    struct Account user;
    printf("Enter FullName: ");
    scanf("%s",&user.fullName);
    printf("\n");


    printf("Enter userName: ");
    scanf("%s",&user.userName);
    printf("\n");

    printf("Enter Password: ");
    scanf("%s",&user.password);
    printf("\n");

    printf("Enter Email: ");
    scanf("%s",&user.email);
    printf("\n");

    printf("Enter Location: ");
    scanf("%s",&user.location);
    printf("\n");

    printf("Enter Age");
    scanf("%d",&user.age);
    printf("\n");

    int flag = 0;

    flag = fprintf(userfile,"%s,%s,%s,%s,%s,%d\n",user.fullName,user.userName,user.password,user.email,user.location, user.age);

        //fwrite(&user, sizeof(struct Account),1,userfile);

    if(flag > 0)
    {
       printf("Account created successfully");
    }
    else
    {
        printf("Error creating Account");
    }
    //printf("Account Created");

    fclose(userfile);
}

void loader()
{
    int i, j;
    // Loop 10 times

     for(i = 0; i < 10; i++) {
        // Print the progress bar
        printf("[");
        for (j = 0; j <= i; j++) {
            printf("=");
        }
        for (j = i+1; j < 10; j++) {
            printf(" ");
        }
        printf("] %d%%\r", (i+1)*10);
        fflush(stdout); //is used for clear the out put buffer


        sleep(1);
    }

    system("cls");
}

void Login()
{
    char userName[MAX_USERNAME];
    char password[MAX_PASSWORD];

   struct Account user;

    printf("UserName: ");
    scanf("%s",&userName);
    printf("\n");

    printf("Password: ");
    scanf("%s",&password);


    FILE *login_details = fopen("account.txt","r");

    if(login_details == NULL)
    {
        printf("Failed to Open File \n");
        return;
    }

     user = get_user(userName,password);

    if(strcmp(user.userName,userName)==0&& strcmp(user.password,password)==0)
    {
        printf("LogIn success \n");
    }
    else
    {
        printf("Login failed \n");
    }
}

struct Account get_user(char* username , char* password)
{
    FILE* data;
    struct Account user;

    data = fopen("account.txt","r");

    if(data != NULL)
    {
        char line[MAX_NAME+MAX_USERNAME+MAX_PASSWORD+MAX_EMAIL+MAX_LOCATION+3];
        char* token;
        char* separator = ",";
        int found = 0;

        while(fgets(line,sizeof(line),data) != NULL)
        {
            token = strtok(line,separator);
            strcpy(user.fullName,token);

            token = strtok(NULL,separator);
            strcpy(user.userName,token);

            token = strtok(NULL,separator);
            strcpy(user.password,token);

            token = strtok(NULL,separator);
            strcpy(user.email,token);

            token = strtok(NULL,separator);
            strcpy(user.location,token);

            token = strtok(NULL,separator);
            user.age = atoi(token); // convert the item taken from the file and put it in an interger variable

            if(strcmp(user.userName,username)==0)
            {
                found = 1;
                break;

            }


        }
        fclose(data);

        if(!found)
        {
           strcpy(user.userName,"Not found");
        }


    }
     return user;

}



