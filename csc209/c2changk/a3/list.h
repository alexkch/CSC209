//Linklist data-structure

struct node {
    int value;
    struct node * next;
};
typedef struct node List;


//Function Headers for list.c

int is_empty(List *);
int length(List *);
List *add_node(List *,  int);
List *create_node(int);
List *remove_node(List *, int); 
int find_nth(List *, int n);
char *tostring(List *);

/*
 * The mark function for linked list which takes in a linked list datastructure
 * and marks all avaliable addresses that can be reached from the linked list
 * in the memList to USED
 */
void mark_list(List *);
