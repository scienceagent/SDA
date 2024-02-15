#include <stdio.h>
// #include <stdlib.h>
#include <string.h>

struct date {
    int day, month, year;
};

struct employee {
    char name[30];
    char gender[10];
    int age;
    float salary;
    struct date birthday;
};

// show all the employee
void print_employee(struct employee emp[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\n**Employee %d:**\n", i + 1);
        printf("Name: %s\n", emp[i].name);
        printf("Gender: %s\n", emp[i].gender);
        printf("Age: %d\n", emp[i].age);
        printf("Salary: %.2f\n", emp[i].salary);
        printf("Birthday: %d-%d-%d\n", emp[i].birthday.day, emp[i].birthday.month, emp[i].birthday.year);
    }
}

// find a employee by name in structure
int find_employee_by_name(struct employee emp[], int n, char* name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(emp[i].name, name) == 0) {
            return i;
        }
    }
    return -1; 
}

//sort by name
int compare_by_name(const void *a, const void *b) {
    return strcmp(((struct employee *)a)->name, ((struct employee *)b)->name);
}

//sort by age
int compare_by_age(const void *a, const void *b) {
    return ((struct employee *)a)->age - ((struct employee *)b)->age;
}

//sort by salary
int compare_by_salary(const void *a, const void *b) {
    return (int)(((struct employee *)a)->salary - ((struct employee *)b)->salary);
}

//insert a new employee
void insert_employee(struct employee emp[], int *n) {
    if (*n < 10) {
        printf("\nEnter details for the new employee:\n");
        printf("Name: ");
        scanf("%s", emp[*n].name);
        printf("Gender: ");
        scanf("%s", emp[*n].gender);
        printf("Age: ");
        scanf("%d", &emp[*n].age);
        printf("Salary: ");
        scanf("%f", &emp[*n].salary);
        printf("Birthday (day month year): ");
        scanf("%d %d %d", &emp[*n].birthday.day, &emp[*n].birthday.month, &emp[*n].birthday.year);
        (*n)++;
        printf("Employee inserted at the end of the array.\n");
    } else {
        printf("Cannot insert more than 10 employees. Array is full.\n");
    }
}

//insert a new emloyee at begining of the array
void insert_employee_start(struct employee emp[], int *n) {
    if (*n < 10) {
        for (int i = *n; i > 0; i--) {
            emp[i] = emp[i - 1];
        }

        printf("\nEnter details for the new employee:\n");
        printf("Name: ");
        scanf("%s", emp[0].name);
        printf("Gender: ");
        scanf("%s", emp[0].gender);
        printf("Age: ");
        scanf("%d", &emp[0].age);
        printf("Salary: ");
        scanf("%f", &emp[0].salary);
        printf("Birthday (day month year): ");
        scanf("%d %d %d", &emp[0].birthday.day, &emp[0].birthday.month, &emp[0].birthday.year);

        (*n)++;
        printf("Employee inserted at the beginning of the array.\n");
    } else {
        printf("Cannot insert more than 10 employees. Array is full.\n");
    }
}

//insert a new employee 
void insert_employee_at_position(struct employee emp[], int *n) {
    int position;

    printf("\nEnter the position (1 to %d) to insert the new employee: ", *n + 1);
    scanf("%d", &position);

    if (position < 1 || position > *n + 1) {
        printf("Invalid position. Please enter a valid position.\n");
        return;
    }

    if (*n < 10) {
        for (int i = *n; i >= position; i--) {
            emp[i] = emp[i - 1];
        }

        printf("\nEnter details for the new employee:\n");
        printf("Name: ");
        scanf("%s", emp[position - 1].name);
        printf("Gender: ");
        scanf("%s", emp[position - 1].gender);
        printf("Age: ");
        scanf("%d", &emp[position - 1].age);
        printf("Salary: ");
        scanf("%f", &emp[position - 1].salary);
        printf("Birthday (day month year): ");
        scanf("%d %d %d", &emp[position - 1].birthday.day, &emp[position - 1].birthday.month, &emp[position - 1].birthday.year);

        (*n)++;
        printf("Employee inserted at position %d.\n", position);
    } else {
        printf("Cannot insert more than 10 employees. Array is full.\n");
    }
}

//delete a employee at a specific position
void delete_employee_at_position(struct employee emp[], int *n) {
    int position;

    printf("\nEnter the position (1 to %d) to delete the employee: ", *n);
    scanf("%d", &position);

    if (position < 1 || position > *n) {
        printf("Invalid position. Please enter a valid position.\n");
        return;
    }
    for (int i = position - 1; i < *n - 1; i++) {
        emp[i] = emp[i + 1];
    }

    (*n)--;
    printf("Employee deleted from position %d.\n", position);
}


int main() {
    struct employee *emp;
    int i, n, choice;
    char search_name[30];
    printf("Enter the number of employees: ");
    scanf("%d", &n);

    emp = (struct employee *)malloc(n * sizeof(struct employee));

    for (i = 0; i < n; i++) {
        printf("\nEnter details for employee %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", emp[i].name);
        printf("Gender: ");
        scanf("%s", emp[i].gender);
        printf("Age: ");
        scanf("%d", &emp[i].age);
        printf("Salary: ");
        scanf("%f", &emp[i].salary);
        printf("Birthday (day month year): ");
        scanf("%d %d %d", &emp[i].birthday.day, &emp[i].birthday.month, &emp[i].birthday.year);
    }

    do {
       printf("\n\nMENU:\n");
        printf("1. Print all employees\n");
        printf("2. Search for an employee by name\n");
        printf("3. Sort employees by name\n");
        printf("4. Sort employees by age\n");
        printf("5. Sort employees by salary\n");
        // printf("6. Insert a new employee at the end\n");
        printf("7. Insert a new employee at the beginning\n");
        printf("8. Insert a new employee at a specific position\n");
        printf("9. Delete an employee at a specific position\n");
        // printf("10. Free memory for the array\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                print_employee(emp, n);
                break;
            case 2:
                printf("Enter the name of the employee to search: ");
                scanf("%s", search_name);
                int position = find_employee_by_name(emp, n, search_name);
                if (position != -1) {
                    printf("Employee found at position %d\n", position + 1);
                } else {
                    printf("Employee not found\n");
                }
                break;
            case 3:
                qsort(emp, n, sizeof(struct employee), compare_by_name);
                printf("Employees sorted by name.\n");
                break;
            case 4:
                qsort(emp, n, sizeof(struct employee), compare_by_age);
                printf("Employees sorted by age.\n");
                break;
            case 5:
                qsort(emp, n, sizeof(struct employee), compare_by_salary);
                printf("Employees sorted by salary.\n");
                break;
           case 6:
            case 7:
                insert_employee_start(emp, &n);
                break;
            case 8:
                insert_employee_at_position(emp, &n);
                break;
            case 9:
                delete_employee_at_position(emp, &n);
                break;
            case 10:
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;

    
}
