/*TEST CASE PASSED*/
// This code implements the First-Come-First-Serve (FCFS) scheduling algorithm.
// It takes as input the number of processes, a time quantum (which is not used here),
// and an array of processes with their process ID (pid), arrival time (at), and burst time (bt).
//@Author: Stefanos Panagiotis Giannakos 3568

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int pid; // process ID
  int at;  // arrival time
  int bt;  // burst time
} process;

void fcfs(process *arr, int n) {
  int completionTime = 0;

  for (int i = 0; i < n; i++) {
    // calculate completion time for process
    completionTime += arr[i].bt;

    // print process ID for each time unit
    for (int j = 0; j < arr[i].bt; j++) {
      printf("%d\n", arr[i].pid); // completion time for each process is
                                  // calculated and printed
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

  fcfs(arr, n);

  free(arr); // free memory

  return 0; /* DO NOT EDIT THIS LINE */
}
