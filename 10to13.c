Below are individual C programs for each question. You can compile each code separately (for example, using `gcc filename.c -o output`) and then run the executable. Each program takes input from the user.

---

### 10. Banker's Algorithm for Deadlock Avoidance

```c
/* Banker's Algorithm for Deadlock Avoidance */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int available[m];
    printf("Enter available resources (space separated):\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    int allocation[n][m], maximum[n][m];
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i);
        printf("  Enter allocated resources (space separated): ");
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
        printf("  Enter maximum resources (space separated): ");
        for (int j = 0; j < m; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    int finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }
    int safeSequence[n];
    int count = 0;
    
    int work[m];
    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }
    
    bool found;
    do {
        found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
    } while(found);

    if (count == n) {
        printf("\nSystem is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("\nSystem is not in a safe state.\n");
    }
    return 0;
}
```

---

### 11. Deadlock Detection Algorithm

```c
/* Deadlock Detection Algorithm */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int available[m];
    printf("Enter available resources (space separated):\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    int allocation[n][m], request[n][m];
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i);
        printf("  Enter allocated resources (space separated): ");
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
        printf("  Enter request (remaining need) resources (space separated): ");
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    int finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }
    int work[m];
    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    bool progress;
    do {
        progress = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    progress = true;
                }
            }
        }
    } while(progress);

    bool deadlock = false;
    printf("\nDeadlocked processes: ");
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("%d ", i);
            deadlock = true;
        }
    }
    if (!deadlock)
        printf("None");
    printf("\n");
    return 0;
}
```

---

### 12a. Sequential (Contiguous) File Allocation Simulation

```c
/* Sequential (Contiguous) File Allocation Simulation */
#include <stdio.h>

int main() {
    int total_blocks, start_block, file_size;
    printf("Enter total number of disk blocks: ");
    scanf("%d", &total_blocks);
    printf("Enter starting block number for file allocation: ");
    scanf("%d", &start_block);
    printf("Enter file size (number of blocks required): ");
    scanf("%d", &file_size);

    if (start_block < 0 || start_block + file_size > total_blocks) {
        printf("Error: File cannot be allocated. Not enough contiguous blocks available.\n");
    } else {
        printf("File allocated in blocks: ");
        for (int i = start_block; i < start_block + file_size; i++) {
            printf("%d ", i);
        }
        printf("\n");
    }
    return 0;
}
```

---

### 12b. Indexed File Allocation Simulation

```c
/* Indexed File Allocation Simulation */
#include <stdio.h>

int main() {
    int index_block, file_size;
    printf("Enter the index block number: ");
    scanf("%d", &index_block);
    printf("Enter file size (number of blocks required): ");
    scanf("%d", &file_size);

    int blocks[file_size];
    printf("Enter the block numbers to be allocated (space separated): ");
    for (int i = 0; i < file_size; i++) {
        scanf("%d", &blocks[i]);
    }

    printf("\nIndex Block: %d\n", index_block);
    printf("File allocated in blocks (via index): ");
    for (int i = 0; i < file_size; i++) {
        printf("%d ", blocks[i]);
    }
    printf("\n");
    return 0;
}
```

---

### 12c. Linked File Allocation Simulation

```c
/* Linked File Allocation Simulation */
#include <stdio.h>

int main() {
    int file_size;
    printf("Enter file size (number of blocks): ");
    scanf("%d", &file_size);

    int blocks[file_size];
    printf("Enter the block numbers in order (space separated): ");
    for (int i = 0; i < file_size; i++) {
        scanf("%d", &blocks[i]);
    }

    printf("\nFile allocated using linked allocation:\n");
    for (int i = 0; i < file_size - 1; i++) {
        printf("Block %d -> Block %d\n", blocks[i], blocks[i+1]);
    }
    printf("Block %d -> NULL\n", blocks[file_size - 1]);
    return 0;
}
```

---

### 13a. FCFS Disk Scheduling Simulation

```c
/* FCFS Disk Scheduling Simulation */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int num_requests, head;
    printf("Enter number of disk requests: ");
    scanf("%d", &num_requests);
    
    int requests[num_requests];
    printf("Enter the disk request queue (space separated): ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    int total_movement = 0;
    int current = head;
    printf("\nHead movement:\n");
    for (int i = 0; i < num_requests; i++) {
        printf("%d -> %d\n", current, requests[i]);
        total_movement += abs(requests[i] - current);
        current = requests[i];
    }
    printf("Total head movement: %d\n", total_movement);
    return 0;
}
```

---

### 13b. SCAN Disk Scheduling Simulation

