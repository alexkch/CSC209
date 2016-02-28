struct node {
    int value;
    struct node * next;
};
typedef struct node List;

int is_empty(List *);
List *add_node(List *, int);
List *remove_node(List *, int);
List *create_node(int);
char *tostring(List *);
