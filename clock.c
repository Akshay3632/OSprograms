#include <stdio.h>
#include <time.h>
 
int main() {
    clock_t start, end;
  
    start = clock();
  
    printf("Enter any character\n");
    getchar();
    
    end = clock();
   
    double duration = ((double)end - start)/CLOCKS_PER_SEC;
     
    printf("Time taken to execute in seconds : %f", duration);
    return 0;
}

