#include <stdio.h>
#include <pthread.h>

#define DIM 64
#define N 16

struct BUFFER{
    unsigned char buffer[DIM];
    int n;
};
struct BUFFER ring_buffer[N];
int read_index = 0;
int write_index = 0;
int N_block = 0;
pthread_mutex_t critical, mutex;
pthread_cond_t not_full, not_empty;
FILE *origine, *destinazione;

//thread di lettura dei dati dal file
void *leggi(void* par)
{
    int n;
    while(!feof(origine))
    {
        pthread_mutex_lock(&critical);
        if(N_block >= N)
        {
            pthread_cond_wait(&not_full, &critical);
            //vado ad effettuare la lettura dal file
            n = fread(ring_buffer[write_index].buffer, 1, DIM, origine);
            if(n > 0)
            {
                //aggiornamento numero di byte del blocco
                ring_buffer[write_index].n = n;
                //incremento contatore numerico di scrittura blocchi dati
                write_index = (write_index + 1) % N;
                //incremento contatore numero di blocchi dati
                pthread_mutex_lock(&mutex);
                N_block++;
                pthread_mutex_unlock(&mutex);
                //notifica condizione di buffer non vuoto al consumatore
                pthread_cond_signal(&not_empty);

            }
            pthread_cond_unlock(&critical);
        }
        end = 1;
        //notifica al consumatore eventualmente sospeso in attesa di dati
        pthread_cond_signal(&not_empty);
        pthread_exit(NULL);
    }
}

//thread per scrivere all'interno del file
void *scrivi(void *par)
{
    while(1)
    {
        if(end && N_block == 0)
            break;
        phtread_mutex_lock(&critical);
        if(N_block > 0)
        {
            //scrittura su file di un blocco dati del ring-buffer
            fwrite(ring_buffer[read_index].buffer, 1, ring_buffer[read_index].n, destinazione);
            //incremento indice di lettura blocchi dati
            read_index = (read_index + 1) % N;
            //decremento contatore numero di blocchi dati
            pthread_mutex_lock(&mutex);
            N_block--;
            pthread_mutex_unlock(&mutex);
            //notifica condizione buffer non pieno al produttore
            pthread_cond_signal(&not_full);
        }
        else
        {
            //sospensione nel caso di buffer vuoto
            pthread_cond_wait(&not_empty, &critical);
        }
        pthread_mutex_unlock(&critical);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv)
{
    pthread_t thread_scrittura, thread_lettura;
    if(argc != 3)
    {
        printf("Numero parametri insufficente\n");
        return 0;
    }
    sorgente = fopen(argv[1], "rb");
    if (sorgente == NULL)
    {
        printf("File sorgente non aperto correttamente\n");
        return 1;
    }

    destinazione = fopen(argv[2], "wb");
    if (destinazione == NULL)
    {
        printf("File destinazione non aperto correttamente\n");
        fclose(sorgente);
        return 1;
    }
    //creazione oggetti mutex e variabili condizione
    pthread_mutex_init(&critical, NULL);
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);
    //creazione thread di lettura e scrittura nel file
    pthread_create(&thread_scrittura, NULL, &scrivi, NULL);
    pthread_create(&thread_lettura, NULL, &leggi, NULL);
    //attesa termianzione thread
    pthread_join(thread_lettura, NULL); // Wait for the reading thread to finish
    pthread_join(thread_scrittura, NULL); // Wait for the reading thread to finish
    //distruzione oggetti mutex
    pthread_mutex_destroy(&critical);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    //chiusura file
    fclose(sorgente);
    fclose(destinazione);
    return 0;
}