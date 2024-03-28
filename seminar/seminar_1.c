#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Sale *readSalesData(char *filename, int *numSales)
{
    FILE *file = fopen("C:/Users/grigo/OneDrive/Desktop/SDA_laboratoare/seminar/sales.csv", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);

    Sale *salesArray = NULL;
    int capacity = 0;
    *numSales = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
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

void calculateMonthlyRevenue(Sale *salesArray, int numSales)
{
    float monthlyRevenue[12] = {0};

    for (int i = 0; i < numSales; i++)
    {
        int year, month;
        sscanf(salesArray[i].sale_date, "%4d-%2d", &year, &month); 
        monthlyRevenue[month - 1] += salesArray[i].unit_price * salesArray[i].quantity_sold;
    }

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
    qsort(salesArray, numSales, sizeof(Sale), compareSalesByRevenue);

    printf("\nTop 5 Best-Selling Products:\n");
    for (int i = 0; i < 5 && i < numSales; i++)
    {
        printf("%d. %s (Revenue: %.2f)\n", i + 1, salesArray[i].product_name, salesArray[i].unit_price * salesArray[i].quantity_sold);
    }
}

#define CATEGORY_TABLE_SIZE 1000

typedef struct
{
    char category[50];
    float totalRevenue;
} CategoryBucket;

typedef struct
{
    CategoryBucket *buckets;
    int size;
} CategoryHashTable;

void initializeCategoryHashTable(CategoryHashTable *categoryHashTable)
{
    categoryHashTable->size = CATEGORY_TABLE_SIZE;
    categoryHashTable->buckets = (CategoryBucket *)malloc(sizeof(CategoryBucket) * categoryHashTable->size);

    for (int i = 0; i < categoryHashTable->size; i++)
    {
        strcpy(categoryHashTable->buckets[i].category, "");
        categoryHashTable->buckets[i].totalRevenue = 0.0f;
    }
}

void insertSaleIntoCategoryHashTable(CategoryHashTable *categoryHashTable, Sale *sale)
{
    int index = -1;

    for (int i = 0; i < categoryHashTable->size; i++)
    {
        if (strcmp(categoryHashTable->buckets[i].category, sale->product_category) == 0)
        {
            index = i;
            break;
        }
    }
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

    categoryHashTable->buckets[index].totalRevenue += sale->unit_price * sale->quantity_sold;
}

void freeCategoryHashTable(CategoryHashTable *categoryHashTable)
{
    free(categoryHashTable->buckets);
}

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

typedef struct CountryCitySales {
  char country[50];
  char city[50];
  int totalQuantitySold;
} CountryCitySales;

typedef struct HashNode
{
  CountryCitySales data;
  struct HashNode *next;
} HashNode;

#define TABLE_SIZE 1000

HashNode *hashTable[TABLE_SIZE];

void initializeHashTable()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    hashTable[i] = NULL;
  }
}

int hashFunction(const char *str)
{
  int hash = 0;
  for (int i = 0; str[i] != '\0'; i++)
  {
    hash += str[i];
  }
  return hash % TABLE_SIZE;
}

void insertIntoHashTable(CountryCitySales *data)
{
  int index = hashFunction(data->country);
  HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
  newNode->data = *data;
  newNode->next = NULL;

  if (hashTable[index] == NULL)
  {
    hashTable[index] = newNode;
  }
  else
  {
    HashNode *current = hashTable[index];
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newNode;

    if (data->totalQuantitySold > current->data.totalQuantitySold)
    {
      current->data = *data;
    }
  }
}


void findTopSellingCitiesPerCountry(Sale *salesArray, int numSales, const char *baseFilename)
{
  static int callCount = 0;
  initializeHashTable();

  for (int i = 0; i < numSales; i++)
  {
    CountryCitySales currentSale;
    strcpy(currentSale.country, salesArray[i].sale_country);
    strcpy(currentSale.city, salesArray[i].sale_city);
    currentSale.totalQuantitySold = salesArray[i].quantity_sold;
    insertIntoHashTable(&currentSale);
  }

  char filename[100];
  sprintf(filename, "%s_%d.csv", baseFilename, callCount++);
  FILE *outputFile = fopen(filename, "a");
  if (callCount == 1)
  {
    fprintf(outputFile, "Country,Top Selling City,Total Quantity Sold\n");
  }

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    HashNode *current = hashTable[i];
    while (current != NULL)
    {
      fprintf(outputFile, "%s,%s,%d\n", current->data.country, current->data.city, current->data.totalQuantitySold);
      current = current->next;
    }
  }

  fclose(outputFile);
}

void calculateMonthlySubcategorySales(Sale *salesArray, int numSales, SubcategoryMonthlySales **subcategorySales, int *numSubcategories)
{
    *numSubcategories = 0;
    *subcategorySales = NULL;

    for (int i = 0; i < numSales; i++)
    {
        int subcategoryIndex = -1;

        for (int j = 0; j < *numSubcategories; j++)
        {
            if (strcmp((*subcategorySales)[j].product_subcategory, salesArray[i].product_subcategory) == 0)
            {
                subcategoryIndex = j;
                break;
            }
        }

        if (subcategoryIndex == -1)
        {
            *numSubcategories += 1;
            *subcategorySales = realloc(*subcategorySales, sizeof(SubcategoryMonthlySales) * (*numSubcategories));

            strcpy((*subcategorySales)[*numSubcategories - 1].product_subcategory, salesArray[i].product_subcategory);
            subcategoryIndex = *numSubcategories - 1;

            for (int k = 0; k < 12; k++)
            {
                (*subcategorySales)[subcategoryIndex].monthlyRevenue[k] = 0.0f;
            }
        }

        int year, month;
        sscanf(salesArray[i].sale_date, "%4d-%2d", &year, &month);
        salesArray[i].year = year;
        salesArray[i].month = month;

        (*subcategorySales)[subcategoryIndex].monthlyRevenue[month - 1] += salesArray[i].unit_price * salesArray[i].quantity_sold;
    }
}

void calculateMonthlySalesTrends(SubcategoryMonthlySales *subcategorySales, int numSubcategories)
{
    for (int i = 0; i < numSubcategories; i++)
    {
        printf("\nSubcategory: %s\n", subcategorySales[i].product_subcategory);
        printf("Month\tRevenue\tTrend\n");

        for (int j = 0; j < 12; j++)
        {
            float trend = (subcategorySales[i].monthlyRevenue[j] - subcategorySales[i].monthlyRevenue[j - 1]) / subcategorySales[i].monthlyRevenue[j - 1] * 100.0f;
            printf("%d\t%.2f\t%.2f%%\n", j+1 , subcategorySales[i].monthlyRevenue[j], trend);
        }
    }
}

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
    CategoryHashTable categoryHashTable;
    initializeCategoryHashTable(&categoryHashTable);
    Sale *salesArray = readSalesData("C:/Users/grigo/OneDrive/Desktop/SDA_laboratoare/seminar/sales.csv", &numSales);
    const char *baseFilename = "top_selling_cities"; 
    SubcategoryMonthlySales *subcategorySales = NULL;
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
            printSalesData(salesArray, numSales); 
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
            printf("Exit\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    free(salesArray);

    return 0;
}
