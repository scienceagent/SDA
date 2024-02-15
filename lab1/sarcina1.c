#include<stdio.h>
#include<string.h>

struct date
{
    int day, month, year;   
};

struct employee
{
    char name[30];
    char gender[10];
    int age;
    float salary;
    struct date birthday;
};

void print_employee(struct employee emp[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("\n");
        printf("Employee %d:\n", i+1);
        printf("Name: %s\n", emp[i].name);
        printf("Gender: %s\n", emp[i].gender);
        printf("Age: %d\n", emp[i].age);
        printf("Salary: %.2f\n", emp[i].salary);
        printf("Birthday: %d-%d-%d\n", emp[i].birthday.day, emp[i].birthday.month, emp[i].birthday.year);
        printf("\n");
    }
}

int find_employee_by_name(struct employee emp[], int n, char* name)
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(strcmp(emp[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    struct employee emp[10];
    int i, n;
    char search_name[30];
    int position;

    printf("Enter the number of employees: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter name: ");
        scanf("%s", emp[i].name);
        printf("Enter gender: ");
        scanf("%s", emp[i].gender);
        printf("Enter age: ");
        scanf("%d", &emp[i].age);
        printf("Enter salary: ");
        scanf("%f", &emp[i].salary);
        printf("Enter birthday (day month year): ");
        scanf("%d %d %d", &emp[i].birthday.day, &emp[i].birthday.month, &emp[i].birthday.year);
        printf("\n");
    }

    printf("\n");
    printf("------DATA PRINT------\n");
    print_employee(emp, n);

    printf("Enter the name of the employee to search: ");
    scanf("%s", search_name);

    position = find_employee_by_name(emp, n, search_name);

    if(position != -1)
    {
        printf("Employee found at position %d\n", position+1);
    }
    else
    {
        printf("Employee not found\n");
        position = find_employee_by_name(emp, n, search_name);
    }

    return 0;
}
