#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Document
{
    int id;
    char name[100];
    int totalLines;
    int linesLeft;
    struct Document *next;
} Document;

typedef struct Printer
{
    int id;
    int printSpeed;
    Document *currentDocument;
    struct Printer *next;
} Printer;

Document *createDocument(int id, char name[], int totalLines);
Document *enqueueDocument(Document *head, Document *newDocument);
void printQueue(Document *head);

Printer *createPrinter(int id, int printSpeed);
void initializePrinters(Printer **headPrinter, int numPrinters);
void assignDocumentToPrinter(Printer *headPrinter, Document *document);

int calculatePrintingTime(int linesLeft, int printerSpeed);

int main()
{
    int numPrinters;
    printf("Enter the number of printers available: ");
    scanf("%d", &numPrinters);

    Document *head = NULL;

    Printer *headPrinter = NULL;
    initializePrinters(&headPrinter, numPrinters);

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
            int id, totalLines;
            char name[100];
            printf("Enter document ID: ");
            scanf("%d", &id);
            printf("Enter document name: ");
            scanf(" %[^\n]", name); // Read name with spaces
            printf("Enter total number of lines: ");
            scanf("%d", &totalLines);

            Document *newDocument = createDocument(id, name, totalLines);
            if (newDocument == NULL)
            {
                break; 
            }

            head = enqueueDocument(head, newDocument);
            printf("Document added to queue.\n");
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
                Document *nextDocument = head;
                head = head->next; 
                assignDocumentToPrinter(headPrinter, nextDocument);
                printf("Assigned document '%s' (ID: %d) for printing.\n", nextDocument->name, nextDocument->id);
                free(nextDocument); 
            }
            break;
        }
        case 3:
            printQueue(head);
            break;
        case 4: {
                int timeStep;
                printf("Enter simulation time step (seconds): ");
                scanf("%d", &timeStep);
                simulatePrinting(headPrinter, timeStep); 
                printf("Simulation completed.\n"); }
                break;
        case 5:
            showStatus(head, headPrinter);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 4);
   
    while (head != NULL)
    {
        Document *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

Document *createDocument(int id, char name[], int totalLines)
{
    Document *newDocument = (Document *)malloc(sizeof(Document));
    if (newDocument == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newDocument->id = id;
    strcpy(newDocument->name, name);
    newDocument->totalLines = totalLines;
    newDocument->linesLeft = totalLines;
    newDocument->next = NULL;
    return newDocument;
}

Document *enqueueDocument(Document *head, Document *newDocument)
{
    if (head == NULL)
    {
        return newDocument;
    }

    Document *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newDocument;
    return head;
}

void simulatePrinting(Printer* headPrinter, int timeStep) {
    for (int i = 0; i < timeStep; i++) {
        Printer* currentPrinter = headPrinter;
        while (currentPrinter != NULL) {
            if (currentPrinter->currentDocument != NULL) {
                int linesPrinted = currentPrinter->printSpeed * timeStep;
                currentPrinter->currentDocument->linesLeft -= linesPrinted;
                
                if (currentPrinter->currentDocument->linesLeft <= 0) {
                    printf("Document %d finished printing.\n", currentPrinter->currentDocument->id);
                    currentPrinter->currentDocument = NULL; // Free printer
                }
            }
            currentPrinter = currentPrinter->next;
        }
    }
}

void printQueue(Document *head)
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
        printf("%d\t%s\t\t%d\t\t%d\n", current->id, current->name, current->totalLines, current->linesLeft);
        current = current->next;
    }
}

Printer *createPrinter(int id, int printSpeed)
{
    Printer *newPrinter = (Printer *)malloc(sizeof(Printer));
    if (newPrinter == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newPrinter->id = id;
    newPrinter->printSpeed = printSpeed;
    newPrinter->currentDocument = NULL;
    newPrinter->next = NULL;
    return newPrinter;
}

void initializePrinters(Printer **headPrinter, int numPrinters)
{
    if (numPrinters <= 0)
    {
        printf("Invalid number of printers. Please enter a positive value.\n");
        return;
    }

    *headPrinter = NULL;

    for (int i = 0; i < numPrinters; i++)
    {
        int printSpeed;
        printf("Enter print speed (lines per millisecond) for printer %d: ", i + 1);
        scanf("%d", &printSpeed);

        Printer *newPrinter = createPrinter(i + 1, printSpeed);
        if (newPrinter == NULL)
        {
            break;
        }

        if (*headPrinter == NULL)
        {
            *headPrinter = newPrinter;
        }
        else
        {
            Printer *current = *headPrinter;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newPrinter;
        }
    }
}

void assignDocumentToPrinter(Printer *headPrinter, Document *document)
{

    if (headPrinter == NULL)
    {
        printf("No printers available for assignment.\n");
        return;
    }

    Printer *currentPrinter = headPrinter;
    while (currentPrinter != NULL)
    {
        if (currentPrinter->currentDocument == NULL)
        { // Find an available printer
            currentPrinter->currentDocument = document;
            return;
        }
        currentPrinter = currentPrinter->next;
    }

    printf("All printers are busy. Document placed on hold.\n");
}

void showStatus(Document *head, Printer *headPrinter)
{
    printf("\nPrint Queue Status:\n");
    printQueue(head); // Reuse the existing printQueue function

    printf("\nPrinter Status:\n");
    if (headPrinter == NULL)
    {
        printf("No printers available.\n");
        return;
    }

    printf("ID\tPrint Speed\tCurrent Document (ID, Lines Left)\n");
    printf("-------\t-----------\t--------------------------------\n");
    Printer *currentPrinter = headPrinter;
    while (currentPrinter != NULL)
    {
        char documentStatus[50];
        if (currentPrinter->currentDocument == NULL)
        {
            strcpy(documentStatus, "Available");
        }
        else
        {
            sprintf(documentStatus, "%d (%d lines left)", currentPrinter->currentDocument->id, currentPrinter->currentDocument->linesLeft);
        }
        printf("%d\t%d\t\t%s\n", currentPrinter->id, currentPrinter->printSpeed, documentStatus);
        currentPrinter = currentPrinter->next;
    }
}

int calculatePrintingTime(int linesLeft, int printerSpeed)
{
    // You can implement this function to estimate printing time based on lines and speed
    // (e.g., consider adding a safety factor or handling potential variations)
    return linesLeft / printerSpeed;
}

void freePrinters(Printer* headPrinter) {
    while (headPrinter != NULL) {
        Printer* temp = headPrinter;
        headPrinter = headPrinter->next;
        free(temp);
    }
}
