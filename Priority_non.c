//PRIORITY SCHEDULING
#include <stdio.h>

void priorityScheduling(int bt[], int p[], int n) {
    int wt[n], tat[n], proc[n];

  
    for (int i = 0; i < n; i++) {
        proc[i] = i + 1; // Process IDs: P1, P2, ...
    }

 
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j] < p[i]) {
                // Swap priorities
                int temp = p[i];
                p[i] = p[j];
                p[j] = temp;

                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process IDs
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

  
    wt[0] = 0; 
    float avgwt = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
        avgwt += wt[i];
    }
    avgwt /= n;


    float avgtat = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avgtat += tat[i];
    }
    avgtat /= n;

    
    printf("Process\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i], p[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avgwt);
    printf("Average Turnaround Time: %.2f\n", avgtat);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], p[n];
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    printf("Enter priorities:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &p[i]);
    }

    priorityScheduling(bt, p, n);

    return 0;
}
