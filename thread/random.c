#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define BUFFER_SIZE 16

int ring_buffer[BUFFER_SIZE];
bool eos = false;
int read_index = 0;
int write_index = 0;
int N_block = 0;
int N_number = 0;
pthread_mutex_t producer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t consumer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

// Function to generate random numbers
void *genera(void *arg)
{
  while (N_number > 0)
  {
    pthread_mutex_lock(&producer_mutex);

    // Wait if buffer is full
    while (N_block >= BUFFER_SIZE)
    {
      pthread_cond_wait(&not_full, &producer_mutex);
    }

    // Generate a new random number and insert it into the circular buffer
    ring_buffer[write_index] = rand() % 1000;
    N_number--;

    // Increment circular write index
    write_index = (write_index + 1) % BUFFER_SIZE;

    // Increment block count
    N_block++;

    // Notify consumer that buffer is not empty
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&producer_mutex);
  }

  eos = true;

  // Notify consumer that generation is done
  pthread_cond_signal(&not_empty);
  return NULL;
}

// Function to visualize random numbers
void *visualizza(void *arg)
{
  while (!eos || N_block > 0)
  {
    pthread_mutex_lock(&consumer_mutex);

    if (N_block > 0)
    {
      // Print the random number from the circular buffer
      printf("%d\n", ring_buffer[read_index]);

      // Increment circular read index
      read_index = (read_index + 1) % BUFFER_SIZE;

      // Decrement block count
      N_block--;

      // Notify producer that buffer is not full
      pthread_cond_signal(&not_full);
    }
    else
    {
      // Wait if buffer is empty
      pthread_cond_wait(&not_empty, &consumer_mutex);
    }

    pthread_mutex_unlock(&consumer_mutex);
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  // Check command line arguments
  if (argc != 2)
  {
    printf("Numero parametri sbagliato\n");
    return -1;
  }

  N_number = atoi(argv[1]);

  // Initialize shared variables
  N_block = 0;

  // Create producer and consumer threads
  pthread_t producer_thread, consumer_thread;
  pthread_create(&producer_thread, NULL, genera, NULL);
  pthread_create(&consumer_thread, NULL, visualizza, NULL);

  // Wait for the threads to complete
  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  return 0;
}
