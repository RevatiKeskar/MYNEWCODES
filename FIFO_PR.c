//FIFO page replacement algorithm
#include<stdio.h>

int main()
{
  int pagecnt=0,framecnt=3,fault=0,hit=0,j=0,found;
  int frame[3];
  

  printf("Enter number of pages : ");
  scanf("%d",&pagecnt);
  int page[pagecnt];

  printf("Enter page sequence : ");
  for(int i=0;i<pagecnt;i++){
    scanf("%d",&page[i]);
  }

  //empty the frames
  for(int i=0;i<framecnt;i++){
    frame[i]=-1;
  }

  //Processing pages
  for(int i=0;i<pagecnt;i++){
    found=0;

    //check if page already exists
    for(int k=0;k<framecnt;k++){
      if(frame[k]==page[i])
      {
        hit++;
        found=1;
        break;
      }
    }
    if(!found)
    {
      fault++;
      frame[j]=page[i];
      j=(j+1)%framecnt;
    }

    //Print
    printf("After page %d : ",page[i]);
    for(int k=0;k<framecnt;k++){
      printf("%d \t",frame[k]);
    }
    if(found){
      printf("(HIT)\n");
    }
    else{
      printf("(FAULT)\n");
    }
    
  }
  //Summary
  printf("Page hits : %d",hit);
  printf("Faults : %d",fault);
  printf("HIT ratio : %d/%d",hit,pagecnt);
  printf("FAULT ratio : %d/%d",fault,pagecnt);
  
}
