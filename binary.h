/*************************************************
This work is the property of Christopher Lucinski.
**************************************************/

struct node {
    char * key;
    void * data;
    struct node * child[2];
};

struct root {
    struct node * treeRoot;
};

struct node * new_node(void * ptr, char * keyPtr);

struct node * add_node(struct node * curLocation, struct node * toAdd);

struct node * find_node(struct node * curLocation, char * keyPtr);

void free_tree(struct node * root);
