/*
**Kakey Fon
**CISC3320
**Program 4.20
**This Multithreaded program will test the previous program (3.20),
**the thread will request sleep in a random number generator and then release the pid.
**This program is in C as well as contain the Unix library that will compile then execute the code, hopefully
**some machine had it.
**This program now run properly in both linux and windows machine using code block
**
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <windows.h>

#define MIN_PID 300
#define MAX_PID 5000
#define SIZE MAX_PID - MIN_PID + 1
#define NUM_THREADS 100



char *bit_map;

//Same basic idea from assignment 3.20 but a bit easy to understand with the allocate map, pid, pid release and pid work
// but adding the function of thread.
// the map to allocated the pid
int allocate_map(void)
{
    bit_map = malloc(sizeof(char)*SIZE);
    if (bit_map == NULL && SIZE != 0) return -1;
    else
    {
        int i;
        for (i=0; i < SIZE; i++)
        {
            bit_map[i] = '0';
        }
        return 1;
    }
}
/* This will storage the size of the thread */
int allocate_pid(void)
{
    int i;
    for (i=0; i < SIZE; i++)
    {
        if (bit_map[i] == '0')
        {
            bit_map[i] = '1';
            return MIN_PID + i;
        }
    }
    return 1;
}
/*The addiction method that will release the pid process Release() this will do most of the calculation for release the thread*/
void release_pid(int pid)
{
    if (pid <= MAX_PID && pid >= MIN_PID)
    {
        int index = pid - MIN_PID;
        bit_map[index] = '0';
    }
}
/* Sleep() mode when the random numbers is generated in main then this will input the sleep time and release time of pid using a each thread */
void *pidWork(void *threadNumber)
{
    int pid = allocate_pid();
    int n = *((int *) threadNumber);
    int s = rand() % 5;
    printf("Thread, %d dallocated pid: %d sleeping mode: %d seconds\n", n, pid, s);
    Sleep(s);
    release_pid(pid);
    printf("Thread, %d released pid: %d\n", n, pid);
    pthread_exit(0);
}

int main(void)
{
/*the output that use random numbers generator to test each pid as a thread and allocated the map*/
    srand(time(NULL));
    int success = allocate_map();
    if (success == -1)
    {
        fprintf(stderr, "Error allocating map");
        return 1;
    }
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    for (i=0; i < NUM_THREADS; i++)// generating a loop for thread
    {
        pthread_attr_init(&attr[i]);
        success = pthread_create(&threads[i], &attr[i], pidWork, (void *) &i); // this part is the pointer object toward pidworks
        if (success != 0)
        {
            fprintf(stderr, "Error making a thread"); // if a error is found then return to -1 to another loop
            return -1;
        }
    }
    for (i=0; i < NUM_THREADS; i++) // looping the output to connecting each thread's numbers
    {
        success = pthread_join(threads[i], NULL);
        if (success != 0)
        {
            fprintf(stderr, "Error connecting to thread");
            return -1;
        }
    }
    printf("SUCCEFUL Thread\n"); // this is end of the program
    exit(EXIT_SUCCESS);
}

