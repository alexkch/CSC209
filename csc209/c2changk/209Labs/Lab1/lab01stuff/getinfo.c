#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

int main() {
	char stu_name[MAX];
	char classes[MAX];

	/* Note that printf("Please enter your name:\n"); is the same as the 
	line below.  The fprintf call makes it explicit where the output is
	going. */

	fprintf(stdout, "Please enter your name:\n");

	/* fgets is reading a line of input from stdin, and saving it in the 
	 * character array stu_name. We want to record that there is an error
	 * if it wasn't able to read from stdin or if the input was empty (only
	 * an newline character).
	 */
	if((fgets(stu_name, MAX, stdin) == NULL) || (strlen(stu_name) <= 1)) {
		fprintf(stderr, "Error: name was not supplied\n");
		return(1);
	}

	/* Remove the newline character */
	stu_name[strlen(stu_name) - 1] = '\0';

	printf("Please enter your classes this term:\n");
	if(fgets(classes, MAX, stdin) == NULL || strlen(classes) <= 1) {
		fprintf(stderr, "Error: no classes were entered.\n");
		return(1);
	}

	classes[strlen(classes) - 1] = '\0';

	/* Look for the end of the first word in the array, and put a null
	 * termination character in, effectively truncating the list to be
	 * only the first word. 
	 */
 	char *space = index(classes, ' ');
	if (space != NULL) { 
		*space = '\0';
	}

	printf("Hi %s, are you enjoying %s?\n", stu_name, classes);

	return 0;
}
