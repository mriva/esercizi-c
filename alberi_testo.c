#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct El {
    char c;
    struct El *left, *right;
} Nodo;

typedef Nodo *Albero;

Albero nN(char valore);
void stampaAlbero(Albero t);
void print(Albero t);
Albero costruisci1();
Albero costruisci2();
Albero costruisci3();
Albero costruisci4();

// TODO PROTOTIPI
int controllaAlberi(Albero ta, Albero tb);
int cercaCammino(Albero t, const char *cammino);

void trovaCammini(Albero node, char **camnini);
void trovaCamminiRic(Albero node, char arr[], char **cammini, int index);

// Utilizzo un contatore globale per tenere traccia dei cammini trovati
int indice_contatore;

int main() {

    Albero t1 = costruisci1();  // albero di riferimento
    Albero t2 = costruisci2();
    Albero t3 = costruisci3();
    Albero t4 = costruisci4();

    stampaAlbero(t1);
    stampaAlbero(t2);
    stampaAlbero(t3);
    stampaAlbero(t4);

    if(cercaCammino(t1,"ciano"))
        printf("ciano PRESENTE IN T1\n");
    else
        printf("ciano NON PRESENTE IN T1\n");

    if(cercaCammino(t3,"col"))
        printf("col PRESENTE IN T3\n");
    else
        printf("col NON PRESENTE IN T3\n");

    if(controllaAlberi(t1, t2))
        printf("t1 e t2 OK\n");
    else
        printf("t1 e t2 NON OK\n");

    if(controllaAlberi(t1, t3))
        printf("t1 e t3 OK\n");
    else
        printf("t1 e t3 NON OK\n");

    if(controllaAlberi(t1, t4))
        printf("t1 e t4 OK\n");
    else
        printf("t1 e t4 NON OK\n");

    return 0;
}

int controllaAlberi(Albero ta, Albero tb) {
    int trovati = 0;

    // alloco un array di puntatori a stringhe per contenere i cammini trovati in un albero
    char **cammini = (char **) malloc(2^10 * sizeof(char *));

    // prima di ogni nuova ricerca, azzero il contatore dei cammini trovati
    indice_contatore = 0;

    trovaCammini(ta, cammini);

    // per ognuno dei cammini trovati, verifico se è soddisfatta la condizione
    for (int i = 0; i < indice_contatore; i++) {
        if (cercaCammino(tb, cammini[i])) {
            trovati++;
        }
    }

    return trovati == indice_contatore;
}

int cercaCammino(Albero t, const char *cammino) {
    if (t == NULL) return 0;
    if (t->left == NULL && t->right == NULL) {
        if (t->c == cammino[0] && cammino[1] == '\0') {
            return 1;
        } else {
            return 0;
        }
    }

    return cercaCammino(t->left, cammino + 1) || cercaCammino(t->right, cammino + 1);
}

// dato un albero, trova tutti i cammini possibili contenuti in esso
void trovaCammini(Albero node, char **cammini) {
    if (node == NULL) {
        return;
    }

    // alloco un array di caratteri per contenere il cammino, max 10 caratteri
    char arr[10] = "";
    trovaCamminiRic(node, arr, cammini, 0);
}

// funzione ricorsiva per trovare i cammini
void trovaCamminiRic(Albero node, char arr[], char **cammini, int index) {
    if (node == NULL) {
        return;
    }

    arr[index] = node->c;

    // se questa condizione è verificata signifia che ci troviamo in una foglia
    // quindi il cammino è stato trovato e lo salviamo nell'array di cammini
    if (node->left == NULL && node->right == NULL) {
        cammini[indice_contatore] = (char *) malloc(1000 * sizeof(char));
        arr[index + 1] = '\0';
        strcpy(cammini[indice_contatore], arr);
        indice_contatore++;
    }

    trovaCamminiRic(node->left, arr, cammini, index + 1);
    trovaCamminiRic(node->right, arr, cammini, index + 1);
}

// Funzione per creare un nuovo nodo
Albero nN(char valore) {
    Albero nodo = (Albero) malloc(sizeof(Nodo));
    nodo->c = valore;nodo->left = NULL;nodo->right = NULL;
    return nodo;
}

// Funzione per stampare l'albero
void stampaAlbero(Albero t) {
    print(t);
    printf("\n");
}

void print(Albero t) {
    if (t == NULL)return;
    else {printf(" (");print(t->left);printf(" %c ", t->c);print(t->right);printf(") ");}
}

Albero costruisci1() {
    Albero radice = nN('c');
    radice->left = nN('i');
    radice->right = nN('o');
    radice->left->left = nN('a');
    radice->left->right = nN('n');
    radice->right->left = nN('l');
    radice->left->left->left = nN('o');
    radice->left->left->right = nN('n');
    radice->left->left->right->right = nN('o');
    return radice;
}

Albero costruisci2() {
    Albero radice = nN('c');
    radice->left = nN('o');
    radice->left->left = nN('l');
    radice->left->right = nN('t');
    radice->left->right->left = nN('t');
    radice->left->right->left->right = nN('o');
    radice->right = nN('i');
    radice->right->left = nN('n');
    radice->right->right = nN('a');
    radice->right->right->left = nN('o');
    radice->right->right->right = nN('n');
    radice->right->right->right->left = nN('o');
    return radice;
}

Albero costruisci3() {
    Albero radice = nN('c');
    radice->left = nN('o');
    radice->left->left = nN('l');
    radice->left->left->left = nN('l');
    radice->left->left->left->left = nN('o');
    radice->left->right = nN('t');
    radice->left->right->left = nN('t');
    radice->left->right->left->right = nN('o');
    radice->right = nN('i');
    radice->right->left = nN('n');
    radice->right->right = nN('a');
    radice->right->right->left = nN('o');
    radice->right->right->right = nN('n');
    radice->right->right->right->left = nN('o');
    return radice;
}

Albero costruisci4() {
    Albero radice = nN('c');
    radice->left = nN('o');
    radice->left->left = nN('l');
    radice->left->right = nN('t');
    radice->left->right->left = nN('t');
    radice->left->right->left->right = nN('o');
    radice->right = nN('i');
    radice->right->left = nN('m');
    radice->right->right = nN('a');
    radice->right->right->left = nN('o');
    radice->right->right->right = nN('n');
    radice->right->right->right->left = nN('o');
    return radice;
}


