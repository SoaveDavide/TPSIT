#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#define  BUFFER_DIM 1024
unsigned char buffer[BUFFER_DIM];
FILE *sorgente, *destinazione;
void *Lettura(void *s)
{
    pthread_t scrittura;
    //continuo a leggere fino a quando ci sono dati all'interno del file
    while (fread(buffer, 1, sizeof(buffer), sorgente) > 0)
    { 
        pthread_create(&scrittura, NULL, Scrittura, NULL);
    }
    pthread_join(scrittura, NULL);
    return NULL;
}

void *Scrittura(void *s)
{
    fwrite(buffer, 1, sizeof(buffer), destinazione);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t lettura;

    if (argc != 3)
    {
        printf("Numero parametri insufficiente\n");
        return 0;
    }

    sorgente = fopen(argv[1], "r");
    if (sorgente == NULL)
    {
        printf("File sorgente non aperto correttamente\n");
        return 0;
    }

    destinazione = fopen(argv[2], "w");
    if (destinazione == NULL)
    {
        printf("File destinazione non aperto correttamente\n");
        fclose(sorgente);
        return 0;
    }

    pthread_create(&lettura, NULL, Lettura, NULL);
    pthread_join(lettura, NULL);

    fclose(sorgente);
    fclose(destinazione);

    return 0;
}
