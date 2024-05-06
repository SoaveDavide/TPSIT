#include <stdio.h>
#include <stdlib.h>
#define BUFFER_DIM 1024
int main(int argc, char *argv[])
{
    // Apriamo un file il lettura poi ne apriamo un altro in scrittura passandogli quello scritto in lettura
    FILE *origine, *destinazione;
    int n; // numero byte da leggere
    unsigned char buffer[BUFFER_DIM];
    if (argc != 3)
    {
        printf("Inserire correttamente il numero di paramentri\n");
        exit(1); // Esco dal programma
    }
    origine = fopen(argv[1], "r");
    if (origine == NULL)//controllo che il file sia aperto
    {
        printf("ERRORE APERTURA FILE ORIGINE\n");
        exit(1);
    }
    destinazione = fopen(argv[2], "w");//apro file di destinazione
    if (destinazione == NULL)//controllo che il file sia aperto
    {
        printf("ERRORE APERTURA FILE destinazione\n");
        exit(1);//esco dal programma
    }
    // cuore del problema
    while (!feof(origine)) // Verifico se sono alla fine del file finchè non sono alla fine
    {
        n = fread(buffer, 1, BUFFER_DIM, origine); // numero di byte alla volta; dimensione; file da leggere
        if (n > 0)
        {
            fwrite(buffer,1,n,destinazione);//Leggo n byte alla volta fino al massimo scrivo sul file di destinazione
        }
        fclose(origine);
        fclose(destinazione);
    }
}