 
 
#include <stdio.h>
#include <string.h>
char * cool();

int main()
{


    char * x;
    x = cool();
    
    
    


    printf("%s \n", x);
    
    
    
    

   return 0;
}


char * cool(){
  
    char * d;
    char str[] = "stack";
    int i = 0;
     d = malloc(8);
    i = snprintf (d, 9, "stockgd");
    printf("%s \n%d\n", d, i);

    
    return str;
    
  
}