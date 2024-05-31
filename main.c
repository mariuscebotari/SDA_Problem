#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int field1;
    int field2;
    int field3;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct QueueNode {
    Node* node;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, Node* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->node = node;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

Node* dequeue(Queue* q) {
    if (q->front == NULL)
        return NULL;

    QueueNode* temp = q->front;
    Node* node = temp->node;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);

    return node;
}


Node* insert_node(Node* root, int key, int field1, int field2, int field3) {
    if (root == NULL){
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->key = key;
        new_node->field1 = field1;
        new_node->field2 = field2;
        new_node->field3 = field3;
        new_node->left = new_node->right = NULL;
        return new_node;
    }
    if (key < root->key)
        root->left = insert_node(root->left, key, field1, field2, field3);
    else if (key > root->key)
        root->right = insert_node(root->right, key, field1, field2, field3);

    return root;
}

void print_2D_util(Node *root, int space) {
    int i;

    if (root == NULL)
        return;

    space += 10;

    print_2D_util(root->right, space);

    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    print_2D_util(root->left, space);
}

void print_2D(Node *root) {
    print_2D_util(root, 0);
}
//balance tree AVL algorithm
int get_height(Node* node) {
    if (node == NULL)
        return 0;
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

Node* perform_right_rotation(Node* root) {
    Node* new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    return new_root;
}

Node* perform_left_rotation(Node* root) {
    Node* new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    return new_root;
}

Node* balance_tree(Node* root) {
    if (root == NULL)
        return root;

    if (get_height(root->left) - get_height(root->right) > 1) {
        if (get_height(root->left->left) >= get_height(root->left->right))
            root = perform_right_rotation(root);
        else {
            root->left = perform_left_rotation(root->left);
            root = perform_right_rotation(root);
        }
    }
    else if (get_height(root->right) - get_height(root->left) > 1) {
        if (get_height(root->right->right) >= get_height(root->right->left))
            root = perform_left_rotation(root);
        else {
            root->right = perform_right_rotation(root->right);
            root = perform_left_rotation(root);
        }
    }

    return root;
}

Node* perform_search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return perform_search(root->right, key);

    return perform_search(root->left, key);
}

Node* mirror_tree(Node* root) {
    if (root == NULL)
        return root;

    Node* temp = root->left;
    root->left = mirror_tree(root->right);
    root->right = mirror_tree(temp);

    return root;
}

Node* clear_tree(Node* root) {
    if (root == NULL)
        return root;

    root->left = clear_tree(root->left);
    root->right = clear_tree(root->right);

    free(root);

    return NULL;
}

Node* free_tree(Node* root) {
    if (root == NULL)
        return root;

    root->left = free_tree(root->left);
    root->right = free_tree(root->right);

    free(root);

    return NULL;
}

void perform_inorder_traversal(Node* root) {
    if (root != NULL) {
        perform_inorder_traversal(root->left);
        printf("%d \n", root->key);
        perform_inorder_traversal(root->right);
    }
}

void perform_preorder_traversal(Node* root) {
    if (root != NULL) {
        printf("%d \n", root->key);
        perform_preorder_traversal(root->left);
        perform_preorder_traversal(root->right);
    }
}

void perform_postorder_traversal(Node* root) {
    if (root != NULL) {
        perform_postorder_traversal(root->left);
        perform_postorder_traversal(root->right);
        printf("%d \n", root->key);
    }
}

void perform_depth_first_search(Node* root) {
    if (root == NULL)
        return;

    printf("%d \n", root->key);
    perform_depth_first_search(root->left);
    perform_depth_first_search(root->right);
}

void perform_breadth_first_search(Node* root) {
    if (root == NULL)
        return;

    Queue* q = create_queue();
    enqueue(q, root);

    while (q->front != NULL) {
        Node* node = dequeue(q);

        printf("%d \n", node->key);

        if (node->left != NULL)
            enqueue(q, node->left);

        if (node->right != NULL)
            enqueue(q, node->right);
    }

    free(q);
}

int main(void){
    Node *root = NULL;
    Node *search_result = NULL;
    int choice, key, field1, field2, field3;

    while(1) {
        printf("\n1. Insert \n2. Print tree \n3. Search and print node \n4. Inorder traversal \n"
               "5. Preorder traversal \n6. Postorder traversal \n7. Depth-first search (DFS) \n"
               "8. Breadth-first search (BFS) \n9. Balance tree \n10. Mirror tree \n"
               "11. Clear tree \n12. Free tree \n13. Exit \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key, field1, field2, and field3 to be inserted: ");
                scanf("%d %d %d %d", &key, &field1, &field2, &field3);
                root = insert_node(root, key, field1, field2, field3);
                break;
            case 2:
                printf("The binary tree is: \n");
                print_2D(root);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search_result = perform_search(root, key);
                if(search_result == NULL)
                    printf("Key not found in tree \n");
                else
                    printf("Node found: key = %d, field1 = %d, field2 = %d, field3 = %d\n",
                           search_result->key, search_result->field1, search_result->field2, search_result->field3);
                break;
            case 4:
                printf("Inorder traversal of the binary tree is: \n");
                perform_inorder_traversal(root);
                break;
            case 5:
                printf("Preorder traversal of the binary tree is: \n");
                perform_preorder_traversal(root);
                break;
            case 6:
                printf("Postorder traversal of the binary tree is: \n");
                perform_postorder_traversal(root);
                break;
            case 7:
                printf("Depth-first search (DFS) of the binary tree is: \n");
                perform_depth_first_search(root);
                break;
            case 8:
                printf("Breadth-first search (BFS) of the binary tree is: \n");
                perform_breadth_first_search(root);
                break;
            case 9:
                printf("Balancing the binary tree... \n");
                root = balance_tree(root);
                break;
            case 10:
                printf("Mirroring the binary tree... \n");
                root = mirror_tree(root);
                break;
            case 11:
                printf("Clearing the binary tree... \n");
                root = clear_tree(root);
                break;
            case 12:
                printf("Freeing the binary tree... \n");
                root = free_tree(root);
                break;
            case 13:
                printf("Exiting the program... \n");
                exit(0);
            default:
                printf("Invalid choice \n");
        }
    }

    return 0;
}
