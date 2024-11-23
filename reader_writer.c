//READER WRITER
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>

//Global semaphores
sem_t read_count_mutex;
sem_t resource;
//shared data
int read_count=0;

void* reader(void *arg)
{
  int reader_id=((int)arg);
  free(arg);
  
  while(1){
    //Entry section for reader
    sem_wait(&read_count_mutex);
    read_count++;
    if(read_count==1){
      sem_wait(&resource);
    }
    sem_post(&read_count_mutex);
    
    //critical section
    printf("Reader %d is reading\n",reader_id);
    sleep(rand()%3+1);
    printf("Reader %d has finished reading\n",reader_id);
    
    //Exit section for reader
    sem_wait(&read_count_mutex);
    read_count--;
    if(read_count==0){
      sem_post(&resource);
    }
    sem_post(&read_count_mutex);
    sleep(rand()%3+1);
  }
  return NULL;
}
void* writer(void *arg)
{
  int writer_id=((int)arg);
  free(arg);
  
  while(1){

    printf("Writer %d is now trying to write..",writer_id);
    sem_wait(&resource);
    //critical section
    printf("Writer %d is writing\n",writer_id);
    sleep(rand()%3+1);
    printf("Writer %d has finished writer\n",writer_id);
    sem_post(&resource);
    sleep(rand()%4+2);
    
  }
  return NULL;
}
int main()
{
  pthread_t readers[3];
  pthread_t writers[2];

  //initialize semaphores
  sem_init(&read_count_mutex,0,1);
  sem_init(&resource,0,1);

  //create reader threds
  for(int i=0;i<3;i++){
    int  *id=malloc(sizeof(int));
    *id=i+1;
    pthread_create(&readers[i],NULL,reader,id);
  
  }

  //create writer threads
  for(int i=0;i<3;i++)
    {
      int * id=malloc(sizeof(int));
      *id=i+1;
      pthread_create(&writers[i],NULL,writer,id);
    }

  //Wait for threads to finish loop
  for(int i=0;i<3;i++){
    pthread_join(readers[i],NULL);
  }
  for(int i=0;i<2;i++){
    pthread_join(writers[i],NULL);
  }

  sem_destroy(&read_count_mutex);
  sem_destroy(&resource);
  return 0;
}
