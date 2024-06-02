#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float grade;
} Student;

void read_array(Student arr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("Enter student %d details (name, age, grade): ", i + 1);
        scanf("%s %d %f", arr[i].name, &arr[i].age, &arr[i].grade);
    }
}

void print_array(Student arr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("Student %d: %s %d %.2f\n", i + 1, arr[i].name, arr[i].age, arr[i].grade);
    }
}

int search_array(Student arr[], int n, char key[])
{
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].name, key) == 0) {
            return i;
        }
    }
    return -1;
}

void sort_array(Student arr[], int n)
{
    Student temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i].name, arr[j].name) > 0) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void insert_at_end(Student arr[], int *n, Student s)
{
    arr[*n] = s;
    (*n)++;
}

void insert_at_beginning(Student arr[], int *n, Student s)
{
    for (int i = *n; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = s;
    (*n)++;
}

void insert_at_position(Student arr[], int *n, Student s, int pos)
{
    for (int i = *n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = s;
    (*n)++;
}

void delete_at_position(Student arr[], int *n, int pos)
{
    for (int i = pos; i < *n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*n)--;
}

int main() {
    int n, choice, pos;
    char key[50];
    Student arr[100], s;

    printf("Enter number of students: ");
    scanf("%d", &n);
    read_array(arr, n);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Read array\n");
        printf("2. Print array\n");
        printf("3. Search array\n");
        printf("4. Sort array\n");
        printf("5. Insert at end\n");
        printf("6. Insert at beginning\n");
        printf("7. Insert at position\n");
        printf("8. Delete at position\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                read_array(arr, n);
                break;
            case 2:
                print_array(arr, n);
                break;
            case 3:
                printf("Enter name to search: ");
                scanf("%s", key);
                pos = search_array(arr, n, key);
                if (pos != -1) {
                    printf("Found at position: %d\n", pos);
                } else {
                    printf("Not found\n");
                }
                break;
            case 4:
                sort_array(arr, n);
                break;
            case 5:
                printf("Enter student details (name, age, grade): ");
                scanf("%s %d %f", s.name, &s.age, &s.grade);
                insert_at_end(arr, &n, s);
                break;
            case 6:
                printf("Enter student details (name, age, grade): ");
                scanf("%s %d %f", s.name, &s.age, &s.grade);
                insert_at_beginning(arr, &n, s);
                break;
            case 7:
                printf("Enter position to insert: ");
                scanf("%d", &pos);
                printf("Enter student details (name, age, grade): ");
                scanf("%s %d %f", s.name, &s.age, &s.grade);
                insert_at_position(arr, &n, s, pos);
                break;
            case 8:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                delete_at_position(arr, &n, pos);
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

