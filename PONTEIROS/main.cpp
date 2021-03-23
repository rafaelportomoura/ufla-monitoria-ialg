#include <iostream>

using namespace std;

int* CriaVetorDeInteiros( int tamanho ) {
    if ( tamanho <= 0 ) {
        throw runtime_error( "CriaVetorDeInteiros: tamanho eh invalido!" );
    }
    int* vet = new int[tamanho];
    for ( int i = 0; i < tamanho; i++ ) {
        vet[i] = 0;
    }
    return vet;
}

//RETORNA POR REFERENCIA UM NOVO TAMANHO
int* RealocaVetorDeInteiros( int& tamanho_antigo, int tamanho_novo, int* vetor ) {
    if ( vetor == NULL ) {
        throw runtime_error( "RealocaVetorDeInteiros: vetor eh igual a NULL!" );
    }
    else if ( tamanho_novo < 0 ) {
        throw runtime_error( "RealocaVetorDeInteiros: tamanho_novo eh invalido!" );
    }


    int* vetAuxiliar = CriaVetorDeInteiros( tamanho_antigo );
    for ( int i = 0; i < tamanho_antigo; i++ ) {
        vetAuxiliar[i] = vetor[i];
    }
    delete vetor;
    vetor = CriaVetorDeInteiros( tamanho_novo );
    if ( tamanho_antigo <= tamanho_novo ) {
        for ( int i = 0; i < tamanho_antigo; i++ ) {
            vetor[i] = vetAuxiliar[i];
        }
    }
    else {
        for ( int i = 0; i < tamanho_novo; i++ ) {
            vetor[i] = vetAuxiliar[i];
        }
    }
    tamanho_antigo = tamanho_novo;
    delete vetAuxiliar;
    return vetor;
}

void ImprimirVetorDeInteiros( int* vetor, int tamanho ) {
    if ( vetor == NULL ) {
        throw runtime_error( "ImprimirVetorDeInteiros: vetor eh igual a NULL!" );
    }
    else if ( tamanho == 0 ) {
        throw runtime_error( "ImprimirVetorDeInteiros: tamanho eh igual a 0!" );
    }

    cout << "Imprimindo Vetor:\nTamanho: " << tamanho << endl;
    for ( int i = 0; i < tamanho; i++ ) {
        cout << "vetor[" << i << "]: " << vetor[i] << endl;
    }
}

void LeVetorDeInteiros( int* vetor, int tamanho, int inicio ) {
    if ( inicio <0 || inicio > tamanho ) {
        throw runtime_error( "LeVetorDeInteiros: inicio eh invalido!" );
    }
    else if ( tamanho == 0 ) {
        throw runtime_error( "LeVetorDeInteiros: tamanho eh igual a 0!" );
    }
    cout << "Lendo Vetor:\nDigite o valor das respectivas posicoes:\n";
    for ( int i = inicio; i < tamanho; i++ ) {
        cout << "vetor[" << i << "]: ";
        cin >> vetor[i];
    }
}


int main() {
    int* meu_vetor = NULL;
    char operacao;
    int tamanho = 0;
    int pos;
    int inteiroAux;
    do {
        cout << "\n _____________________________________________________________________________________________"
            << "\n|                                            MENU                                             |"
            << "\n| L - Le todo o vetor         | I - Imprimir vetor            | R - Deleta Vetor              |"
            << "\n| D - Le Determinada Posicao  | A - Altera o tamanho do vetor | C - Criar Vetor               |"
            << "\n| F - Finalizar programa      |                               |                               |"
            << "\n|_____________________________|_______________________________|_______________________________|"
            << "\n|Digite a comando: ";
        cin >> operacao;
        try {
            switch ( operacao ) {
                case 'I':
                case 'i':
                    ImprimirVetorDeInteiros( meu_vetor, tamanho );
                    break;
                case 'L':
                case 'l':
                    LeVetorDeInteiros( meu_vetor, tamanho, 0 );
                    break;
                case 'D':
                case 'd':
                    cout << "Digite a posicao de inicio: ";
                    cin >> pos;
                    cout << "Digite a posicao de fim (a mesma de inicio para posicao especifica): ";
                    cin >> inteiroAux;
                    if ( inteiroAux < 0 || inteiroAux < pos ) {
                        throw runtime_error( "Posicao de fim eh invalida!" );
                    }
                    inteiroAux++;
                    if ( inteiroAux > tamanho && pos > 0 ) {
                        cout << "Posicao de fim maior que tamanho, aumentando tamanho do vetor antes da leitura!\n"
                            << "Tamanho antigo: " << tamanho << endl;
                        meu_vetor = RealocaVetorDeInteiros( tamanho, inteiroAux, meu_vetor );
                        cout << "Tamanho novo: " << tamanho << endl
                            << "Voltando a leitura do vetor!";
                    }
                    LeVetorDeInteiros( meu_vetor, inteiroAux, pos );
                    break;
                case 'R':
                case 'r':
                    if ( meu_vetor == NULL ) {
                        throw runtime_error( "DeletandoVetorDeInteiros: meu_vetor nao existe!" );
                    }

                    cout << "Deletando vetor!";
                    delete meu_vetor;
                    meu_vetor = NULL;
                    break;
                case 'A':
                case 'a':
                    cout << "Digite o novo tamanho do vetor: ";
                    cin >> inteiroAux;
                    meu_vetor = RealocaVetorDeInteiros( tamanho, inteiroAux, meu_vetor );
                    break;
                case 'C':
                case 'c':
                    if ( meu_vetor != NULL ) {
                        throw runtime_error( "CriarVetorDeInteiros: meu_vetor ja existe!" );
                    }
                    cout << "Digite o novo tamanho do vetor: ";
                    cin >> inteiroAux;
                    meu_vetor = CriaVetorDeInteiros( inteiroAux );
                    tamanho = inteiroAux;
                    cout << "Vetor de inteiros com tamanho " << tamanho << " foi criado com sucesso!" << endl;
                    break;
                case 'F':
                case 'f':
                    delete meu_vetor;
                    cout << "Finalizando!\n";
                    operacao = 'f';
                    break;
                default:
                    cout << "Comando Invalido\n";
                    break;
            }
        }
        catch ( runtime_error& e ) {
            cerr << "[ERRO] " << e.what() << '\n';
        }
    } while ( operacao != 'f' );

    return 0;
}