#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define DIM 1024
int main(int argc, char *argv[])
{
    int p;
    int fd[2];
    FILE *file;
    unsigned char buffer[DIM];
    int status;
    int n;

    if (pipe(fd) < 0)
    {
        printf("Errore creazione della pipe");
        exit(-1);
    }

    p = fork();

    if (p < 0)
    {
        printf("Errore creazione del processo figlio");
        close(fd[0]);
        close(fd[1]);
        exit(-1);
    }
    else if (p > 0)
    {
        // Sono nel padre
        p = fork();
        if (p < 0)
        {
            printf("Figlio non creato correttamente\n");
        }
        else if (p > 0)
        {
            close(fd[0]);
            file = fopen("memoryProcess.txt", "rb");
            if (file == NULL)
            {
                printf("Errore apertura file sorgente");
                close(fd[1]);
                wait(&status);
                exit(-1);
            }
            else
            {
                while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) // itera fino a quando n non è uguale a 0 che equivale a dire che il file è terminato
                {
                    write(fd[1], buffer, n);
                }
                fclose(file);  // chiudo il file
                close(fd[1]);  // chiudo l'uscita della pipe affinchè venga eliminata dal S.O.
                wait(&status); // aspetto la terminazione del processo figlio
                return 0;
            }
        }
        else
        {
            // Sono nel secondo figlio
            // wait(&status);
            int contatore = 0;
            char a = atoi(argv[1]);
            char c;
            close(fd[1]);
            while ((n = read(fd[0], buffer, sizeof(buffer))) > 0)
            {

                for (int i = 0; i < n; i++)
                {
                    if (buffer[i] == a)
                    {
                        contatore++;
                    }
                }
            }
            printf("\nIl carattere %c è presente nel file: %d volte", a, contatore);
            close(fd[0]);
            fclose(file);
            return 1;
        }
    }
    else
    {
        // Sono nel figlio
        close(fd[1]);
        file = fopen("copia.txt", "wb");
        if (file == NULL)
        {
            printf("Errore apertura file destinazione");
            close(fd[0]);
            exit(-1);
        }
        else
        {
            while ((n = read(fd[0], buffer, sizeof(buffer))) > 0)
            {
                fwrite(buffer, 1, n, file);
            }
            fclose(file);
            close(fd[0]);
            return 0;
        }
    }
}
