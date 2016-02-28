#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "fstree.h"
#include "gc.h"


void mark_sweep_sig(int sig);

int main() {
   
    extern Fstree * root;
    root = create_node("root");
    
    //printf("ROOT: %p (size of root: %d)\n", root, sizeof(Fstree));
    //printf("ROOT->name (%s) : %p (size of root: %d)\n\n\n", root->name, root->name, strlen(root->name) + 1);
    //do_transactions("fs_trans1");
    // print_tree(root, 0);

    /* try uncommenting various bits to use other test files */

    do_transactions("fs_trans2");
    print_tree(root, 0);
    
    //do_transactions("fs_trans_loop");
    // don't call print_tree once you have a loop. It isn't sophisticated 
    // enough to handle the loop

/*
    Or you can put the calls directly in here but be careful, you
    can't use string literals for the paths or you will get Segmentation errors.

    add_node("","one");  // add_node (path, name)
    print_tree(root, 0);
    add_node("one","oneone");  // add_node (path, name)
    print_tree(root, 0);
    printf("************\n");

    char dest_path[20] = "one/oneone";
    char src_path[20] = "";
    char name[10] = "one";

    // this makes a link as a child of  one/oneone back to /one
    add_hard_link(dest_path, src_path, name);
    // DON"T call print_tree now since it doesn't handle loops and 
    //  will print infinitely
    // print_tree(root, 0);

*/

    // once you've implemented your garbage collector on fstree, you can
    // call it from here at various points to clean up the garbage
    
    struct sigaction fstreeSIG;
    fstreeSIG.sa_flags = 0;
    fstreeSIG.sa_handler = mark_sweep_sig;
    
    sigemptyset(&fstreeSIG.sa_mask);

    
    if(sigaction(SIGUSR1, &fstreeSIG, NULL) != 0){
      exit(1);
    }
    
    
    usleep(200000000);
    
    
    return 0;
}

void mark_sweep_sig(int sig){

    extern Fstree * root;
  
    mark_and_sweep(root, mark_fstree);
    printf("works");
    
}
