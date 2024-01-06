/*TEST CASE PASSED*/
// This code implements a simplified version of Shortest Job First (SJF),
// non-preeptive, scheduling //algorithm using Bubble Sort for sorting the
// processes based on burst time.
//@Author: Stefanos Panagiotis Giannakos 3568

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int pid; // process ID
  int at;  // arrival time
  int bt;  // burst time
  int tt;  // total time
} process;

void bubbleSort(process arr[], int n) { // Implementation of bS
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j].bt > arr[j + 1].bt) {
        process temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

// Function of SJF
void sjf(process *arr, int n) {
  // Select the first process as the initial reference
  process first = arr[0];

  // Calculate the total time required by all processes
  int tt = arr[0].at;
  for (int i = 0; i < n; ++i) {
    tt += arr[i].bt;
  }

  // Sort the array of processes based on burst time using the bubble sort
  // algorithm
  bubbleSort(arr, n);

  // Initialize the current process with the first process
  process proc = first;

  // Simulate the SJF scheduling
  for (int i = first.at; i < tt; ++i) {
    // Check if the current process has completed its burst time
    if (proc.bt == 0) {
      // Find the next available process with the shortest burst time
      int index = 0;
      while (arr[index].at > i || arr[index].bt == 0) {
        index++;
      }

      // Update the current process to the next selected process
      proc = arr[index];

      // Mark the selected process as completed by setting its burst time to 0
      arr[index].bt = 0; // remove the process from the queue
    }

    // Execute the current process for one time unit and print its PID
    proc.bt--;
    printf("%d\n", proc.pid);
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

  sjf(arr, n);
  free(arr);

  return 0; /* DO NOT EDIT THIS LINE */
}