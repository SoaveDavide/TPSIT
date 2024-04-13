#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

typedef struct {
    float media;
    char nome[20];
    char cognome[20];
    char classe[3];
} Studente;

void* stampaStudente(void *s);
void* stampaStudenteSuFile(void *s);

int main() {
    Studente s1;
    pthread_t threadStampa, threadStampaSuFile;
    s1.media = 6;
    strcpy(s1.nome, "Davide");
    strcpy(s1.cognome, "Soave");
    strcpy(s1.classe, "4E");
    
    pthread_create(&threadStampa, NULL, &stampaStudente, (void *)&s1);
    pthread_create(&threadStampaSuFile, NULL, &stampaStudenteSuFile, (void *)&s1);
    
    pthread_join(threadStampa, NULL);
    pthread_join(threadStampaSuFile, NULL);
    
    return 0;
}

void* stampaStudente(void *s) {
    Studente *studente = (Studente *)s;
    printf("Studente: %s %s, Classe: %s, Media: %.2f\n", studente->nome, studente->cognome, studente->classe, studente->media);
    return NULL;
}

void* stampaStudenteSuFile(void *s) {
    Studente *studente = (Studente *)s;
    FILE *file = fopen("studenti.txt", "a");
    if (file == NULL) {
        fprintf(stderr, "Errore nell'apertura del file.\n");
        return NULL;
    }
    fprintf(file, "Studente: %s %s, Classe: %s, Media: %.2f\n", studente->nome, studente->cognome, studente->classe, studente->media);
    fclose(file);
    return NULL;
}
