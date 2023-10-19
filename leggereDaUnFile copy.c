#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    FILE *nomi;
    char c;
    // char vetNome[20];
    nomi = fopen("nomi.txt", "r"); // Contiene la possibilità di aprire o chiudere un file
    // Se non c'è un file lo crea
    if (nomi == NULL)
    {
        printf("File non aperto:ERRORE\n");
        exit(1); // Chiude il programma
    }
    do
    {
        c = fgetc(nomi); // ci metto un carattere referenziato del file
        putchar(c); //Finchè non finisco il file
    } while (c!=EOF); //EOF è l'ultimo carattere del file 
    /*for (int i = 0; i < 4; i++)
    {
        printf("inserisci il nome %d\n", i + 1);
        scanf("%s", vetNome);
        fputs(vetNome, nomi); // per metterlo nel file (lo scrive)
        fputc('\n', nomi);    // Per metterlo a capo
        // Elimina i nomi di prima perciò lo apriamo in "Append" con 'a'
    }*/
    fclose(nomi); // Per chiudere un file
    // printf("OK FILE APERTO\n");
    return 0;
}