#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure to store sales data
typedef struct
{
    char sale_date[11];
    int product_id;
    char product_name[50];
    char product_category[50];
    char product_subcategory[50];
    float unit_price;
    int quantity_sold;
    char sale_country[50];
    char sale_city[50];
} Sale;

// Function to read sales data from CSV file into a dynamic array
Sale *readSalesData(char *filename, int *numSales)
{
    FILE *file = fopen("C:/Users/grigo/OneDrive/Desktop/SDA_laboratoare/seminar/sales.csv", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Assuming the first line in the file contains headers
    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);

    // Initialize a dynamic array to store sales data
    Sale *salesArray = NULL;
    int capacity = 0;
    *numSales = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Resize the array if needed
        if (*numSales == capacity)
        {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            salesArray = realloc(salesArray, capacity * sizeof(Sale));
            if (salesArray == NULL)
            {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
        }

        // Parse the CSV line and store data in the array
        sscanf(buffer, "%[^,],%d,%[^,],%[^,],%[^,],%f,%d,%[^,],%[^\n]",
               salesArray[*numSales].sale_date,
               &salesArray[*numSales].product_id,
               salesArray[*numSales].product_name,
               salesArray[*numSales].product_category,
               salesArray[*numSales].product_subcategory,
               &salesArray[*numSales].unit_price,
               &salesArray[*numSales].quantity_sold,
               salesArray[*numSales].sale_country,
               salesArray[*numSales].sale_city);
        (*numSales)++;
    }
    fclose(file);
    return salesArray;
}

// Function to calculate total revenue for each month
void calculateMonthlyRevenue(Sale *salesArray, int numSales)
{
    // Create an array to store monthly revenue
    float monthlyRevenue[12] = {0};

    // Iterate through sales data and accumulate revenue for each month
    for (int i = 0; i < numSales; i++)
    {
        int year, month;
        sscanf(salesArray[i].sale_date, "%4d-%2d", &year, &month); // Extract year and month from the date
        monthlyRevenue[month - 1] += salesArray[i].unit_price * salesArray[i].quantity_sold;
    }

    // Print the results
    printf("Monthly Revenue:\n");
    for (int i = 0; i < 12; i++)
    {
        printf("Month %d: %.2f\n", i + 1, monthlyRevenue[i]);
    }
}

int compareSalesByRevenue(const void *a, const void *b) {
  const Sale *sale1 = (const Sale *)a;
  const Sale *sale2 = (const Sale *)b;
  return (sale2->unit_price * sale2->quantity_sold) - (sale1->unit_price * sale1->quantity_sold);
}

void findTop5Products(Sale *salesArray, int numSales) {
  // In-place calculation and sorting with quicksort
  qsort(salesArray, numSales, sizeof(Sale), compareSalesByRevenue);

  // Print the top 5 best-selling products
  printf("Top 5 Best-Selling Products:\n");
  for (int i = 0; i < 5 && i < numSales; i++) {
    printf("%d. %s (Revenue: %.2f)\n", i + 1, salesArray[i].product_name, salesArray[i].unit_price * salesArray[i].quantity_sold);
  }
}

// Function to distribute sales by product category
void distributeSalesByCategory(Sale *salesArray, int numSales)
{
}

// Function to print sales data
void printSalesData(Sale *salesArray, int numSales)
{
    for (int i = 0; i < numSales; i++)
    {
        printf("Sale Date: %s\n", salesArray[i].sale_date);
        printf("Product ID: %d\n", salesArray[i].product_id);
        printf("Product Name: %s\n", salesArray[i].product_name);
        printf("Product Category: %s\n", salesArray[i].product_category);
        printf("Product Subcategory: %s\n", salesArray[i].product_subcategory);
        printf("Unit Price: %.2f\n", salesArray[i].unit_price);
        printf("Quantity Sold: %d\n", salesArray[i].quantity_sold);
        printf("Sale Country: %s\n", salesArray[i].sale_country);
        printf("Sale City: %s\n", salesArray[i].sale_city);
        printf("---------------------\n");
    }
}

int main()
{
    int numSales, choice;
    Sale *salesArray = readSalesData("C:/Users/grigo/OneDrive/Desktop/SDA_laboratoare/seminar/sales.csv", &numSales);

    do
    {
        printf("\nMENU:\n");
        printf("1. Print all data from .csv file\n");
        printf("2. Monthly revenue\n");
        printf("3. Top 5 best-selling products\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printSalesData(salesArray, numSales); // Call function to print sales data
            break;
        case 2:
            calculateMonthlyRevenue(salesArray, numSales);
            break;
        case 3:
            findTop5Products(salesArray, numSales);
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);


    // Call functions to answer business questions
    
    distributeSalesByCategory(salesArray, numSales);

    // Free dynamically allocated memory
    free(salesArray);

    return 0;
}
