#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#define TOT 5
// libreria per aprire la FIFO
#include <fcntl.h>
int main(int argc, char *argv[])
{
    int fd;
    /*if (mkfifo("sumo", 0777) < 0)
    {
        printf("fifo non creata\n");
        return 1;
    }*/
    int somma;
    int vettore[TOT];
    fd = open("sumo", O_RDONLY);
    if (read(fd, vettore, sizeof(vettore)) == -1)
    {
        printf("Non sono riuscito a leggere\n");
        close(fd);
        return 2;
    }
    printf("Sono riuscito a leggere dalla FIFO\n");
    for (int i = 0; i < TOT; i++)
    {
        somma += vettore[i];
    }
    printf("La somma risulta: %d\n", somma);
    close(fd);
    return 0;
}