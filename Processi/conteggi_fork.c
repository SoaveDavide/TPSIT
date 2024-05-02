#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Il padre genera un figlio. Il primo conta da 0 a 19. L'altro da 0 a 9
int p;
int conta_padre;
int conta_figlio;
int main()
{
    // Il padre prima fa le sue cose poi genera il figlio

    p = fork();
    if (p < 0)
    {
        printf("Errore: il processo figlio non è nato\n");
        exit(1);
    }
    else if (p > 0)
    {
        // Siamo dentro al padre
        printf("Io sono il padre. Il mio PID è uguale a %d. Mio figlio ha PID = %d. \n", getpid(), p);
        for (conta_padre = 0; conta_padre <= 50; conta_padre++)
        {
            printf("Conto del padre = %d\n", conta_padre);
        }
    }
    else
    {
        // figlio
        printf("Sono il figlio. Il mio PID è = %d. Mio padre ha PID = %d\n", getpid(), getppid());
        for (conta_figlio = 0; conta_figlio <= 30; conta_figlio++)
        {
            printf("Conto del figlio = %d\n", conta_figlio);
        }
    }

    return 0;
}
