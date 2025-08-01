#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_STREET_LEN 100
#define MAX_CITY_LEN 50
#define MAX_ZIP_LEN 10

//Assuming buffer length of 3 for age, the maximum buffer for an input is sum of all + 3 for grade and major + 5 for whitespace and null terminator
#define MAX_BUFFER_LEN (MAX_NAME_LEN + MAX_STREET_LEN + MAX_CITY_LEN + MAX_ZIP_LEN + 10)

typedef enum{
    F = 1,
    D,
    C,
    B,
    A
} GRADE;

typedef enum{
    CS = 1,
    EE,
    ME,
    CE,
    BIO

}MAJOR;

typedef struct {
    char *street;
    char *city;
    char *zip;

}address ;

typedef struct {
    char *name;
    int age;
    GRADE grade;
    MAJOR major;
    address addr;
}student ;

GRADE str_to_enum_grade(const char *str) {
    if (strcmp(str, "F") == 0) return F;
    if (strcmp(str, "D") == 0) return D;
    if (strcmp(str, "C") == 0) return C;
    if (strcmp(str, "B") == 0) return B;
    if (strcmp(str, "A") == 0) return A;
    return -1; // Invalid grade
};

MAJOR str_to_enum_major(const char *str) {
    if (strcmp(str, "CS") == 0) return CS;
    if (strcmp(str, "EE") == 0) return EE;
    if (strcmp(str, "ME") == 0) return ME;
    if (strcmp(str, "CE") == 0) return CE;
    if (strcmp(str, "BIO") == 0) return BIO;
    return -1; // Invalid major
};

char *enum_to_str_grade(GRADE grade) {
    switch (grade) {
        case F: return "F";
        case D: return "D";
        case C: return "C";
        case B: return "B";
        case A: return "A";
        default: return "Invalid Grade";
    }
}

char *enum_to_str_major(MAJOR major) {
    switch (major) {
        case CS: return "CS";
        case EE: return "EE";
        case ME: return "ME";
        case CE: return "CE";
        case BIO: return "BIO";
        default: return "Invalid Major";
    }
}

void display_student(student *students, int n) {
    for (int i = 0; i < n; i++) {
        student *s = &students[i];

        printf("Name: %s,", s->name);
        printf(" Age: %d,", s->age);
        printf(" Grade: %s,", enum_to_str_grade(s->grade));
        printf(" Major: %s,", enum_to_str_major(s->major));
        printf(" Address: %s, %s, %s \n", s->addr.street, s->addr.city, s->addr.zip);
    }
}
void mem_free(student *students, int n) {
    for (int i = 0; i < n; i++) {
        free(students[i].name);
        free(students[i].addr.street);
        free(students[i].addr.city);
        free(students[i].addr.zip);
    }
    free(students);
    return;
}
void create_student(student *new_student) {
        new_student->name = (char *)malloc(MAX_NAME_LEN * sizeof(char));
        new_student->age = 0;
        new_student->addr.street = (char *)malloc(MAX_STREET_LEN * sizeof(char));   
        new_student->addr.city = (char *)malloc(MAX_CITY_LEN * sizeof(char));    
        new_student->addr.zip = (char *)malloc(MAX_ZIP_LEN * sizeof(char));
        
        char result[100];
        char temp_grade[2];
        char temp_major[3];
        scanf("%s %d %s %s %s %s %s", 
               new_student->name, 
               &new_student->age, 
               temp_grade, 
               temp_major, 
               new_student->addr.street,
               new_student->addr.city, 
               new_student->addr.zip);

        new_student->grade = str_to_enum_grade(temp_grade);
        new_student->major = str_to_enum_major(temp_major);
}

void update_student(student *students,int n){
    char temp_name[MAX_NAME_LEN];
    char temp_grade[2];
    scanf("%s %s",temp_name, temp_grade);

    for (int i = 0; i < n; i++) {
        if (strcmp(students[i].name, temp_name) == 0) {
            students[i].grade = str_to_enum_grade(temp_grade);
            //printf("Updated Grade for %s: %s\n", students[i].name, enum_to_str_grade(students[i].grade));
            return;
        }
    }
    
}


int main() {
    int n;
    scanf("%d", &n);
    student *students = NULL;
    students = (student *)malloc(sizeof(student) * n);  // Pointer to hold array of students
    for (int i = 0; i < n; i++) {
        create_student(&students[i]);
        };

    
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char command[10];
        scanf("%s", command);
        if (strcmp(command, "ADD") == 0) {
            n++;
            students = (student *)realloc(students, sizeof(student) * n);
            create_student(&students[n - 1]);  // Add new student at the end of the array
            // TODO: Read and add new student (resize array if needed)
        } 
        else if (strcmp(command, "UPDATE") == 0) {
            update_student(students, n);
            // TODO: Read name and new grade, update student
        } 
        else if (strcmp(command, "PRINT") == 0) {
            display_student(students,n);
            // TODO: Print all students
        }
    }

    // Free the allocated memory for students array
    mem_free(students, n);
    return 0;

};

