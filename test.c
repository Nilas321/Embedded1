#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_NAME_LEN 50
#define MAX_STREET_LEN 50
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

void main(){
    student *new_student = (student *)malloc(sizeof(student));

    new_student->name = (char *)malloc(MAX_NAME_LEN * sizeof(char));

    new_student->addr.street = (char *)malloc(MAX_STREET_LEN * sizeof(char));
    
    new_student->addr.city = (char *)malloc(MAX_CITY_LEN * sizeof(char));
    
    new_student->addr.zip = (char *)malloc(MAX_ZIP_LEN * sizeof(char));

    char s[MAX_BUFFER_LEN] = "John 20 A CS 123-Main-St Springfield 12345";
    char result[100];
    char temp_grade[2];
    char temp_major[3];
    sscanf(s, "%s %d %s %s %s %s %s", 
           new_student->name, 
           &new_student->age, 
           temp_grade, 
           temp_major, 
           new_student->addr.street,
           new_student->addr.city, 
           new_student->addr.zip);

    new_student->grade = str_to_enum_grade(temp_grade);
    new_student->major = str_to_enum_major(temp_major);

    printf("Name: %s\n", new_student->name);
    printf("Age: %d\n", new_student->age);
    printf("Grade: %d\n", new_student->grade);
    printf("Major: %d\n", new_student->major);
    printf("Address: %s, %s, %s\n", new_student->addr.street, new_student->addr.city, new_student->addr.zip);
    free(new_student->name);
    free(new_student->addr.street);
    free(new_student->addr.city);   
    free(new_student->addr.zip);
    free(new_student);
    return;
};