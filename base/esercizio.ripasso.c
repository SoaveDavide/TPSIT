#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#define DIM 10000
int p;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Inserimento di parametri sbagliato\n");
        return 1;
    }
    int vettore[DIM]; // creazione del vettore
    int n;            // numero inserito dall'utente
    FILE *copia;
    copia = fopen("ripasso.txt", "w"); // apro il file
    if (copia == NULL)
    {
        printf("File non aperto\n");
        exit(1);
    }

    n = atoi(argv[1]);
    // generazione dei numeri casuali
    srand(time(NULL));
    for (int i = 0; i < DIM; i++)
    {
        int random = rand() % 501;
        vettore[i] = random;
        // printf("%d\n", vettore[i]);
    }
    for (int i = 0; i < DIM; i++)
    {
        fprintf(copia, "[%d] --> %d\n", i, vettore[i]); // scrivo nel file i numeri
    }
    fclose(copia);

    p = fork();
    if (p > 0)
    {

        p = fork();
        if (p > 0)
        {
            // sono nel padre
            for (int i = 0; i < 2000; i++)
            {
                if (n == vettore[i])
                {
                    // Scrivo sulla linea di comado sia indice che numero che PID
                    printf("Sono il processo padre e ho PID = %d. Il numero: %d si trova all'indice:%d\n", getpid(), n, i);
                }
            }
        }
        else
        {
            // Sono nel primo figlio
            for (int i = 2000; i < 6000; i++)
            {
                if (n == vettore[i])
                {
                    // Scrivo sulla linea di comado sia indice che numero che PID
                    printf("Sono il processo figlio e ho PID = %d. Il numero: %d si trova all'indice:%d\n", getpid(), n, i);
                }
            }
        }
    }
    else
    {
        // Sono nel secondo figlio
        for (int i = 6000; i < DIM + 1; i++)
        {
            if (n == vettore[i])
            {
                // Scrivo sulla linea di comado sia indice che numero che PID
                printf("Sono il processo figlio 2 e ho PID = %d. Il numero: %d si trova all'indice:%d\n", getpid(), n, i);
            }
        }
    }
    return 0;
}