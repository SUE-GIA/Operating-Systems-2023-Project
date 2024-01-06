/*TEST CASE PASSED*/
// This code implements the Round Robin (RR)(rr) scheduling algorithm with any quantum using a dynamic array to for the process pointers.
//@Author: Stefanos Panagiotis Giannakos 3568

#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a process
typedef struct {
  int pid; // process ID
  int at;  // arrival time
  int bt;  // burst time
  int tt;  // total time
} process;

// Define a structure for the rr queue
typedef struct {
  process **queue; // dynamic array of process pointers
  int front;       // front index of the queue
  int rear;        // rear index of the queue
} RoundRobinQueue;

RoundRobinQueue rrQueue = {NULL, -1, -1}; // Global rr queue

// Function to enqueue a process into the rr queue
void roundrobin_enqueue(RoundRobinQueue *rrQueue, process *element, int *size) {
  // Initialize the queue if it's empty
  if ((*rrQueue).front == -1) {
    (*rrQueue).front = 0;
    (*rrQueue).rear = 0;
    (*rrQueue).queue = malloc(sizeof(process *));
  } else {
    // Expand the queue by reallocating memory
    (*rrQueue).rear++;
    (*rrQueue).queue =
        realloc((*rrQueue).queue, ((*rrQueue).rear + 1) * sizeof(process *));
  }

  // Check if memory allocation is successful
  if ((*rrQueue).queue == NULL) {
    exit(EXIT_FAILURE);
  }

  // Enqueue the process
  (*rrQueue).queue[(*rrQueue).rear] = element;
  *size = (*rrQueue).rear - (*rrQueue).front + 1;
}

// Function to dequeue a process from the rr queue
process *roundrobin_dequeue(RoundRobinQueue *rrQueue, int *size) {
  // Check if the queue is empty or front exceeds rear
  if ((*rrQueue).front == -1 || (*rrQueue).front > (*rrQueue).rear) {
    exit(EXIT_FAILURE);
  }

  // Dequeue the process from the front of the queue
  process *element = (*rrQueue).queue[(*rrQueue).front];
  (*rrQueue).front++;

  // Check if the queue is empty after dequeue
  if ((*rrQueue).front > (*rrQueue).rear) {
    free((*rrQueue).queue);
    (*rrQueue).front = -1;
    (*rrQueue).rear = -1;
    *size = 0;
    (*rrQueue).queue = NULL;
  } else {
    *size = (*rrQueue).rear - (*rrQueue).front + 1;
  }

  return element;
}

// Function to implement the rr 
void rr(process *arr, int n, int quantum) {
  int tt = arr[0].at;
  for (int i = 0; i < n; ++i) {
    tt += arr[i].bt;
  }

  int index = 1;
  int quantumrem = quantum;
  process *proc = &arr[0];
  int queue_size = 0;

  // Simulate the rr
  for (int i = arr[0].at; i < tt; ++i) {
    // Enqueue arriving processes
    if (arr[index].at == i) {
      roundrobin_enqueue(&rrQueue, &arr[index], &queue_size);
      index++;
    }

    // Check if the current process is completed its bt
    if ((*proc).bt == 0)
      quantumrem = 0;

    // Check if the time quantum is exhausted
    if (quantumrem == 0) {
      if ((*proc).bt > 0)
        roundrobin_enqueue(&rrQueue, proc, &queue_size);
      proc = roundrobin_dequeue(&rrQueue, &queue_size);
      quantumrem = quantum;
    }

    // Execute the current process for one time unit and print its PID
    (*proc).bt--;
    quantumrem--;
    printf("%d\n", (*proc).pid);
  }

  // Free memory
  free(rrQueue.queue);
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

  RoundRobinQueue rrQueue = {NULL, -1, -1};


  rr(arr, n, quantum);

  // Free memory
  free(rrQueue.queue);
  free(arr);

  return 0;/* DO NOT EDIT THIS LINE */
}
