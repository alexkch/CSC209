#include <stdio.h>
#include <strings.h>

int main(int argc, char * argv[]) {
	
	
	char * name = argv[1];
	FILE * fp;
	fp = fopen(name, "w");
	
	int i;
	int x;
	for( x = 0; x < 100; x++) {
		
		// set i to a random int between 0 and 99
		i = random() % 100;
		fwrite(&i, sizeof(int), 1, fp);
		
	}
	return 0;
}