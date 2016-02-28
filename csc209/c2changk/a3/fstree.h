struct subdir {
	struct fsnode *fptr;
	struct subdir *next;
};

typedef struct subdir Link;

struct fsnode {
	char *name;
	Link *links;
};

typedef struct fsnode Fstree;

#define MAX_PATH 256
#define MAX_LINE 1024

/*
 * All definition of functions are in fstree.c
 *
 */


Fstree *create_node(char *name);
void add_node(char *path, char *name);
void add_hard_link(char *dest_path, char *src_path, char *name);
void remove_node(char *path, char *name);
void do_transactions(char *transfile);
void print_tree(Fstree *f, int depth);

/*
 * The mark function for fstree which takes in a Fstree datastructure
 * and marks all avaliable addresses that can be reached from the Fstree
 * in the memList to USED
 */
void mark_fstree(Fstree *);
