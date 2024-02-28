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
    int month;
    int year;
} Sale;

typedef struct
{
    char product_subcategory[50];
    float monthlyRevenue[12];
} SubcategoryMonthlySales;

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

int compareSalesByRevenue(const void *a, const void *b)
{
    const Sale *sale1 = (const Sale *)a;
    const Sale *sale2 = (const Sale *)b;
    return (sale2->unit_price * sale2->quantity_sold) - (sale1->unit_price * sale1->quantity_sold);
}

void findTop5Products(Sale *salesArray, int numSales)
{
    // In-place calculation and sorting with quicksort
    qsort(salesArray, numSales, sizeof(Sale), compareSalesByRevenue);

    // Print the top 5 best-selling products
    printf("\nTop 5 Best-Selling Products:\n");
    for (int i = 0; i < 5 && i < numSales; i++)
    {
        printf("%d. %s (Revenue: %.2f)\n", i + 1, salesArray[i].product_name, salesArray[i].unit_price * salesArray[i].quantity_sold);
    }
}

#define CATEGORY_TABLE_SIZE 1000 // Choose an appropriate size for the category hash table

// Define a structure to store sales data for each product category
typedef struct
{
    char category[50];
    float totalRevenue;
    // Add other fields as needed
} CategoryBucket;

typedef struct
{
    CategoryBucket *buckets;
    int size;
} CategoryHashTable;

// Function to initialize the category hash table
void initializeCategoryHashTable(CategoryHashTable *categoryHashTable)
{
    categoryHashTable->size = CATEGORY_TABLE_SIZE;
    categoryHashTable->buckets = (CategoryBucket *)malloc(sizeof(CategoryBucket) * categoryHashTable->size);

    if (categoryHashTable->buckets == NULL)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < categoryHashTable->size; i++)
    {
        strcpy(categoryHashTable->buckets[i].category, "");
        categoryHashTable->buckets[i].totalRevenue = 0.0f;
        // Initialize other fields
    }
}

// Function to insert a sale into the category hash table
void insertSaleIntoCategoryHashTable(CategoryHashTable *categoryHashTable, Sale *sale)
{
    int index = -1;

    // Find the index for the given product category
    for (int i = 0; i < categoryHashTable->size; i++)
    {
        if (strcmp(categoryHashTable->buckets[i].category, sale->product_category) == 0)
        {
            index = i;
            break;
        }
    }

    // If the category is not found, create a new entry
    if (index == -1)
    {
        for (int i = 0; i < categoryHashTable->size; i++)
        {
            if (strcmp(categoryHashTable->buckets[i].category, "") == 0)
            {
                index = i;
                strcpy(categoryHashTable->buckets[i].category, sale->product_category);
                break;
            }
        }
    }

    // Update the total revenue for the category
    categoryHashTable->buckets[index].totalRevenue += sale->unit_price * sale->quantity_sold;
}

// Function to free memory used by the category hash table
void freeCategoryHashTable(CategoryHashTable *categoryHashTable)
{
    free(categoryHashTable->buckets);
}

// Function to display sales distribution by category
void displaySalesByCategory(CategoryHashTable *categoryHashTable)
{
    printf("\nSales Distribution by Category:\n");
    for (int i = 0; i < CATEGORY_TABLE_SIZE; i++)
    {
        if (strcmp(categoryHashTable->buckets[i].category, "") != 0)
        {
            printf("Category: %s, Total Revenue: %.2f\n", categoryHashTable->buckets[i].category, categoryHashTable->buckets[i].totalRevenue);
        }
    }
}

typedef struct
{
    char country[50];
    char city[50];
    int totalQuantitySold;
} CountryCitySales;

