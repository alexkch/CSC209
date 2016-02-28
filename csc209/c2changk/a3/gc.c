#include "gc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

MemList * memHead = NULL; //The head of the global MemList variable (the entire program only has one memList)


void * gc_malloc(int nbytes) {
  
  sigset_t sigs;
  sigset_t old_sigs;
  
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGUSR1); 

  //Blocks the signal here, since we dont want malloc to be interrupted
  if (sigprocmask(SIG_BLOCK, &sigs, NULL) != 0) { 
    perror("sigprocmask");
    exit(1);
  }
  
  //setting aside nbytes of memory for whichever function called gc_malloc
  //assign a pointer to the newly allocated memory
  void * malloc_ptr;
  if ((malloc_ptr = malloc(nbytes)) == NULL){
    perror("malloc");
    exit(1);
  }
   
  // creates a struct mem_chunk. Each mem_chunk stores the address of the
  // everything which has been malloced in our program. The mem_chunks make up the 
  // global mem_list.
  MemList * currentPtr;
  currentPtr = memHead;
    
  if (memHead == NULL){
    
    if ((memHead = malloc(sizeof(MemList))) == NULL ){
      perror("malloc");
      exit(1);
    }

    memHead->address = malloc_ptr;
  }
  else {

    if ((currentPtr = malloc(sizeof(MemList))) == NULL ){
	perror("malloc");
	exit(1); 
    }
    
    currentPtr->address = malloc_ptr;
    currentPtr->next = memHead;
    
    memHead = currentPtr;
  }	
  
  //unblocks the signal here, to accept SIGUSR1 
  if (sigprocmask(SIG_UNBLOCK, &sigs, NULL) != 0) {
    perror("sigprocmask");
    exit(1);
  }
  
  //return the pointer back to whichever function called gc_malloc, so they can use
  //the newly allocated memory
  return malloc_ptr; 
}    


void mark_and_sweep(void * obj, void (*mark_obj)(void *)){
  
  reset(); // reset everything in mem_list to NOT_USED 
  
  (*mark_obj)(obj); // mark the elements that can be "reached", using a different function for each
                    // data structure
  mklog(1);// write to log file before sweep     
   
  sweep(); // sweep the memlist
    
  mklog(2);// write the results of sweep 
} 


void reset(){
  
  MemList * currPointer;  

  //goes through the global memList and resets each mem_chunk to NOTUSED
  for (currPointer = memHead; currPointer != NULL; currPointer = currPointer->next){
    currPointer->in_use = NOT_USED;
  }
  
}


void sweep(){
  
  MemList * currPointer;
  MemList * prevPointer;
  
  currPointer = memHead;
  prevPointer = NULL;

  /* For 1st node, indicate there is no previous. 
   * Visit each node, maintaining a pointer to
   * the previous node we just visited.
   */
  while (currPointer != NULL){
    
    if (currPointer->in_use == NOT_USED){ //When we find a element in our memList that is NOT_USED, we want to remove it
      
      if (prevPointer == NULL){
	
	memHead = memHead->next;
	free(currPointer->address);       // Since the data structure already deleted the node, we 
	free(currPointer);                //  should free it as we can never use it anymore, afterwards
	currPointer = currPointer->next;  //  free the unwanted mem_chunk and remove it form the global memList
      }                                    
      else{
	
	prevPointer->next = currPointer->next;
	free(currPointer->address);
	free(currPointer);
	currPointer = currPointer->next;
      }
    }
    else{
      prevPointer = currPointer;
      currPointer = currPointer->next;
    
    }
      
  }
  
}
    

int mark_one(void *vptr){

  
  MemList * currentPtr;
  currentPtr = memHead;
  
  //Takes in an address and looks for it in the global memList. Marks the address
  //to USED if it is in memList and returns 0
  //                  or on failure returns 1
  while (currentPtr != NULL){

    if (currentPtr->address == vptr){
      
      if (currentPtr->in_use == USED){
	return 1;
      }
      else{
	currentPtr->in_use = USED;
	return 0;
      }
    
    }

    currentPtr = currentPtr->next;  

    
  }
  
  return 1;
  
}


void mklog(int numcase){


  //Opens a logfile with the macro name "LOGFILE" (in gc.h)
  //write to it the output of calling mark&sweep
  FILE * logfileptr;
  if ((logfileptr = fopen(LOGFILE, "a")) == NULL){
    perror("fopen");
    exit(1);
  }
   

  int numaddress;
  numaddress = 0;
  MemList * addressptr;
  addressptr = memHead;

  //The cases are just formating, case 1 has formating uses of BEFORE the call to sweep  
  if (numcase == 1){           

    fprintf(logfileptr, "___________________________________________________________\n\n");  
    fprintf(logfileptr, "CALL TO Mark&Sweep\n\n");
    fprintf(logfileptr, "Before Sweep:\n\n");
       
    fprintf(logfileptr, "(Addresses):\n"); 

    
    while (addressptr != NULL){
      numaddress += 1;
      fprintf(logfileptr, "%p\t", ((int * )(addressptr->address)));
      addressptr = addressptr->next;
    }
    fprintf(logfileptr, "\n\nNum addresses in memlist (Before Sweep): %d\n\n\n\n", numaddress);

  }  
  
  //This has formating for AFTER the call to sweep
  else{            
  
    fprintf(logfileptr, "After Sweep\n\n");

    fprintf(logfileptr, "{Addresses):\n"); 
    while (addressptr != NULL){
      numaddress += 1;
      fprintf(logfileptr, "%p\t", ((int * )(addressptr->address)));
      addressptr = addressptr->next;
    }
    fprintf(logfileptr, "\n\nNum addresses in memlist (After Sweep): %d\n\n\n\n", numaddress);


    }

    fclose(logfileptr);

}


