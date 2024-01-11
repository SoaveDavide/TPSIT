#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#define DIM 10000
int p;
int main(int argc, char *argv[])
{
    int vettore[DIM]; // creazione del vettore
    int n;            // numero inserito dall'utente
    FILE *copia;
    fopen(argv[2], 'w');
    if (copia == NULL)
    {
        printf("File non aperto\n");
        exit(1);
    }
    if (argc != 3)
    {
        printf("Inserimento di parametri sbagliato\n");
        return 1;
    }
    else
    {
        n = atoi(argv[1]);
        // generazione dei numeri casuali
        srand(time(NULL));
        for (int i = 0; i < DIM; i++)
        {
            int random = rand() % 501;
            vettore[i] = random;
            // printf("%d\n", vettore[i]);
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
            for (int i = 6000; i < DIM; i++)
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
}