#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 200

#define ROLLNUMBER 20
#define NAME 50
#define NUMBER 20
#define EMAIL 30
#define ADDRESS 50

struct addressbook
{
    char rollno[ROLLNUMBER];
    char name[NAME];
    char number[NUMBER];
    char email[EMAIL];
    char address[ADDRESS];
};

typedef struct addressbook record;


/**
 * @brief ADDRESS BOOK Utility functions
 * 
 */
int insertStudent(char *);
void ModifyStudent(char *);
void studentInfo(char *, char*);
void deleteStudent(char *, int);


int main(int argc, char * argv[])
{
    int choice;
    char * filename = argv[1];
    deleteStudent(filename, 1);
    
    do
    {
        printf("========================= \nAddress Book\n=========================\n");
        printf("[1] Add New student\n[2] Modify Student record\n[3] Search Student\n[4] Delete Student record\n[5] Exit Application\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                if(insertStudent(filename))
                {
                    printf("\nInserted student record successfully...\n\n");
                }
                else
                {
                    printf("\nError in inserting a student record...\n\n");
                }
                break;
            }

            case 2:
            {
                ModifyStudent(filename);
                break;
            }
            
            case 3:
            {
                char target[MAXSIZE];
                system("clear");
                printf("\nStudent Name: ");
                scanf("%s", target);
                studentInfo(filename, target);
                break;
            }

            case 4:
            {
                int choice2;
                printf("\n\nDELETION MECHANISM:\n[1] Delete student records based on #DELETE# entries\n[2] Delete by name\n");
                printf("\nEnter your choice of type of deletion [1] / [2]: ");
                scanf("%d", &choice2);

                deleteStudent(filename, choice2);
                break;
            }

            case 5:
            {
                exit(0);
                break;
            }

            default:
                break;
        }

    } while (choice >=1 && choice <= 5);
    
}

int insertStudent(char * filename)
{
    record db;
    FILE * database = fopen(filename, "ab+");
    if(!database)
    {
        printf("ERROR IN DEALING WITH FILE %s", filename);
        return 0;
    }

    system("clear");

    printf("\nEnter Student Roll number: ");
    scanf("%s", db.rollno);



    printf("\nEnter Student name: ");
    scanf("%s", db.name);

    printf("\nEnter the student contact number: ");
    scanf("%s", db.number);

    printf("\nEnter the student email address: ");
    scanf("%s", db.email);

    printf("\nEnter the student address: ");
    scanf("%s", db.address);

    fprintf(database, "%s %s %s %s %s \n", db.rollno, db.name, db.number, db.email, db.address);
    fclose(database);

    return 1;
    
}

void ModifyStudent(char * filename)
{
    record db;
    char * tempfile = "tempdb.dat";
    FILE * database = fopen(filename, "r");
    FILE * tempdb = fopen(tempfile, "w");

    char target[MAXSIZE];
    
    if(database == NULL)
    {
        printf("\n\nThe File is Empty...\n\n");
        return;
    }

    else
    {
        printf("\nEnter Student RollNo to Modify: ");
        scanf("%s", target);
        while(!feof(database))
        {
            printf("Hello");
            fscanf(database, "%s %s %s %s %s ", db.rollno, db.name, db.number, db.email,  db.address);


            if(strcmp(target, db.rollno) != 0)
            {
                fprintf(tempdb, "%s %s %s %s %s \n", db.rollno, db.name, db.number, db.email, db.address);
            }
            else
            {
                record temp;
                
                char edit = 'Y';
                char buffer[MAXSIZE];

                while(edit == 'Y' || edit == 'y')
                {
                    printf("\n\nStudent Information based on ROLLNO: \n\n");
                    printf("ROLL NO:    %s", db.rollno);
                    printf("\nNAME:     %s", db.name);
                    printf("\nNUMBER:   %s", db.number);
                    printf("\nEMAIL:    %s", db.email);
                    printf("\nADDRESS:  %s\n\n", db.address);
                    printf("--------------------------------------\nSelect what you wanted to modify:\n--------------------------------------\n[1] Rollno\n[2] Name\n[3] Number\n[4] Email address\n[5] Address\n\nEnter your choice: ");
                    char choice;
                    getchar();
                    scanf("%c\n", &choice);

                    switch(choice)
                    {
                        case 1:
                            {
                                printf("\nEnter the new Rollno: ");
                                scanf("%s", db.rollno);
                                printf(" Modified Roll to '%s'\n\n", db.rollno);
                                break;
                            }

                        case 2:
                            {
                                printf("\nEnter the new name: ");
                                scanf(" %s", db.name);
                                printf("Modified the Name to '%s'\n\n", db.name);
                                break;
                            }

                        case 3:
                            {
                                printf("\nEnter the new number: ");
                                scanf(" %s", db.number);
                                printf("Modified the number to '%s'\n\n", db.number);
                                break;
                            }

                        case 4:
                            {
                                printf("\nEnter the new email address: ");
                                scanf("%s", db.email);
                                printf("Modified the email address to '%s'\n\n", db.email);
                                break;
                            }

                        case 5:
                            {
                                printf("\nEnter the new address: ");
                                scanf("%s", db.address);
                                printf("Modified the address to '%s' \n\n", db.address);
                                break;
                            }
                    }
                    printf("Do you want to save or edit the student roll no %s [Y / N]  ", db.rollno);
                    scanf("%c", &edit);
                }
                printf("\n\nModified the record successfully...\n\n");
                fprintf(tempdb, "%s %s %s %s %s \n", db.rollno, db.name, db.number, db.email, db.address);
            }

                
        }
    }

        fclose(database);
        //remove(filename);
        fclose(tempdb);
        rename(tempfile, filename);
}

