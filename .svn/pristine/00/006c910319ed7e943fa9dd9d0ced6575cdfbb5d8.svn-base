/***************************
 *  * binarytree.h
 *   ***************************/

typedef char DATA;

struct node
{
 DATA d;
 struct node *left;
 struct node *right;
};

typedef struct node NODE;
typedef NODE *BTREE;
//define a new type called BTREE which is a pointer to the NODE
BTREE newnode(void);

BTREE init_node(DATA d, BTREE p1, BTREE p2);

BTREE create_tree(DATA a[], int i, int size);

void preorder (BTREE root);

void inorder (BTREE root);

void postorder (BTREE root);

