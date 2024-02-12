#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define DIM 1024
// creare una struct "libro" costituita da titolo, autore e prezzo
// passarla al figlio dal padre
struct libro
{
    char autore[20];
    char titolo[10];
    float prezzo;
}libro1;

int main(int argc, char *argv[])
{
    int p;
    int fd[2];
    int status;
    if (pipe(fd) < 0)
    {
        printf("Pipe non creata correttamente\n");
        exit(-1);
    }
    p = fork(); // creazione del processo figlio
    if (p < 0)
    {
        printf("Errore creazione di processo\n");
        exit(-1);
    }
    else if (p > 0)
    {
        close(fd[0]);
        libro1.prezzo = 5;
        strcpy(libro1.autore, "Giacomo Leopardi");
        strcpy(libro1.titolo, "Infinito");
        write(fd[1],&libro1, sizeof(libro1));
        wait(&status);
        close(fd[1]);
        // sono nel padre;
    }
    else
    {
        close(fd[1]);
        struct libro libro_ricevuto;
        read(fd[0], &libro_ricevuto, sizeof(libro_ricevuto));
        printf("Ho ricevuto il libro\n: TITOLO: %s, AUTORE: %s, PREZZO: %f ", libro_ricevuto.titolo, libro_ricevuto.autore, libro_ricevuto.prezzo);
        close(fd[0]);
        // sono nel figlio;
    }
    return 0;
}