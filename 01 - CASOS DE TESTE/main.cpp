#include <iostream>

using namespace std;

int main() {
  int vetor[5];
  for ( int posicao = 0; posicao < 5; posicao++ ) {
    cin >> vetor[posicao];
  }
  int maior = vetor[0];
  for ( int posicao = 1; posicao < 5; posicao++ ) {
    if ( vetor[posicao] > maior ) {
      maior = vetor[posicao];
    }
  }
  cout << "maior: " << maior << endl;
  return 0;
}