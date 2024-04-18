#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#define DIM 10

int array[DIM];
void *InserimentoPrimaMeta(void *s)
{
    
    // Esegue operazioni sulla prima metà dell'array
    for (int i = 0; i < DIM/2; i++)
    {
        if (array[i] == 8)
        {
            printf("Il numero 8 si trova in posizione: %d\n", i);
        }
    }
    return NULL;
}

/*void *InserimentoSecondaMeta(void *s)
{
    int *array = (int *)s;
    // Esegue operazioni sulla seconda metà dell'array
    for (int i = DIM/2; i < DIM; i++)
    {
        if (array[i] == 8)
        {
            printf("Il numero 8 si trova in posizione: %d\n", i);
        }
    }
    return NULL;
}*/

int main()
{
    
    pthread_t threadPrima, threadSeconda;
    int num = 0;
    int *p = &num;
    // Fase di inserimento
    printf("Inserire %d numeri:\n", DIM);
    for (int i = 0; i < DIM; i++)
    {
        scanf("%d", &array[i]);
    }

    pthread_create(&threadPrima, NULL, &InserimentoPrimaMeta,  p);
    pthread_create(&threadSeconda, NULL, &InserimentoPrimaMeta, p); // Passaggio dell'indirizzo del sesto elemento
    pthread_join(threadPrima, NULL);
    pthread_join(threadSeconda, NULL);

    return 0;
}
