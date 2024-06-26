#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define DIM 1000

int array[DIM];
int num;

void *RicercaPrima(void *s)
{
    int presente = 0;
    for (int i = 0; i < DIM / 4; i++)
    {
        if (array[i] == num)
        {
            printf("Il numero %d si trova in posizione: %d\n", num, i);
            presente++;
        }
    }
    if (presente == 0)
    {
        printf("Numero non presente nella prima metà\n");
    }
    return NULL;
}

void *RicercaSeconda(void *s)
{
    int presente = 0;
    for (int i = DIM / 4; i < DIM / 2; i++)
    {
        if (array[i] == num)
        {
            presente++;
            printf("Il numero %d si trova in posizione: %d\n", num, i);
        }
    }
    if (presente == 0)
    {
        printf("Numero non presente nella seconda metà\n");
    }
    return NULL;
}

void *RicercaTerza(void *s)
{
    int presente = 0;
    for (int i = DIM / 2; i < (DIM / 2 + DIM / 4); i++)
    {
        if (array[i] == num)
        {
            printf("Il numero %d si trova in posizione: %d\n", num, i);
            presente++;
        }
        
    }
    if (presente == 0)
    {
        printf("Numero non presente nella terza metà\n");
    }
    return NULL;
}

void *RicercaQuarta(void *s)
{
    int presente = 0;
    for (int i = (DIM / 2 + DIM / 4); i < DIM; i++)
    {
        if (array[i] == num)
        {
            printf("Il numero %d si trova in posizione: %d\n", num, i);
            presente ++;
        }
        
    }
    if (presente == 0)
    {
        printf("Numero non presente nella quarta metà\n");
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t threadPrima, threadSeconda, threadTerza, threadQuarta;

    // faccio inserire all'utente il numero che si vuole ricercare
    printf("Inserire numero da ricercare: \n");
    scanf("%d", &num);

    // inserimento di valori casuali all'interno dell'array
    for (int i = 0; i < DIM; i++)
    {
        int r = rand() % 500;
        array[i] = r;
    }

    pthread_create(&threadPrima, NULL, &RicercaPrima, NULL);
    pthread_create(&threadSeconda, NULL, &RicercaSeconda, NULL);
    pthread_create(&threadTerza, NULL, &RicercaTerza, NULL);
    pthread_create(&threadQuarta, NULL, &RicercaQuarta, NULL);

    pthread_join(threadPrima, NULL);
    pthread_join(threadSeconda, NULL);
    pthread_join(threadTerza, NULL);
    pthread_join(threadQuarta, NULL);

    return 0;
}
