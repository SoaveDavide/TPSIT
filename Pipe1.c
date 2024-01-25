#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
int main(int argc, char *argv[])
{
    // Far comunicare padre e figlio attraverso un pipe
    // padre manda messaggio al figlio
    int p;
    int fd[2];
    char buffer[BUFFER_SIZE];
    int n;

    if (pipe(fd) == -1)
    {
        printf("\nErrore creazione pipe\n");
        exit(-1);
    }
    // creazione pipe con controllo che non restituiscan -1

    p = fork();
    if (p < 0)
    {
        printf("\nErrore generazione figlio");
    }
    if (p > 0)
    {
        printf("\n sono il processo padre e ho PID:%d, mio figlio ha PID: %d", getpid(), p);
        close(fd[0]); // chiusura pipe in lettura (output pipe)

        const char *messaggio = "Buona fortuna";
        if (write(fd[1], messaggio, strlen(messaggio)) == -1) // funzione cui passare 3 parametri
        {
            printf("\nErrore scrittura nella pipe");
            close(fd[1]);
            exit(-1);
        }
        close(fd[1]);
    }
    else
    {
        printf("\n sono il processo figlio e ho PID:%d, mio padre ha PID:%d", getpid(), getppid());
        close(fd[1]); // fd[1] è la scrittura quindi la chiudo perché il figlio deve leggere
        n = read(fd[0], buffer, BUFFER_SIZE);
        if (n == -1)
        {
            printf("\nErrore nella lettura della pipe");
            close(fd[0]);
            exit(-1);
        }
        else
        {
            buffer[n] = '\0';
            printf("\nMessaggio letto: %s\n", buffer);
            close(fd[0]);
        }
    }
    return 0;
}