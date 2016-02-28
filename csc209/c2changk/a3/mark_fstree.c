#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fstree.h"
#include "gc.h"


void mark_fstree(Fstree * froot){
  
  /* This function traverses through the fstree datastructure
   * It will mark everything to USED in the global mem_list that
   * can be reached from froot
   */ 
  mark_one(froot->name);
  mark_one(froot);

  Link * link = froot->links;

  while (link != NULL){
    
    mark_one(link);

    if (mark_one(link->fptr) == 0){ //if the call to mark_one returns 0, we know that
                                    //the node hasnt been reached before, thus we recursively call
      mark_one(link->fptr->name);   //onto that node itself 
      mark_fstree(link->fptr);
    }
    
    link = link->next;
      
  }

}
