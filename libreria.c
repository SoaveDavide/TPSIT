#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 38
#define MAX_CATEGORIA 100

typedef struct
{
    char titolo[DIM];
    char autore[DIM];
    int anno_pubblicazione;
    float prezzo;
    char genere[DIM];
} Libro;

typedef struct
{
    char nome[DIM];
    Libro libri[DIM];
    int num_libri; // numero di libri presenti all'interno della categoria
} Categoria;

Libro biblioteca[DIM];
Categoria categorie[MAX_CATEGORIA];
int numeroCategorie = 0; // Contatore delle categorie

// Funzione per rimuovere newline e spazi iniziali e finali da una stringa
void rimuoviNewline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
    {
        str[len - 1] = '\0';
    }
    while (len > 0 && (str[len - 1] == ' '))
    {
        str[--len] = '\0';
    }
    size_t start = 0;
    while (str[start] == ' ')
    {
        start++;
    }
    if (start > 0)
    {
        memmove(str, str + start, len - start + 1);
    }
}

// Controllo se la categoria esiste
int RicercaCateogoria(char *nome)
{
    rimuoviNewline(nome);
    for (int i = 0; i < numeroCategorie; i++) // Controlla fino al numero effettivo di categorie
    {
        rimuoviNewline(categorie[i].nome);
        if (strcmp(categorie[i].nome, nome) == 0)
        {
            return i; // Ritorna l'indice quando la trova
        }
    }
    return -1; // Se non trova nulla
}

// Creazione di nuove categorie o aggiunta di libri a categorie esistenti
void CreazioneCategorie(Libro libro)
{
    int esiste = RicercaCateogoria(libro.genere);
    if (esiste != -1) // La categoria esiste
    {
        // Aggiungi il libro alla categoria esistente
        int index = categorie[esiste].num_libri;
        categorie[esiste].libri[index] = libro; // Copia l'intero struct
        categorie[esiste].num_libri++;          // Incrementa il numero di libri nella categoria
    }
    else // Crea una nuova categoria se non esiste
    {
        strcpy(categorie[numeroCategorie].nome, libro.genere); // Imposta il nome della categoria
        categorie[numeroCategorie].libri[0] = libro;           // Aggiungi il primo libro
        categorie[numeroCategorie].num_libri = 1;              // Imposta il contatore dei libri a 1
        numeroCategorie++;                                     // Incrementa il numero di categorie
    }
}

// Lettura dei dati dal file CSV
void LetturaDaFile(Libro biblioteca[DIM])
{
    // Apertura file
    FILE *fp;
    if ((fp = fopen("libreria_libri.csv", "r")) == NULL)
    {
        printf("File non aperto correttamente\n");
        return;
    }

    // Inizializza il contatore
    int count = 0;

    // Lettura dei dati dal file
    char buffer[256]; // buffer per una riga
    // Salta la prima riga (intestazione)
    fgets(buffer, sizeof(buffer), fp);
    while (fgets(buffer, sizeof(buffer), fp) != NULL && count < DIM)
    {
        rimuoviNewline(buffer);
        // Parsing della riga
        sscanf(buffer, "%[^,],%[^,],%d,%f,%[^,\n]",
               biblioteca[count].titolo,
               biblioteca[count].autore,
               &biblioteca[count].anno_pubblicazione,
               &biblioteca[count].prezzo,
               biblioteca[count].genere);

        // Aggiungi il libro alla sua categoria
        CreazioneCategorie(biblioteca[count]);

        // Aggiornamento indice dell'array
        count++;
    }
    // Chiusura file
    fclose(fp);
}
void StampaCategorie()
{
    for (int i = 0; i < numeroCategorie; i++)
    {
        printf("Categoria: %s\n", categorie[i].nome);
    }
}
// Stampa l'intera biblioteca
void StampaBiblioteca(Libro biblioteca[DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        // Solo stampare se il titolo non è vuoto
        if (strlen(biblioteca[i].titolo) > 0)
        {
            // Stampa i dettagli del libro
            printf("Libro [%d]: titolo: %s, autore: %s, anno di pubblicazione: %d, prezzo: %.2f, genere: %s\n",
                   i,
                   biblioteca[i].titolo,
                   biblioteca[i].autore,
                   biblioteca[i].anno_pubblicazione,
                   biblioteca[i].prezzo,
                   biblioteca[i].genere);
        }
    }
}

// Ricerca di un libro per titolo
void RicercaTitolo(char titolo[DIM], Libro biblioteca[DIM])
{
    rimuoviNewline(titolo); // Rimuovi eventuali newline dall'input dell'utente
    for (int i = 0; i < DIM; i++)
    {
        // Confronta il titolo cercato con il titolo dei libri nella biblioteca
        if (strcmp(titolo, biblioteca[i].titolo) == 0)
        {
            // Stampa i dettagli del libro trovato
            printf("Libro trovato: [%d]: titolo: %s, autore: %s, anno di pubblicazione: %d, prezzo: %.2f, genere: %s\n",
                   i,
                   biblioteca[i].titolo,
                   biblioteca[i].autore,
                   biblioteca[i].anno_pubblicazione,
                   biblioteca[i].prezzo,
                   biblioteca[i].genere);
            return; // Esci dopo aver trovato il libro
        }
    }
    printf("Libro non trovato\n"); // Messaggio se il libro non è trovato
}

// Ricerca di libri per genere
void RicercaGenere(char *genere)
{
    int indice = RicercaCateogoria(genere); // Trova l'indice della categoria
    if (indice != -1)
    {
        printf("Libri della categoria '%s':\n", categorie[indice].nome);
        for (int i = 0; i < categorie[indice].num_libri; i++)
        {
            Libro libro = categorie[indice].libri[i];
            printf("Libro [%d]: titolo: %s, autore: %s, anno di pubblicazione: %d, prezzo: %.2f\n",
                   i,
                   libro.titolo,
                   libro.autore,
                   libro.anno_pubblicazione,
                   libro.prezzo);
        }
    }
    else
    {
        printf("Categoria non trovata.\n");
    }
}

int main(int argc, char *argv[])
{
    LetturaDaFile(biblioteca);    // Funzione per leggere i dati dal file
    StampaBiblioteca(biblioteca); // Funzione per stampare i dettagli della biblioteca

    char titolo[DIM], genere[DIM];
    printf("Inserire il titolo del libro che vuoi cercare:\n");
    fgets(titolo, sizeof(titolo), stdin); // Utilizza fgets per leggere l'input
    rimuoviNewline(titolo);               // Rimuovi newline dall'input
    RicercaTitolo(titolo, biblioteca);    // Funzione per cercare un libro per titolo
    StampaCategorie();
    // Ricerca per genere
    printf("Inserisci un genere:\n");
    fgets(genere, sizeof(genere), stdin);
    //uso fgets in quanto non toglie gli spazi come scanf e perché include il carattere \n alla fine della stringa
    
    rimuoviNewline(genere); // Rimuovi newline dall'input
    RicercaGenere(genere);

    return 0;
}
