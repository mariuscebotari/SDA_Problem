#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float grade;
} Student;

typedef struct Node {
    Student data;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(Student s) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = s;
    new_node->left = new_node->right = NULL;
    return new_node;
}

Node* insert_node(Node* root, Student s) {
    if (root == NULL) {
        return create_node(s);
    }
    if (strcmp(s.name, root->data.name) < 0) {
        root->left = insert_node(root->left, s);
    } else if (strcmp(s.name, root->data.name) > 0) {
        root->right = insert_node(root->right, s);
    }
    return root;
}

void inorder_traversal(Node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%s %d %.2f\n", root->data.name, root->data.age, root->data.grade);
        inorder_traversal(root->right);
    }
}

int calculate_depth(Node* root) {
    if (root == NULL) return 0;
    int left_depth = calculate_depth(root->left);
    int right_depth = calculate_depth(root->right);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

Node* search_node(Node* root, char key[]) {
    if (root == NULL || strcmp(root->data.name, key) == 0) {
        return root;
    }
    if (strcmp(key, root->data.name) < 0) {
        return search_node(root->left, key);
    }
    return search_node(root->right, key);
}

int calculate_node_depth(Node* root, char key[], int depth) {
    if (root == NULL) return -1;
    if (strcmp(root->data.name, key) == 0) {
        return depth;
    }
    if (strcmp(key, root->data.name) < 0) {
        return calculate_node_depth(root->left, key, depth + 1);
    }
    return calculate_node_depth(root->right, key, depth + 1);
}

int calculate_node_height(Node* node) {
    if (node == NULL) return 0;
    int left_height = calculate_node_height(node->left);
    int right_height = calculate_node_height(node->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

void print_leaves(Node* root) {
    if (root != NULL) {
        print_leaves(root->left);
        if (root->left == NULL && root->right == NULL) {
            printf("%s %d %.2f\n", root->data.name, root->data.age, root->data.grade);
        }
        print_leaves(root->right);
    }
}

void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    int choice;
    char key[50];
    Node* root = NULL;
    Student s;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert node\n");
        printf("2. Inorder traversal\n");
        printf("3. Calculate tree depth\n");
        printf("4. Search node\n");
        printf("5. Calculate node depth\n");
        printf("6. Calculate node height\n");
        printf("7. Print leaves\n");
        printf("8. Free tree\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter student details (name, age, grade): ");
                scanf("%s %d %f", s.name, &s.age, &s.grade);
                root = insert_node(root, s);
                break;
            case 2:
                inorder_traversal(root);
                break;
            case 3:
                printf("Tree depth: %d\n", calculate_depth(root));
                break;
            case 4:
                printf("Enter name to search: ");
                scanf("%s", key);
                Node* found_node = search_node(root, key);
                if (found_node != NULL) {
                    printf("Found: %s %d %.2f\n", found_node->data.name, found_node->data.age, found_node->data.grade);
                } else {
                    printf("Not found\n");
                }
                break;
            case 5:
                printf("Enter name to search for depth calculation: ");
                scanf("%s", key);
                int depth = calculate_node_depth(root, key, 0);
                if (depth != -1) {
                    printf("Node depth: %d\n", depth);
                } else {
                    printf("Not found\n");
                }
                break;
            case 6:
                printf("Enter name to search for height calculation: ");
                scanf("%s", key);
                Node* node_for_height = search_node(root, key);
                if (node_for_height != NULL) {
                    printf("Node height: %d\n", calculate_node_height(node_for_height));
                } else {
                    printf("Not found\n");
                }
                break;
            case 7:
                print_leaves(root);
                break;
            case 8:
                free_tree(root);
                root = NULL;
                break;
            case 9:
                free_tree(root);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
