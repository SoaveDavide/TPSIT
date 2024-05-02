#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int limite1 = atoi(argv[1]);
    int limite2 = atoi(argv[2]);
    int n[5];
    int somma = 0;
    if (limite1 >= 30 && limite1 <= 50) // stampa i due limiti
    {
        printf("Il primo limite risulta: %d", limite1);
    }
    if (limite2 >= 30 && limite2 <= 50)
    {
        printf("Il secondo limite risulta: %d", limite2);
    }
        for (int i = 0; i < 5; i++)
        {
            printf("Inserire un numero\n");
            scanf("%d", &n[i]);
            if (n[i] >= limite1 && n[i] <= limite2) // controlla che il numero venga inserito dai due limiti
            {
                printf("il numero %d inserito si trovva in posizione: %d", n[i], i + 1);
            }
            if (n[i] >= limite1 && n[i] <= limite2)
            {
                somma += n[i]; // viene effettuata la somma
            }
        }
    printf("La somma risulta %d", somma);
    return 0;
}