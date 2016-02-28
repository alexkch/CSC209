#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <signal.h>

void custom_sig(int sig);

int main(int argc, char * argv[]){
	
	// set i to a random integer between 0 and 99

	char * name = argv[1];
	
	

	struct sigaction newact;
	newact.sa_handler = custom_sig;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
		

	int i;
	FILE * pfile;
	pfile = fopen (name, "r");
	int buf;
	

	if ( sigaction(SIGALRM, &newact, NULL) != 0) {
		exit(1);
	}

	while (1 != 2){
		i = random() % 100;
		fseek(pfile, i, SEEK_SET );
		fread(&buf, 1, sizeof(int), pfile);
		
	}
return 0;
}


void custom_sig(int sig){

	fprintf(stderr, "SIGALRM recieved\n");
	exit(0);
}

