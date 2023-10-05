#include <stdio.h>
void main(int argc, char *argv[])
{
    typedef struct
    {
        char nome[20];
        char cognome;
        int media;
    } studente_i;
    studente_i studente;
    studente_i *stud = (studente_i*) &studente;
    //studente_i *stud = &studente; funziona lo stesso in quanto metto dentro al puntatore un indirizzo di memoria
    strcpy(stud -> nome, "nome");
    strcpy(stud -> cognome, "cognome");
    stud -> media = 0;
    printf ("%d\n", stud -> nome);
    printf ("%d\n", stud -> cognome);
    printf ("%d\n", stud -> media);
    return 0;
}