#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM 50
#define SERVERPORT 1313

int ContaOccorrenze(char str[DIM], char c)
{
    int n = 0;
    for (int i = 0; i < DIM; i++)
    { 
        if (str[i] == c)
        {
            n++;
        }
    }
    return n;
}

int main()
{
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    char str[DIM];
    char c;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    listen(socketfd, 10);
    socklen_t fromlen = sizeof(servizio);
    printf("Server in ascolto...\n");

    for (;;)//ciclo infinito
    {
        int soa;
        fflush(stdout);
        soa = accept(socketfd, (struct sockaddr *)&servizio, &fromlen);

        read(soa, str, sizeof(str)); // Lettura della stringa
        printf("Stringa ricevuta: %s\n", str);
        
        read(soa, &c, sizeof(c)); // Lettura del carattere
        printf("Carattere ricevuto: %c\n", c);

        int n = ContaOccorrenze(str, c);
        printf("Numero di occorrenze: %d\n", n);
        write(soa, &n, sizeof(n)); // Invio delle occorrenze

        close(soa); // Chiusura socket
    }

    close(socketfd);
    return 0;
}