void studentInfo(char * filename, char * target)
{
    
    int flag_found = 0;
    FILE * database = fopen(filename, "r");
    record db;

    if(database == NULL)
    {
        printf("\n\nThe File is Empty...\n\n");
        return;
    }
    else
    {
        

        // while(!feof(database))
        while(fread(&db, sizeof(db), 1, database))
        {
            //fscanf(database, "%s %s %s %s %s ", db.rollno, db.name, db.number, db.email, db.address);
            
            if((strcmp(target, db.name) == 0) && (strcmp("#DELETE#", db.rollno) != 0))
            {
                flag_found = 1;

                printf("ROLL NO:    %s", db.rollno);
                printf("\nNAME:     %s", db.name);
                printf("\nNUMBER:   %s", db.number);
                printf("\nEMAIL:    %s", db.email);
                printf("\nADDRESS:  %s\n\n", db.address);

            }
        }
        if(!flag_found)
        {
            printf("\n\nThere is no record with that name...\n\n");
            fclose(database);
            return;
        }
        fclose(database);
    }
}

void deleteStudent(char * filename, int option)
{
    record db;
    char * tempfile = "tempdb.dat";
    FILE * database = fopen(filename, "rb");
    FILE * backup = fopen("backup.dat", "wb");
    FILE * tempdb = fopen(tempfile, "wb");
    char  deleteRef[MAXSIZE] = "#DELETE#";

    char target[MAXSIZE];
    
    if(database == NULL)
    {
        printf("\n\nThe File is Empty...\n\n");
        return;
    }

    if(option == 2)
    {
        printf("\nEnter Student Name: ");
        scanf("%s", target);
        strcpy(deleteRef, target);
    }

    while(fread(&db, sizeof(db), 1, database))
    {
        printf("\n\n%s\n%s\n\n", deleteRef, db.rollno);
        if(strcmp(deleteRef, db.rollno))
        {
            fwrite(&db, sizeof(db), 1, tempdb);
        }
        else
        {
            fwrite(&db, sizeof(db), 1, backup);
        }
    }
    /* 
    while(!feof(database))
    {
        fscanf(database, "%s %s %s %s %s", db.rollno, db.name, db.number, db.email,  db.address);

        if(feof(database))
            break;
        
        switch (option)
        {
            case 1:
                {
                    int x = strcmp(deleteRef, db.rollno);
                    printf("%d",x);
                    if(x)
                    {
                        printf("\n..\n");
                        fprintf(tempdb, "%s %s %s %s %s \n", db.rollno, db.name, db.number, db.email, db.address);
                    }
                    else
                    {
                        printf("\n..1\n");
                        fprintf(backup, "%s %s %s %s %s \n", db.rollno, db.name, db.number, db.email, db.address);
                    }
                }
            case 2:
                {
                    if(strcmp(target, db.name) != 0)
                    {
                        printf("\n..\n");
                        fprintf(tempdb, "%s %s %s %s %s \n", db.rollno, db.name, db.number, db.email, db.address);
                    }
                    else
                    {
                        printf("\n..1\n");
                        fprintf(backup, "%s %s %s %s %s \n", db.rollno, db.name, db.number, db.email, db.address);
                    }
                }
            
            default:
                break;
        }
    } */
    fclose(database);
    fclose(tempdb);
    fclose(backup);
    int y = remove(filename);

    printf("\n\nDELETED record/'s successfully...\n\n");
    rename(tempfile, filename);

}