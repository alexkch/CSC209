/* Read and execute a list of operations on a linked list.
 * Periodically call the garbage collector.
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "gc.h"

#define MAX_LINE 128
#define ADD_NODE 1
#define DEL_NODE 2
#define PRINT_LIST 3


int main(int argc, char **argv) {
  
    char line[MAX_LINE];
    char *str;

    struct sigaction fstreeSIG;
    fstreeSIG.sa_flags = 0;
    fstreeSIG.sa_handler = mark_sweep_sig;
    
    sigemptyset(&fstreeSIG.sa_mask);
    if(sigaction(SIGUSR1, &fstreeSIG, NULL) != 0){
      exit(1);
    }

 
    if(argc != 2) {
        fprintf(stderr, "Usage: do_trans filename\n");
        exit(1);
    }

    FILE *fp;
    if((fp = fopen(argv[1], "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    List *ll = NULL;
    int count = 1;
    
    while(fgets(line, MAX_LINE, fp) != NULL) {

        char *next;
        int value;
        int type = strtol(line, &next, 0);

        switch(type) {
            case ADD_NODE :
                value = strtol(next, NULL, 0);
                ll = add_node(ll, value);
                break;
            case DEL_NODE :
                value = strtol(next, NULL, 0);
                ll = remove_node(ll, value);
                break;
            case PRINT_LIST :
                str = tostring(ll);
                printf("List is %s\n", str);
		free(str);
                break;
            default :
                fprintf(stderr, "Error: bad transaction type\n");

        }
    
        
        if(count % 10 == 0) {
            mark_and_sweep(ll, mark_list);

	    char check[MAX_LINE];
            fgets(check, MAX_LINE, stdin);
        
	  
	}       
        count++;

    }
    return 0;
}

void mark_sweep_sig(int sig){

    extern Fstree * root;
  
    mark_and_sweep(root, mark_fstree);
    printf("works");
    
}