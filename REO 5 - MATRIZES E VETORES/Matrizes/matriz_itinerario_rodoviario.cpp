#include <iostream>
using namespace std;

int main() {
    string cidades[5];
    int distancia[5][5];
    float consumo;
    for ( int i = 0; i < 5; i++ ) {
        cin >> cidades[i];
    }
    for ( int linha = 0; linha < 5; linha++ ) {
        for ( int coluna = 0; coluna < 5; coluna++ ) {
            if ( linha == coluna ) {
                distancia[linha][coluna] = 0;
            }
            else {
                cin >> distancia[linha][coluna];
            }
        }
    }
    cin >> consumo;
    for ( int linha = 0; linha < 5; linha++ ) {
        for ( int coluna = 0; coluna < 5; coluna++ ) {
            if ( distancia[linha][coluna] < 250 && distancia[linha][coluna] != 0 ) {
                cout << cidades[linha] << " " << cidades[coluna] << endl;
            }
        }
    }
    float combustivel = 0;
    for ( int linha = 0; linha < 5; linha++ ) {
        for ( int coluna = 0; coluna < 5; coluna++ ) {
            if ( distancia[linha][coluna] != 0 ) {
                combustivel = distancia[linha][coluna] / consumo;
                cout << cidades[linha] << " " << cidades[coluna] << " " << combustivel << endl;
            }
        }
    }
    return 0;
}
