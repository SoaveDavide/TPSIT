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
    int somma;
    int vettore[TOT];
    fd = open("sumo", O_RDONLY);
    if (read(fd, &vettore, sizeof(vettore)) == -1)
    {
        printf("Non sono riuscito a leggere\n");
    }
    printf("Sono riuscito a leggere dalla FIFO\n");
    for (int i = 0; i < TOT; i++)
    {
        somma += vettore[i];
    }
    printf("La somma risulta: %d\n", somma);
}