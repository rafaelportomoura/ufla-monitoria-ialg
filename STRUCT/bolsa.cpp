#include <iostream>
using namespace std;

const int QUANTIDADE_DE_COMPANHIAS = 10;

struct bolsa {
    string companhia;
    float valor;
    float porcentagem;
};


void leitura( bolsa minhaBolsa[ ] ) {
    for ( unsigned i = 0; i < QUANTIDADE_DE_COMPANHIAS; i++ ) {
        getline( cin, minhaBolsa[i].companhia );
        cin >> minhaBolsa[i].valor >> minhaBolsa[i].porcentagem;
        cin.ignore();
    }
}


void selectionSort( bolsa minhaBolsa[ ] ) {
    bolsa minhaBolsaAUX;
    int posicao_maior;

    for ( unsigned i = 0; i < QUANTIDADE_DE_COMPANHIAS; i++ ) {
        posicao_maior = i;
        for ( unsigned j = i; j < QUANTIDADE_DE_COMPANHIAS; j++ ) {
            if ( minhaBolsa[j].valor > minhaBolsa[posicao_maior].valor ) {
                posicao_maior = j;
            }
        }
        minhaBolsaAUX = minhaBolsa[i];
        minhaBolsa[i] = minhaBolsa[posicao_maior];
        minhaBolsa[posicao_maior] = minhaBolsaAUX;
    }
}

void ranking( bolsa minhaBolsa[ ] ) {
    selectionSort( minhaBolsa );
    cout << "RANKING: " << endl;
    for ( unsigned i = 0; i < QUANTIDADE_DE_COMPANHIAS; i++ ) {
        cout << minhaBolsa[i].companhia << " R$ " << minhaBolsa[i].valor << endl;
    }
}

int main() {
    bolsa minhaBolsa[QUANTIDADE_DE_COMPANHIAS];
    leitura( minhaBolsa );
    ranking( minhaBolsa );
    return 0;
}