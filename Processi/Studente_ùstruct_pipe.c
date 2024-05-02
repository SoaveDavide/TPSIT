#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    // creare una pipe in cui da un processo padre passo al processo figlio uno studente caratterizato da nome, congome e media
    typedef struct
    {
        char nome[20];
        char cognome[20];
        int media;
    } studente;

    int p;
    int fd[2];
    if (pipe(fd) < 0)
    {
        printf("Pipe non creata correttamente\n");
        return -1;
    }
    // creazione processo padre e figlio
    p = fork();
    if (p < 0)
    {
        printf("Fork non andata a buon fine\n");
        close(fd[2]);
        return -1;
    }
    else if (p > 0)
    {
        //int status;
        // sono nel processo padre
        // chiusura estremo di lettura
        close(fd[0]);
        // creazione del primo strumento (tipo di dato)
        studente st1;
        st1.media = 6;
        strcpy(st1.nome, "Davide");
        strcpy(st1.cognome, "Soave");
        if (write(fd[1], &st1, sizeof(st1)) < 0)
        {
            printf("Scrittura non avvenuta \n");
            close(fd[1]);
            return -1;
            // controllo che la scrittua avvenga con successo
        }
        // aspetto che il processo figlio termini per evitare che diventi zombie
        //wait(&status);
        // una volta terminato il programma posso chiudere anche l'altra estremità
        close(fd[1]);
    }
    else
    {
        // sono nel figlio
        // chiusura estremo di scrittura
        close(fd[1]);
        studente st1;
        int n = read(fd[0], &st1, sizeof(st1));
        if (n < 0)
        {
            printf("Lettura non avvenuta \n");
            close(fd[0]);
            return -1;
            // controllo che la lettura avvenga con successo
        }
        printf("MEDIA: %d, NOME: %s, COGNOME: %s", st1.media, st1.nome, st1.cognome);
        close(fd[0]);
    }
    return 0;
}