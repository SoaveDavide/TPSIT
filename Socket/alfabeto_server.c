#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM 50
#define SERVERPORT 1313

void Alfabeto(char stringa[DIM]) {
    char temp;
    int n = strlen(stringa);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (stringa[i] > stringa[j]) {
                temp = stringa[i];
                stringa[i] = stringa[j];
                stringa[j] = temp;
            }
        }
    }
}

int main() {
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    
    char str[DIM];
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    listen(socketfd, 10);
    
    printf("Server in ascolto...\n");

    for (;;) { // ciclo infinito
        socklen_t fromlen = sizeof(servizio);
        int soa = accept(socketfd, (struct sockaddr *)&servizio, &fromlen);
        
        read(soa, str, sizeof(str));
        str[strcspn(str, "\n")] = '\0'; 
        printf("Stringa ricevuta: %s\n", str);

        Alfabeto(str);
        printf("Stringa alfabetizzata: %s\n", str);

        write(soa, str, strlen(str) + 1); 
        close(soa); // Chiusura socket
    }

    close(socketfd);
    return 0;
}
