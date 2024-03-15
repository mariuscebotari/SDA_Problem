#include <stdio.h>
#include "functions.h"

Sale *sales = NULL;
int num_sales = 0;


int count_rows(FILE *file) {
    const int buffer_size = 500;
    char buffer[buffer_size];
    int lines = 0;
    while (fgets(buffer, buffer_size, file)) {
        lines++;
    }
    rewind(file);
    return lines ? lines : 0;
}

void read_sales_data(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int num_rows = count_rows(file);

    sales = (Sale *)calloc(num_rows, sizeof(Sale));
    if (sales == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    char line[MAX_COLS * MAX_STRING_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL && num_sales < num_rows) {
        sscanf(line, "%10s,%d,%[^,],%[^,],%[^,],%f,%d,%[^,],%[^\n]",
               sales[num_sales].date, &sales[num_sales].product_id, sales[num_sales].product_name,
               sales[num_sales].category, sales[num_sales].subcategory, &sales[num_sales].unit_price,
               &sales[num_sales].quantity_sold, sales[num_sales].country, sales[num_sales].city);
        num_sales++;
    }

    fclose(file);
}

float calculate_total_revenue(int month, int year) {
    float total_revenue = 0;
    int sale_month, sale_year;
    for (int i = 0; i < num_sales; i++) {
        sscanf(sales[i].date, "%d-%d", &sale_year, &sale_month);

        if (sale_month == month && sale_year == year) {
            total_revenue += sales[i].unit_price * sales[i].quantity_sold;
        }
    }
    return total_revenue;
}

void print_top_5_products() {
    for (int i = 0; i < num_sales - 1; i++) {
        for (int j = i + 1; j < num_sales; j++) {
            float revenue_i = sales[i].unit_price * sales[i].quantity_sold;
            float revenue_j = sales[j].unit_price * sales[j].quantity_sold;
            if (revenue_j > revenue_i) {
                Sale temp = sales[i];
                sales[i] = sales[j];
                sales[j] = temp;
            }
        }

        if (i == 5) {
            break;
        }

    }
    printf("Top 5 products by revenue:\n");
    for (int i = 0; i < 5; i++) {
        float revenue = sales[i].unit_price * sales[i].quantity_sold;
        printf("%d. %s (%s) - Revenue: %.2f\n", i + 1, sales[i].product_name, sales[i].category, revenue);
    }
}

void print_sales_per_category(const char *category) {
    int total_sales = 0;
    for (int i = 0; i < num_sales; i++) {
        if (strcmp(sales[i].category, category) == 0) {
            total_sales += sales[i].quantity_sold;
        }
    }
    printf("Total sales for category '%s': %d\n", category, total_sales);
}

void print_cities_with_highest_sales(const char *country) {
    int max_sales = 0;
    char max_city[MAX_STRING_LENGTH] = "";

    for (int i = 0; i < num_sales; i++) {
        if (strcmp(sales[i].country, country) == 0 && sales[i].quantity_sold > max_sales) {
            max_sales = sales[i].quantity_sold;
            strcpy(max_city, sales[i].city);
        }
    }

    if (max_sales > 0) {
        printf("City with the highest sales for %s: %s (Sales: %d)\n", country, max_city, max_sales);
    } else {
        printf("No sales data found for %s\n", country);
    }
}

void print_monthly_sales_trends(int year) {
    char subcategory[100];
    printf("Input subcategory: ");
    scanf(" %s", subcategory);
    int monthly_sales[12] = {0};

    for (int i = 0; i < num_sales; i++) {
        int sale_year;
        int sale_month;
        sscanf(sales[i].date, "%d-%d", &sale_year, &sale_month);
        if (sale_year == year) {
            if (strcmp(sales[i].subcategory, subcategory) == 0) {
                monthly_sales[sale_month - 1] += sales[i].quantity_sold;
            }
        }
    }

    // printeaza vanzarile lunare
    printf("Monthly sales trends for %d:\n", year);
    for (int i = 0; i < 12; i++) {
        printf("Month %2d: %3d sales\n", i + 1, monthly_sales[i]);
    }
}

void free_sales_data() {
    free(sales);
}

int main() {
    read_sales_data("H:\\CLionProjects\\Seminar\\sales.txt");

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Total revenue for a specific month and year\n");
        printf("2. Top 5 products by revenue\n");
        printf("3. Sales per category\n");
        printf("4. Cities with highest sales for a specific country\n");
        printf("5. Monthly sales trends for a specific year\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1: {
                int month, year;
                printf("Enter month and year (MM YYYY): ");
                scanf("%d %d", &month, &year);
                float revenue = calculate_total_revenue(month, year);
                printf("Total revenue for %d/%d: %.2f\n", month, year, revenue);
                break;
            }
            case 2:
                print_top_5_products();
                break;
            case 3: {
                char category[MAX_STRING_LENGTH];
                printf("Enter category: ");
                scanf("%s", category);
                print_sales_per_category(category);
                break;
            }
            case 4: {
                char country[MAX_STRING_LENGTH];
                printf("Enter country: ");
                scanf("%s", country);
                print_cities_with_highest_sales(country);
                break;
            }
            case 5: {
                int year;
                printf("Enter year: ");
                scanf("%d", &year);
                print_monthly_sales_trends(year);
                break;
            }
            case 6:
                printf("You closed the program!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    free_sales_data();
    return 0;
}