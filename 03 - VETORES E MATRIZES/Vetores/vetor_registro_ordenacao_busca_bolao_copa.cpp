#include <iostream>
using namespace std;


struct time {
    int identificador;
    string nome;
    int gols_marcados;
};


int procuraTime( time meuVetorDeTimes[ ], int identificador, int tamanho ) {
    int timeInexistente = -1;
    for ( int posicao = 0; posicao < tamanho; posicao++ ) {
        if ( meuVetorDeTimes[posicao].identificador == identificador ) {
            return posicao;
        }
    }
    return timeInexistente;
}

void intercala( time meuVetorDeTimes[ ], int inicio, int meio, int fim ) {
    int i = inicio, j = meio + 1;
    int tamanho = fim - inicio + 1;
    time aux[tamanho]; // vetor auxiliar
    for ( int k = 0; k < tamanho; k++ ) {
        if ( ( i <= meio ) and ( j <= fim ) ) {
            if ( meuVetorDeTimes[i].identificador <= meuVetorDeTimes[j].identificador ) {
                aux[k] = meuVetorDeTimes[i]; // copia trecho1 em aux[]
                i++; // avança em trecho1
            }
            else { //
                aux[k] = meuVetorDeTimes[j]; // copia trecho2 em aux[]
                j++; // avanca em trecho2
            }

        }
        else if ( i > meio ) { // terminou o trecho1
            aux[k] = meuVetorDeTimes[j];
            j++;
        }
        else { // terminou o trecho2
            aux[k] = meuVetorDeTimes[i];
            i++;
        }
    }
    // terminando: copiar de aux[] em a[inicio:fim]
    for ( int k = 0; k < tamanho; k++ ) {
        meuVetorDeTimes[inicio + k] = aux[k];
    }
}

void mergesort( time meuVetorDeTimes[ ], int inicio, int fim ) {
    int meio;
    if ( inicio < fim ) {
        meio = ( inicio + fim ) / 2;
        mergesort( meuVetorDeTimes, inicio, meio );
        mergesort( meuVetorDeTimes, meio + 1, fim );
        intercala( meuVetorDeTimes, inicio, meio, fim );
    }
}

void lerVetorDeTimes( time meuVetorDeTimes[ ], int tamanho ) {
    for ( int i = 0; i < tamanho; i++ ) {
        cin >> meuVetorDeTimes[i].identificador >> meuVetorDeTimes[i].nome >> meuVetorDeTimes[i].gols_marcados;
    }
}

int main() {
    int tamanho;
    cin >> tamanho;
    time meuVetorDeTimes[tamanho];
    lerVetorDeTimes( meuVetorDeTimes, tamanho );
    int identificador;
    cin >> identificador;
    mergesort( meuVetorDeTimes, 0, tamanho - 1 );
    int posicao = procuraTime( meuVetorDeTimes, identificador, tamanho );
    cout << posicao << endl;
    if ( posicao >= 0 ) {
        cout << meuVetorDeTimes[posicao].nome << " " << meuVetorDeTimes[posicao].gols_marcados << endl;
    }

    return 0;
}