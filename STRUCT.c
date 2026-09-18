#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define N_CLIENTI 300
#define N_LIMIT 300
#define FILA 8
#define NUMERO_OMBRELLONE 68

typedef struct{
    char Nome[N_LIMIT];
    char Numero_Di_Telefono[N_LIMIT];
}Cliente;

typedef struct{
    Cliente cliente_prenotazione;
    int giorno;
    int mese;
    int anno;
    int fila;
    int numero_ombrellone;
    int lettino;
    int sdraio;
    int sedia;
    float prezzo;
}Prenotazione;

typedef struct{
    Prenotazione elenco[N_CLIENTI];
    int piano[FILA][NUMERO_OMBRELLONE];
    int numPrenotazioni;   // <-- nuovo campo: quante celle di elenco sono occupate
}Prenotazioni;

void stampaSpiaggia(Prenotazioni *p) {
    printf("\n--- Stato Spiaggia ---\n\n");
    
    for (int f = 0; f <= FILA; f++) {
        if(f==0){
            printf("Fila VIP: ");
        }else if(f %2 == 0){
            printf("Fila %d B: ", f/2);
        }else{
            printf("Fila %d A: ", (f/2)+1 );
        }
        for (int n = 0; n < NUMERO_OMBRELLONE; n++) {
            if (p->piano[f][n] == 0) {
                printf("L ");  // Libero
            } else {
                printf("O ");  // Occupato
            }
        }
        printf("\n");
    }
    
    printf("\nLegenda: L = Libero, O = Occupato\n");
}

void inizializzaSpiaggia(Prenotazioni *p) {
    for (int f = 0; f < FILA; f++) {
        for (int n = 0; n < NUMERO_OMBRELLONE; n++) {
            p->piano[f][n] = 0;
        }
    }
    p->numPrenotazioni = 0;   // <-- importante: parte da zero
}

int aggiungiPrenotazione(Prenotazioni *p) {
    if (p->numPrenotazioni >= N_CLIENTI) {
        printf("Elenco prenotazioni pieno!\n");
        return -1;
    }

    Prenotazione nuova;

    printf("Nome cliente: ");
    scanf(" %[^\n]", nuova.cliente_prenotazione.Nome);
    printf("Numero di telefono: ");
    scanf(" %[^\n]", nuova.cliente_prenotazione.Numero_Di_Telefono);

    printf("Giorno: ");
    scanf("%d", &nuova.giorno);
    printf("Mese: ");
    scanf("%d", &nuova.mese);
    printf("Anno: ");
    scanf("%d", &nuova.anno);

    printf("Fila (0-%d): ", FILA - 1);
    scanf("%d", &nuova.fila);
    printf("Numero ombrellone (0-%d): ", NUMERO_OMBRELLONE - 1);
    scanf("%d", &nuova.numero_ombrellone);

    if (nuova.fila < 0 || nuova.fila >= FILA ||
        nuova.numero_ombrellone < 0 || nuova.numero_ombrellone >= NUMERO_OMBRELLONE) {
        printf("Posizione non valida!\n");
        return -1;
    }

    if(p->piano[nuova.fila][nuova.numero_ombrellone] == 1) {
        printf("Ombrellone gia' occupato in quella posizione!\n");
        return -1;
    }

    printf("Lettino (0/1): ");
    scanf("%d", &nuova.lettino);
    printf("Sdraio (0/1): ");
    scanf("%d", &nuova.sdraio);
    printf("Sedia (0/1): ");
    scanf("%d", &nuova.sedia);
    printf("Prezzo: ");
    scanf("%f", &nuova.prezzo);

    p->elenco[p->numPrenotazioni] = nuova;
    p->numPrenotazioni++;

    p->piano[nuova.fila][nuova.numero_ombrellone] = 1;

    printf("Prenotazione aggiunta con successo!\n");
    return 0;
}

int main(){
    Prenotazioni prenotazioni;
    inizializzaSpiaggia(&prenotazioni);
    stampaSpiaggia(&prenotazioni);
    return 0;
}