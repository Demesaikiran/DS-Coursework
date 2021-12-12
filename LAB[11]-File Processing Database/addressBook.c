#include<stdio.h>
#include<stdlib.h>


#define MAXSIZE 100

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
 * @brief string utility functions
 *  
 */

int strcmp(const char *, const char *);
char * strcpy(char *, const char *);

/**
 * @brief ADDRESS BOOK Utility functions
 * 
 */
int insertStudent(char *);
void ModifyStudent(char *);
void studentInfo(char *);
void deleteStudent(char *, int);
void displayDatabase(char *);



int main(int argc, char * argv[])
{
    int choice;
    char * filename = argv[1];
    FILE * filemaking = fopen(filename, "ab+");
    fclose(filemaking);
    deleteStudent(filename, 1);
    
    do
    {
        printf("========================= \nAddress Book\n=========================\n");
        printf("[1] Add New student\n[2] Modify Student record\n[3] Search Student\n[4] Delete Student record\n[5] Display Database\n[6] Exit Application\n\nEnter your choice: ");
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
                studentInfo(filename);
                break;
            }

            case 4:
            {
                int choice2;
                printf("\n\nDELETION MECHANISM:\n[1] Delete student records based on #DELETE# entries\n[2] Delete by rollno\n");
                printf("\nEnter your choice of type of deletion [1] / [2]: ");
                scanf("%d", &choice2);

                deleteStudent(filename, choice2);
                break;
            }

            case 5:
            {
                displayDatabase(filename);
                break;
            }

            case 6:
            {
                exit(0);
            }

            default:
                break;
        }

    } while (choice >=1 && choice <= 5);
    
}

int strcmp(const char * s1, const char * s2)
{
    int flag = 0;
    while(*s1 != '\0' && *s2 != '\0')
    {
        if(*s1 != *s2) flag = 1;
        s1++;
        s2++;
    }
    return flag == 0 ? 0 : 1;

}

