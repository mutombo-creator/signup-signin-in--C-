#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//definition of my constant variables
#define MAX_NAME 100
#define MAX_USERNAME 100
#define MAX_PASSWORD 8
#define MAX_EMAIL 100
#define MAX_LOCATION 100

struct Account get_user(char* username , char* password);
struct Account search_user(char* username);
void uda(char* name);
void del(char* username);


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
    char username[MAX_USERNAME];

    while(option != 3)
    {

        printf("\t\t\t\t\t****************************************************\n");
        printf("\t\t\t\t\t*             Welcome to Speech Therapy system      *\n");
        printf("\t\t\t\t\t****************************************************\n\n");
        printf("Menu!\n");
        printf("1:login \n");
        printf("2:signUp \n");
        printf("3:Admin \n");
        printf("4:Exit \n");

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

                break;

            default:
                printf("Invalid Option");
                break;
        }
    }
    return 0;
}

//function for creating an account
void CreateAccount()
{
    FILE *userfile;
    userfile = fopen("account.txt","a+");

    if(userfile == NULL)
    {
         perror("Failed: ");
    }


    struct Account user;
    printf("Enter Name: ");
    //gets(user.fullName);
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

    printf("Enter Age: ");
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
//function for the loader
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

//function for the user login
void Login()
{
    char userName[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char name[MAX_NAME];
    int option;

    int back = 0;

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
        system("cls");
        printf("welcome %s \n", user.fullName);
        printf("..........DashBoard.........\n");

        printf("\n");
        printf("1:search | \t2:Update\t | 3:logOut \n");

        printf("\n");

        printf("option: ");
        scanf("%d",& option);

        switch(option)
        {
            case 1:
                system("cls");

                searchAccount();
                printf("Back to main (1: yes , 2: No)\n");
                scanf("%d",&back);
                if(back == 1)
                    system("cls");
                break;

            case 2:
                system("cls");
                printf("Enter Name: ");
                scanf("%s",name);
                uda(name);
                printf("Back to main (1: yes , 2: No)\n");
                scanf("%d",&back);
                if(back == 1)
                    system("cls");

            default:
                printf("Invalid Option \n");
                break;
        }

    }
    else
    {
        printf("Login failed UserName or password Incorect \n");
    }

    //lets loop through the file





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

        if(found ==0)
        {
           strcpy(user.userName,"Not found");
        }


    }
     return user;

}

void searchAccount()
{
    char error[20] = "Not found";
    char searchName[MAX_USERNAME];
    struct Account use;
    printf("************** Search ********* \n");



    printf("Enter UserName: ");
    scanf("%s",&searchName);

     use = search_user(searchName);

    if( strcmp(use.userName,error)==0)
    {
        printf("User does not Exist \n");
        return;
    }
    else
    {
        printf("..........User Data.........\n");

        printf("+----------------------+--------+---------------+------------------------+\n");
        printf("|        Name          |  Age   |    Username   |          Email         |\n");
        printf("+----------------------+--------+---------------+------------------------+\n");

        printf("| %-20s| %6d | %-14s| %-23s|\n", use.fullName, use.age, use.userName, use.email);
        printf("+----------------------+--------+---------------+------------------------+\n");


    }



}


struct Account search_user(char* username)
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

        if(found==0)
        {
           strcpy(user.userName,"Not found");

        }


    }
     return user;

}
void uda(char* name)
{
    //updating
    FILE* userfile;
    FILE* ufile;
    int found = 0;
    int num_users = 0;
    int i;
    int non = 0;
    struct Account st[100];

    userfile = fopen("account.txt", "r");
     if (userfile == NULL) {
        printf("Failed to Open File\n");
        return;
    }

       while (fscanf(userfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%d\n", st[num_users].fullName, st[num_users].userName, st[num_users].password, st[num_users].email, st[num_users].location, &st[num_users].age) == 6) {
        if (strcmp(st[num_users].fullName, name) == 0) {
            found = 1;
            num_users++;
        }
        num_users++;
    }
    fclose(userfile);
    ufile = fopen("account.txt", "w+");
    if (ufile == NULL) {
        perror("Failed to Open File: \n");
        return;
    }

    if(found== 1)
    {
       for( i =0; i<num_users; i++)
       {
           if (strcmp(st[i].fullName, name) == 0) {

              printf("Enter new UserName: ");
              scanf("%s",&st[i].userName);
              printf("\n");

              printf("Enter new Password: ");
              scanf("%s",&st[i].password);
              printf("\n");

              printf("Enter new Email: ");
              scanf("%s",&st[i].email);
              printf("\n");

              printf("Enter new Location: ");
              scanf("%s",&st[i].location);
              printf("\n");

              printf("Enter new Age: ");
              scanf("%d", &st[i].age);
              printf("\n");

              fprintf(ufile, "%s,%s,%s,%s,%s,%d\n", st[i].fullName, st[i].userName, st[i].password, st[i].email, st[i].location, st[i].age);
           }
           else
           {
              if(st[i].age == non)
              {
                  //implementation
              }
              else
              {
                fprintf(ufile, "%s,%s,%s,%s,%s,%d\n", st[i].fullName, st[i].userName, st[i].password, st[i].email, st[i].location, st[i].age);
              }

           }
       }
       fclose(ufile);

       printf("Updated succefully");
    }
    else
    {
        printf("User Not found");
    }




}
void del(char* username)
{
    //deleting an account
    FILE* userfile;
    FILE* ufile;
    int found = 0;
    int num_users = 0;
    int i;
    int non = 0;
    struct Account st[100];

    userfile = fopen("account.txt", "r");
     if (userfile == NULL) {
        printf("Failed to Open File\n");
        return;
    }

       while (fscanf(userfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%d\n", st[num_users].fullName, st[num_users].userName, st[num_users].password, st[num_users].email, st[num_users].location, &st[num_users].age) == 6) {
        if (strcmp(st[num_users].userName, username) == 0) {
            found = 1;
            num_users++;
        }
        num_users++;
    }
    fclose(userfile);
    ufile = fopen("account.txt", "w+");
    if (ufile == NULL) {
        perror("Failed to Open File: \n");
        return;
    }

    if(found== 1)
    {
       for( i =0; i<num_users; i++)
       {
           if (strcmp(st[i].userName, username) == 0) {

             //dont write it to the file
           }
           else
           {
              if(st[i].age == non)
              {
                  //implementation
              }
              else
              {
                fprintf(ufile, "%s,%s,%s,%s,%s,%d\n", st[i].fullName, st[i].userName, st[i].password, st[i].email, st[i].location, st[i].age);
              }

           }
       }
       fclose(ufile);

       printf("Deleted succefully");
    }
    else
    {
        printf("User Not found");
    }





}
void adminDash()
{
    printf("########ADMIN DASHBOARD#########");

}
