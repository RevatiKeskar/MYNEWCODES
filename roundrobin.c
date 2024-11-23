//Round Robin
#include<stdio.h>

struct Process{
  int pid;
  int at;
  int bt;
  int rbt;
  int wt;
  int tat;
};
void roundrobin(struct Process p[],int n)
{
  int completed=0,time=0,quantumn=2;
  while(completed<n)
  {
    int progress=0;
    for(int i=0;i<n;i++)
    {
      if(p[i].at<=time && p[i].rbt>0){
        progress=1;
        if(p[i].rbt>quantumn)
        {
          p[i].rbt-=quantumn;
          time+=quantumn;
        }
        else{
          time+=p[i].rbt;
          p[i].rbt=0;
          p[i].tat=time-p[i].at;
          p[i].wt=p[i].tat-p[i].bt;
          completed++;
        }
        
      }   
      
    }
    if(!progress)
      {
        time++;
      }
  }
    
  //Calculating waiting time and turnaround time
  float avgwt=0,avgtat=0;
  for(int i=0;i<n;i++)
    {
      avgwt+=p[i].wt;
      avgtat+=p[i].tat;
    }
  avgwt/=n;
  avgtat/=n;
  printf("Averaage waiting time : %f",avgwt);
  printf("Average turnaound time : %f",avgtat);
}

int main()
{
  struct Process p[]={{1,2,4,4,0,0},{2,3,5,5,0,0},{3,2,3,3,0,0},{4,1,2,2,0,0}};
  int n=sizeof(p)/sizeof(p[0]);

  roundrobin(p,n);
}
