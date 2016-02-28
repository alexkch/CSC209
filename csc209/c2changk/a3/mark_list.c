#include "gc.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
mark_list takes in the head of the linklist data structure, and marks the REACHABLE elements
inside the linked list as used to prevent it from being deleted by the garbage collector
by marking it as USED.

*/
void mark_list(List * Linklist){
  
  
  // Iterate through every single element in the link list and mark it as USED
  while (Linklist != NULL) {
 
    mark_one(Linklist); // Calls mark_one (helper function) which the element as used by the program  
    Linklist = Linklist->next;
  
    
  }
}