char * strcpy(char * destination, const char * source)
{
    if(destination == NULL) return NULL;

    char * pointer = destination;
    while(* source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';

    return pointer;

}


int insertStudent(char * filename)
{
    FILE * database = fopen(filename, "rb+");
    record db;

    if(database == NULL)
    {
        printf("\n\nCannot open the file %s\n\n", filename);
        return 0;
    }

    long int recordSize = sizeof(db);
    char choice = 'Y';

    system("clear");

    fseek(database, 0, SEEK_END);
    while(choice == 'Y' || choice == 'y')
    {

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

        fwrite(&db, recordSize, 1, database);
        printf("\n\nRecord added to the %s storage successfully...", filename);

        printf("\n\nDo you want to add more records? [Y / N]: ");
        getchar();
        scanf("%c", &choice);
    }
    fclose(database);
    // Returning 1 for successful operations happend in the function.
    return 1;
}

void ModifyStudent(char * filename)
{
    FILE * database = fopen(filename, "rb+");
    record db;
    char rollno[MAXSIZE];

    if(database == NULL)
    {
        printf("\n\nCannot open the file %s\n\n", filename);
    }

    long int recordSize = sizeof(db);
    char choice = 'Y';
    system("clear");

    while(choice == 'Y' || choice == 'y')
    {
        printf("\n\nEnter the rollno of the student to modify the record: ");
        scanf("%s", rollno);
        getchar();

        rewind(database);
        int isExists = 0;
        while(fread(&db, recordSize, 1, database) == 1)
        {
            if(strcmp(db.rollno, rollno) == 0)
            {
                isExists =1;
                printf("\n\nStudent Information based on ROLLNO: \n\n");
                printf("ROLL NO:    %s", db.rollno);
                printf("\nNAME:     %s", db.name);
                printf("\nNUMBER:   %s", db.number);
                printf("\nEMAIL:    %s", db.email);
                printf("\nADDRESS:  %s\n\n", db.address);

                printf("--------------------------------------\nEnter the new details to modify the record:\n--------------------------------------\n");


                char choice2;
                printf("\nDo you want to edit the rollno of the student %s [Y / N]: ", rollno);
                scanf("%c", &choice2);
                if(choice2 == 'Y' || choice2 == 'y')
                {
                    printf("\nEnter Student new rollno: ");
                    scanf("%s", db.rollno);
                    //printf("\n%s\n", db.rollno);
                    fflush(stdin);
                }

                printf("\nDo you want to edit the name of the student %s [Y / N]: ", rollno);
                getchar();
                scanf("%c", &choice2);
                if(choice2 == 'Y' || choice2 == 'y')
                {
                    printf("\nEnter Student new name: ");
                    scanf("%s", db.name);
                    printf("\n%s\n",db.name);
                    fflush(stdin);
                }
                
                printf("\nDo you want to edit the contact number of the student %s [Y / N]: ", rollno);
                getchar();
                scanf("%c", &choice2);
                if(choice2 == 'Y' || choice2 == 'y')
                {
                    printf("\nEnter Student new contact number: ");
                    scanf("%s", db.number);
                    fflush(stdin);
                }
                
                printf("\nDo you want to edit the email address of the student %s [Y / N]: ", rollno);
                getchar();
                scanf("%c", &choice2);
                if(choice2 == 'Y' || choice2 == 'y')
                {
                    printf("\nEnter Student new email address: ");
                    scanf("%s", db.email);
                    fflush(stdin);
                }

                printf("\nDo you want to edit the address of the student %s [Y / N]: ", rollno);
                getchar();
                scanf("%c", &choice2);
                if(choice2 == 'Y' || choice2 == 'y')
                {
                    printf("\nEnter Student new address: ");
                    scanf("%s", db.address);
                    fflush(stdin);
                }

                fseek(database, -recordSize, SEEK_CUR);
                fwrite(&db, recordSize, 1, database);
                break;

            }
        }
        if(isExists == 0)
        {
            printf("\n\nThere is no record found with the rollno %s\n\n", rollno);
        }
        else
        {
            printf("\n\nModified the data record of %s successfully...\n", rollno);
        }

        printf("\nDo you want to modify another record [Y / N]: ");
        getchar();
        scanf("%c", &choice);
    }
    printf("\n\n");
    system("clear");
    fclose(database);
}

void studentInfo(char * filename)
{
    FILE * database = fopen(filename, "rb");
    record db;
    char name[MAXSIZE];

    if(database == NULL)
    {
        printf("\n\nCannot open the file %s\n\n", filename);
    }

    long int recordSize = sizeof(db);
    char choice = 'Y';
    system("clear");

    while(choice == 'Y' || choice == 'y')
    {
        int flag = 0;
        printf("\n\nEnter the name of the student: ");
        scanf("%s", name);

        rewind(database);
        while(fread(&db, recordSize, 1, database) == 1)
        {
            if(strcmp(db.name, name) == 0)
            {
                flag = 1;
                printf("\n\nStudent Information based on Name: \n\n");
                printf("ROLL NO:    %s", db.rollno);
                printf("\nNAME:     %s", db.name);
                printf("\nNUMBER:   %s", db.number);
                printf("\nEMAIL:    %s", db.email);
                printf("\nADDRESS:  %s\n\n", db.address);

            }
        }
        if(flag == 0)
        {
            printf("\n\nNo record found with name %s\n", name);
        }

        printf("\nDo you want to search for another record [Y / N]: ");
        getchar();
        scanf("%c", &choice);
    }
    system("clear");
    fclose(database);
}

void deleteStudent(char * filename, int option)
{
    FILE * database; 
    record db;
    char rollno[MAXSIZE];

    if((database= fopen(filename, "rb+")) == NULL)
    {
        printf("\n\nCannot open the file %s\n\n", filename);
    }
    char deleteref[MAXSIZE] = "#DELETE#";

    long int recordSize = sizeof(db);
    char choice = 'Y';
    system("clear");


    char * tempfile = "temp.dat";
    FILE * tempdb = fopen(tempfile, "wb");
    rewind(database);
    if(option == 2)
    {
        printf("Enter the rollno of the student to delete the record: ");
        scanf("%s", rollno);
        fflush(stdin);
        getchar();
        strcpy(deleteref, rollno);
    }

    while(fread(&db, recordSize, 1, database) == 1)
    {
        int check = (strcmp(db.rollno, deleteref) != 0);
        printf("\n%d\n",check);
        if(check)
            fwrite(&db, recordSize, 1, tempdb);
    }
    fclose(database);
    fclose(tempdb);
    remove(filename);
    rename(tempfile, filename);

}

void displayDatabase(char * filename)
{
    FILE * database = fopen(filename, "rb");
    record db;
    long int recordSize = sizeof(db);

    if(database == NULL)
    {
        printf("\n\nCannot open the file %s\n\n", filename);
    }

    system("clear");
    int checkEmpty = 0;
    printf("\nROLLNO\t\tNAME\t\tCONCTACT\tEMAIL\t\tADDRESS\n\n");
    while(fread(&db, recordSize, 1, database) == 1)
    {
        checkEmpty = 1;
        printf("\n%s\t%s\t%s\t%s\t%s\n", db.rollno, db.name, db.number, db.email, db.address);
    }
    printf("\n\n");

    if(checkEmpty == 0)
    {
        printf("\n\nThe database file is empty...\n\n");
    }
}
