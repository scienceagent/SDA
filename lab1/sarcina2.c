#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date
{
    int day, month, year;
} Date;

typedef struct Employee
{
    char name[30];
    char gender[10];
    int age;
    float salary;
    Date birthday;
} Employee;

typedef struct EmployeeVector
{
    Employee *data;
    size_t size;
    size_t capacity;
} EmployeeVector;

int compare_by_name(const void *a, const void *b);
int compare_by_age(const void *a, const void *b);
int compare_by_salary(const void *a, const void *b);

void initialize_vector(EmployeeVector *vector, size_t capacity);
void push_back(EmployeeVector *vector, Employee new_Employee);
void push_front(EmployeeVector *vector, Employee new_Employee);
void pop_back(EmployeeVector *vector);
void pop_front(EmployeeVector *vector);
void print_employee_vector(EmployeeVector *vector); 
void free_employee_vector(EmployeeVector *vector);

int find_employee_by_name(EmployeeVector *vector, char *name);
void generate_random_data(EmployeeVector *vector, int number_of_employees);

void insert_employee_start(EmployeeVector *vector);
void insert_employee_at_position(EmployeeVector *vector, int position);
void delete_employee_at_position(EmployeeVector *vector);
void read_employee_details(EmployeeVector *vector); 

void print_employee_details(const Employee *employee); 
void get_valid_employee_number(const EmployeeVector *vector, size_t *employee_number);
void print_employee_information(const Employee *employee, const EmployeeVector *vector);

void initialize_vector(EmployeeVector *vector, size_t capacity)
{
    vector->data = (Employee *)malloc(capacity * sizeof(Employee));
    vector->size = 0;
    vector->capacity = capacity;
}

void push_back(EmployeeVector *vector, Employee new_employee)
{
    if (vector->size < vector->capacity)
    {
        vector->data[vector->size++] = new_employee;
    }
    else
    {
        size_t new_capacity = vector->capacity * 2;
        vector->data = (Employee *)realloc(vector->data, new_capacity * sizeof(Employee));
        vector->capacity = new_capacity;
        vector->data[vector->size++] = new_employee;
    }
}

void push_front(EmployeeVector *vector, Employee new_employee)
{
    if (vector->size < vector->capacity)
    {
        for (size_t index = vector->size; index > 0; index--)
        {
            vector->data[index] = vector->data[index - 1];
        }
        vector->data[0] = new_employee;
        vector->size++;
    }
    else
    {
        size_t new_capacity = vector->capacity * 2;
        vector->data = (Employee *)realloc(vector->data, new_capacity * sizeof(Employee));
        vector->capacity = new_capacity;
        for (size_t index = vector->size; index > 0; index--)
        {
            vector->data[index] = vector->data[index - 1];
        }
        vector->data[0] = new_employee;
        vector->size++;
    }
}

void pop_back(EmployeeVector *vector)
{
    if (vector->size > 0)
    {
        vector->size--;
    }
}

void pop_front(EmployeeVector *vector)
{
    if (vector->size > 0)
    {
        for (size_t index = 0; index < vector->size - 1; index++)
        {
            vector->data[index] = vector->data[index + 1];
        }
        vector->size--;
    }
}

void free_employee_vector(EmployeeVector *vector)
{
    free(vector->data);
    vector->size = 0;
    vector->capacity = 0;
}

void print_employee_vector_recursive(EmployeeVector *vector, size_t index)
{
    if (index == vector->size)
    {
        return;
    }

    printf("\n**Employee %lu:**\n", index + 1);
    printf("Name: %s\n", vector->data[index].name);
    printf("Gender: %s\n", vector->data[index].gender);
    printf("Age: %d\n", vector->data[index].age);
    printf("Salary: %.2f\n", vector->data[index].salary);
    printf("Birthday: %d-%d-%d\n", vector->data[index].birthday.day, vector->data[index].birthday.month, vector->data[index].birthday.year);

    print_employee_vector_recursive(vector, index + 1);
}

void print_employee_vector(EmployeeVector *vector)
{
    print_employee_vector_recursive(vector, 0);
}

int find_employee_by_name(EmployeeVector *vector, char *name)
{
    for (size_t index = 0; index < vector->size; index++)
    {
        if (strcmp(vector->data[index].name, name) == 0)
        {
            return index;
        }
    }
    return -1;
}

void generate_random_data(EmployeeVector *vector, int number_of_employees)
{
    for (int index = 0; index < number_of_employees; index++)
    {
        Employee new_employee;
        sprintf(new_employee.name, "Employee%d", index + 1);
        sprintf(new_employee.gender, (rand() % 2 == 0) ? "Male" : "Female");
        new_employee.age = rand() % 41 + 20;
        new_employee.salary = (float)(rand() % 50001 + 30000);
        new_employee.birthday.day = rand() % 31 + 1;
        new_employee.birthday.month = rand() % 12 + 1;
        new_employee.birthday.year = rand() % 21 + 1980;

        push_back(vector, new_employee);
    }
}

