#include <iostream>

using namespace std;

struct funcionarios {
    int id;
    string nome;
};



void imprimirFuncionarios( int capacidade, int tamanho, funcionarios* vetor_de_funcionarios ) {
    cout << "\nCapacidade de funcionarios: " << capacidade
        << "\nQuantidade de funcionarios: " << tamanho
        << "\nID\tNOME\n";
    for ( int i = 0; i < tamanho; i++ ) {
        cout << vetor_de_funcionarios[i].id << "\t" << vetor_de_funcionarios[i].nome << endl;
    }
}


funcionarios* RealocaVetorDeFuncionarios( int& capacidade, funcionarios* vetor_de_funcionarios ) {
    funcionarios* vetor_auxiliar = new funcionarios[capacidade];
    for ( int i = 0; i < capacidade; i++ ) {
        vetor_auxiliar[i] = vetor_de_funcionarios[i];
    }
    delete[ ] vetor_de_funcionarios;
    vetor_de_funcionarios = new funcionarios[capacidade + 5];
    for ( int i = 0; i < capacidade; i++ ) {
        vetor_de_funcionarios[i] = vetor_auxiliar[i];
    }
    delete[ ] vetor_auxiliar;
    capacidade += 5;
    return vetor_de_funcionarios;
}

funcionarios* lerFuncionarios( int& capacidade, int& tamanho, funcionarios* vetor_de_funcionarios ) {
    string nome;
    cin >> nome;
    while ( nome != "-1" ) {
        if ( tamanho >= capacidade ) {
            vetor_de_funcionarios = RealocaVetorDeFuncionarios( capacidade, vetor_de_funcionarios );
        }
        vetor_de_funcionarios[tamanho].id = tamanho;
        vetor_de_funcionarios[tamanho].nome = nome;
        tamanho++;
        cin >> nome;
    }
    return vetor_de_funcionarios;
}


int main() {
    char comando;
    int capacidade = 5;
    int tamanho = 0;
    funcionarios* vetor_de_funcionarios;
    vetor_de_funcionarios = new funcionarios[capacidade];
    do {
        cin >> comando;
        switch ( comando ) {
            case 'L':
            case 'l':
                vetor_de_funcionarios = lerFuncionarios( capacidade, tamanho, vetor_de_funcionarios );
                break;

            case 'I':
            case 'i':
                imprimirFuncionarios( capacidade, tamanho, vetor_de_funcionarios );
                break;

            case 'S':
            case 's':
                cout << "Finalizando!";
                break;

            default:
                cout << "Opcao Invalida!\n";
                break;
        }
    } while ( comando != 's' );
    return 0;
}