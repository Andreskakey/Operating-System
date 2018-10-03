/*
**Kakey Fon
**CISC3320
**Program 4.20
**This Multithreaded program will test the previous program (3.20),
**the thread will request sleep in a random number generator and then release the pid.
**This program is in C as well as contain the Unix library that will compile then execute the code, hopefully
**some machine had it.
**
*/

// the Unix and thread library are include below
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//Assignment 3.20  but adding the thread
#define MIN_PID 300
#define MAX_PID 5000
#define SIZE MAX_PID - MIN_PID + 1
#define NUM_THREADS 100

char *bit_map;

//Same basic idea from assignment 3.20 but a bit easy to understand with the allocate map, pid, pid release and pid work
// but adding the function of thread
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
//The addiction method that will release the pid process Release()
void release_pid(int pid)
{
    if (pid <= MAX_PID && pid >= MIN_PID)
    {
        int index = pid - MIN_PID;
        bit_map[index] = '0';
    }
}
// Sleep() mode when the random numbers is generated in main
void *pidWork(void *threadNumber)
{
    int pid = allocate_pid();
    int n = *((int *) threadNumber);
    int s = rand() % 10;
    printf("Thread, %d, allocated pid: %d, sleeping mode: %d seconds\n", n, pid, s);
    sleep(s); // somehow this isn't in the library (support to be in unix library), meaning this program will work if I take this out.
    release_pid(pid);
    printf("Thread, %d,released pid: %d\n", n, pid);
    pthread_exit(0);
}
//the output that use random numbers generator to test each pid as a thread
int main(void)
{
    srand(time(NULL));
    int success = allocate_map();
    if (success == -1)
    {
        fprintf(stderr, "Error allocating");
        return 1;
    }
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    for (i=0; i < NUM_THREADS; i++)
    {
        pthread_attr_init(&attr[i]);
        success = pthread_create(&threads[i], &attr[i], pidWork, (void *) &i);
        if (success != 0)
        {
            fprintf(stderr, "Error making a thread");
            return -1;
        }
    }
    for (i=0; i < NUM_THREADS; i++)
    {
        success = pthread_join(threads[i], NULL);
        if (success != 0)
        {
            fprintf(stderr, "Error connecting to thread");
            return -1;
        }
    }
    printf("SUCCEFUL Thread\n");
    exit(EXIT_SUCCESS);
}

