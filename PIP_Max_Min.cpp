#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/* The library */
#define MIN_PID 300
#define MAX_PID 5000
#define cb CHAR_BIT

/**Kakey Fon
**CISC3320
**Program assignment 3.20
** These pid is returned to the pid manager when the
process completes execution, and the
manager may later reassign this
pid with different variable, for instance each child
can scan the memory segment by segement until it find a free slot and
returned the index of those slot, replace the 0 with variable.
 **/

int sz = MAX_PID - MIN_PID + 1;

unsigned char *non;

int allocate_map();
int allocate_pid();
void release_pid( int pid );

/* the output that will print our the result*/
int main()
{
    int map = allocate_map();
    if (map == 1) {
        printf("\nThe OS for pid management\n");
        int id = 0, i = 0;
        while (i < 10) { //make 10 variable
            int value = allocate_pid();
            printf("\nProcess# %d: Pid# = %d", i + 1, value);
            i++;
        }
      int val = allocate_pid(); printf("\nProcess# %d: Pid# = %d\n", i+1, val);
    }
    else printf("\nFailed to initialize the data\n");
    return 1;
}

/* Creates and initializes the date for pids;
 returns -1 if unsuccessful, 1 if successful */
int allocate_map(void) {

    non = (unsigned char*)malloc((sz+cb-1)/cb * sizeof(char));
    if (non) return 1;
        return -1;
}

/* Allocates and returns 1 if it is unable */
int allocate_pid(void) {
    int i = 0;
    int next;
    int pid = non[i/cb] & (1 << (i & (cb-1))); // the pointer of the program
        while ( i <= ( MAX_PID - MIN_PID ) && (pid != 0)) {
            i++; next++;
            pid = non[i/cb] & (1 << (i & (cb-1)));
            }
                if (MIN_PID > MAX_PID) next = MIN_PID;
                   if (i == ( MAX_PID-MIN_PID )+ 1)
                        return -1;
                        non[i/cb] |= 1 << (i & (cb-1));
                        return i+MIN_PID;
}

/* Releases  pid*/
void release_pid(int pid) {
    if (pid < 300) {
        printf("\nInvalid PID: It should be in between 300 and 5000.");
        return;
    }
    int i = pid - MIN_PID;
    non[i/cb] &= ~(1 << (i & (cb-1)));
}
