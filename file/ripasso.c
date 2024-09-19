#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define DIM 100

void Inserimento(int vettore[DIM])
{
    //generazione di numeri casuali all'interno dell'array
    for(int i=0; i < DIM; i++)
    {
        vettore[i] = rand()%101;
    }
}
void Menu()
{
    printf("[1] Visualizzi a video gli elementi dell’array\n");    
    printf("[2] Visualizzi a video l’array invertito\n");    
    printf("[3] Visualizzi a video la somma e media degli elementi del vettore\n");    
    printf("[4] Visualizzi a video tutti i numeri pari\n");    
    printf("[5] Visualizzi a video tutti i numeri dispari\n");    
    printf("[6] Ricerchi un numero (letto in input) nell’array\n");    
    printf("[7] Elimini un elemento (letto in input) dell’array\n");    
    printf("[8] Alterni (o scambi ) a due a due le posizioni del vettore\n");    
    printf("[9] Ordini il vettore\n");    
    printf("[10] Uscire\n");   
}
int main()
{
    int vettore[DIM];
    int uscire = 0;//variabile che mi permette di uscire dal ciclo
    do 
    {
        int scelta; //scelta nel menu
        scanf("%")
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
        
    }
    } while(uscire == 0)
    
    
    return 0;
}
