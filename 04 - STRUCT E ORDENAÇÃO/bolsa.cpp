#include <iostream>
using namespace std;

const int QUANTIDADE_DE_COMPANHIAS = 10;

struct bolsa {
    string companhia;
    float valor;
    float porcentagem;
};


void leitura( bolsa minhaBolsa[ ] ) {
    for ( int i = 0; i < QUANTIDADE_DE_COMPANHIAS; i++ ) {
        getline( cin, minhaBolsa[i].companhia );
        cin >> minhaBolsa[i].valor >> minhaBolsa[i].porcentagem;
        cin.ignore();
    }
}


void selectionSort( bolsa minhaBolsa[ ] ) {
    bolsa minhaBolsaAUX;
    int posicao_maior;

    for ( int i = 0; i < QUANTIDADE_DE_COMPANHIAS; i++ ) {
        posicao_maior = i;
        for ( int j = i; j < QUANTIDADE_DE_COMPANHIAS; j++ ) {
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
    for ( int i = 0; i < QUANTIDADE_DE_COMPANHIAS; i++ ) {
        cout << "Posicao " << i + 1 << endl
            << "\tCompanhia: " << minhaBolsa[i].companhia << endl
            << "\tValor: R$ " << minhaBolsa[i].valor << endl
            << "\tPorcentagem: " << minhaBolsa[i].porcentagem << endl << endl;
    }
}

int main() {
    bolsa minhaBolsa[QUANTIDADE_DE_COMPANHIAS];
    leitura( minhaBolsa );
    ranking( minhaBolsa );
    return 0;
}