
#include<stdio.h>
int checkHit(int page,int pageframe[],int filled){
    for(int i=0;i<filled;i++){
        if(page==pageframe[i]) return 1;
    }
    return 0;
}

void printFrame(int page,int pageframe[],int filled){
    printf("%d :\t",page);
    for(int i=0;i<filled;i++){
        printf("%d\t",pageframe[i]);
    }
}
int main(){
    int pages[]={3,0,1,1,0,2,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int n=sizeof(pages)/sizeof(pages[0]);

    int pageframe[3];
    int filled=0;
    int pagefault=0;
    printf("Page\tFrame1\tFrame2\tFrame3\n");

    for(int i=0;i<n;i++){
        int page=pages[i];
        if(checkHit(page,pageframe,filled)){
            printFrame(page,pageframe,filled);
        }else if(filled < 3){
            pagefault++;
            pageframe[filled++]=page;
            printFrame(page,pageframe,filled);
        }else{
           int distance[3]={0};
            int maxDistance=0;
            int index;
           for(int j=0;j<filled;j++){
                for(int k=i+1;k<n;k++){
                    distance[j]++;
                    if(pageframe[j]==pages[k]){

                        break;
                    }
                }
                if(maxDistance < distance[j]){
                    maxDistance=distance[j];
                    index=j;
                }
           }

           for(int j=0;j<filled;j++){
            if(distance[j]==0){
                distance[j]=n;
            }
           }

           for(int j=0;j<filled;j++){
            if(maxDistance < distance[j]){
                maxDistance=distance[j];
                index=j;
            }
           }

           pageframe[index]=page;
           pagefault++;
           printFrame(page,pageframe,filled);

        }
        printf("\n");
    }


    int hits=n-pagefault;
    printf("\nNumber of hits : %d\n",hits);
    printf("Number of Fault : %d\n",pagefault);
    printf("Number of Pages : %d\n",n);
    printf("Hits ratio : %d/%d\n",hits,n);
    printf("Fault ratio : %d/%d\n",pagefault,n);
}
