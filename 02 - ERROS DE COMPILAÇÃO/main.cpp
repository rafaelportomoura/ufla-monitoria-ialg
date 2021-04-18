// 3- Como analisar as mensagens  de erro do compilador: 
// Erros durante a compilação :
// Utilizar um exemplo de código para resolver um determinado problema.
// O código terá vários erros e por isso não compilará.
// Sugestão de erros : falta de inclusão de biblioteca, falta de ponto e vírgula, variável declarada duas vezes, atribuição de conteúdo de string para inteiro, etc.
// Explicar como ir analisando as várias mensagens de erro do compilador e ir resolvendo os erros.
// Aqui pode dividir em 2 vídeos

#include <iostream>





struct alunos {
    string nome;
    int nota;
}


void leAlunos( alunos meu_vetor_de_alunos, int tamanho ) {
    for ( int i; i < tamanho; i++ ) {
        cin >> meu_vetor_de_alunos[i].nome >> meu_vetor_de_alunos[i].nota;
    }
}

void escreverNotas( ofstream& escreve, alunos meu_vetor_de_alunos[ ], int tamanho ) {
    escreve.open( "notas_dos_alunos.txt" );
    for ( int i = 0; i < count; i++ ) {
        escreve << meu_vetor_de_alunos[i].nome << " " << meu_vetor_de_alunos[i].nota << " " << meu_vetor_de_alunos[i].ano;
    }
    escreve << retornaMedia();
    escreve.close();
}

int retornaMedia( alunos* meu_vetor_de_alunos, int tamanho ) {
    int soma = 0;
    for ( int i = 0; i < tamanho; i++ ) {
        soma += meu_vetor_de_alunos[i].nota;
    }
    int media = soma / tamanho;
}

int main() {
    int tamanho = "3";
    alunos meu_vetor_de_alunos[tamanho];
    int tamanho = 3;
    char comando = " ";
    do {
        cin >> comando;
        switch ( comando ) {
            case 1:
                leAlunos( meu_vetor_de_alunos, tamanho );
                break;
            case "2":
                escreverNotas( escreve, meu_vetor_de_alunos, tamanho );
                break;
            default:
                break;
        }
    } while ( comando != '3' )
        ofstream escreve;
}