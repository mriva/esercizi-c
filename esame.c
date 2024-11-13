#include <stdio.h>
#include <string.h>


#define NUM_STUDENTI 5
#define NUM_VERIFICHE 5


typedef struct {
    char cognome[50];
    int voti[NUM_VERIFICHE];
    int n; // numero di verifiche effettivo
} Studente;

float analizzaStudenti (Studente[], int, float*);
void studentiBravi (Studente[], int, char[]);

int main(void) {
    // dichiarazione ed inizializzazione classe
    Studente classe[NUM_STUDENTI] = {
        {"Boracchi", {7, 8, 9, 6}, 4},
        {"Campi", {8, 8, 8, 8, 8}, 5},
        {"Peretti", {4, 6, 7, 5}, 4},
        {"Conti", {9, 8, 8}, 3},
        {"Valoriani", {4, 6, 7, 3}, 4}
    };
    float media_massima, media_totale;
    char bravi[NUM_STUDENTI * 50] = {'\0'};
    
    
    media_totale = analizzaStudenti(classe, NUM_STUDENTI, &media_massima);
    
    printf("media totale: %f \n", media_totale );
    printf("media massima: %f \n", media_massima);
    
    
    studentiBravi(classe, NUM_STUDENTI, bravi);
    
    printf("%s \n", bravi);

    return 0;
}

float analizzaStudenti (Studente classe[NUM_STUDENTI], int len, float* media_massima) {
    float media_totale = 0, m_max = 0, media_studente;
    int i, j;
    int voti_tot = 0;
    
    for(i = 0; i < len; i++) {
        media_studente = 0;
        for (j = 0; j < classe[i].n; j++){
            media_totale += classe[i].voti[j];
            voti_tot++;
            media_studente += classe[i].voti[j];
        }
        media_studente /= classe[i].n;
        if (media_studente > m_max) {
            m_max = media_studente;
        }
    }
    media_totale = media_totale / voti_tot;
    *media_massima = m_max;
    
    return media_totale;
}

void studentiBravi (Studente classe[NUM_STUDENTI], int len, char* bravi) {
    int i, j, lung_nome;
    float media_totale = 0, media_studente = 0, inutile = 0;
    
    media_totale = analizzaStudenti(classe, NUM_STUDENTI, &inutile);
    
    for(i = 0; i < len; i++) {
        media_studente = 0;
        lung_nome = 0;
        for (j = 0; j < classe[i].n; j++){
            media_studente += classe[i].voti[j];
        }
        media_studente /= classe[i].n;
        if (media_studente > media_totale) {
            strcat(bravi, classe[i].cognome);
            strcat(bravi, " ");
        }
    }
}
