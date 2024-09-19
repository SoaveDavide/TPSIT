#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define DIM 5

void Inserimento(int vettore[DIM])
{
    // Generazione di numeri casuali all'interno dell'array
    for (int i = 0; i < DIM; i++)
    {
        vettore[i] = rand() % 101; // Numeri casuali tra 0 e 100
    }
}
void Stampa(int vettore[DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        printf("%d\n", vettore[i]);
    }
}
void VisualizzaDispari(int vettore[DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        if (vettore[i] % 2 != 0)
        {
            printf("%d\n", vettore[i]);
        }
    }
}
void VisualizzaPari(int vettore[DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        if (vettore[i] % 2 == 0)
        {
            printf("%d\n", vettore[i]);
        }
    }
}
void Invertito(int vettore[DIM])
{
    for (int i = DIM; i >= 0; i--)
    {
        printf("%d\n", vettore[i]);
    }
}
void Ricerca(int ricerca, int vettore[DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        if (ricerca == vettore[i])
        {
            printf("Il numero ricercato è: %d\n", vettore[i]);
        }
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
int main(int argc, char *argv[])
{
    int vettore[DIM];
    srand(time(NULL)); // Inizializzazione del seme per la generazione casuale
    Inserimento(vettore);
    int uscire = 0; // variabile che mi permette di uscire dal ciclo
    do
    {
        Menu();
        int scelta; // scelta nel menu
        printf("Inserisci scelta:\n");
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            // Visualizzazione dell'array
            printf("I numeri dell'array sono: \n");
            Stampa(vettore);
            break;
        case 2:
            printf("Array invertito:\n");
            Invertito(vettore);
            break;
        case 3:
            break;
        case 4:
            printf("I numeri pari sono: \n");
            VisualizzaPari(vettore);
            break;
        case 5:
            printf("I numeri dispari sono: \n");
            VisualizzaDispari(vettore);
            break;
        case 6:
            int ricerca;
            printf("Inserisci il numero da ricercare:\n");
            scanf("%d", &ricerca);
            Ricerca(ricerca, vettore);
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
    } while (uscire == 0);
    return 0;
}
