#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define DEFAULT_BUFFER_SIZE 1024

unsigned char *buffer = NULL;
size_t buffer_size = 0;

FILE *sorgente, *destinazione;

void *Lettura(void *arg)
{
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, buffer_size, sorgente)) > 0)
    {
        // passa il numero di byte da leggere alla funzione Scrittura
        Scrittura((void*)bytesRead);
        //Quando la funzione Lettura legge un certo numero di byte dal file di origine, 
        //passa questa quantità alla funzione Scrittura come argomento.
    }
    return NULL;
}

void *Scrittura(void *arg)
{
    //rappresenta il numero di byte da scrivere nel file di destinazione
    size_t bytesToWrite = (size_t)arg;
    fwrite(buffer, 1, bytesToWrite, destinazione);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t lettura, scrittura;

    if (argc != 3)
    {
        printf("Numero parametri insufficiente\n");
        return 1;
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


    pthread_create(&lettura, NULL, Lettura, NULL);
    pthread_join(lettura, NULL); // Wait for the reading thread to finish
    
    fclose(sorgente);
    fclose(destinazione);

    // Free dynamically allocated memory
    free(buffer);

    return 0;
}
