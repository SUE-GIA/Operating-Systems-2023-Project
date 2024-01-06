/*TEST CASE PASSED*/
// This code implements the Shortest Remaining Time First (SRTF), preemptive, scheduling algorithm.
// It takes as input the number of processes, a time quantum, and an array of processes as fcfs
//@Author: Stefanos Panagiotis Giannakos 3568

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int pid;       // process ID
  int at;        // arrival time
  int bt;        // burst time
  int rt;        // remaining time
  int completed; // checks if process completed
} process;

// function SRTF preemptive
void srtf(process *arr, int n, int quantum) {
  int currentTime = 0;
  int completedProcesses = 0;

  // loop until all processes are completed
  while (completedProcesses < n) {
    // finds the index of the process with the shortest remaining time (curent
    // time )
    int shortestProcessIndex = -1;
    for (int i = 0; i < n; ++i) {
      if (!arr[i].completed && arr[i].at <= currentTime &&
          (shortestProcessIndex == -1 ||
           arr[i].rt < arr[shortestProcessIndex].rt)) {
        shortestProcessIndex = i;
      }
    }

    if (shortestProcessIndex == -1) {
      currentTime++; // if process available to execute, move to the next unit
                     // of time
    } else {
      // process for the minimum of quantum and remaining time
      int executeTime = (arr[shortestProcessIndex].rt < quantum)
                            ? arr[shortestProcessIndex].rt
                            : quantum;

      // print ID at each time unit
      for (int t = 0; t < executeTime; t++) {
        printf("%d\n", arr[shortestProcessIndex].pid);
      }

      currentTime += executeTime;
      arr[shortestProcessIndex].rt -= executeTime;

      if (arr[shortestProcessIndex].rt == 0) {
        arr[shortestProcessIndex].completed = 1;
        completedProcesses++;
      }
    }
  }
}

int main() {
  /* read in data - DO NOT EDIT (START) */
  int n;
  int quantum;
  scanf("%d", &n);
  scanf("%d", &quantum);
  process *arr;
  arr = malloc(n * sizeof(process));
  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i].pid);
    scanf("%d", &arr[i].at);
    scanf("%d", &arr[i].bt);
  }
  /* read in data - DO NOT EDIT (END) */
  for (int i = 0; i < n; ++i) {
    arr[i].rt = arr[i].bt;
    arr[i].completed = 0;
  }
  srtf(arr, n, quantum);
  free(arr);
  return 0; /* DO NOT EDIT THIS LINE */
}
