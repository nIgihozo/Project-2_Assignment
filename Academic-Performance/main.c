#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_COURSE 50
#define PASS_THRESHOLD 50.0f
#define STUDENT_ID "54321"

// Students records Structure

typedef struct {
    int id;
    char name[MAX_NAME];
    char course[MAX_COURSE];
    float grade;
} Student;

// Function pointer for the menu actions
typedef void(*MenuAction)(Student **, int *);
// Function Prototypes

void headers_display(void);
void add_student(Student **students, int *count);
void display_students(Student **students, int *count);
void sort_students(Student **students, int *count);
void calculate_average(Student **students, int *count);
void find_top_student(Student **students, int *count);
void search_student(Student **students, int *count);
void remove_student(Student **students, int *count);
void custom_analysis(Student **students, int *count);
void generate_summary_report(Student **students, int *count);

// Displaying Headers
void headers_display (void) {
    printf("\nOutput Headers\n");
    printf("Student ID: %s\n", STUDENT_ID);
    printf("Project: Dynamic Academic Performance and Risk Analysis Engine\n");
    printf("Custom Analysis: Academic Risk Index\n");
}

int main(void) {
    int count = 10;
    // Dynamically allocate the initial dataset for the 10 students
    Student *students = (Student *)malloc(count * sizeof(Student));

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
        {110, "Didier SHEMA", "Mathematics", 65.0f},
    };

    for (int i = 0; i < count; i++) {
        *(students + i) = initial_data[i];
    }

    // Function Pointers and Operations
    MenuAction menu_actions[] = {
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

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please select number that are available on the menu list");
            while (getchar() != '\n'); // This is to clear the buffer
            continue;
        }
        if (choice >= 1 && choice <= 9) {
            menu_actions[choice - 1](&students, &count);
        } else if (choice == 10) {
            printf("Exiting program...\n");
        } else {
            printf("Choice is out of the range. Try again\n");
        }
    } while (choice != 10);

    // Dynamically free the allocated memory
    free(students);
    students = NULL;
    return 0;
}

// 1. Checking for student IDs duplicates
void add_student(Student **students, int *count) {
    int new_id;
    printf("Enter Student ID: ");
    scanf("%d", &new_id);

    // Check if that ID is already exists
    for (int i = 0; i < *count; i++) {
        if ((*students)[i].id == new_id) {
            printf("Alert: Student ID %d Already exist!\n", new_id);
            return;
        }
    }

    Student *temp = (Student *)realloc(*students, (*count + 1) * sizeof(Student));
    if (temp == NULL) {
        printf("Memory Reallocation Failled\n");
        return;
    }

    *students = temp;

    Student *new_student = *students + *count;
    new_student->id = new_id;

    printf("Enter full name: ");
    scanf(" %49[^\n]", new_student->name);
    printf("Enter Course: ");
    scanf(" %49[^\n]", new_student->course);
    do {
    printf("Enter Grade (0 -100): ");
    scanf("%f", &new_student->grade);
    if(new_student->grade < 0.0f || new_student->grade > 100.0f){
        printf("Invalid entered grades. Grades must ranged from 0 - 100 only!\n");
    }
    } while (new_student->grade < 0.0f || new_student->grade > 100.0f);

    (*count)++;
    printf("New student has been added successfully!! Total records: %d\n", *count);
}

//Display all students
void display_students(Student **students, int *count) {
    if (*count == 0) {
        printf("Alert: No students records found!!\n");
        return;
    }
    printf("\n%-6s | %-22s | %-6s\n", "ID", "NAME", "COURSE", "GRADE");
    printf("------------------------------------------------------------\n");

    // Traversal pointer-based
    Student *ptr = *students;
    Student *end = *students + *count;
    while (ptr < end ) {
        printf("%-6d | %-20s | %-22s | %-6.2f\n", ptr->id, ptr->name, ptr->course, ptr->grade);
        ptr++;
    }
}

// Sorting students by Names, ID, or Grade
void sort_students(Student **students, int *count) {
    if (*count < 2) {
        printf("\nNot enough records to continue with sorting.\n");
        return;
    }

    int sort_choice;
    printf("\nSort Options:\n1. Grade (High or Low)\n2. Name (A to Z)\n3.ID(High or Low)\nEnter Your Choice: ");
    if (scanf("%d", &sort_choice) != 1) {
        while(getchar() != '\n');
        return;
    }
    // Bubble sort standard
    for (int i = 0; i < *count - 1; i++) {
        for (int j = 0; j < *count - i - 1; j++) {
            int swap_needed = 0;
            if (sort_choice == 1 && (*students)[j].grade < (*students)[j + 1].grade){
                swap_needed = 1;
        } else if (sort_choice == 2 && strcmp((*students)[j].name, (*students)[j + 1].name) > 0 ) {
            swap_needed = 1;
        } else if (sort_choice == 3 && (*students)[j].id > (*students)[j + 1].id) {
           swap_needed = 1; 
        }

        if (swap_needed) {
            Student temp = (*students)[j];
            (*students)[j] = (*students)[j + 1];
            (*students)[j +1] = temp;
        }
    }
}

// Printing Sorted Students
printf("Records Sorted Successfully!.\n");
display_students(students, count);
}

//  Calculating Average Grades
void calculate_average(Student **students, int *count) {
    if (*count == 0) {
        printf("\nNo records that are available to calculate the avarage.\n");
        return;
    }

    float sum = 0.0f;
    for (Student *ptr = *students; ptr < *students + *count; ptr++) {
        sum += ptr->grade;
    }
    printf("\n Class Average Grade: %.2f\n", sum / *count);
}