void findTopSellingCitiesPerCountry(Sale *salesArray, int numSales, const char *baseFilename)
{
    static int callCount = 0; // Static variable to track call count

    // Create an array to store total sales quantity for each city in each country
    int numCountries = 0;
    CountryCitySales *countryCitySales = NULL;

    // Iterate through sales data
    for (int i = 0; i < numSales; i++)
    {
        int countryIndex = -1;

        // Check if the country is already in the array
        for (int j = 0; j < numCountries; j++)
        {
            if (strcmp(countryCitySales[j].country, salesArray[i].sale_country) == 0)
            {
                countryIndex = j;
                break;
            }
        }

        // If the country is not in the array, add it
        if (countryIndex == -1)
        {
            numCountries++;
            countryCitySales = realloc(countryCitySales, numCountries * sizeof(CountryCitySales));
            if (countryCitySales == NULL)
            {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
            strcpy(countryCitySales[numCountries - 1].country, salesArray[i].sale_country);
            countryIndex = numCountries - 1;
        }

        // Update total sales quantity for the city in the country
        countryCitySales[countryIndex].totalQuantitySold += salesArray[i].quantity_sold;
        strcpy(countryCitySales[countryIndex].city, salesArray[i].sale_city);
    }

    // Open output CSV file in append mode ("a")
    char filename[100];
    sprintf(filename, "%s_%d.csv", baseFilename, callCount++); // Generate unique filename using call count
    FILE *outputFile = fopen(filename, "a");
    if (outputFile == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Only write the header row if it's the first call (callCount == 1)
    if (callCount == 1)
    {
        fprintf(outputFile, "Country,Top Selling City,Total Quantity Sold\n");
    }

    // Print data to the CSV file
    for (int i = 0; i < numCountries; i++)
    {
        fprintf(outputFile, "%s,%s,%d\n", countryCitySales[i].country, countryCitySales[i].city, countryCitySales[i].totalQuantitySold);
    }

    // Close the file
    fclose(outputFile);

    // Free allocated memory
    free(countryCitySales);
}

// Function to calculate monthly sales for each subcategory
void calculateMonthlySubcategorySales(Sale *salesArray, int numSales, SubcategoryMonthlySales **subcategorySales, int *numSubcategories)
{
    // Initialize the array to store subcategory sales
    *numSubcategories = 0;
    *subcategorySales = NULL;

    // Iterate through sales data and accumulate revenue for each subcategory and month
    for (int i = 0; i < numSales; i++)
    {
        int subcategoryIndex = -1;

        // Check if the subcategory is already in the array
        for (int j = 0; j < *numSubcategories; j++)
        {
            if (strcmp((*subcategorySales)[j].product_subcategory, salesArray[i].product_subcategory) == 0)
            {
                subcategoryIndex = j;
                break;
            }
        }

        // If the subcategory is not in the array, add it
        if (subcategoryIndex == -1)
        {
            *numSubcategories += 1;
            *subcategorySales = realloc(*subcategorySales, sizeof(SubcategoryMonthlySales) * (*numSubcategories));
            if (*subcategorySales == NULL)
            {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
            strcpy((*subcategorySales)[*numSubcategories - 1].product_subcategory, salesArray[i].product_subcategory);
            subcategoryIndex = *numSubcategories - 1;

            // Initialize monthly revenue array
            for (int k = 0; k < 12; k++)
            {
                (*subcategorySales)[subcategoryIndex].monthlyRevenue[k] = 0.0f;
            }
        }

        // Extract year and month from the date
        int year, month;
        sscanf(salesArray[i].sale_date, "%4d-%2d", &year, &month);
        salesArray[i].year = year;
        salesArray[i].month = month;

        // Accumulate revenue for the subcategory and month
        (*subcategorySales)[subcategoryIndex].monthlyRevenue[month - 1] += salesArray[i].unit_price * salesArray[i].quantity_sold;
    }
}

// Function to calculate trends based on monthly sales
void calculateMonthlySalesTrends(SubcategoryMonthlySales *subcategorySales, int numSubcategories)
{
    // Iterate through subcategories and calculate trends
    for (int i = 0; i < numSubcategories; i++)
    {
        printf("\nSubcategory: %s\n", subcategorySales[i].product_subcategory);
        printf("Month\tRevenue\tTrend\n");

        for (int j = 1; j < 12; j++)
        {
            float trend = (subcategorySales[i].monthlyRevenue[j] - subcategorySales[i].monthlyRevenue[j - 1]) / subcategorySales[i].monthlyRevenue[j - 1] * 100.0f;
            printf("%d\t%.2f\t%.2f%%\n", j + 1, subcategorySales[i].monthlyRevenue[j], trend);
        }
    }
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
    int numSales, choice, numSubcategories;
    // Initialize category hash table
    CategoryHashTable categoryHashTable;
    initializeCategoryHashTable(&categoryHashTable);
    Sale *salesArray = readSalesData("C:/Users/grigo/OneDrive/Desktop/SDA_laboratoare/seminar/sales.csv", &numSales);
    const char *baseFilename = "top_selling_cities"; // Adjust the name as needed
    SubcategoryMonthlySales *subcategorySales = NULL;
    // Read sales data and insert into category hash table
    for (int i = 0; i < numSales; i++)
    {
        insertSaleIntoCategoryHashTable(&categoryHashTable, &salesArray[i]);
    }
    do
    {
        printf("\nMENU:\n");
        printf("1. Print all data from .csv file\n");
        printf("2. Monthly revenue\n");
        printf("3. Top 5 best-selling products\n");
        printf("4. Distribute sales by product category\n");
        printf("5. Top selling cities for each country\n");
        printf("6. Monthly sales for different subcategories of products\n");
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
            break;
        case 4:
            displaySalesByCategory(&categoryHashTable);
            break;
        case 5:
            findTopSellingCitiesPerCountry(salesArray, numSales, baseFilename);
            break;
        case 6:
            calculateMonthlySubcategorySales(salesArray, numSales, &subcategorySales, &numSubcategories);
            calculateMonthlySalesTrends(subcategorySales, numSubcategories);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // Free dynamically allocated memory
    free(salesArray);

    return 0;
}
