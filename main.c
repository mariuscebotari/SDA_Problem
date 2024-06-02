#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float grade;
} Student;

typedef struct Node{
    Student data;
    struct Node* next;
} Node;

Node* create_node(Student s)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = s;
    new_node->next = NULL;
    return new_node;
}

void read_list(Node** head, int n)
{
    Student s;
    for (int i = 0; i < n; i++) {
        printf("Enter student %d details (name, age, grade): ", i + 1);
        scanf("%s %d %f", s.name, &s.age, &s.grade);
        insert_at_end(head, s);
    }
}

void print_list(Node* head)
{
    Node* temp = head;
    while (temp != NULL) {
        printf("%s %d %.2f\n", temp->data.name, temp->data.age, temp->data.grade);
        temp = temp->next;
    }
}

Node* search_list(Node* head, char key[])
{
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data.name, key) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void sort_list(Node** head)
{
    if (*head == NULL) return;
    Node* i, *j;
    Student temp;
    for (i = *head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->data.name, j->data.name) > 0) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void insert_at_end(Node** head, Student s)
{
    Node* new_node = create_node(s);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void insert_at_beginning(Node** head, Student s)
{
    Node* new_node = create_node(s);
    new_node->next = *head;
    *head = new_node;
}

void insert_at_position(Node** head, Student s, int pos)
{
    Node* new_node = create_node(s);
    if (pos == 0) {
        new_node->next = *head;
        *head = new_node;
        return;
    }
    Node* temp = *head;
    for (int i = 0; temp != NULL && i < pos - 1; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL)
    {
        return;
    }
    new_node->next = temp->next;
    temp->next = new_node;
}

void delete_at_position(Node** head, int pos)
{
    if (*head == NULL) return;
    Node* temp = *head;
    if (pos == 0) {
        *head = temp->next;
        free(temp);
        return;
    }
    for (int i = 0; temp != NULL && i < pos - 1; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        return;
    }
    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

void free_list(Node** head)
{
    Node* temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main() {
    int n, choice, pos;
    char key[50];
    Node* head = NULL;
    Student s;

    printf("Enter number of students: ");
    scanf("%d", &n);
    read_list(&head, n);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Read list\n");
        printf("2. Print list\n");
        printf("3. Search list\n");
        printf("4. Sort list\n");
        printf("5. Insert at end\n");
        printf("6. Insert at beginning\n");
        printf("7. Insert at position\n");
        printf("8. Delete at position\n");
        printf("9. Free list\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter number of students: ");
                scanf("%d", &n);
                read_list(&head, n);
                break;
            case 2:
                print_list(head);
                break;
            case 3:
                printf("Enter name to search: ");
                scanf("%s", key);
                Node* found_node = search_list(head, key);
                if (found_node != NULL) {
                    printf("Found: %s %d %.2f\n", found_node->data.name, found_node->data.age, found_node->data.grade);
                } else {
                    printf("Not found\n");
                }
                break;
            case 4:
                sort_list(&head);
                break;
            case 5:
                printf("Enter student details (name, age, grade): ");
                scanf("%s %d %f", s.name, &s.age, &s.grade);
                insert_at_end(&head, s);
                break;
            case 6:
                printf("Enter student details (name, age, grade): ");
                scanf("%s %d %f", s.name, &s.age, &s.grade);
                insert_at_beginning(&head, s);
                break;
            case 7:
                printf("Enter position to insert: ");
                scanf("%d", &pos);
                printf("Enter student details (name, age, grade): ");
                scanf("%s %d %f", s.name, &s.age, &s.grade);
                insert_at_position(&head, s, pos);
                break;
            case 8:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                delete_at_position(&head, pos);
                break;
            case 9:
                free_list(&head);
                head = NULL;
                break;
            case 10:
                free_list(&head);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
