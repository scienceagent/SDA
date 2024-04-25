#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Document
{
    int id;
    char name[100];
    int total_lines;
    int estimated_print_time;
    int lines_left;
    struct Document *next;
} Document;

typedef struct Printer
{
    int id;
    int print_speed;
    Document *current_document;
    struct Printer *next;
} Printer;

Document *create_document(int id, char name[], int total_Lines);
Document *enqueue_document(Document *head, Document *new_document);
void print_Queue(Document *head);

Printer *create_printer(int id, int printSpeed);
void initialize_printers(Printer **headPrinter, int numPrinters);
void assign_document_to_printer(Printer *headPrinter, Document *document);

int main()
{
    int num_printers;
    printf("Enter the number of printers available: ");
    scanf("%d", &num_printers);

    Document *head = NULL;

    Printer *head_printer = NULL;
    initialize_printers(&head_printer, num_printers);

    int choice;
    do
    {
        printf("\nPrint Queue Management System\n");
        printf("1. Add a document\n");
        printf("2. Assign document to printer (for demo)\n");
        printf("3. Display print queue\n");
        printf("4. Simulate printing\n");
        printf("5. Show Print Queue and Printer Status\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int num_documents;
            printf("Enter the number of documents to generate: ");
            scanf("%d", &num_documents);

            if (num_documents <= 0)
            {
                printf("Invalid number of documents.\n");
                break;
            }

            for (int i = 0; i < num_documents; i++)
            {
                int id = rand() % 1000 + 1;
                char name[100];
                sprintf(name, "Document-%d", id);
                int total_Lines = rand() % 1000 + 1;

                Document *new_document = create_document(id, name, total_Lines);
                if (new_document == NULL)
                {
                    break;
                }

                head = enqueue_document(head, new_document);
                printf("Document added to queue.\n");
            }
            break;
        }
        case 2:
        {
            if (head == NULL)
            {
                printf("Print queue is empty.\n");
            }
            else
            {
                Document *next_document = head;
                head = head->next;
                assign_document_to_printer(head_printer, next_document);
                printf("Assigned document '%s' (ID: %d) for printing.\n", next_document->name, next_document->id);
                free(next_document);
            }
            break;
        }
        case 3:
            print_Queue(head);
            break;
        case 4:
        {
            int time_step;
            printf("Enter simulation time step (seconds): ");
            scanf("%d", &time_step);
            simulate_Printing(head_printer, head, time_step);
            printf("Simulation completed.\n");
            show_Status(head, head_printer);
        }
        break;
        case 5:
            show_Status(head, head_printer);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 6);

    while (head != NULL)
    {
        Document *temp = head;
        head = head->next;
        free(temp);
    }

    free_Printers(head_printer);

    return 0;
}

