#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

struct TreeNode
{
    int value;
    struct TreeNode *left_child;
    struct TreeNode *right_child;
};
typedef struct TreeNode TreeNode;

struct Tree
{
    TreeNode *root;
    int size;
};
typedef struct Tree Tree;

Tree *create_tree()
{
    Tree *t = (Tree *)malloc(sizeof(Tree));
    t->root = NULL;
    t->size = 0;
    return t;
}

bool empty_tree(Tree *t)
{
    return t->size == 0;
}

void insert_tree(Tree *t, int value)
{
    TreeNode *tn = (TreeNode *)malloc(sizeof(TreeNode));
    tn->left_child = tn->right_child = NULL;
    tn->value = value;
    if (empty_tree(t))
    {
        t->root = tn;
        t->size++;
        return;
    }
    TreeNode *root = t->root;
    while (true)
    {
        if (value < root->value)
        {
            if (root->left_child == NULL)
            {
                root->left_child = tn;
                t->size++;
                return;
            }
            else
            {
                root = root->left_child;
            }
        }
        else if (value > root->value)
        {
            if (root->right_child == NULL)
            {
                root->right_child = tn;
                t->size++;
                return;
            }
            else
            {
                root = root->right_child;
            }
        }
        else
        {
            break;
        }
    }
}

void insert_tree_mirror(Tree *t, int value)
{
    TreeNode *tn = (TreeNode *)malloc(sizeof(TreeNode));
    tn->left_child = tn->right_child = NULL;
    tn->value = value;
    if (empty_tree(t))
    {
        t->root = tn;
        t->size++;
        return;
    }
    TreeNode *root = t->root;
    while (true)
    {
        if (value > root->value)
        {
            if (root->left_child == NULL)
            {
                root->left_child = tn;
                t->size++;
                return;
            }
            else
            {
                root = root->left_child;
            }
        }
        else if (value < root->value)
        {
            if (root->right_child == NULL)
            {
                root->right_child = tn;
                t->size++;
                return;
            }
            else
            {
                root = root->right_child;
            }
        }
        else
        {
            break;
        }
    }
}

void print_tree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->left_child);
    printf("%d\t", root->value);
    print_tree(root->right_child);
}

bool search(TreeNode *root, int key)
{
    if (root == NULL)
    {
        return false;
    }
    if (root->value == key)
    {
        return true;
    }
    if (key < root->value)
    {
        return search(root->left_child, key);
    }
    return search(root->right_child, key);
}

void inorder_traversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    inorder_traversal(root->left_child);
    printf("%d\t", root->value);
    inorder_traversal(root->right_child);
}

void preorder_traversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d\t", root->value);
    preorder_traversal(root->left_child);
    preorder_traversal(root->right_child);
}

void postorder_traversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    postorder_traversal(root->left_child);
    postorder_traversal(root->right_child);
    printf("%d\t", root->value);
}

void mirror(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    TreeNode *temp = root->left_child;
    root->left_child = root->right_child;
    root->right_child = temp;
    mirror(root->left_child);
    mirror(root->right_child);
}

TreeNode *construct_balanced_tree(int sorted_array[], int start, int end)
{
    if (start > end)
    {
        return NULL;
    }
    int mid = (start + end) / 2;
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->value = sorted_array[mid];
    root->left_child = construct_balanced_tree(sorted_array, start, mid - 1);
    root->right_child = construct_balanced_tree(sorted_array, mid + 1, end);

    return root;
}

Tree *create_balanced_tree(int sorted_array[], int size)
{
    Tree *t = create_tree();
    t->root = construct_balanced_tree(sorted_array, 0, size - 1);
    t->size = size;
    return t;
}

void bubble_sort(int arr[], int n)
{
    int swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}

void print_level_order(TreeNode *root);
void print_current_level(TreeNode *root, int level);
int height(TreeNode *root);

void print_current_level(TreeNode *root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->value);
    else if (level > 1)
    {
        print_current_level(root->left_child, level - 1);
        print_current_level(root->right_child, level - 1);
    }
}

int height(TreeNode *root)
{
    if (root == NULL)
        return 0;
    else
    {
        int lheight = height(root->left_child);
        int rheight = height(root->right_child);

        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

void print_level_order(TreeNode *root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        print_current_level(root, i);
}

void print_tree_matrix(int **M, TreeNode *root, int col, int row, int height)
{
    if (root == NULL)
        return;
    M[row][col] = root->value;
    print_tree_matrix(M, root->left_child, col - (int)pow(2, height - 2), row + 1, height - 1);
    print_tree_matrix(M, root->right_child, col + (int)pow(2, height - 2), row + 1, height - 1);
}

int depth(TreeNode *root)
{
    if (root == NULL)
        return 0;
    else
    {
        int ldepth = depth(root->left_child);
        int rdepth = depth(root->right_child);
        return (ldepth > rdepth) ? (ldepth + 1) : (rdepth + 1);
    }
}

void tree_printer(TreeNode *root)
{
    int h = depth(root);
    int col = (int)pow(2, h) - 1;
    int **M = (int **)malloc(h * sizeof(int *));
    for (int i = 0; i < h; i++)
    {
        M[i] = (int *)malloc(col * sizeof(int));
        for (int j = 0; j < col; j++)
        {
            M[i][j] = 0;
        }
    }
    print_tree_matrix(M, root, col / 2, 0, h);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (M[i][j] == 0)
                printf(" ");
            else
                printf("%d", M[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < h; i++)
    {
        free(M[i]);
    }
    free(M);
}

int main()
{
    Tree *t = create_tree();
    int n;

    printf("number of elements: ");
    scanf("%d", &n);

    int *array = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);
        array[i] = a;
        insert_tree(t, a);
    }
    bubble_sort(array, n);
    int y = 0;
    while (1)
    {
        int option;
        printf("\n\nInorder-1\nPreorder-2\nPostorder-3\nMirror-4\nBfs-5\nBalnsat-6\nPrintarea-7\nIesire-0\n\n\n");
        scanf("%d", &option);
        if (option == 1)
        {
            printf("Inorder traversal: ");
            inorder_traversal(t->root);
            printf("\n");
        }
        else if (option == 2)
        {
            printf("Preorder traversal: ");
            preorder_traversal(t->root);
            printf("\n");
        }
        else if (option == 3)
        {
            printf("Postorder traversal: ");
            postorder_traversal(t->root);
            printf("\n");
        }
        else if (option == 4)
        {
            printf("Mirroring\n");
            mirror(t->root);
            print_tree(t->root);
            printf("\n");
        }
        else if (option == 5)
        {
            printf("BFS\n");
            print_level_order(t->root);
            printf("\n");
        }
        else if (option == 6)
        {
            printf("Balansarea copacului\n");
            Tree *balanced_tree = create_balanced_tree(array, n);
            tree_printer(balanced_tree->root);

            print_tree(balanced_tree->root);
            printf("\n");
            free(balanced_tree);
        }
        else if (option == 7)
        {
            printf("Printing Tree\n");
            tree_printer(t->root);
            print_tree(t->root);
            printf("\n");
        }
        else if (option == 8)
        {
            int g;
            scanf("%d", &g);
            n += g;
            int *array = (int *)realloc(array, n * sizeof(int));

            for (int i = n - 1; i < n; i++)
            {
                int a;
                scanf("%d", &a);
                array[i] = a;
                insert_tree_mirror(t, a);
            }

            printf("Printing Tree\n");
            tree_printer(t->root);
            print_tree(t->root);
            printf("\n");
        }
        else if (option == 0)
        {
            free(array);
            free(t);
            break;
        }
    }
    return 0;
}
