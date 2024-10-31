// CLIENT
#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <string.h>     //funz. stringhe
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     //file header che consente l'accesso alle API dello standard POSIX

#define DIM 50
#define SERVERPORT 1313

int main(int argc, char **argv)
{ // creazione di un elemento di tipo sockaddr vedi pagina 162
    struct sockaddr_in servizio;
    // inizializzazione dell'elemento di tipo sockaddr
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY); //  La funzione htonl accetta un numero a 32 bit in ordine di byte host e restituisce un numero a 32 bit nell'ordine dei byte di rete usato nelle reti TCP/IP (la famiglia di indirizzi AF_INET o AF_INET6).
    servizio.sin_port = htons(SERVERPORT);        // La funzione htons accetta un numero a 16 bit nell'ordine dei byte host e restituisce un numero a 16 bit nell'ordine dei byte di rete usato nelle reti TCP/IP (la famiglia di indirizzi AF_INET o AF_INET6).
    char str1[DIM];                               // Stringa da inviare
    char alfabeto[DIM];
    int socketfd;                                 // identificatore della socket
    // creazione e definizione del Socket di tipo stream tcp pg 163
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // connessione al server pag.173
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)); // come è andata la creazione della socket, struttura (richiamando la struttura), grandezza della struttura o del messaggio
    
    printf("Inserisci la stringa\n");
    scanf("%s", str1);
    write(socketfd, str1, sizeof(str1));
    
    read(socketfd, alfabeto, sizeof(alfabeto));
    printf("Stringa alfabetizzata: %s\n", alfabeto);
    
    close(socketfd);
    return 0;
}
