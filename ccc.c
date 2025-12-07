#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct student{
    int roll;
    char name[50];
    char sec[5];
    char branch[10];
    float marks;
};

char currentRole[10], currentUser[20];

int loginSystem();
void mainMenu();
void adminMenu();
void userMenu();
void guestMenu();
void staffMenu();

void addStudent();
void displayStudent();
void searchStudent();
void updateStudent();
void deleteStudent();

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    if (loginSystem()) {
        mainMenu();
    } else {
        printf("\nLogin Failed. Exiting...\n");
    }
    return 0;
}

int loginSystem() {
    char username[20], password[20];
    char fileUser[20], filePass[20], fileRole[10];

    printf("============= Login Screen ==============\n");
    printf("Username: ");
    scanf("%19s", username);
    printf("Password: ");
    scanf("%19s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("Error: credentials.txt not found!\n");
        return 0;
    }

    while (fscanf(fp, "%19s %19s %9s", fileUser, filePass, fileRole) == 3) {
        if (strcmp(username, fileUser) == 0 &&
            strcmp(password, filePass) == 0)
        {
            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void mainMenu() {
    if(strcmp(currentRole,"ADMIN")==0)
        adminMenu();
    else if (strcmp(currentRole,"STAFF")==0)
        staffMenu();
    else if (strcmp(currentRole,"GUEST")==0)
        guestMenu();
    else if (strcmp(currentRole,"USER")==0)
        userMenu();
}

/* ====================== ADMIN MENU ========================= */

void adminMenu(){
    int choice;
    do{
        clearScreen();
        printf("\n-----ADMIN MENU-----\n");
        printf("1.ADD STUDENT \n");
        printf("2.DISPLAY STUDENT \n");
        printf("3.SEARCH STUDENT \n");
        printf("4.UPDATE STUDENT \n");
        printf("5.DELETE STUDENT \n");
        printf("6.LOGOUT \n");
        printf("ENTER CHOICE: \n");
        scanf("%d",&choice);

        clearScreen();

        switch(choice){
            case 1:addStudent();break;
            case 2:displayStudent();break;
            case 3:searchStudent();break;
            case 4:updateStudent();break;
            case 5:deleteStudent();break;
            case 6:printf("Logging out\n");return;
            default: printf("Invalid choice!\n");
        }
        printf("\nPress Enter to continue...");
        getchar(); getchar();
    }while (1);
}

/* ====================== STAFF MENU ========================= */

void staffMenu() {
    int choice;
    do {
        clearScreen();
        printf("\n----- STAFF MENU -----\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearScreen();

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudent(); break;
            case 3: searchStudent(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
        printf("\nPress Enter to continue...");
        getchar(); getchar();
    } while (1);
}

/* ====================== GUEST MENU ========================= */

void guestMenu() {
    int choice;
    do {
        clearScreen();
        printf("\n----- GUEST MENU -----\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        clearScreen();
         
        switch(choice) {
            case 1: displayStudent(); break;
            case 2: searchStudent(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
        printf("\nPress Enter to continue...");
        getchar(); getchar();
    } while (1);
}

/* ====================== USER MENU ========================= */

void userMenu() {
    int choice;
    do {
        clearScreen();
        printf("\n----- USER MENU -----\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        clearScreen();

        switch(choice) {
            case 1: displayStudent(); break;
            case 2: searchStudent(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
        printf("\nPress Enter to continue...");
        getchar(); getchar();
    } while (1);
}


/* ---------- ADD STUDENT ---------- */
void addStudent() {
    struct student s;
    FILE *fp = fopen(STUDENT_FILE, "a");

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Roll: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Section: ");
    scanf("%s", s.sec);
    printf("Enter Branch: ");
    scanf("%s", s.branch);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %s %s %.2f\n", s.roll, s.name, s.sec, s.branch, s.marks);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

/* ---------- DISPLAY STUDENTS ---------- */
void displayStudent() {
    struct student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("ROLL\tNAME\tSECTION\tBRANCH\tMARKS\n");
    printf("------------------------------------------\n");

    while (fscanf(fp, "%d %s %s %s %f",
                  &s.roll, s.name, s.sec, s.branch, &s.marks) == 5)
    {
        printf("%d\t%s\t%s\t%s\t%.2f\n",
               s.roll, s.name, s.sec, s.branch, s.marks);
    }

    fclose(fp);
}

/* ---------- SEARCH STUDENT ---------- */
void searchStudent() {
    struct student s;
    int roll, found = 0;

    printf("Enter Roll to Search: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No file found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %s %s %f",
                  &s.roll, s.name, s.sec, s.branch, &s.marks) == 5)
    {
        if (s.roll == roll) {
            printf("\nRecord Found:\n");
            printf("ROLL: %d\nNAME: %s\nSECTION: %s\nBRANCH: %s\nMARKS: %.2f\n",
                   s.roll, s.name, s.sec, s.branch, s.marks);
            found = 1;
            break;
        }
    }

    fclose(fp);
    if (!found) printf("Record Not Found!\n");
}

/* ---------- UPDATE STUDENT ---------- */
void updateStudent() {
    struct student s;
    int roll, found = 0;

    printf("Enter Roll to Update: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    while (fscanf(fp, "%d %s %s %s %f",
                  &s.roll, s.name, s.sec, s.branch, &s.marks) == 5)
    {
        if (s.roll == roll) {
            found = 1;

            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Section: ");
            scanf("%s", s.sec);
            printf("Enter New Branch: ");
            scanf("%s", s.branch);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }

        fprintf(temp, "%d %s %s %s %.2f\n",
                s.roll, s.name, s.sec, s.branch, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Record Updated Successfully!\n");
    else
        printf("Record Not Found!\n");
}

/* ---------- DELETE STUDENT ---------- */
void deleteStudent() {
    struct student s;
    int roll, found = 0;

    printf("Enter Roll to Delete: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    while (fscanf(fp, "%d %s %s %s %f",
                  &s.roll, s.name, s.sec, s.branch, &s.marks) == 5)
    {
        if (s.roll == roll) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d %s %s %s %.2f\n",
                s.roll, s.name, s.sec, s.branch, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Record Deleted Successfully!\n");
    else
        printf("Record Not Found!\n");
}

