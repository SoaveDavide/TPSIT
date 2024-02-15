#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>

// libreria per aprire la FIFO
#include <fcntl.h>
int main(int argc, char *argv[])
{
    // dichiarazione delle var
    // una fifo non ha bisogno di un legame di parentela
    int fd;
    // int x;
    //  creazione FIFO
    if (mkfifo("myfifo1", 0777) == -1) // ARGOMENTI(CONSTANTE DI CARATTERI, PERMESSI CHE ASSEGNO AGLI UTENTI PER USO FIFO)
    {
        printf("FIFO non aperta (errore creazione FIFO) \n");
        return 1;
    }

    // aprire in scrittura la FIFO
    fd = open("myfifo1", O_WRONLY); // fd è uguale a 1 poiché ho parto la FIFO in scrittura
    printf("Ho aperto la FIFO \n");

    int x = 90;

    if (write(fd, &x, sizeof(x)) == -1)
    {
        printf("Errore in scirttura nella FIFO \n");
        return 2;
    }
    printf("Ho scritto nella FIFO\n");
    
    close(fd);
    return 0;
}