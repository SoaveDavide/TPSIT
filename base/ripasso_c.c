#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define num 10000
int arrayDiNumeri[num];

void Ricerca(int firstIndex, int lastIndex, int value)
{
    for (int i = firstIndex; i < lastIndex; i++)
    {
        if (arrayDiNumeri[i] == value)
        {
            printf("posizione nell'array: %d - PID: %d", i, getpid());
        }
    }
}

int main()
{
    int p, numeroDaCercare;
    p = fork();
    if (p < 0)
    {
        exit(1);
    }
    if (p > 0)
    {
        // padre
        Ricerca(0, (num/2), numeroDaCercare);
    }
    else
    {
        // figlio
        Ricerca(0, (num/2), num);
    }
    return 0;
}