Document *create_document(int id, char name[], int total_Lines)
{
    Document *new_document = (Document *)malloc(sizeof(Document));
    if (new_document == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    new_document->id = id;
    strcpy(new_document->name, name);
    new_document->total_lines = total_Lines;
    new_document->lines_left = total_Lines;
    new_document->next = NULL;
    return new_document;
}

Document *enqueue_document(Document *head, Document *new_document)
{
    if (head == NULL)
    {
        return new_document;
    }

    Document *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_document;
    return head;
}

void calculate_Estimated_Print_Time(Printer *headPrinter, Document *headDocument)
{
    Document *current_document = headDocument;
    while (current_document != NULL)
    {
        int shortest_time = INT_MAX;
        Printer *current_printer = headPrinter;
        while (current_printer != NULL)
        {
            if (current_printer->current_document == NULL)
            {
                int estimated_Time = (current_document->lines_left + current_printer->print_speed - 1) / current_printer->print_speed;
                if (estimated_Time < shortest_time)
                {
                    shortest_time = estimated_Time;
                }
            }
            current_printer = current_printer->next;
        }
        current_document->estimated_print_time = shortest_time;
        current_document = current_document->next;
    }
}

void simulate_Printing(Printer *head_printer, Document *head_document, int time_step)
{
    calculate_Estimated_Print_Time(head_printer, head_document);

    for (int t = 0; t < time_step; t++)
    {
        printf("Time Step: %d\n", t + 1);

        Printer *current_Printer = head_printer;
        while (current_Printer != NULL)
        {
            if (current_Printer->current_document != NULL)
            {
                int lines_To_Print = current_Printer->print_speed;
                if (current_Printer->current_document->lines_left < lines_To_Print)
                {
                    lines_To_Print = current_Printer->current_document->lines_left;
                }
                usleep(1000000 / current_Printer->print_speed);

                current_Printer->current_document->lines_left -= lines_To_Print;

                printf("Printer %d printed %d lines of document %d. Remaining lines: %d\n",
                       current_Printer->id, lines_To_Print, current_Printer->current_document->id,
                       current_Printer->current_document->lines_left);

                if (current_Printer->current_document->lines_left <= 0)
                {
                    printf("Document %d finished printing.\n", current_Printer->current_document->id);
                    current_Printer->current_document = NULL;
                }
            }
            current_Printer = current_Printer->next;
        }

        calculate_Estimated_Print_Time(head_printer, head_document);

        Document *current_Document = head_document;
        while (current_Document != NULL)
        {
            if (current_Document->lines_left > 0)
            {
                assign_document_to_printer(head_printer, current_Document);
            }
            current_Document = current_Document->next;
        }
    }
}

void print_Queue(Document *head)
{
    if (head == NULL)
    {
        printf("Print queue is empty.\n");
        return;
    }

    printf("\nPrint Queue:\n");
    printf("ID\tName\t\tTotal Lines\tRemaining Lines\n");
    printf("-------\t---------------\t--------------\t----------------\n");
    Document *current = head;
    while (current != NULL)
    {
        printf("%d\t%s\t\t%d\t\t%d\n", current->id, current->name, current->total_lines, current->lines_left);
        current = current->next;
    }
}

Printer *create_printer(int id, int print_speed)
{
    Printer *new_Printer = (Printer *)malloc(sizeof(Printer));
    if (new_Printer == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    new_Printer->id = id;
    new_Printer->print_speed = print_speed;
    new_Printer->current_document = NULL;
    new_Printer->next = NULL;
    return new_Printer;
}

void initialize_printers(Printer **head_printer, int num_printers)
{
    if (num_printers <= 0)
    {
        printf("Invalid number of printers. Please enter a positive value.\n");
        return;
    }

    *head_printer = NULL;

    for (int i = 0; i < num_printers; i++)
    {
        int print_speed = rand() % 1000 + 1;

        Printer *new_printer = create_printer(i + 1, print_speed);
        if (new_printer == NULL)
        {
            break;
        }

        if (*head_printer == NULL)
        {
            *head_printer = new_printer;
        }
        else
        {
            Printer *current = *head_printer;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new_printer;
        }
    }
}

void assign_document_to_printer(Printer *head_Printer, Document *document)
{
    if (head_Printer == NULL)
    {
        printf("No printers available for assignment.\n");
        return;
    }

    Printer *most_Efficient_Printer = NULL;
    int shortest_Time = INT_MAX;
    Printer *current_Printer = head_Printer;
    while (current_Printer != NULL)
    {
        if (current_Printer->current_document == NULL)
        {
            if (document->estimated_print_time < shortest_Time)
            {
                shortest_Time = document->estimated_print_time;
                most_Efficient_Printer = current_Printer;
            }
        }
        current_Printer = current_Printer->next;
    }

    if (most_Efficient_Printer != NULL)
    {
        most_Efficient_Printer->current_document = document;
        printf("Assigned document '%s' (ID: %d) to printer %d.\n", document->name, document->id, most_Efficient_Printer->id);
    }
    else
    {
        printf("All printers are busy. Document placed on hold.\n");
    }
}

void show_Status(Document *head, Printer *head_Printer)
{
    printf("\nPrinter Status:\n");
    if (head_Printer == NULL)
    {
        printf("No printers available.\n");
    }
    else
    {
        printf("ID\tPrint Speed\tCurrent Document (ID, Lines Left)\n");
        printf("-------\t-----------\t--------------------------------\n");
        Printer *current_Printer = head_Printer;
        while (current_Printer != NULL)
        {
            char document_Status[50];
            if (current_Printer->current_document == NULL)
            {
                strcpy(document_Status, "Available");
            }
            else
            {
                sprintf(document_Status, "%d (%d lines left)", current_Printer->current_document->id, current_Printer->current_document->lines_left);
            }
            printf("%d\t%d\t\t%s\n", current_Printer->id, current_Printer->print_speed, document_Status);
            current_Printer = current_Printer->next;
        }
    }

    printf("\nFinished Documents:\n");
    printf("ID\tName\n");
    printf("-------\t---------------\n");
    Document *current = head;
    while (current != NULL)
    {
        if (current->lines_left == 0)
        {
            printf("%d\t%s\n", current->id, current->name);
        }
        current = current->next;
    }
}

void free_Printers(Printer *head_Printer)
{
    while (head_Printer != NULL)
    {
        Printer *temp = head_Printer;
        head_Printer = head_Printer->next;
        free(temp);
    }
}
