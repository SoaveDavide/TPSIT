#include <stdio.h>

// Definizione della struttura
struct coordinate
{
    int x;
    int y;
    int z;
} puntoIniziale;


main(int argc, char *argv[])
{
    puntoIniziale.x = 3;
    puntoIniziale.y = -1;
    puntoIniziale.z = 4;
    printf("Punto iniziale");
    stampa(puntoIniziale);
    punto_modificato(puntoIniziale);
    return 0;
}

void stampa(struct coordinate p1)
{
    printf("\nX %d, Y %d, Z %d\n", p1.x, p1.y, p1.z);
}

void punto_modificato(struct coordinate p1)
{
    p1.x++;
    p1.y++;
    p1.z++;
    printf("punto 2\nX %d, Y %d, Z %d\n", p1.x, p1.y, p1.z);
}