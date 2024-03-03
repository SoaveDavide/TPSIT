#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#define DIM 1024
int main(int argc, char *argv[])
{
    int fd;
    int p;
    unsigned char buffer[DIM];
    int n;
    while (strcmp(buffer, "HALT") != 0) { // Rimuovi il punto e virgola qui
        p = fork();
        if (p < 0) {
            printf("Figlio non creato\n");
            return 0;
        }
        if (p > 0) { // Sono nel padre
            fd = open("chat", O_RDONLY);
            if (fd < 0) {
                printf("FIFO non aperta correttamente\n");
                return -1;
            }
            
            while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
                buffer[n] = '\0'; // Assicura che il buffer sia terminato correttamente
                printf("%s", buffer);
            }
            close(fd);
        } else if (p == 0) { // Sono nel figlio
            fd = open("chat", O_WRONLY);
            if (fd < 0) {
                printf("FIFO non aperta correttamente\n");
                return -1;
            }
            do {
                scanf("%s", buffer);
                n = write(fd, buffer, strlen(buffer)); // Scrivi solo la quantità effettiva di dati
                if (n < 0) {
                    printf("Errore nella scrittura sulla FIFO\n");
                    return -1;
                }
            } while (strcmp(buffer, "HALT") != 0);
            close(fd);
            exit(0); // Esci dal figlio dopo aver inserito HALT
        }
    }
    return 0;
}