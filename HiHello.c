#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
void forkexample()
{
     if (fork()==0)
     printf("hello from child \n");
else
       printf("hii from parent \n");
}
int main()
{
forkexample();
return 0;
}

