#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define DIM 64 // definizione dimensione singolo blocco
#define N 16   // definizione di numero blocchi

struct BUFFER
{
    unsigned char buffer;
    int n;
};
struct BUFFER ring_buffer[N];
// definizione indici di lettura e di scrittura
int read_index;
int write_index;
int N_BLOCK; // numero blocchi che vengono scritti e letti di volta in volta

// definizione variabile di tipo FILE
FILE *origine, *destinazione;
// definizioni variabili per il mutex e per il signal
pthread_mutex_t critical, mutex;
pthread_cond_t not_full, not_empty;
// fine del file con variabili booleana
int end = 0;
// creazione delle funzioni che implementano il codice dei due thread
void *Lettura(void *arg)
{
    int n; // numero di byte che vengono letti dal file
    while (feof(origine))
    {
        pthread_mutex_lock(&critical);
        if (N_BLOCK >= N) // controllo che il buffer non sia pieno
        {
            // condizione wait
            pthread_cond_wait(&not_full, &critical);
        }
        n = fread(ring_buffer[write_index].buffer, 1, DIM, origine);
        if (n > 0)
        {
            // aggiornamento numero blocchi scritti
            ring_buffer[write_index].n = n;
            // contatore di lettura aggiornato
            write_index = (write_index + 1) % N;
            // aumento numero blocchi scritti
            N_BLOCK++;
            // manda il segnale all'altro thread che il buffer non è pieno
            pthread_cond_signal(&not_empty);
        }
        // sblocco il mutex da questo thread
        pthread_mutex_unlock(&critical);
    }
    end = 1; // ho raggiunto la fine del file
    pthread_cond_signal(&not_empty);
    pthread_exit(NULL);
}

void *Scrittura(void *arg)
{
    while (1)
    {
        // controllo che il buffer non sia vuoto
        if (end && N_BLOCK == 0)
            break;
        // blocco il thread
        pthread_mutex_lock(&mutex);

        if (N_BLOCK > 0)
        {
            fwrite(ring_buffer[read_index].buffer, 1, ring_buffer[read_index].n, destinazione);
            // incremento dell'indice di lettura dal buffer
            read_index = (read_index + 1) % N;
            // diminuzione del numero scritti
            N_BLOCK--;
            pthread_cond_signal(&not_full);
        }
        else
        {
            pthread_cond_wait(&not_empty, &critical);
        }
        pthread_mutex_unclock(&mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // definizione di variabile pthread_t
    pthread_t lettura, scrittura;
    // controllo che l'utente abbia inserito il nome del file tra i parametri
    if (argc != 3)
    {
        printf("Numero parametri sbagliato.\n");
        return 0;
    }
    // apertura file da leggere e controllo
    if (fopen(argv[1], "rb") == NULL)
    {
        printf("Apertura file sbagliata\n");
        return 1;
    }
    // apertura del file su cui copiare e controllo
    if (fopen(argv[2], "wb") == NULL)
    {
        printf("Apertura del file non riuscita\n");
        fclose(origine);
        return 0;
    }
    // creazione della sezione scritica
    pthread_mutex_init(&critical, NULL);
    pthread_mutex_init(&mutex, NULL);
    // creazione del signal
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);
    // istanzia del thread di lettura
    pthread_create(lettura, NULL, &lettura, NULL);
    pthread_create(scrittura, NULL, &scrittura, NULL);
    // distruzione del mutex
    pthread_mutex_destroy(&critical);
    pthread_mutex_destroy(&mutex);
    // distruzione del signal
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    // attendo la terminazione dei thread
    pthread_join(lettura, NULL);
    pthread_join(scrittura, NULL);
    // chiusura dei file
    fclose(origine);
    fclose(destinazione);
    return 0;
}