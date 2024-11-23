//ZOMBIE
//Zombie

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void swap(int *a,int *b)
{
  int temp;
  temp=*a;
  *a=*b;
  *b=temp;
}

void ascending(int arr[],int n)
{
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if(arr[i]>arr[j])
      {swap(&arr[i],&arr[j]);}
    }
  }
  //print
  for(int i=0;i<n;i++){
    printf("%d\t",arr[i]);
  }
}

void descending(int arr[],int n)
{
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if(arr[i]<arr[j])
      {swap(&arr[i],&arr[j]);}
    }
  }
  //print
  for(int i=0;i<n;i++){
    printf("%d\t",arr[i]);
  }
}

int main()
{
  int n;
  printf("Enter number of elements: ");
  scanf("%d",&n);
  int *arr;
  
  //dynamically allocate memory to the array
  arr=(int*)malloc(n*sizeof(int));
  
  printf("Enter array elements : ");
  for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
  }

  //start forking process
  printf("Hi i am the current running process pid = %d\tppid=%d\n",getpid(),getppid());

  int pid=fork();

  if(pid<0)
  {
    printf("Error");
    exit(0);
  }
  else if(pid==0)//Child 
  {
    descending(arr,n);
    for(int i=0;i<n;i++){
    printf("i=%d\tarr=%d\tp=%d\tpid=%d\tppid=%d\n",i,arr[i],pid,getpid(),getppid());
    sleep(2);
    }
    printf("Child process completed!");
  }
  else{  //parent
    ascending(arr,n);
    printf("PID = %d,PPID = %d",getpid(),getppid());
    sleep(5);
    for(int i=0;i<n;i++){
      printf("i=%d\tarr=%d\tp=%d\tpid=%d\tppid=%d\n",i,arr[i],pid,getpid(),getppid());
      sleep(5);
    }
  }
  printf("Exiting parent process PID = %d\tPPID = %d\n",getpid(),getppid());
  return 0;
}
