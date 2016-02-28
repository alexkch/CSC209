/* External functions that are the interface to the garbage collector */

#ifndef LOGFILE
#define LOGFILE "gc.log"
#endif

#define NOT_USED 0
#define USED 1


struct mem_chunk {
    int in_use;
    void * address;
    struct mem_chunk *next;
}; 
typedef struct mem_chunk MemList; 




/* A wrapper around malloc to keep track of dynamically allocated memory
 */
void * gc_malloc(int nbytes);


/* Executes the garbage collector.
 * mark_obj will traverse the data structure rooted at obj, calling
 * mark_one for each dynamically allocated chunk of memory to mark
 * that it is still in use. Uses helpers reset(), sweep(), and mark_list to
 * preform the task. Writes the output to log file using mklog.
 */
void mark_and_sweep(void *obj, void (*mark_obj)(void *));


/* Mark vptr as still in use
 * Return code:
 *   0 on success
 *   1 if memory chunk pointed to by vptr was already marked as in use
 */
int mark_one(void *vptr);


/* Helper function for Mark&Sweep. Reset will change the in_use of every
 * element inside the global MemList to NOTUSED
 */
void reset();


/* Helper function for Mark&Sweep. Sweep will delete all Mem_chunk elements 
 * with their in_use set as NOTUSED. The function will also free the 
 * corresponding address that the Mem_chunk stored and the Mem_chunk node itself 
 */ 
void sweep();


/* Mklog will write to LOGFILE (macro). It will write the addresses of the 
 * current nodes in the memList. MKlog has 2 cases; 1  addresses before sweep 
 *                                                  2  addresses after sweep
 */  
void mklog(int numcase);
