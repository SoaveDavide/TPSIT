#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define DIM 100

void Inserimento(int vettore[DIM])
{
    // Generazione di numeri casuali all'interno dell'array
    for(int i = 0; i < DIM; i++)
    {
        vettore[i] = rand() % 101; // Numeri casuali tra 0 e 100
    }
}

void Menu()
{
    printf("[1] Visualizzare a video gli elementi dell’array\n");    
    printf("[2] Visualizzare a video l’array invertito\n");    
    printf("[3] Visualizzare a video la somma e la media degli elementi del vettore\n");    
    printf("[4] Visualizzare a video tutti i numeri pari\n");    
    printf("[5] Visualizzare a video tutti i numeri dispari\n");    
    printf("[6] Ricercare un numero (letto in input) nell’array\n");    
    printf("[7] Eliminare un elemento (letto in input) dell’array\n");    
    printf("[8] Alternare (o scambiare) a due a due le posizioni del vettore\n");    
    printf("[9] Ordinare il vettore\n");    
    printf("[10] Uscire\n");   
}
int main()
{
    int vettore[DIM];
    srand(time(NULL)); // Inizializzazione del seme per la generazione casuale
    Inserimento(vettore);
    int uscire = 0;//variabile che mi permette di uscire dal ciclo
    do 
    {
        Menu();
        int scelta; //scelta nel menu
        printf("Inserisci scelta:\n");
        scanf("%d", &scelta);
    switch(scelta)
    {
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
        case 8:
        break;
        case 9:
        break;
        case 10:
        uscire = 1;
        break;
        default: 
        printf("Scelta non valida\n");
        break;
        
    }
    } while(uscire == 0);
    return 0;
}
