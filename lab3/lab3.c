#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car
{
    char make[50];
    char model[50];
    int year;
};

struct TreeNode
{
    struct Car car;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct BinaryTree
{
    struct TreeNode *root;
};

struct TreeNode *create_node(struct Car car);
struct TreeNode *insert_node(struct TreeNode *root, struct Car car);
void inorder_traversal(struct TreeNode *root);
int calculate_depth(struct TreeNode *root);
struct TreeNode *search_node(struct TreeNode *root, char *make);
int calculate_node_depth(struct TreeNode *root, char *make);
int calculate_node_height(struct TreeNode *root, char *make);
void display_leaves(struct TreeNode *root);
void clean_tree(struct TreeNode *root);
void free_tree(struct TreeNode *root);

int main()
{
    struct BinaryTree tree;
    tree.root = NULL;
    int choice;
    struct Car car;

    do
    {
        printf("\nBinary Tree Operations:\n");
        printf("1. Insert Car\n");
        printf("2. Display Tree (Inorder Traversal)\n");
        printf("3. Calculate Depth of Tree\n");
        printf("4. Search for a Car\n");
        printf("5. Calculate Depth of a Car\n");
        printf("6. Calculate Height of a Car\n");
        printf("7. Display Tree Leaves\n");
        printf("8. Clean Tree\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter car details (make, model, year): ");
            scanf("%s %s %d", car.make, car.model, &car.year);
            tree.root = insert_node(tree.root, car);
            break;
        case 2:
            printf("Tree elements (Inorder Traversal):\n");
            inorder_traversal(tree.root);
            printf("\n");
            break;
        case 3:
            printf("Depth of the tree: %d\n", calculate_depth(tree.root));
            break;
        case 4:
            printf("Enter make of car to search: ");
            char make[50];
            scanf("%s", make);
            if (search_node(tree.root, make) != NULL)
                printf("Car with make %s found.\n", make);
            else
                printf("Car with make %s not found.\n", make);
            break;
        case 5:
            printf("Enter make of car to calculate depth: ");
            scanf("%s", make);
            printf("Depth of the car with make %s: %d\n", make, calculate_node_depth(tree.root, make));
            break;
        case 6:
            printf("Enter make of car to calculate height: ");
            scanf("%s", make);
            printf("Height of the car with make %s: %d\n", make, calculate_node_height(tree.root, make));
            break;
        case 7:
            printf("Tree leaves:\n");
            display_leaves(tree.root);
            printf("\n");
            break;
        case 8:
            clean_tree(tree.root);
            printf("Tree cleaned.\n");
            break;
        case 9:
            free_tree(tree.root);
            printf("Memory freed. Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 9);

    return 0;
}

struct TreeNode *create_node(struct Car car)
{
    struct TreeNode *new_node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (new_node == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->car = car;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct TreeNode *insert_node(struct TreeNode *root, struct Car car)
{
    if (root == NULL)
    {
        root = create_node(car);
    }
    else
    {
        if (strcmp(car.make, root->car.make) <= 0)
        {
            root->left = insert_node(root->left, car);
        }
        else
        {
            root->right = insert_node(root->right, car);
        }
    }
    return root;
}

void inorder_traversal(struct TreeNode *root)
{
    if (root != NULL)
    {
        inorder_traversal(root->left);
        printf("Make: %s, Model: %s, Year: %d\n", root->car.make, root->car.model, root->car.year);
        inorder_traversal(root->right);
    }
}

int calculate_depth(struct TreeNode *root)
{
    if (root == NULL)
        return 0;
    else
    {
        int left_depth = calculate_depth(root->left);
        int right_depth = calculate_depth(root->right);

        if (left_depth > right_depth)
            return left_depth + 1;
        else
            return right_depth + 1;
    }
}

struct TreeNode *search_node(struct TreeNode *root, char *make)
{
    if (root == NULL || strcmp(root->car.make, make) == 0)
        return root;

    if (strcmp(make, root->car.make) < 0)
        return search_node(root->left, make);

    return search_node(root->right, make);
}

int calculate_node_depth(struct TreeNode *root, char *make)
{
    struct TreeNode *node = search_node(root, make);
    if (node == NULL)
        return -1;
    else
        return calculate_depth(node) - 1;
}

int calculate_node_height(struct TreeNode *root, char *make)
{
    struct TreeNode *node = search_node(root, make);
    if (node == NULL)
        return -1;
    else
        return calculate_depth(node) - 1;
}

void display_leaves(struct TreeNode *root)
{
    if (root != NULL)
    {
        display_leaves(root->left);
        if (root->left == NULL && root->right == NULL)
            printf("Make: %s, Model: %s, Year: %d\n", root->car.make, root->car.model, root->car.year);
        display_leaves(root->right);
    }
}

void clean_tree(struct TreeNode *root)
{
    if (root != NULL)
    {
        clean_tree(root->left);
        clean_tree(root->right);
        free(root);
    }
}

void free_tree(struct TreeNode *root)
{
    clean_tree(root);
}