// Find Top-Performing Student
void find_top_student(Student **students, int *count) {
    if (*count == 0) {
        printf("\nNo Records Available.\n");
        return;
    }

    Student *top = *students;
    for (Student *ptr = *students + 1; ptr < *students + *count; ptr++) {
        if (ptr->grade > top->grade) {
            top = ptr;
        }
    }

    printf("\nTop Student:\nID: %d | Name: %s | Course: %s | Grade: %.2f\n", top->id, top->name, top->course, top->grade);
}

// Search Student by ID or Name
// 6. Search Student by ID or Name
void search_student(Student **students, int *count) {
    if (*count == 0) {
        printf("\nNo records to search.\n");
        return;
    }

    int mode;
    printf("\nSearch By:\n1. Student ID\n2. Name\nChoice: ");
    if (scanf("%d", &mode) != 1) {
        while (getchar() != '\n');
        return;
    }

    if (mode == 1) {
        int search_id, found = 0;
        printf("Enter ID to search: ");
        scanf("%d", &search_id);
        for (int i = 0; i < *count; i++) {
            if ((*students)[i].id == search_id) {
                printf("Found: %d | %s | %s | %.2f\n",
                       (*students)[i].id, (*students)[i].name, (*students)[i].course, (*students)[i].grade);
                found = 1;
                break;
            }
        }
        if (!found) printf("No student found with ID %d.\n", search_id);
    } else if (mode == 2) {
        char search_name[MAX_NAME];
        int found = 0;
        printf("Enter Name to search: ");
        scanf(" %49[^\n]", search_name);
        for (int i = 0; i < *count; i++) {
            if (strcmp((*students)[i].name, search_name) == 0) {
                printf("Found: %d | %s | %s | %.2f\n",
                       (*students)[i].id, (*students)[i].name, (*students)[i].course, (*students)[i].grade);
                found = 1;
            }
        }
        if (!found) printf("No student found matching \"%s\".\n", search_name);
    }
}

// 7. Remove Student Record (Shrinks dynamic array)
void remove_student(Student **students, int *count) {
    if (*count == 0) {
        printf("\nNo records available to remove.\n");
        return;
    }

    int target_id, found_index = -1;
    printf("\nEnter Student ID to remove: ");
    if (scanf("%d", &target_id) != 1) {
        while (getchar() != '\n');
        return;
    }

    for (int i = 0; i < *count; i++) {
        if ((*students)[i].id == target_id) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("Student ID %d not found.\n", target_id);
        return;
    }

    // Shift records left
    for (int i = found_index; i < *count - 1; i++) {
        (*students)[i] = (*students)[i + 1];
    }
    (*count)--;

    // Shrink memory
    if (*count > 0) {
        Student *temp = (Student *)realloc(*students, *count * sizeof(Student));
        if (temp != NULL) {
            *students = temp;
        }
    }

    printf("Student ID %d removed. Remaining records: %d\n", target_id, *count);
}

// 8. Custom Academic Analysis: Academic Risk Index (ARI)
void custom_analysis(Student **students, int *count) {
    if (*count == 0) {
        printf("\nNo student records to evaluate.\n");
        return;
    }

    int high_risk = 0, moderate_risk = 0, low_risk = 0;

    printf("\n=== Academic Risk Index (ARI) Analysis ===\n");
    printf("%-6s | %-20s | %-6s | %-15s\n", "ID", "Name", "Grade", "Risk Level");
    printf("------------------------------------------------------\n");

    for (Student *ptr = *students; ptr < *students + *count; ptr++) {
        const char *risk_status;
        if (ptr->grade < PASS_THRESHOLD) {
            risk_status = "High Risk";
            high_risk++;
        } else if (ptr->grade < 65.0f) {
            risk_status = "Moderate Risk";
            moderate_risk++;
        } else {
            risk_status = "Low Risk";
            low_risk++;
        }
        printf("%-6d | %-20s | %-6.2f | %-15s\n", ptr->id, ptr->name, ptr->grade, risk_status);
    }

    printf("\nRisk Distribution:\n");
    printf("- High Risk (< 50):     %d student(s)\n", high_risk);
    printf("- Moderate Risk (50-64): %d student(s)\n", moderate_risk);
    printf("- Low Risk (>= 65):     %d student(s)\n", low_risk);
}

// 9. Summary Report
void generate_summary_report(Student **students, int *count) {
    if (*count == 0) {
        printf("\nNo records available for summary report.\n");
        return;
    }

    float sum = 0.0f;
    float highest = (*students)[0].grade;
    float lowest = (*students)[0].grade;
    int pass_count = 0;
    int fail_count = 0;

    for (Student *ptr = *students; ptr < *students + *count; ptr++) {
        sum += ptr->grade;
        if (ptr->grade > highest) highest = ptr->grade;
        if (ptr->grade < lowest)  lowest = ptr->grade;
        if (ptr->grade >= PASS_THRESHOLD) pass_count++;
        else fail_count++;
    }

    printf("\n================ ACADEMIC SUMMARY REPORT ================\n");
    printf("Total Student Records     : %d\n", *count);
    printf("Class Average Grade       : %.2f\n", sum / *count);
    printf("Highest Grade             : %.2f\n", highest);
    printf("Lowest Grade              : %.2f\n", lowest);
    printf("Students Passing (>= %.1f): %d\n", PASS_THRESHOLD, pass_count);
    printf("Students At Risk (< %.1f) : %d\n", PASS_THRESHOLD, fail_count);
    printf("=========================================================\n");
}
