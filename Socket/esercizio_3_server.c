// SERVER
#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <string.h>     //funz. stringhe
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX

#define DIM 50
#define SERVERPORT 1313
int Palindroma(char *str)
{
    int palindroma = 0;
    for (int i = 0; i < strlen(str) / 2; i++)
    {
        if (str[i] != str[strlen(str) - 1 - i])
        {
            palindroma = 1;
        }
    }
    return palindroma;
}
int main()
{
    struct sockaddr_in servizio; // record con i dati del server e del client
    // definizione dei dati del socket p.161
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    int socketfd, soa, fromlen = sizeof(servizio);
    char str[DIM];
    // impostazione del transport endpoint del server p.163-164
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // leghiamo l'indirizzo al transport endpoint p. 164
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    // poniamo il server in ascolto delle richieste dei client
    listen(socketfd, 10); // pu� attendere fino a 10 client
    // ciclo infinito
    for (;;)
    {
        printf("\n\nServer in ascolto...");
        fflush(stdout);
        // il server accetta la connessione pag. 165
        soa = accept(socketfd, (struct sockaddr *)&servizio, &fromlen);
        // legge dal client
        read(soa, str, sizeof(str));
        int check = Palindroma(str);
        write(socketfd,&check,sizeof(check));
        close(soa);
    }
    return 0;
}
