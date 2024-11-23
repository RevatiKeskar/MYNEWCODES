#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
};

void sjrf_scheduling(struct Process processes[], int n) {
    int completed = 0, time = 0, min_index;

    while (completed < n) {
        int min_remaining_time = INT_MAX;
        min_index = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        processes[min_index].remaining_time--;
        time++;

        if (processes[min_index].remaining_time == 0) {
            completed++;
            processes[min_index].completion_time = time;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    sjrf_scheduling(processes, n);

    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time);
    }

    return 0;
}

