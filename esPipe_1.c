#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define DIM_ARRAY 5
int main(int argc, char *argv[])
{

    int p;
    int fd[2];
    int array[DIM_ARRAY];
    int status;
    int n;
    if (pipe(fd) == -1)
    {
        printf("\nErrore creazione pipe");
        exit(-1); // esco dal prg
    }
    p = fork();
    if (p < 0)
    {
        printf("\nFork non creata");
    }
    else if (p > 0)
    {
        printf("\n sono il processo padre e ho PID:%d, mio figlio ha PID: %d", getpid(), p);
        wait(&status); // il padre aspetta la terminazione del figlio
        close(fd[1]);
        n = read(fd[0], array, DIM_ARRAY);
        printf("Inserisci un numero\n");
        int f;
        scanf("%d", f);
        printf("\nNumeri ricevuti dopo la moltiplicazione:\n");
        for (int i = 0; i < n; i++)
        {
            array[i] *= f;
            printf("%d ", array[i]);
        }
        printf("\n");

        // Close read end of the pipe
        close(fd[0]);
    }
    else
    {
        printf("\n Sono il processo figlio e ho PID = %d", getpid());
        for (int i = 0; i < DIM_ARRAY; i++)
        {
            printf("\nInserisci un numero");
            scanf("%d", &array[i]);
        }
        close(fd[0]);
        if (write(fd[1], array, DIM_ARRAY) == -1)
        {
            printf("\nErrore di scrittura nella pipe");
            close(fd[1]); // bisogna sempre chiudere il fd
            exit(-1);
        }
        close(fd[1]);
    }
}