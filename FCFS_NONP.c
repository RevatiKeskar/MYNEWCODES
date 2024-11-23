//FCFS SCHEDULING ALGORITHM
#include<stdio.h>
float findwaitingtime(int bt[],int wt[],int n)
{
  wt[0]=0;
  float avgwt=0;
  for(int i=1;i<n;i++)
  {
    wt[i]=bt[i-1]+wt[i-1]; //burst time of previous process + waiting time of previous process
    avgwt+=wt[i];
  }
  avgwt/=n;
  return avgwt;
}


float findturnaroundtime(int bt[],int wt[],int tat[],int n)
{
  float avgtat=0;
  for(int i=0;i<n;i++)
    {
      tat[i]=bt[i]+wt[i];//tat=brust time + waiting time 
      avgtat+=tat[i];
    }
  avgtat/=n;
  return avgtat;
}


void fcfs(int bt[],int n)
{
  int wt[n],tat[n];

  //Calculating waiting time
  float avgwt=findwaitingtime(bt,wt,n);
  //Calculating turnaround time
  float avgtat=findturnaroundtime(bt,wt,tat,n);

  //print
  printf("Average waiting time : %f",avgwt);
  printf("Average turnaround time : %f",avgtat);
  
}
int main(){
  int n;
  printf("Enter number of processes : ");
  scanf("%d",&n);

  //enter burst time of processess
  int bt[n];
  printf("Enter burst time of processes : ");
  for(int i=0;i<n;i++){
    scanf("%d",&bt[i]);
  }

  fcfs(bt,n);
}