void insert_employee_start(EmployeeVector *vector)
{
    Employee new_employee;

    sprintf(new_employee.name, "Employee%d", vector->size + 1);
    sprintf(new_employee.gender, (rand() % 2 == 0) ? "Male" : "Female");
    new_employee.age = rand() % 41 + 20;
    new_employee.salary = (float)(rand() % 50001 + 30000);
    new_employee.birthday.day = rand() % 31 + 1;
    new_employee.birthday.month = rand() % 12 + 1;
    new_employee.birthday.year = rand() % 21 + 1980;

    push_front(vector, new_employee);
}

void insert_employee_at_position(EmployeeVector *vector, int position)
{
    generate_random_data(vector, 1);
}

int get_valid_position(size_t size)
{
    int position;
    do
    {
        printf("\nEnter the position (1 to %lu) to delete the employee: ", size);
        scanf("%d", &position);
    } while (position < 1 || position > (int)size);
    return position - 1;
}

void shift_elements(EmployeeVector *vector, size_t start, size_t end)
{
    for (size_t index = end; index > start; index--)
    {
        vector->data[index] = vector->data[index - 1];
    }
}

void delete_employee_at_position(EmployeeVector *vector)
{

    size_t position = get_valid_position(vector->size);

    shift_elements(vector, position, vector->size - 1);
    pop_back(vector);
}

void print_employee_details(const Employee *employee)
{
    printf("Name: %s\n", employee->name);
    printf("Gender: %s\n", employee->gender);
    printf("Age: %d\n", employee->age);
    printf("Salary: %.2f\n", employee->salary);
    printf("Birthday: %d-%d-%d\n", employee->birthday.day, employee->birthday.month, employee->birthday.year);
}

void get_valid_employee_number(const EmployeeVector *vector, size_t *employee_number)
{
    do
    {
        printf("\nEnter the employee number (1 to %lu) to read details: ", vector->size);
        scanf("%lu", employee_number);
    } while (*employee_number < 1 || *employee_number > vector->size);

    *employee_number -= 1; 
}

void print_employee_information(const Employee *employee, const EmployeeVector *vector)
{
    printf("\nDetails for Employee %lu:\n", employee - vector->data + 1);
    print_employee_details(employee); 
}

void read_employee_details(EmployeeVector *vector)
{
    size_t employee_number;
    get_valid_employee_number(vector, &employee_number);
    print_employee_information(&vector->data[employee_number], vector);
}

int compare_by_name(const void *a, const void *b)
{
    return strcmp(((struct Employee *)a)->name, ((struct Employee *)b)->name);
}

int compare_by_age(const void *a, const void *b)
{
    return ((struct Employee *)a)->age - ((struct Employee *)b)->age;
}

int compare_by_salary(const void *a, const void *b)
{
    return (int)(((struct Employee *)a)->salary - ((struct Employee *)b)->salary);
}

int main()
{
    EmployeeVector employee_vector;
    int choice;
    char search_name[30];

    printf("Write the initial capacity of the employee vector: ");
    scanf("%lu", &employee_vector.capacity);

    initialize_vector(&employee_vector, employee_vector.capacity);

    generate_random_data(&employee_vector, employee_vector.capacity);

    do
    {
        printf("\n\nMENU:\n");
        printf("1. Print all employees\n");
        printf("2. Search for an employee by name\n");
        printf("3. Sort employees by name\n");
        printf("4. Sort employees by age\n");
        printf("5. Sort employees by salary\n");
        printf("6. Read details about an employee\n");
        printf("7. Insert a new employee at the beginning\n");
        printf("8. Insert a new employee at a specific position\n");
        printf("9. Delete an employee at a specific position\n");
        printf("10. Free memory\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            print_employee_vector(&employee_vector);
            break;
        case 2:
            printf("Write the name of the employee to search: ");
            scanf("%s", search_name);
            int position = find_employee_by_name(&employee_vector, search_name);
            if (position != -1)
            {
                printf("Employee found at position %d\n", position + 1);
            }
            else
            {
                printf("Employee not found\n");
            }
            break;
        case 3:
            qsort(employee_vector.data, employee_vector.size, sizeof(Employee), compare_by_name);
            printf("Employees sorted by name.\n");
            break;
        case 4:
            qsort(employee_vector.data, employee_vector.size, sizeof(Employee), compare_by_age);
            printf("Employees sorted by age.\n");
            break;
        case 5:
            qsort(employee_vector.data, employee_vector.size, sizeof(Employee), compare_by_salary);
            printf("Employees sorted by salary.\n");
            break;
        case 6:
            read_employee_details(&employee_vector); 
            break;
        case 7:
            insert_employee_start(&employee_vector);
            break;
        case 8:
            printf("Enter the position for inserting the employee: ");
            scanf("%d", &position);
            insert_employee_at_position(&employee_vector, position);
            break;

        case 9:
            delete_employee_at_position(&employee_vector);
            break;
        case 10:
            free_employee_vector(&employee_vector);
            break;
        case 0:
            printf(".....\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    free_employee_vector(&employee_vector);
    return 0;
}