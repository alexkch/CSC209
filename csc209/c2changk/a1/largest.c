#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32 //since max is define as 31 (assumption given)

int main(int argc, char ** argv) {

    char directory[1] = {"-"}; //comparison string to see if the file is a 
                                //file
    char permission[MAX]; //permission storage
    int d; //garbage storage for unwanted information
    char storage[MAX]; //garbage storage for unwanted information
    char group[MAX]; //group name storage 
    int size; //size storage
    int largest = 0; //largest file starts at default 0 size
    char file[MAX]; //filename storage
    char largest_file[MAX]; //largest file name we want to return

    scanf("%s %s", storage, storage); //skips over first line "total NUM" 

    while (scanf("%s %d %s %s %d %s %d %s %s", permission, &d, storage, group, &size, storage, &d, storage, &file) == 9) {
      //while loop which loops over each line, since each line has 9 parts information we want, the loop
      // will terminate when scanf cannot assign the 9 parameters with the given standard input

    /*  TEST CASES
    printf("%s %d %s %s %d %s %d %s %s\n", permission, d, storage, group, size, storage, d, storage, file);
    printf("%d\n", size);
    printf("%d\n", largest);
    printf("%d\n", (size > largest));
    */
    
    if ((strncmp(permission, directory, 1) == 0)){ 
    //tests if it is a file 
    
         if (argc != 0){
	   //executes if commandline arg is given

	   //checks to see if group is the same as the commandline arg, as well as if the size is the largest
	   // updates largest file name and size iff the requirement above is met
            if ((strcmp(group, argv[2]) == 0) && (size > largest) == 1){
                largest = size;
                strncpy(largest_file, file, MAX);

                }
            }
	 else { //executes if no arg is given in commandline
	   if ((size > largest) == 1){ //updates only if the new size is larger then the current largest
                largest = size;
                strncpy(largest_file, file, MAX);
            }

        }   
    }
    
    /* TEST CASES
    printf("%s %d %s %s %d %s %d %s %s\n", permission, d, storage, group, size, storage, d, storage, file);
    printf("%d\n", largest);
    */
}

/* EXIT LOOP TEST
printf("%s %d %s %s %d %s %d %s %s\n", permission, d, storage, group, size, storage, d, storage, file);
*/


printf("%d\t", largest);

printf("%s", largest_file);

return 0;
}
