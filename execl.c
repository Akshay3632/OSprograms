#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
pid_t pid;

pid=fork();
 
if(pid<0)
{
 perror("fork failed");
 exit(1);
  }
  else if(pid==0)
{
printf("child process executting...\n");
 
char*command="ls";
if(execlp(command,command,(char*)NULL)==-1)
{
perror("exec failed");
exit(1);
}
}
else
{
printf("parent procesws sleeping..\n");
sleep(5);
printf("parent process eoke up.\n");
}
return 0;
}
