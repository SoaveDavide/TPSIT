#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    while (1)
    {
        int x = 2;
        printf("Sono un processo e ho PID: %d, indirizzo di x: %p\n", getpid(), &x);
        
        int n;
        int *array;
        array = (int*)malloc(5 * sizeof(int));
        printf("Array ha indirizzo %p", &array);
        free(array);
    }
    return 0;
}