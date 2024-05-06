#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#define BUFFER_DIM 1024

unsigned char buffer[BUFFER_DIM];
FILE *sorgente, *destinazione;

void *Lettura(void *s)
{
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sorgente)) > 0)
    { 
        
    }
    return NULL;
}

void *Scrittura(void *s)
{
    size_t bytesToWrite = (size_t)s;
    fwrite(buffer, 1, bytesToWrite, destinazione);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t lettura, scrittura;

    if (argc != 3)
    {
        printf("Numero parametri insufficiente\n");
        return 0;
    }

    sorgente = fopen(argv[1], "rb");
    if (sorgente == NULL)
    {
        printf("File sorgente non aperto correttamente\n");
        return 0;
    }

    destinazione = fopen(argv[2], "wb");
    if (destinazione == NULL)
    {
        printf("File destinazione non aperto correttamente\n");
        fclose(sorgente);
        return 0;
    }

    pthread_create(&lettura, NULL, Lettura, NULL);
    pthread_create(&scrittura, NULL, Scrittura, NULL);

    pthread_join(lettura, NULL); // Aspetta che il thread di lettura finisca prima di chiudere i file
    pthread_join(scrittura, NULL); // Aspetta che il thread di scrittura finisca prima di continuare la lettura
    
    fclose(sorgente);
    fclose(destinazione);

    return 0;
}
