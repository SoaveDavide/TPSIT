#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>
#define TOT 5
// libreria per aprire la FIFO
#include <fcntl.h>
int main(int argc, char *argv[])
{
    int fd;
    int vettore[TOT];
    fd = open("sumo", O_WRONLY);
    for (int i = 0; i < TOT; i++)
    {
        int r = rand() % 100;
        vettore[i] = &r;
    }
    
    if (write(fd, &vettore, sizeof(vettore)) == -1)
    {
        printf("\nLa scrittura è avvenuta in maniera sbagliata");
        return 1;
    }
    printf("\n Ho scritto nella FIFO");
    close(fd);
    return 0;
}