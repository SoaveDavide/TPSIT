#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h> //libreria nuova thread

void* stampaBuongiorno(void *par) //obbligato a mettere puntatore a void
{
    //ci metto 
    printf("buongiorno\n");
    return NULL;
}
void* stampaSera(void *par)
{
    //ci metto 
    printf("buonasera\n");
    return NULL;
}
void* stampaNotte(void *par)
{
    //ci metto 
    printf("buonanotte\n");
    return NULL;
}
int main(int argc, char *argv[]) // questo programma diventa processo ma anche thread principale
{
    // creare tre variabili di tipo thread
    pthread_t threadGiorno, threadSera, threadNotte;
    char *msg1 = "Buongiorno";
    char *msg1 = "BuonaSera";
    char *msg1 = "Buonanotte";
    printf("ciao\n");

    pthread_create(&threadGiorno, NULL, &stampaBuongiorno, NULL);
    pthread_create(&threadSera, NULL, &stampaSera, NULL);
    pthread_create(&threadNotte, NULL, &stampaNotte, NULL);

    pthread_join(threadGiorno, NULL);
    pthread_join(threadSera, NULL);
    pthread_join(threadNotte, NULL);
     // serve a lanciare un thread
    // nel secondo parametro posso mettere dei valori per modificare la libreria standard

    //printf("buongiorno\n");
    
    // lo spacco in 4 thread

    return 0;
}