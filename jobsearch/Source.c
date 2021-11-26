#define _CRT_SECURE_NO_WARNINGS
//#include <stddef.h>
//#include <stdint.h>
//#include <conio.h>
//#include "csv.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static char curid[9];//to use the id of the current user in every function
static int usertype;//to check the type of user in every function 1 for candid 2 for empl
void mainmenu();
const char* getfield(char*,int);
void printfile(char*);
char* questionnaire(int);
void signupemployer();
void signinemployer();
//int checkifidexist(char string[50])
//{
//    //this func get the id number and check if it exist and return the row his shown
//    int row = 0;
//    FILE* stream = fopen("employer.csv", "r");
//    char line[1024];
//    while (fgets(line, 1024, stream))
//    {
//        row++;
//        char* tmp = _strdup(line);
//        if (strcmp(getfield(tmp, 1), string) == 0)
//        {
//            fclose(stream);
//            return row;
//        }
//        // NOTE strtok clobbers tmp
//        free(tmp);
//    }
//    fclose(stream);
//    return 0;
//}
void editempfield(int cultoedit, char* field)
{
    char cul1[50], cul2[50], cul3[50], cul4[50], cul5[50], cul6[50], cul7[50];
    int row = 0;
    FILE* stream = fopen("employer.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        row++;
        char* tmp = _strdup(line);
        if (strcmp(getfield(tmp, 1), curid) == 0)
            break;
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(stream);
    FILE* stream2 = fopen("employer.csv", "r");
    FILE* stream3 = fopen("tmp.csv", "w");
    char ch;
    char tmpline[1024];
    int num1 = 0;
    int numcheck = 0;
    while (fgets(line, 1024, stream2))
    {
        num1++;
        if (num1 == row)
        {
            char* tmp = _strdup(line);
            char* tmp2 = _strdup(line);
            char* tmp3 = _strdup(line);
            char* tmp4 = _strdup(line);
            char* tmp5 = _strdup(line);
            char* tmp6 = _strdup(line);
            char* tmp7 = _strdup(line);
            strcpy(cul1, getfield(tmp, 1));
            strcpy(cul2, getfield(tmp2, 2));
            strcpy(cul3, getfield(tmp3, 3));
            strcpy(cul4, getfield(tmp4, 4));
            strcpy(cul5, getfield(tmp5, 5));
            strcpy(cul6, getfield(tmp6, 6));
            strcpy(cul7, getfield(tmp7, 7));
            break;
        }
        fprintf(stream3, "%s", line);
    }
    fclose(stream2);
    fclose(stream3);
    if (cultoedit == 2)//edit password
        strcpy(cul2, field);
    else if (cultoedit == 4)//edit email
        strcpy(cul4, field);
    else if (cultoedit == 5)//edit phone
        strcpy(cul5, field);
    stream2 = fopen("employer.csv", "r");
    stream3 = fopen("tmp.csv", "a");
    fprintf(stream3, "%s,%s,%s,%s,%s,%s,%s\n", cul1, cul2, cul3, cul4, cul5, cul6, cul7);
    while (fgets(line, 1024, stream2))
    {
        numcheck++;
        if (num1 < numcheck)
            fprintf(stream3, "%s", line);
    }
    fclose(stream2);
    fclose(stream3);
    stream2 = fopen("employer.csv", "w");//target
    stream3 = fopen("tmp.csv", "r");//source

    if (stream2 == NULL)
    {
        fclose(stream3);
        printf("we got a problem \n");
        return;
    }
    while ((ch = fgetc(stream3)) != EOF)
        fputc(ch, stream2);

    printf("profile edit successfully.\n");
    fclose(stream3);
    fclose(stream2);
}
void editempprofile()
{
    char val[50];
    int choice = 9;
    while (choice != 1 && choice != 2 && choice != 3 && choice != 0)
    {
        printf("Please choose one of the option:\n");
        printf("which field you want to edit:\n");
        printf("1 - password\n");
        printf("2 - email\n");
        printf("3 - phone \n");
        printf("0 - back to menu \n");
        scanf("%d", &choice);
    }
    if (choice == 1)
    {
        printf("enter the new password:\n");
        scanf("%s", &val);
        while (checkpassword(val) != 1)
        {
            printf("enter the new password:\n");
            scanf("%s", &val);
        }
        editempfield(2, val);
    }
    else if (choice == 2)
    {
        printf("enter the new email:\n");
        scanf("%s", &val);
        editempfield(4, val);
    }
    else if (choice == 3)
    {
        printf("enter the new phone number:\n");
        scanf("%s", &val);
        editempfield(5, val);
    }
    else if (choice == 0)
        return;
}
void jobcandidview()
{
    char jobs[1000][20];
    char jobs2[1000][20];
    int z;
    int num = 0;
    FILE* stream = fopen("viewjobs.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        if (strcmp(getfield(tmp, 1), curid) == 0)
        {
            strcpy(jobs[num], getfield(tmp2, 2));
            num++;
        }
        // NOTE strtok clobbers tmp
        free(tmp);
        free(tmp2);
    }
    fclose(stream);
    if (num == 0)
    {
        printf("you dont see any jobs yet\n");
        return;
    }
    strcpy(jobs2[0],jobs[0]);
    int index = 1;
    for (int i = 1; i < num; i++)
    {
        for (z = 0; z < index; z++)
            if (strcmp(jobs2[z], jobs[i]) == 0)
                break;
        if (z == index)
        {
            strcpy(jobs2[index], jobs[i]);
            index++;
        }

    }
    for (int i = 0; i < index; i++)
    {
        jobs2[i][strlen(jobs2[i])-4] = '\0';
        printfile(jobs2[i]);
        printf("Press Any Key to Continue\n");
        getch();
    }
}
void editcandidfield(int cultoedit, char* field)
{
    char cul1[50], cul2[50], cul3[50], cul4[50], cul5[50], cul6[50], cul7[50], cul8[50], cul9[50];
    int row = 0;
    FILE* stream = fopen("candidate.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        row++;
        char* tmp = _strdup(line);
        if (strcmp(getfield(tmp, 1), curid) == 0)
            break;
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(stream);
    FILE* stream2 = fopen("candidate.csv", "r");
    FILE* stream3 = fopen("tmp.csv", "w");
    char ch;
    char tmpline[1024];
    int num1 = 0;
    int numcheck = 0;
    while (fgets(line, 1024, stream2))
    {
        num1++;
        if (num1 == row)
        {
            char* tmp = _strdup(line);
            char* tmp2 = _strdup(line);
            char* tmp3 = _strdup(line);
            char* tmp4 = _strdup(line);
            char* tmp5 = _strdup(line);
            char* tmp6 = _strdup(line);
            char* tmp7 = _strdup(line);
            char* tmp8 = _strdup(line);
            char* tmp9 = _strdup(line);
            strcpy(cul1, getfield(tmp, 1));
            strcpy(cul2, getfield(tmp2, 2));
            strcpy(cul3, getfield(tmp3, 3));
            strcpy(cul4, getfield(tmp4, 4));
            strcpy(cul5, getfield(tmp5, 5));
            strcpy(cul6, getfield(tmp6, 6));
            strcpy(cul7, getfield(tmp7, 7));
            strcpy(cul8, getfield(tmp8, 8));
            strcpy(cul9, getfield(tmp9, 9));
            break;
        }
        fprintf(stream3, "%s", line);
    }
    fclose(stream2);
    fclose(stream3);
    if (cultoedit == 2)//edit password
        strcpy(cul2, field);
    else if (cultoedit == 5)//edit email
        strcpy(cul5, field);
    else if (cultoedit == 9)//edit quiz
        strcpy(cul9, field);

    stream2 = fopen("candidate.csv", "r");
    stream3 = fopen("tmp.csv", "a");
    fprintf(stream3, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", cul1, cul2, cul3, cul4, cul5, cul6, cul7, cul8, cul9);
    while (fgets(line, 1024, stream2))
    {
        numcheck++;
        if (num1 < numcheck)
            fprintf(stream3, "%s", line);
    }
    fclose(stream2);
    fclose(stream3);

    stream2 = fopen("candidate.csv", "w");//target
    stream3 = fopen("tmp.csv", "r");//source

    if (stream2 == NULL)
    {
        fclose(stream3);
        printf("we got a problem \n");
        return;
    }
    while ((ch = fgetc(stream3)) != EOF)
        fputc(ch, stream2);

    printf("profile edit successfully.\n");
    fclose(stream3);
    fclose(stream2);

}
void editcandidprofile()
{
    char val[50];
    int choice=9;
    while (choice != 1 && choice != 2 && choice != 3 && choice != 0)
    {
        printf("Please choose one of the option:\n");
        printf("which field you want to edit:\n");
        printf("1 - password\n");
        printf("2 - email\n");
        printf("3 - Answer the questionnaire again \n");
        printf("0 - back to menu \n");
        scanf("%d", &choice);
    }
    if (choice == 1)
    {
        printf("enter the new password:\n");
        scanf("%s", &val);
        while (checkpassword(val) != 1)
        {
            printf("enter the new password:\n");
            scanf("%s", &val);
        }
        editcandidfield(2, val);
    }
    else if (choice == 2)
    {
        printf("enter the new email:\n");
        scanf("%s", &val);
        editcandidfield(5, val);
    }
    else if (choice == 3)
    {
        strcpy(val,questionnaire(1));
        editcandidfield(9, val);
    }
    else if (choice == 0)
        return;
}
void newjobs()
{
    int checkifprint = 0;
    int alreadysee = 0;
    FILE* fptr;
    char c;
    char comptext[20];
    char empid[20], jobid[10];
    char choice = '0';
    int row = 0;
    FILE* stream = fopen("jobs.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        alreadysee = 0;
        row++;
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        char* tmp3 = _strdup(line);
        char sec = getfield(tmp, 3)[4];
        char* valid = getfield(tmp2, 4);
        if (strcmp(valid, "1") == 0)
        {
            
            strcpy(empid, getfield(tmp, 1));
            strcpy(jobid, getfield(tmp3, 2));
            strcat(empid, "-");
            strcat(empid, jobid);
            strcat(empid, ".txt");
            strcpy(comptext, empid);
            FILE* stream2 = fopen("viewjobs.csv", "r");

            char line2[1024];
            while (fgets(line2, 1024, stream2))
            {
                char* idcheck = _strdup(line2);
                char* filename = _strdup(line2);
                char* theid = getfield(idcheck, 1);
                char* thetext = getfield(filename, 2);
                if (((strcmp(theid, curid) == 0))&& (strcmp(thetext, comptext) == 0))
                {
                        alreadysee++;
                        break;
                }

                // NOTE strtok clobbers tmp
                free(idcheck);
                free(filename);
            }
            fclose(stream2);
            if (alreadysee != 0)
                continue;
            printf("%s", line);
            fptr = fopen(empid, "r");
            if (fptr == NULL)
            {
                printf("Cannot open file \n");
                continue;
                // exit(0);
            }

            // Read contents from file
            c = fgetc(fptr);
            while (c != EOF)
            {
                printf("%c", c);
                c = fgetc(fptr);
            }
            printf("\n\n\n");
            fclose(fptr);
            checkifprint++;
            if (usertype == 1)
            {
                FILE* fpt;
                fpt = fopen("viewjobs.csv", "a");
                fprintf(fpt, "%s,%s\n", curid, empid);
                fclose(fpt);
            }
            printf("Press Any Key to Continue\n");
            getch();
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    if (checkifprint == 0)
        printf("there is no job that you dont see yet :) \n");
}
void seealljobs()
{
    FILE* fptr;
    char c;
    char empid[20], jobid[10];
    char choice = '0';
    int row = 0;
    FILE* stream = fopen("jobs.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        row++;
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        char* tmp3 = _strdup(line);
        char sec = getfield(tmp, 3)[4];
        char* valid = getfield(tmp2, 4);
        if (strcmp(valid, "1") == 0)
        {
            printf("%s", line);
            strcpy(empid, getfield(tmp, 1));
            strcpy(jobid, getfield(tmp3, 2));
            strcat(empid, "-");
            strcat(empid, jobid);
            strcat(empid, ".txt");
            fptr = fopen(empid, "r");
            if (fptr == NULL)
            {
                printf("Cannot open file \n");
                continue;
                // exit(0);
            }

            // Read contents from file
            c = fgetc(fptr);
            while (c != EOF)
            {
                printf("%c", c);
                c = fgetc(fptr);
            }
            printf("\n\n\n");
            fclose(fptr);
            printf("Press Any Key to Continue\n");
            getch();
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }
}
void searchbypro()
{
    int checkifpront = 0;
    FILE* fptr;
    char c;
    char empid[20], jobid[10];
    char choice = '0';
    while (choice < 'a' || choice>'k')
    {
        printf("Please select one of the following:\n");
        printf("* What job are you looking for ?\n");
        printf("software:\n");
        printf("a - developer\n");
        printf("b - manager\n");
        printf("c - automation\n");
        printf("d - solution architect\n");
        printf("e - data engineer / analyst\n");
        printf("electric engineering:\n");
        printf("f - chip design\n");
        printf("g - high voltage\n");
        printf("h - signal processing\n");
        printf("industrial and management engineering:\n");
        printf("i - low tech management\n");
        printf("g - data and information systems\n");
        printf("k - PMO\n");
        scanf(" %c", &choice);
    }
    int row = 0;
    FILE* stream = fopen("jobs.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        row++;
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        char* tmp3 = _strdup(line);
        char sec = getfield(tmp, 3)[0];
        char* valid = getfield(tmp2, 4);
        if ((sec == choice)&& (strcmp(valid, "1") == 0))
        {
            printf("%s", line);
            strcpy(empid, getfield(tmp, 1));
            strcpy(jobid, getfield(tmp3, 2));
            strcat(empid, "-");
            strcat(empid, jobid);
            strcat(empid, ".txt");
            fptr = fopen(empid, "r");
            if (fptr == NULL)
            {
                printf("Cannot open file \n");
                continue;
                // exit(0);
            }
            checkifpront++;
            // Read contents from file
            c = fgetc(fptr);
            while (c != EOF)
            {
                printf("%c", c);
                c = fgetc(fptr);
            }
            printf("\n\n\n");
            fclose(fptr);
            if (usertype == 1)
            {
                FILE* fpt;
                fpt = fopen("viewjobs.csv", "a");
                fprintf(fpt, "%s,%s\n", curid,empid);
                fclose(fpt);
            }
            printf("Press Any Key to Continue\n");
            getch();
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(stream);
    if (checkifpront==0)
        printf("no avaliable jobs in this prof\n");
}
void removejob()
{
    char conv[50];
    int check[100];
    int t = 0;
    int n = 0, choice;
    char cul1[50], cul2[50], cul3[50], cul4[50];
    int num = 0;
    FILE* stream = fopen("jobs.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        if (strcmp(getfield(tmp, 1), curid) == 0)
        {
            num++;
            if (strcmp(getfield(tmp2, 4), "1") == 0)
            {
                check[n] = num;
                n++;
            }
        }
        // NOTE strtok clobbers tmp
        free(tmp);
        free(tmp2);
    }
    fclose(stream);
    if (n == 0)
    {
        printf("you dont enter any jobs yet\n");
        return;
    }
    while (t == 0)
    {
        printf("those are the avialibale jobs you upload\nplease choose the one you want to delete\n");
        for (int i = 0; i < n; i++)
            printf("%d\n", check[i]);
        scanf("%d", &choice);
        for (int i = 0; i < n; i++)
            if (check[i] == choice)
            {
                t++;
                break;
            }
    }
    num = 0;
    sprintf(conv, "%d", (choice));
    stream = fopen("jobs.csv", "r");
    while (fgets(line, 1024, stream))
    {
        num++;
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        if (strcmp(getfield(tmp, 1), curid) == 0)
            if (strcmp(getfield(tmp2, 2), conv) == 0)
                break;
        // NOTE strtok clobbers tmp
        free(tmp);
        free(tmp2);
    }
    fclose(stream);

    FILE* stream2 = fopen("jobs.csv", "r");
    FILE* stream3 = fopen("tmp.csv", "w");
    char ch;
    char tmpline[1024];
    int num1 = 0;
    int numcheck = 0;
    while (fgets(line, 1024, stream2))
    {
        num1++;
        if (num1 == num)
        {
            char* tmp = _strdup(line);
            char* tmp2 = _strdup(line);
            char* tmp3 = _strdup(line);
            strcpy(cul1, getfield(tmp, 1));
            strcpy(cul2, getfield(tmp2, 2));
            strcpy(cul3, getfield(tmp3, 3));
            break;
        }
        fprintf(stream3, "%s", line);
    }
    fclose(stream2);
    fclose(stream3);



    stream2 = fopen("jobs.csv", "r");
    stream3 = fopen("tmp.csv", "a");
    fprintf(stream3, "%s,%s,%s,%s\n", cul1, cul2, cul3, "0");
    while (fgets(line, 1024, stream2))
    {
        numcheck++;
        if (num1 < numcheck)
            fprintf(stream3, "%s", line);
    }
    fclose(stream2);
    fclose(stream3);

    stream2 = fopen("jobs.csv", "w");//target
    stream3 = fopen("tmp.csv", "r");//source

    if (stream2 == NULL)
    {
        fclose(stream3);
        printf("we got a problem \n");
        return;
    }
    while ((ch = fgetc(stream3)) != EOF)
        fputc(ch, stream2);

    printf("job removed successfully.\n");
    fclose(stream3);
    fclose(stream2);


}
void printfile(char* filename)
{
    char c;
    FILE* fptr;
    strcat(filename, ".txt");
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        return;
        // exit(0);
    }

    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(fptr);
    }
    printf("\n\n\n");
    fclose(fptr);
}
void smartmatch()
{
    int grade = 0;
    int minans;
    char rightans[20];
    char candidans[20];
    char candidid[20];
    int check[100];
    int t=0;
    int n = 0,choice;
    int num = 0;
    FILE* stream = fopen("jobs.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        if (strcmp(getfield(tmp, 1), curid) == 0)
        {
            num++;
            if (strcmp(getfield(tmp2, 4), "1") == 0)
            {
                check[n] = num;
                n++;
            }
        }
        // NOTE strtok clobbers tmp
        free(tmp);
        free(tmp2);
    }
    fclose(stream);
    if (n == 0)
    {
        printf("you dont enter any jobs yet\n");
        return;
    }
    while (t == 0)
    {
        printf("those are the avialibale jobs you upload\nplease choose the one you looking for match\n");
        for (int i = 0; i < n; i++)
            printf("%d\n", check[i]);
        scanf("%d", &choice);
        for (int i = 0; i < n; i++)
            if (check[i] == choice)
            {
                t++;
                break;
            }
    }
    FILE* stream2 = fopen("jobs.csv", "r");
    //char line[1024];
    while (fgets(line, 1024, stream2))
    {
        char conv[50];
        sprintf(conv, "%d", (choice));
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        char* tmp3 = _strdup(line);
        if ((strcmp(getfield(tmp, 1), curid) == 0)&&(strcmp(getfield(tmp2, 2), conv) == 0))
        {
            strcpy(rightans, getfield(tmp3, 3));
            break;
        }
        // NOTE strtok clobbers tmp
        free(tmp);
        free(tmp2);
    }
    fclose(stream2);

    printf("enter minimum right questions ot of 9 questions\n");
    scanf("%d", &minans);

    FILE* stream3 = fopen("candidate.csv", "r");
    //char line[1024];
    while (fgets(line, 1024, stream3))
    {
        grade = 0;
        char zerocheck;
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        strcpy(candidid, getfield(tmp, 1));
        strcpy(candidans, getfield(tmp2, 9));
        for (int i = 0; i < strlen(candidans); i++)
        {
            zerocheck = rightans[i];
            if ((candidans[i] == rightans[i]) || rightans[i] =='0')
                grade++;
        }

        if (minans <= grade)
        {
            printf("The candidate %s answered %d correct questions out of 9\n\n", candidid, grade);
            printfile(candidid);
            free(tmp);
            free(tmp2);
            printf("Press Any Key to Continue\n");
            getch();
            continue;
        }
        // NOTE strtok clobbers tmp
        free(tmp);
        free(tmp2);
    }
    fclose(stream3);

}
void myuploadedjobs()
{
    FILE* fptr;
    char c;
    char empid[20], jobid[10];
    int row = 0;
    FILE* stream = fopen("jobs.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        row++;
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        char* tmp3 = _strdup(line);
        char* sec = getfield(tmp, 1);
        char* valid = getfield(tmp2, 4);
        if ((strcmp(sec, curid) == 0) && (strcmp(valid, "1") == 0))
        {
            printf("%s", line);
            strcpy(empid, getfield(tmp, 1));
            strcpy(jobid, getfield(tmp3, 2));
            strcat(empid, "-");
            strcat(empid, jobid);
            strcat(empid, ".txt");
            fptr = fopen(empid, "r");
            if (fptr == NULL)
            {
                printf("Cannot open file \n");
                printf("Press Any Key to Continue\n");
                getch();
                continue;
                // exit(0);
            }

            // Read contents from file
            c = fgetc(fptr);
            while (c != EOF)
            {
                printf("%c", c);
                c = fgetc(fptr);
            }
            printf("\n\n\n");
            fclose(fptr);
            printf("Press Any Key to Continue\n");
            getch();
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(stream);

}
int numofjobs()
{
    if (usertype == 1)
    {
        printf("you are login as candid\n");
        return 0;
    }
    int num = 0;
    FILE* stream = fopen("jobs.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = _strdup(line);
        if (strcmp(getfield(tmp, 1), curid) == 0)
        {
            num++;
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(stream);
    return num;

}
void postajob()
{
    char conv[50];
    char ch, source_file[50], target_file[50];
    FILE* source, * target;
    char answ[10];
    int num = numofjobs();//how many jobs you already upload
    strcpy(answ, questionnaire(2));
    /*/*/
    printf("Enter the path of the job details\n");
    gets(source_file);
    source = fopen(source_file, "r");
    while (source == NULL)
    {
        printf("Enter valid path of the job details\n");
        gets(source_file);
        source = fopen(source_file, "r");
    }
    strcpy(target_file, curid);
    strcat(target_file, "-");
    sprintf(conv, "%d", (num+1));
    strcat(target_file, conv);
    strcat(target_file, ".txt");

    target = fopen(target_file, "w");

    if (target == NULL)
    {
        fclose(source);
        printf("we got a problem \n");
        return;
    }
    while ((ch = fgetc(source)) != EOF)
        fputc(ch, target);

    printf("jod details added successfully.\n");
    fclose(source);
    fclose(target);

    FILE* fpt;
    fpt = fopen("jobs.csv", "a");
    fprintf(fpt, "%s,%d,%s,%s\n", curid, num+1, answ,"1");
    fclose(fpt);
    printf("jobs added \n");

}
void serachbyarea()
{
    int checkifprint = 0;
    FILE* fptr;
    char c;
    char empid[20], jobid[10];
    char choice = '0';
    while (choice < '1' || choice>'7')
    {
        printf("Please select one of the following:\n");
        printf("* In what area do you look for?\n");
        printf("1 - North\n");
        printf("2 - Sharon\n");
        printf("3 - Center\n");
        printf("4 - Jerusalem\n");
        printf("5 - South\n");
        printf("6 - Abroad\n");
        printf("7 - From home\n");
        scanf(" %c", &choice);
    }
    int row = 0;
    FILE* stream = fopen("jobs.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        row++;
        char* tmp = _strdup(line);
        char* tmp2 = _strdup(line);
        char* tmp3 = _strdup(line);
        char sec = getfield(tmp, 3)[4];
        char* valid = getfield(tmp2, 4);
        if (((sec == choice) || (sec == '0'))&& (strcmp(valid, "1") == 0))
        {
            printf("%s", line);
            strcpy(empid, getfield(tmp, 1));
            strcpy(jobid, getfield(tmp3, 2));
            strcat(empid, "-");
            strcat(empid, jobid);
            strcat(empid, ".txt");
            fptr = fopen(empid, "r");
            if (fptr == NULL)
            {
                printf("Cannot open file \n");
                continue;
                // exit(0);
            }
            checkifprint++;
            // Read contents from file
            c = fgetc(fptr);
            while (c != EOF)
            {
                printf("%c", c);
                c = fgetc(fptr);
            }
            printf("\n\n\n");
            fclose(fptr);
            if (usertype == 1)
            {
                FILE* fpt;
                fpt = fopen("viewjobs.csv", "a");
                fprintf(fpt, "%s,%s\n", curid, empid);
                fclose(fpt);
            }
            printf("Press Any Key to Continue\n");
            getch();
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(stream);
    if (checkifprint == 0)
        printf("no avaliable jobs in this area\n");
}
void candidmenu()
{
    char choice;
    do
    {
        printf("Please select one of the following:\n");
        printf("1 - search by area\n");//done V
        printf("2 - Search by profession\n");//done V
        printf("3 - see all vacancies\n");//done V
        printf("4 - see the job i dont see yet\n");//done V
        printf("5 - jobs that im already view\n");//done V
        printf("6 - edit profile\n");
        printf("0 - main menu\n");
        scanf(" %c", &choice);
        switch (choice)
        {
        case '1':
        {
            serachbyarea();
            break;
        }
        case '2':
        {
            searchbypro();
            break;
        }
        case '3':
        {
            seealljobs();
            break;
        }
        case '4':
        {
            newjobs();
            break;
        }
        case '5':
        {
            jobcandidview();
            break;
        }
        case '6':
        {
            editcandidprofile();
            break;
        }
        case '0':
            mainmenu();
            return;
        }
    } while (choice != 0);

}
void employermenu()
{
    char choice;
    do
    {
        printf("Please select one of the following:\n");
        printf("1 - post a job\n");//done V
        printf("2 - smart match\n");//done
        printf("3 - search jobs by area\n");//done V
        printf("4 - Search jobs by profession\n");//done V
        printf("5 - see the jobs i add\n");//done V
        printf("6 - delete jobs\n");//done V
        printf("7 - edit profile\n");//done V
        printf("0 - main menu\n");
        scanf(" %c", &choice);
        switch (choice)
        {
        case '1':
        {
            postajob();
            break;
        }
        case '2':
        {
            smartmatch();
            break;
        }
        case '3':
        {
            serachbyarea();
            break;
        }
        case '4':
        {
            searchbypro();
            break;
        }
        case '5':
        {
            myuploadedjobs();
            break;
        }
        case '6':
        {
            removejob();
            break;
        }
        case '7':
        {
            editempprofile();
            break;
        }
        case '0':
            mainmenu();
            return;
        }
    } while (choice != 0);

}
void employerentermenu()
{
    int choice;
    printf("Please choose:\n");
    printf("1 - Log in\n");
    printf("2 - Create New Account\n");
    printf("0 - Back to the main menu \n");
    scanf("%d", &choice);
    while (choice != 1 && choice != 2 && choice != 0)
    {
        printf("Please choose one of the option:\n");
        printf("1 - Log in\n");
        printf("2 - Create New Account\n");
        printf("0 - Back to the main menu \n");
        scanf("%d", &choice);
    }
    if (choice == 1)
        signinemployer();
    else if (choice == 2)
        signupemployer();
    else if (choice == 0)
        mainmenu();
}
char* entergoodid()
{
    //this func print to ented id and check if its could be a good id
    int tmp = 1;
    char id[50];

    printf("enter your ID : \n");
    while (tmp == 1)
    {
        scanf("%s", &id);
        tmp = 0;
        if (strlen(id) != 9)
        {
            printf("enter 9 dig ID : \n");
            tmp++;
            continue;
        }
        for (int i = 0; i < strlen(id); i++)
        {
            if ((id[i] < '0' || id[i] > '9'))
            {
                tmp++;
                printf("enter 9 dig ID : \n");
                break;
            }
        }

    }
    /*char* retstr;
    strcpy(retstr, id);*/
    return id;
}
void signinemployer()
{
    char id[10];
    strcpy(id, entergoodid());
    int row = checkifidexist(id, "employer.csv");
    while (row == 0)
    {
        printf("doesnt exist\n");
        strcpy(id, entergoodid());
        row = checkifidexist(id, "employer.csv");
    }
    char password[30];
    printf("enter password\n");
    scanf("%s", &password);
    while (checkpasswordtoid(id, password, "employer.csv") == 0)
    {
        printf("wrong!, enter password again\n");
        scanf("%s", &password);
    }
    printf("sign in succseful \n");
    strcpy(curid, id);
    usertype = 2;
}
const char* getfield(char* line, int num)
{
    //this func get the line from csv file and the number of colm and return the data in this colmn
    const char* tok;
    for (tok = strtok(line, ",");
        tok && *tok;
        tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
void signupcandid()
{
    char ch, source_file[50], target_file[50];
    FILE* source, * target;
    char string[50];
    char answ[10];
    char id[50];
    char city[50];
    char age[10];
    char address[50];
    char phone[50];
    char email[50];
    char name[50];
    char namefile[20];
    char password[30];
    /*printf("enter your ID : \n");
    scanf("%s", string);
    while (strlen(string) != 9)
    {
        printf("enter 9 dig ID : \n");
        scanf("%s", string);
    }*/
    strcpy(id, entergoodid());
    int b = checkifidexist(id,"candidate.csv");
    while (b != 0)
    {
        printf("exist\n");
        strcpy(id, entergoodid());
        b = checkifidexist(id, "candidate.csv");
    }
    printf("valid id\n");
    printf("enter 8 digit password with 1 letter and 1 number : \n");
    scanf("%s", &password);
    b = checkpassword(password);
    while ((strlen(password) < 8)||b==0)
    {
        printf("enter 8 digit password : \n");
        scanf("%s", &password);
        b = checkpassword(password);
    }
    printf("enter your name :\n ");
    //check for better sulotion
    getchar();
    gets(name);
    printf("enter your age : \n");
    scanf("%s", &age);
    printf("enter your email : \n");
    scanf("%s", &email);
    printf("enter your phone number : \n");
    scanf("%s", &phone);
    printf("enter your city : \n");
    getchar();
    gets(city);
    printf("enter your address : \n");
    //getchar();
    gets(address);

    strcpy(answ, questionnaire(1));
    
    printf("Enter the path of the resume\n");
    gets(source_file);
    source = fopen(source_file, "r");
    while (source == NULL)
    {
        printf("Enter the path of the resume\n");
        gets(source_file);
        source = fopen(source_file, "r");
    }
    strcpy(target_file, id);
    strcat(target_file, ".txt");
    target = fopen(target_file, "w");

    if (target == NULL)
    {
        fclose(source);
        printf("we got a problem \n");
        return;
    }
    while ((ch = fgetc(source)) != EOF)
        fputc(ch, target);

    fclose(source);
    fclose(target);

    /*here gonne be the quiz for thr candid
    every answer gonne add to string
    and every char int he string goonne be answer for one quiestion
    just for simple im gonne simple string */
    //the field int the csv file gonne be like that
    // |id| |password| |name| |age| |email| |phone| |city| |address| |quiz answer|
    
    FILE* fpt;
    fpt = fopen("candidate.csv", "a");
    fprintf(fpt, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", id, password, name, age, email, phone, city, address, answ);
    fclose(fpt);

    printf("sign up succseful \n");
    //id[10] = '\n';
    strcpy(curid, id);
    usertype = 1;
}
void signupemployer()
{
    char id[50];
    char city[50];
    char address[50];
    char phone[50];
    char email[50];
    char name[50];
    char password[30];
    /*printf("enter your ID : \n");
    scanf("%s", string);
    while (strlen(string) != 9)
    {
        printf("enter 9 dig ID : \n");
        scanf("%s", string);
    }*/
    strcpy(id, entergoodid());
    int b = checkifidexist(id, "employer.csv");
    while (b != 0)
    {
        printf(" this id already exist\n");
        strcpy(id, entergoodid());
        b = checkifidexist(id, "employer.csv");
    }
    printf("valid id\n");
    printf("enter 8 digit password with 1 letter and 1 number : \n");
    scanf("%s", &password);
    b = checkpassword(password);
    while ((strlen(password) < 8) || b == 0)
    {
        printf("enter 8 digit password : \n");
        scanf("%s", &password);
        b = checkpassword(password);
    }
    printf("enter your company name :\n ");
    //check for better sulotion
    getchar();
    gets(name);
    printf("enter company contact email : \n");
    scanf("%s", &email);
    printf("enter the company phone number : \n");
    scanf("%s", &phone);
    printf("enter company city : \n");
    getchar();
    gets(city);
    printf("enter company address : \n");
    getchar();
    gets(address);
    FILE* fpt;
    fpt = fopen("employer.csv", "a");
    fprintf(fpt, "%s,%s,%s,%s,%s,%s,%s\n", id, password, name, email, phone, city, address);
    fclose(fpt);
    printf("sign up succseful \n");
    strcpy(curid, id);
    usertype = 2;

}
int checkifidexist(char id[50], char nameoffile[50])
{
    //this func get the id number and check if it exist and return the row his shown
    int row = 0;
    FILE* stream = fopen(nameoffile, "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        row++;
        char* tmp = _strdup(line);
        if (strcmp(getfield(tmp, 1), id) == 0)
        {
            fclose(stream);
            return row;
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(stream);
    return 0;
}
int checkpassword(char string[30])
{
    //this func get password and check if its ok password return 1 if its ok 0 if not
    int tmp = 0;
    for (int i = 0; i < strlen(string); i++)
    {
        if ((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z'))
        {
            tmp++;
            break;
        }
    }
    for (int i = 0; i < strlen(string); i++)
    {
        if ((string[i] >= '0' && string[i] <= '9'))
        {
            tmp++;
            break;
        }
    }
    if (tmp == 2)
        return 1;
    else
        return 0;
}
int checkpasswordtoid(char id[10], char password[30], char nameoffile[50])
{
    //this fun get the id and the password apper in the csv file and return 1 if its match 0 if not
    int row = checkifidexist(id, nameoffile);
    FILE* stream = fopen(nameoffile, "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = _strdup(line);
        row--;
        if (row != 0)
            continue;
        if (strcmp(getfield(tmp, 2), password) == 0)
        {
            fclose(stream);
            return 1;
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(stream);
    return 0;

}
void signincandid()
{
    char id[10];
    strcpy(id, entergoodid());
    int row = checkifidexist(id,"candidate.csv");
    while (row == 0)
    {
        printf("doesnt exist\n");
        strcpy(id, entergoodid());
        row = checkifidexist(id, "candidate.csv");
    }
    char password[30];
    printf("enter password\n");
    scanf("%s", &password);
    while (checkpasswordtoid(id, password, "candidate.csv") == 0)
    {
        printf("wrong!, enter password again\n");
        scanf("%s", &password);
    }
    printf("sign in succseful \n");
    strcpy(curid, id);
    usertype = 1;

}
void candidentermenu()
{
    int choice;
    printf("Please choose:\n");
    printf("1 - Log in\n");
    printf("2 - Create New Account\n");
    printf("0 - Back to the main menu \n");
    scanf("%d", &choice);
    while (choice != 1 && choice != 2 && choice != 0)
    {
        printf("Please choose one of the option:\n");
        printf("1 - Log in\n");
        printf("2 - Create New Account\n");
        printf("0 - Back to the main menu \n");
        scanf("%d", &choice);
    }
    if (choice == 1)
        signincandid();
    else if (choice == 2)
        signupcandid();
    else if (choice == 0)
        mainmenu();
}
void mainmenu()
{
    char choice[30];
    printf("Welcome to the Search High.Job\n");
    printf("Please choose:\n");
    printf("1 - I'm Candidate\n");
    printf("2 - I'm Employer\n");
    printf("0 - For Exit\n");
    scanf("%s", &choice);
    while ((choice[0] < '0' || choice[0] >'2') || strlen(choice)!=1)
    {
        if (!choice)
            exit(0);
        printf("Please choose one of the option:\n");
        printf("1 - I'm Candidate\n");
        printf("2 - I'm Employer\n");
        printf("0 - For Exit\n");
        scanf("%s", &choice);
    }
    if (strcmp(choice,"1")==0)
        candidentermenu();
    else if (strcmp(choice, "2") == 0)
        employerentermenu();
    else if (strcmp(choice, "0") == 0)
        exit(0);

}
char* questionnaire(int type)//type 1 for candid 2 for emlo
{
    int tmp;
    char retanswer[10];
    char answer[10];
    char choice='0';
    if (type == 2)
    {
        printf("You will receive a questionnaire that the candidate has received to complete\n");
        printf("Please choose the answer you want the candidate to choose.\n");
        printf("If there is a question that is not relevant to the job or to your requirements, choose the option 0.\n");
        printf("The questionnaire is created to find a match between the employer and the candidate.\n");
        printf("Then, the system will match and will show you the best candidates for the job in ascending order.\n");
    }
    while (choice < 'a' || choice>'k')
    {
        printf("Please select one of the following:\n");
        printf("* What job are you looking for ?\n");
        printf("software:\n");
        printf("a - developer\n");
        printf("b - manager\n");
        printf("c - automation\n");
        printf("d - solution architect\n");
        printf("e - data engineer / analyst\n");
        printf("electric engineering:\n");
        printf("f - chip design\n");
        printf("g - high voltage\n");
        printf("h - signal processing\n");
        printf("industrial and management engineering:\n");
        printf("i - low tech management\n");
        printf("g - data and information systems\n");
        printf("k - PMO\n");
        scanf(" %c", &choice);
    }
    answer[0] = choice;
    choice = 'z';
    while ((choice < '1' || choice>'5')&&(!(type==2 && choice=='0')))
    {
        printf("Please select one of the following:\n");
        printf("* What is your education?\n");
        printf("1 - Course\n");
        printf("2 - Practical Engineer\n");
        printf("3 - B.Tech\n");
        printf("4 - B.A.\n");
        printf("5 - B.Sc\n");
        if (type == 2)
            printf("0 - Does not matter \n");
        scanf(" %c", &choice);
    }
    answer[1] = choice;
    choice = 'z';
    while ((choice < '1' || choice>'3' )&& (!(type == 2 && choice == '0')))
    {
        printf("Please select one of the following:\n");
        printf("* How many years of experience do you have?\n");
        printf("1 - Junior(0 - 3 years)\n");
        printf("2 - Intermediate(3 - 5 years)\n");
        printf("3 - Senior(5 + years)\n");
        if (type == 2)
            printf("0 - Does not matter \n");
        scanf(" %c", &choice);
    }
    answer[2] = choice;
    choice = 'z';
    while ((choice < '1' || choice>'5') && (!(type == 2 && choice == '0')))
    {
        printf("Please select one of the following:\n");
        printf("* What type of job are you looking for?\n");
        printf("1 - Full - time\n");
        printf("2 - Part - time\n");
        printf("3 - Internship\n");
        printf("4 - temporary\n");
        printf("5 - Student servant\n");
        if (type == 2)
            printf("0 - Does not matter \n");
        scanf(" %c", &choice);
    }
    answer[3] = choice;
    choice = 'z';
    while ((choice < '1' || choice>'7' )&& (!(type == 2 && choice == '0')))
    {
        printf("Please select one of the following:\n");
        printf("* In what area do you prefer to work?\n");
        printf("1 - North\n");
        printf("2 - Sharon\n");
        printf("3 - Center\n");
        printf("4 - Jerusalem\n");
        printf("5 - South\n");
        printf("6 - Abroad\n");
        printf("7 - From home\n");
        if (type == 2)
            printf("0 - Does not matter \n");
        scanf(" %c", &choice);
    }
    answer[4] = choice;
    choice = 'z';
    while ((choice < '1' || choice>'4') && (!(type == 2 && choice == '0')))
    {
        printf("Please select one of the following:\n");
        printf("* What is your salary requirement?\n");
        printf("1 - 5,000 - 8,000\n");
        printf("2 - 8,000 - 12,000\n");
        printf("3 - 12,000 - 17,000\n");
        printf("4 - +17,000\n");
        if (type == 2)
            printf("0 - Does not matter \n");
        scanf(" %c", &choice);
    }
    answer[5] = choice;
    choice = 'z';
    while ((choice < '1' || choice>'4') && (!(type == 2 && choice == '0')))
    {
        printf("Please select one of the following:\n");
        printf("* What is your English level?\n");
        printf("1 - Basic English\n");
        printf("2 - Good English\n");
        printf("3 - Native English level\n");
        printf("4 - Does not speak English at all\n");
        if (type == 2)
            printf("0 - Does not matter \n");
        scanf(" %c", &choice);
    }
    answer[6] = choice;
    choice = 'z';
    while ((choice < '1' || choice>'2') && (!(type == 2 && choice == '0')))
    {
        printf("Please select one of the following:\n");
        printf("* Do you agree to a relocation (if you need to)?\n");
        printf("1 - Yes\n");
        printf("2 - No\n");
        if (type == 2)
            printf("0 - Does not matter \n");
        scanf(" %c", &choice);
    }
    answer[7] = choice;
    choice = 'z';
    while ((choice < '1' || choice>'3') && (!(type == 2 && choice == '0')))
    {
        printf("Please select one of the following:\n");
        printf("* Do you have a driver license?\n");
        printf("1 - Driving license for a car\n");
        printf("2 - Driving license for a motorcycle\n");
        printf("3 - Driving license for car and motorcycle\n");
        if (type == 2)
            printf("0 - Does not matter \n");
        scanf(" %c", &choice);
    }
    answer[8] = choice;
    answer[9] = '\0';
    tmp = strlen(answer);
    /*for (int i = 0; i < 10; i++)
        retanswer[i] = answer[i];
    tmp = strlen(retanswer);*/
    return answer;
}
int main()
{
    mainmenu();
    while (true)
    {
        system("cls");
        if (usertype == 1)
        {
            printf("you log in as candid\n");
            candidmenu();

        }
        else if (usertype == 2)
        {
            printf("you log in as emploe\n");
            employermenu();
        }
    }
    return 0;
}