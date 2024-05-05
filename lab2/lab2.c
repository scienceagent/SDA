#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bank_account
{
    char account_number[100];
    char account_holder[100];
    float balance;
    int branch_code;
    char branch_address[100];
    char account_type[100];
} bank_account;

typedef struct Node
{
    bank_account account;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
} List;

bank_account *create_account();
void insert_at_end(List *list);
void insert_at_beginning(List *list);
void insert_at_position(List *list, int position);
void delete_at_position(List *list, int position);
void print_list(List *list);
void search_by_holder(List *list, const char *search_holder);
void sort_by_balance(List *list);
void reverse_list(List *list);
void clear_list(List *list);
void menu();

int main()
{
    List list;
    list.head = NULL;
    int choice;

    do
    {
        menu();
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insert_at_end(&list);
            break;
        case 2:
            insert_at_beginning(&list);
            break;
        case 3:
            int position;
            printf("Enter the position to insert the account: ");
            scanf("%d", &position);
            insert_at_position(&list, position);
            break;
        case 4:
        {
            int position;
            printf("Enter the position to delete the account: ");
            scanf("%d", &position);
            delete_at_position(&list, position);
            break;
        }
        case 5:
            print_list(&list);
            break;
        case 6:
        {
            char search_holder[50];
            printf("Enter the account holder name to search for: ");
            scanf(" %[^\n]s", search_holder);
            search_by_holder(&list, search_holder);
            break;
        }
        case 7:
            sort_by_balance(&list);
            break;
        case 8:
            reverse_list(&list);
            break;
        case 9:
            clear_list(&list);
            printf("List cleared.\n");
            break;
        case 0:
            printf("Exit\n");
            break;
        default:
            printf("Try again\n");
        }
    } while (choice != 0);

    return 0;
}

bank_account *create_account()
{
    bank_account *new_account = (bank_account *)malloc(sizeof(bank_account));

    printf("Account number: ");
    scanf(" %[^\n]s", new_account->account_number);
    printf("Account holder name: ");
    scanf(" %[^\n]s", new_account->account_holder);
    printf("Balance: ");
    scanf("%f", &new_account->balance);
    printf("Branch code of bank: ");
    scanf("%d", &new_account->branch_code);
    printf("Branch address: ");
    scanf(" %[^\n]s", new_account->branch_address);
    printf("Account type: ");
    scanf(" %[^\n]s", new_account->account_type);

    return new_account;
}

void insert_at_end(List *list)
{
    bank_account *new_account = create_account();
    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->account = *new_account;
    new_node->next = NULL;

    if (list->head == NULL)
    {
        list->head = new_node;
    }
    else
    {
        Node *temporary = list->head;
        while (temporary->next != NULL)
        {
            temporary = temporary->next;
        }
        temporary->next = new_node;
    }
}

void insert_at_beginning(List *list)
{
    bank_account *new_account = create_account();
    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->account = *new_account;
    new_node->next = list->head;
    list->head = new_node;
}

void insert_at_position(List *list, int position)
{

    if (position == 1)
    {
        insert_at_beginning(list);
        return;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    bank_account *new_account = create_account();
    new_node->account = *new_account;

    Node *temporary = list->head;
    int count = 1;

    while (temporary != NULL && count < position - 1)
    {
        temporary = temporary->next;
        count++;
    }

    new_node->next = temporary->next;
    temporary->next = new_node;
}

void delete_at_position(List *list, int position)
{

    Node *temporary = list->head;
    Node *previous = NULL;
    int count = 1;

    if (position == 1)
    {
        list->head = temporary->next;
        free(temporary);
        printf("Account deleted from position %d.\n", position);
        return;
    }

    while (temporary != NULL && count < position)
    {
        previous = temporary;
        temporary = temporary->next;
        count++;
    }

    previous->next = temporary->next;
    free(temporary);
}

void print_account(bank_account *account)
{
    printf("Account Number: %s\n", account->account_number);
    printf("Account Holder: %s\n", account->account_holder);
    printf("Balance: %.2f\n", account->balance);
    printf("Branch Code: %d\n", account->branch_code);
    printf("Branch Address: %s\n", account->branch_address);
    printf("Account Type: %s\n", account->account_type);
}

void print_list(List *list)
{

    printf("List contents:\n");
    Node *current = list->head;
    int index = 1;
    while (current != NULL)
    {
        printf("Account %d:\n", index++);
        print_account(&current->account);
        printf("\n");
        current = current->next;
    }
}

void search_by_holder(List *list, const char *search_holder)
{

    Node *temporary = list->head;
    int position = 1;
    while (temporary != NULL)
    {
        if (strcmp(temporary->account.account_holder, search_holder) == 0)
        {
            printf("Account found at position %d.\n", position);
            return;
        }
        temporary = temporary->next;
        position++;
    }
}

void sort_by_balance(List *list)
{

    Node *current, *next_account;
    bank_account temp_account;

    for (current = list->head; current != NULL; current = current->next)
    {
        for (next_account = current->next; next_account != NULL; next_account = next_account->next)
        {
            if (current->account.balance > next_account->account.balance)
            {
                temp_account = current->account;
                current->account = next_account->account;
                next_account->account = temp_account;
            }
        }
    }
}

void reverse_list(List *list)
{
    Node *previous = NULL;
    Node *current = list->head;
    Node *next_account = NULL;

    while (current != NULL)
    {
        next_account = current->next;
        current->next = previous;
        previous = current;
        current = next_account;
    }

    list->head = previous;
}

void clear_list(List *list)
{
    Node *temp;
    while (list->head != NULL)
    {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}

void menu()
{
    printf("\nMENU\n");
    printf("1. Insert at end\n");
    printf("2. Insert at beginning\n");
    printf("3. Insert at position\n");
    printf("4. Delete at position\n");
    printf("5. Display list\n");
    printf("6. Search by account holder\n");
    printf("7. Sort by balance\n");
    printf("8. Reverse list\n");
    printf("9. Clear list\n");
    printf("0. Exit\n");
}
