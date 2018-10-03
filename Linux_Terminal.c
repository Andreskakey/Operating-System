/*
**Kakey Fon
**CISC3320
**Program 5.36
**This program will decides how many producer and consumer thread will be created, as well, how long is sleeping time using Section 5.9.4 idea. 
**the thread will request sleep in a random number generator and then release the pid.
**This program is in C as well as contain the Unix library that will compile then execute the code, hopefully
**some machine had it.
**The program can run in linux terminal, as well as in windows computer in a safe race condition. However, the windows doesn't have gnome
**to run this program poperly, already this in the campus and on my home computer.
**To run this in linux computer, I use the gcc object (536) with the -pthread and compile using the ./536 20 20 5
**
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h> // required import to display time part of clock() and time()
#include <unistd.h> // the Unix library
//#include <windows.h> // the Windows that will run this program

#define TRUE 1
#define BUFFER_SIZE 5
#define MAX_SLEEP 5

#define MIN 300
#define MAX 5000

int buffer[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t empty;
sem_t full;
time_t currentTime; // the system time
clock_t programTime; // counting the ticks since program started

/*this is the insert and removed points use for semaphone and mutex lock.*/
int insertPointer = 0, removePointer = 0; 

void *producer(void *param);
void *consumer(void *param);

void getTime()
{
	currentTime = time(NULL); // Day Month Date HH:MM:SS Year
}

int myRand() {
   return rand() % (MAX - MIN + 1) + MIN;
}

int print_buffer(){
	int i;
	for (i=0; i< BUFFER_SIZE; i++)
		printf("slot %d: %d\n", i, buffer[i]);
	printf("\n");
	return 0;
}

int init_buffer(){// the buffer
	int i;
	for (i=0; i< BUFFER_SIZE; i++)
		buffer[i] = -1;
	return 0;
}

int insert_item(int item)
{
	sem_wait(&empty); // decrement semaphore
	pthread_mutex_lock(&mutex); // locks the mutex

	int test = buffer[insertPointer]; // checks if slot already has value in its

	if(test == -1) // is the slot empty? the do this
	{
		buffer[insertPointer] = item; // if so then insert item at slot pointed by insertPointer
		insertPointer = (insertPointer + 1) % BUFFER_SIZE; // calculate next slot (wraps around)
		getTime(); // get the system time
		programTime = clock(); // get clock ticks since program started

		printf("Producer produced %d at time %s number of tick : %ld) (Thread ID: %lu)\n", item, ctime(&currentTime), programTime, pthread_self()); // output the information
		print_buffer(); // prints the buffer
	}

	pthread_mutex_unlock(&mutex); // unlock the mutex
	sem_post(&full); // increment semaphroe
}

int remove_item()
{
	sem_wait(&full);
	pthread_mutex_lock(&mutex); // lock the mutex (acquire)

	int item = buffer[removePointer]; // consume the item pointed in the buffer by removePointer

	if(item != -1) // Is the slot already empty
	{
		buffer[removePointer] = -1; // if so then keep it empty
		removePointer = (removePointer + 1) % BUFFER_SIZE; // calculates next slot (wraps around)
		getTime(); // get system time as date and time
		programTime = clock(); // this will tic the program sincer started

		printf("Consumer consumed %d at time %s number of tick %ld) (Thread ID: %lu)\n", item, ctime(&currentTime), programTime, pthread_self()); // output the information
		print_buffer(); // prints state of the buffer
	}

	pthread_mutex_unlock(&mutex); // unlock the mutex (release)
	sem_post(&empty); // increment the semaphore by 1 more
}
/* the main method for C in linux*/
int main(int argc, char *argv[])
{
	//The output will of sleepTime, producerThread, and consumerThread
	int sleepTime, producerThreads, consumerThreads;
	int i, j;

	if(argc != 4)
	{
		fprintf(stderr, "Useage: <sleep time> <producer threads> <consumer threads>\n");
		return -1;
	}

	sleepTime = atoi(argv[1]);
	producerThreads = atoi(argv[2]);
	consumerThreads = atoi(argv[3]);

	/* Initialize buffer to be -1 */
	init_buffer();

	/* Initialize the synchronization tools */
	printf("%d\n",pthread_mutex_init(&mutex, NULL));
	printf("%d\n",sem_init(&empty, 0, BUFFER_SIZE));
	printf("%d\n",sem_init(&full, 0, 0));
	srand(time(0));

	/* this create the producer and consumer threads */
	for(i = 0; i < producerThreads; i++)
	{
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, producer, NULL);
	}

	for(j = 0; j < consumerThreads; j++)
	{
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, consumer, NULL);
	}

	/* Sleep for the user in an specified time */
	sleep(sleepTime);
	//Sleep(sleepTime); for windows machine
	return 0;
}

/* the producer will generate a random numbers then it will show the sleeping time of the object as a pointer.*/
void *producer(void *param)
{
	int random;
	int r;

	while(TRUE)
	{
		r = rand() % MAX_SLEEP;
        sleep(r);
	//Sleep(r); for windows machine
		random = myRand();
		getTime();
		programTime = clock();

		printf("Producer tries to insert %d at time %s number of tick : %ld) (Thread ID: %lu)\n", random, ctime(&currentTime), programTime, pthread_self()); // Modified to show date and time, clock ticks elapsed since program started, and the thread ID.
		if(insert_item(random))
			fprintf(stderr, "Error\n");
	}

}

/*The consumer will remove the next variable in the buffer.*/
void *consumer(void *param)
{
	int r;

	while(TRUE)
	{
		r = rand() % MAX_SLEEP;
		sleep(r); 
		//Sleep(r); for windows machine
		getTime();
		programTime = clock();

		printf("Consumer tries to consume at time %s number of Tick: %ld) (Thread ID: %lu)\n", ctime(&currentTime), programTime, pthread_self()); // Modified to show date and time, clock ticks elapsed since program started, and the thread ID.

		if(remove_item())
			fprintf(stderr, "Error Consuming\n");

        return;
	}
}
