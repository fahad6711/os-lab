#include <stdio.h>

#define MAX_PARTITIONS 10

void worstFit(int partitions[], int np, int processes[], int n);

int main() {
    int partitions[MAX_PARTITIONS], processes[MAX_PARTITIONS];
    int np, n, i;
    
    printf("Enter number of memory partitions: ");
    scanf("%d", &np);
    
    printf("Enter sizes of %d partitions: ", np);
    for(i = 0; i < np; i++) {
        scanf("%d", &partitions[i]);
    }
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter sizes of %d processes: ", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &processes[i]);
    }
    
    printf("\nWorst Fit Allocation:\n");
    worstFit(partitions, np, processes, n);
    
    return 0;
}

void worstFit(int partitions[], int np, int processes[], int n) {
    int allocation[MAX_PARTITIONS], i, j;
    for(i = 0; i < n; i++) allocation[i] = -1;
    
    for(i = 0; i < n; i++) {
        int worstIdx = -1;
        for(j = 0; j < np; j++) {
            if(partitions[j] >= processes[i]) {
                if(worstIdx == -1 || partitions[j] > partitions[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        
        if(worstIdx != -1) {
            allocation[i] = worstIdx;
            partitions[worstIdx] -= processes[i];
        }
    }
    
    for(i = 0; i < n; i++) {
        if(allocation[i] != -1)
            printf("Process %d allocated to Partition %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d not allocated\n", i+1);
    }
}
