#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Date
{
    int day, month, year;
};

typedef struct Employee
{
    char name[30];
    char gender[10];
    int age;
    float salary;
    struct Date birthday;
} Employee;

void generate_random_data(struct Employee *emp);
void print_employee(struct Employee emp[], int n);
int find_employee_by_name(struct Employee emp[], int n, char *name);

void generate_random_data(struct Employee *emp)
{
    char names[][30] = {"Dan", "Stas", "Natasa", "Mihai", "Octavian", "Grigore", "Nastea", "Vlad", "Valerian", "Patricia"};
    char genders[][10] = {"Male", "Female"};

    strcpy(emp->name, names[rand() % 10]);
    strcpy(emp->gender, genders[rand() % 2]);
    emp->age = rand() % 40 + 20;               
    emp->salary = (rand() % 5000 + 50000) / 100.0; 
    emp->birthday.day = rand() % 28 + 1;    
    emp->birthday.month = rand() % 12 + 1;      
    emp->birthday.year = rand() % 10 + 1990;    
}

void print_employee(struct Employee emp[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("\n");
        printf("Employee %d:\n", i + 1);
        printf("Name: %s\n", emp[i].name);
        printf("Gender: %s\n", emp[i].gender);
        printf("Age: %d\n", emp[i].age);
        printf("Salary: %.2f\n", emp[i].salary);
        printf("Birthday: %d-%d-%d\n", emp[i].birthday.day, emp[i].birthday.month, emp[i].birthday.year);
        printf("\n");
    }
}

int find_employee_by_name(struct Employee emp[], int n, char *name)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (strcmp(emp[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    struct Employee emp[10];
    int i, n;
    char search_name[30];
    int position;

    printf("Enter the number of employees: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        generate_random_data(&emp[i]);
    }

    printf("\n");
    printf("------DATA PRINT------\n");
    print_employee(emp, n);

    printf("Enter the name of the employee to search: ");
    scanf("%s", search_name);

    position = find_employee_by_name(emp, n, search_name);

    if (position != -1)
    {
        printf("Employee found at position %d\n", position + 1);
    }
    else
    {
        printf("Employee not found\n");
    }

    return 0;
}
