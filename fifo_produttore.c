#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#define TOT 5
// libreria per aprire la FIFO
int main(int argc, char *argv[])
{
    int fd;
    /*if (mkfifo("sumo", 0777) == -1)
    {
        perror("mkfifo");
        return 1;
    }*/
    int vettore[TOT];
    fd = open("sumo", O_WRONLY);
    for (int i = 0; i < TOT; i++)
    {
        int r = rand() % 100;
        vettore[i] = r;
    }

    if (write(fd, vettore, sizeof(vettore)) == -1)
    {
        printf("\nLa scrittura è avvenuta in maniera sbagliata");
        close(fd);
        return 1;
    }
    printf("\n Ho scritto nella FIFO");
    close(fd);
    return 0;
}