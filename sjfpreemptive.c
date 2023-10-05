#include<stdio.h>
int main()
int arrival_time[10],burst_time[10],temp[10];
int i,smallest,count=0,time,limit;
double wait_time=0,turnaround_time=0,end;
float average_waiting_time,average_turnaround_time;

   printf("enter the total number of process:");
   scanf("%d",&limit);
   printf("enter the details of  %d proceddesn",limit);
   for(i=0;i<limit;i++)
{
    printf("nenter arrival time:t");
    scanf("%d",&arrival_time[i]);
    printf("enter burst time:t");
     scanf("%d",&burst_time[i]);
     temp[i]=busrt_time[i];
}
burst_time[9]=9999;
for(time=0;count !=limit;time++)
{
      smallest=9;
      for(i=0;i<limit;i++)
{
if(arrival_time[i]<=time && burst_time[i]<burst_time[smallest]&&burst_time[i]>0)
{
    smallest=i;

}
}
burst_time[smallest]--;
if(burst_time[smallest]==0)
{
    count++;
    end=time+1;
    wait_time=wait_time+end-arrival_time[smallest]-temp[smallest]; 
    turnarround_time=turnaround_time+end-arrival_time[smallest];
}
}
average_waiting_time=wait_time/limit;
average_turnaround_time=turnaround_time/limit;

printf("average waiting time:t%lfn",average_waiting_time);
printf("average turnaround time:t%lfn",average_turnaround_time);
return 0;
}