```c
/* SCAN Disk Scheduling Simulation (Elevator Algorithm) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int compare_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int num_requests, head, disk_size;
    char direction[10];
    printf("Enter number of disk requests: ");
    scanf("%d", &num_requests);
    int requests[num_requests];
    printf("Enter the disk request queue (space separated): ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the disk size (total number of blocks): ");
    scanf("%d", &disk_size);
    printf("Enter head movement direction (left/right): ");
    scanf("%s", direction);

    qsort(requests, num_requests, sizeof(int), compare_int);
    int total_movement = 0;
    int current = head;
    printf("\nService sequence:\n");

    if (strcmp(direction, "left") == 0) {
        int left[num_requests], right[num_requests];
        int leftCount = 0, rightCount = 0;
        for (int i = 0; i < num_requests; i++) {
            if (requests[i] < head)
                left[leftCount++] = requests[i];
            else
                right[rightCount++] = requests[i];
        }
        // Service left part in descending order
        for (int i = leftCount - 1; i >= 0; i--) {
            printf("%d -> %d\n", current, left[i]);
            total_movement += abs(current - left[i]);
            current = left[i];
        }
        // Move to 0 if not already there
        if (current != 0) {
            printf("%d -> %d\n", current, 0);
            total_movement += current;
            current = 0;
        }
        // Service right part in ascending order
        for (int i = 0; i < rightCount; i++) {
            printf("%d -> %d\n", current, right[i]);
            total_movement += abs(right[i] - current);
            current = right[i];
        }
    } else if (strcmp(direction, "right") == 0) {
        int left[num_requests], right[num_requests];
        int leftCount = 0, rightCount = 0;
        for (int i = 0; i < num_requests; i++) {
            if (requests[i] < head)
                left[leftCount++] = requests[i];
            else
                right[rightCount++] = requests[i];
        }
        // Service right part in ascending order
        for (int i = 0; i < rightCount; i++) {
            printf("%d -> %d\n", current, right[i]);
            total_movement += abs(right[i] - current);
            current = right[i];
        }
        // Move to end if not already at the end
        if (current != disk_size - 1) {
            printf("%d -> %d\n", current, disk_size - 1);
            total_movement += abs((disk_size - 1) - current);
            current = disk_size - 1;
        }
        // Service left part in descending order
        for (int i = leftCount - 1; i >= 0; i--) {
            printf("%d -> %d\n", current, left[i]);
            total_movement += abs(current - left[i]);
            current = left[i];
        }
    } else {
        printf("Invalid direction!\n");
        return 1;
    }
    printf("Total head movement: %d\n", total_movement);
    return 0;
}
```

---

### 13c. C-SCAN Disk Scheduling Simulation

```c
/* C-SCAN Disk Scheduling Simulation */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int compare_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int num_requests, head, disk_size;
    char direction[10];
    printf("Enter number of disk requests: ");
    scanf("%d", &num_requests);
    int requests[num_requests];
    printf("Enter the disk request queue (space separated): ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the disk size (total number of blocks): ");
    scanf("%d", &disk_size);
    printf("Enter head movement direction (left/right): ");
    scanf("%s", direction);

    qsort(requests, num_requests, sizeof(int), compare_int);
    int total_movement = 0;
    int current = head;
    printf("\nService sequence:\n");

    if (strcmp(direction, "right") == 0) {
        int right[num_requests], left[num_requests];
        int rightCount = 0, leftCount = 0;
        for (int i = 0; i < num_requests; i++) {
            if (requests[i] >= head)
                right[rightCount++] = requests[i];
            else
                left[leftCount++] = requests[i];
        }
        // Service right part in ascending order
        for (int i = 0; i < rightCount; i++) {
            printf("%d -> %d\n", current, right[i]);
            total_movement += abs(right[i] - current);
            current = right[i];
        }
        // Go to the end if not already there
        if (current != disk_size - 1) {
            printf("%d -> %d\n", current, disk_size - 1);
            total_movement += abs((disk_size - 1) - current);
            current = disk_size - 1;
        }
        // Jump from end to beginning (simulate jump; jump cost is taken as disk_size - 1)
        printf("%d -> %d (jump)\n", current, 0);
        total_movement += (disk_size - 1);
        current = 0;
        // Service left part in ascending order
        for (int i = 0; i < leftCount; i++) {
            printf("%d -> %d\n", current, left[i]);
            total_movement += abs(left[i] - current);
            current = left[i];
        }
    } else if (strcmp(direction, "left") == 0) {
        int right[num_requests], left[num_requests];
        int rightCount = 0, leftCount = 0;
        for (int i = 0; i < num_requests; i++) {
            if (requests[i] <= head)
                left[leftCount++] = requests[i];
            else
                right[rightCount++] = requests[i];
        }
        // Service left part in descending order
        for (int i = leftCount - 1; i >= 0; i--) {
            printf("%d -> %d\n", current, left[i]);
            total_movement += abs(current - left[i]);
            current = left[i];
        }
        // Go to beginning if not already there
        if (current != 0) {
            printf("%d -> %d\n", current, 0);
            total_movement += current;
            current = 0;
        }
        // Jump from beginning to end
        printf("%d -> %d (jump)\n", current, disk_size - 1);
        total_movement += (disk_size - 1);
        current = disk_size - 1;
        // Service right part in descending order
        for (int i = rightCount - 1; i >= 0; i--) {
            printf("%d -> %d\n", current, right[i]);
            total_movement += abs(current - right[i]);
            current = right[i];
        }
    } else {
        printf("Invalid direction!\n");
        return 1;
    }
    printf("Total head movement: %d\n", total_movement);
    return 0;
}
```

---

Each of these programs takes user input and simulates the corresponding algorithm or allocation strategy in C.
