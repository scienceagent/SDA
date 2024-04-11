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

void initialize_vector(EmployeeVector *vec, size_t capacity);
void push_back(EmployeeVector *vec, Employee newEmployee);
void push_front(EmployeeVector *vec, Employee newEmployee);
void pop_back(EmployeeVector *vec);
void pop_front(EmployeeVector *vec);
void print_employee_vector(EmployeeVector *vec);
void free_employee_vector(EmployeeVector *vec);

int find_employee_by_name(EmployeeVector *vec, char *name);
void insert_employee_start(EmployeeVector *vec);
void insert_employee_at_position(EmployeeVector *vec, int position);
void delete_employee_at_position(EmployeeVector *vec);
void read_employee_details(EmployeeVector *vec);

void generate_random_data(EmployeeVector *vec, int n);

void initialize_vector(EmployeeVector *vec, size_t capacity)
{
    vec->data = (Employee *)malloc(capacity * sizeof(Employee));
    vec->size = 0;
    vec->capacity = capacity;
}

void push_back(EmployeeVector *vec, Employee newEmployee)
{
    if (vec->size < vec->capacity)
    {
        vec->data[vec->size++] = newEmployee;
    }
    else
    {
        size_t new_capacity = vec->capacity * 2;
        vec->data = (Employee *)realloc(vec->data, new_capacity * sizeof(Employee));
        vec->capacity = new_capacity;
        vec->data[vec->size++] = newEmployee;
    }
}

void push_front(EmployeeVector *vec, Employee newEmployee)
{
    if (vec->size < vec->capacity)
    {
        for (size_t i = vec->size; i > 0; i--)
        {
            vec->data[i] = vec->data[i - 1];
        }
        vec->data[0] = newEmployee;
        vec->size++;
    }
    else
    {
        size_t new_capacity = vec->capacity * 2;
        vec->data = (Employee *)realloc(vec->data, new_capacity * sizeof(Employee));
        vec->capacity = new_capacity;
        for (size_t i = vec->size; i > 0; i--)
        {
            vec->data[i] = vec->data[i - 1];
        }
        vec->data[0] = newEmployee;
        vec->size++;
    }
}

void pop_back(EmployeeVector *vec)
{
    if (vec->size > 0)
    {
        vec->size--;
    }
}

void pop_front(EmployeeVector *vec)
{
    if (vec->size > 0)
    {
        for (size_t i = 0; i < vec->size - 1; i++)
        {
            vec->data[i] = vec->data[i + 1];
        }
        vec->size--;
    }
}

void free_employee_vector(EmployeeVector *vec)
{
    free(vec->data);
    vec->size = 0;
    vec->capacity = 0;
}

void print_employee_vector_recursive(EmployeeVector *vec, size_t i) {
    if (i == vec->size) {
        return;
    }

    printf("\n**Employee %lu:**\n", i + 1);
    printf("Name: %s\n", vec->data[i].name);
    printf("Gender: %s\n", vec->data[i].gender);
    printf("Age: %d\n", vec->data[i].age);
    printf("Salary: %.2f\n", vec->data[i].salary);
    printf("Birthday: %d-%d-%d\n", vec->data[i].birthday.day, vec->data[i].birthday.month, vec->data[i].birthday.year);

    print_employee_vector_recursive(vec, i + 1);
}

void print_employee_vector(EmployeeVector *vec) {

    print_employee_vector_recursive(vec, 0);
}

