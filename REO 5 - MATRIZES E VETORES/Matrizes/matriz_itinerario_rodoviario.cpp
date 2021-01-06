#include <iostream>
using namespace std;

int main() {
    string cidades[5];
    int distancia[5][5];
    float combustivel;
    for (int i = 0; i < 5; i++) {
        cin >> cidades[i];
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == j) {
                distancia[i][j] = 0;
            }
            else {
                cin >> distancia[i][j];
            }
        }
    }
    cin >> combustivel;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (distancia[i][j] < 250 && distancia[i][j] != 0) {
                cout << cidades[i] << " " << cidades[j] << endl;
            }
        }
    }
    float consumo = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (distancia[i][j] != 0) {
                consumo = distancia[i][j] / combustivel;
                cout << cidades[i] << " " << cidades[j] << " " << consumo << endl;
            }
        }
    }
    return 0;
}
