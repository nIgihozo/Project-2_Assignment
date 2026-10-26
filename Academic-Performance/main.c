#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_COURSE 10
#define PASS_TRESHOLD 50.0f
#define STUDENT_ID 54321

// Students records Structure

typedef struct {
    int id;
    char name[MAX_COURSE];
    char course[MAX_COURSE];
    float grades;
} Student;

// Function Prototypes

void add_student(Students, **students, int *count);
void display_students(Student, **students, int *count);
void sort_students(Student, **students, int *count);
void calculate_average(Student, **students, int *count);
void find_top_student(Student, **students, int *count);
void search_student(Student, **students, int *count);
void remove_student(Student, **students, int *count);
void custom_analysis(Student, **students, int *count);
void generate_summary_report(Student, **students, int *count);

// Displaying Headers
void headers_display {
    printf("\nOutput Headers\n");
    printf("Student ID: %s\n", STUDENT_ID);
    printf("Project: Dynamic Academic Performance and Risk Analysis Engine\n");
    printf("Custom Analysis: Academic Risk Index\n");
}

int main(void) {
    int count = 10;
    // Dynamically allocate the initial dataset for the 10 students
    Student **students = (Student)

    // 10 Initial Students Dataset
    Student initial_data[10] = {
        {101, "Celine IRAKOZE", "Networking", 85.5f},
        {102, "Gabin IGABA", "Law", 75.0f},
        {103, "Angel MUGISHA", "Industrial IT", 80.7f},
        {104, "Cynthia IKIREZI", "Law", 65.0f},
        {105, "Jane K GASINGE", "Networking", 50.0f},
        {106, "Gideon DRE", "Mathematics", 35.5f},
        {107, "Eddy BYIRINGIRO", "Mathematics", 15.0f},
        {108, "King NDANYUZWE", "Network Maintainance", 90.0f},
        {109, "Kevin ISHIMWE", "Wireless Maintaince", 78.0f},
        {110, "Didier SHEMA", "Mathematics", 65.0f}
    };

    for (int i = 0; i < count; i++) {
        *(students + i) = initial_data[i]
    }

    // Function Pointers and Operations
    void (**menu_actions[])(Student **, int *) = {
        add_student,
        display_students,
        sort_students,
        calculate_average,
        find_top_student,
        search_student,
        remove_student,
        custom_analysis,
        generate_summary_report
    };

    int choice;
    do {
        headers_display();
        printf("\n MENU CHOICES\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Students Record\n");
        printf("3. Sort Students\n");
        printf("4. Calculate Average Grade\n");
        printf("5. Finding Top-Performing Student\n");
        printf("6. Search Student (ID / Names)\n");
        printf("7. Remove Student Record\n");
        printf("8. Run Custom Analysis\n");
        printf("9. Display Summary Records\n");
        printf("10. Exit The Program\n");
        printf("Enter your choice: \n");

    }
}