int find_employee_by_name(EmployeeVector *vec, char *name)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        if (strcmp(vec->data[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void generate_random_data(EmployeeVector *vec, int n)
{
    for (int i = 0; i < n; i++)
    {
        Employee newEmployee;
        sprintf(newEmployee.name, "Employee%d", i + 1);
        sprintf(newEmployee.gender, (rand() % 2 == 0) ? "Male" : "Female");
        newEmployee.age = rand() % 41 + 20;
        newEmployee.salary = (float)(rand() % 50001 + 30000);
        newEmployee.birthday.day = rand() % 31 + 1;
        newEmployee.birthday.month = rand() % 12 + 1;
        newEmployee.birthday.year = rand() % 21 + 1980;

        push_back(vec, newEmployee);
    }
}

void insert_employee_start(EmployeeVector *vec)
{
    Employee newEmployee;

    sprintf(newEmployee.name, "Employee%d", vec->size + 1);
    sprintf(newEmployee.gender, (rand() % 2 == 0) ? "Male" : "Female");
    newEmployee.age = rand() % 41 + 20;
    newEmployee.salary = (float)(rand() % 50001 + 30000);
    newEmployee.birthday.day = rand() % 31 + 1;
    newEmployee.birthday.month = rand() % 12 + 1;
    newEmployee.birthday.year = rand() % 21 + 1980;

    push_front(vec, newEmployee);
}


void insert_employee_at_position(EmployeeVector *vec, int position)
{
    generate_random_data(vec, 1);
}

int get_valid_position(size_t size) {
    int position;
    do {
        printf("\nEnter the position (1 to %lu) to delete the employee: ", size);
        scanf("%d", &position);
    } while (position < 1 || position > (int)size);
    return position - 1; 
}

void shift_elements(EmployeeVector *vec, size_t start, size_t end) {
    for (size_t i = end; i > start; i--) {
        vec->data[i] = vec->data[i - 1];
    }
}

void delete_employee_at_position(EmployeeVector *vec) {

    size_t position = get_valid_position(vec->size);

    shift_elements(vec, position, vec->size - 1); 
    pop_back(vec); 
}

void print_employee_details(const Employee *employee) {
    printf("Name: %s\n", employee->name);
    printf("Gender: %s\n", employee->gender);
    printf("Age: %d\n", employee->age);
    printf("Salary: %.2f\n", employee->salary);
    printf("Birthday: %d-%d-%d\n", employee->birthday.day, employee->birthday.month, employee->birthday.year);
}

void read_employee_details(EmployeeVector *vec) {
    size_t employee_number;
    do {
        printf("\nEnter the employee number (1 to %lu) to read details: ", vec->size);
        scanf("%lu", &employee_number);
    } while (employee_number < 1 || employee_number > vec->size);

    employee_number--; 

    printf("\nDetails for Employee %lu:\n", employee_number + 1);
    print_employee_details(&vec->data[employee_number]); 

}

int main()
{
    EmployeeVector empVector;
    int choice;
    char search_name[30];

    printf("Enter the initial capacity of the employee vector: ");
    scanf("%lu", &empVector.capacity);

    initialize_vector(&empVector, empVector.capacity);

    generate_random_data(&empVector, empVector.capacity);

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

        switch (choice)
        {
        case 1:
            print_employee_vector(&empVector);
            break;
        case 2:
            printf("Enter the name of the employee to search: ");
            scanf("%s", search_name);
            int position = find_employee_by_name(&empVector, search_name);
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
            qsort(empVector.data, empVector.size, sizeof(Employee), compare_by_name);
            printf("Employees sorted by name.\n");
            break;
        case 4:
            qsort(empVector.data, empVector.size, sizeof(Employee), compare_by_age);
            printf("Employees sorted by age.\n");
            break;
        case 5:
            qsort(empVector.data, empVector.size, sizeof(Employee), compare_by_salary);
            printf("Employees sorted by salary.\n");
            break;
        case 6:
            read_employee_details(&empVector);
            break;
        case 7:
            insert_employee_start(&empVector);
            break;
        case 8:
            printf("Enter the position for inserting the employee: ");
            scanf("%d", &position);
            insert_employee_at_position(&empVector, position);
            break;

        case 9:
            delete_employee_at_position(&empVector);
            break;
        case 10:
            free_employee_vector(&empVector);
            break;
        case 0:
            printf(".....\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    free_employee_vector(&empVector);
    return 0;
}