/*
 * Generate a random series of add, delete, and print operations on a 
 * linked list.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "gc.h"

#define MAX_VAL 100

/* The probability of generating print and add operations
 * The probability of generating a delete operation is 
 * 1 - (PROB_PRINT + PROB_ADD)
 */
#define PROB_PRINT 0.05
#define PROB_ADD 0.55



int main(int argc, char **argv) {
    long type;
    long value;
    int length = 0;
    List *ll;
    //char * outstr; //added
    
    FILE * fp;
    fp = NULL;
    if (argc > 2){
      perror("Too many arguements");
      exit(1);
    }
    
    else if (argc == 2){
      fp = fopen(argv[1], "w");
    }
    
    int i;
    for(i = 0; i < MAX_VAL; i++) {
        double prob = (double)random() / RAND_MAX;
        if(prob < PROB_PRINT) {
            type = 3;
	    printf("%ld\n", type);
	    //outstr = tostring(ll); //added
            //printf("List is %s\n", outstr); //added
	    if (fp) {
	      fprintf(fp, "3\n");
	    }
        }
        if(prob < PROB_PRINT + PROB_ADD) {
            type = 1;
            value = random() % MAX_VAL;
            ll = add_node(ll, value);
            length++;
            printf("%ld %ld\n", type, value);
	    if (fp){
	      fprintf(fp, "1 %ld\n", value);
	    }
        } else {
            type = 2;
            if(length > 0) {
                // choose a node that is in the list to delete
                int index = random() % length;
                value = find_nth(ll, index);
                ll = remove_node(ll, value);
                length--;
                printf("%ld %ld\n", type, value);
		if (fp){
		  fprintf(fp, "2 %ld\n", value);
		}
            } 
        }
    }
    if (fp){
      fclose(fp);
    }
    return 0;
}


