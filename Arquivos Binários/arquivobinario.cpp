#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const string NOME_ARQUIVO_PRINCIPAL = "funcionarios.dat";
const string NOME_ARQUIVO_INPUT = "teste.input";

int POSICAO_INVALIDA;
int TAMANHO;

struct cabecalho {
    int quantidade_registros;
};

ostream& operator<<( ostream& saida, cabecalho& meu_cabecalho ) {
    saida << "Quantidade de Funcionarios: " << meu_cabecalho.quantidade_registros << endl;
    return saida;
}


struct funcionario {
    int identificacao;
    char nome[30];
    float salario;
};

istream& operator>>( istream& leitura, funcionario& meu_funcionario ) {
    leitura >> meu_funcionario.identificacao >> meu_funcionario.salario >> meu_funcionario.nome;
    return leitura;
}

void saidaLeitura() {
    cout << "Digite identificacao (int) | salario (float) | nome (char[20])\n";
}

ostream& operator<<( ostream& saida, funcionario& meu_funcionario ) {
    saida << "Identificacao: " << meu_funcionario.identificacao << endl;
    saida << "Nome: " << meu_funcionario.nome << endl;;
    saida << "Salario: " << meu_funcionario.salario << endl;
    return saida;
}


ifstream arquivo_input;
fstream meu_arquivo;
funcionario meu_funcionario;
cabecalho meu_cabecalho;

void le_cabecalho() {
    meu_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str(), ios::binary | ios::in );
    if ( meu_arquivo ) {
        meu_arquivo.seekg( 0, ios::beg );
        meu_arquivo.read( ( char* )&meu_cabecalho, sizeof( cabecalho ) );
        meu_arquivo.close();
    }
    else {
        meu_arquivo.close();
        throw std::runtime_error( "Lendo cabecalho: Arquivo não existe!" );

    }
}

void atualiza_cabecalho() {
    meu_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str(), ios::binary | ios::in | ios::out );
    if ( meu_arquivo ) {
        meu_arquivo.seekp( 0, ios::beg );
        meu_arquivo.write( ( const char* )&meu_cabecalho, sizeof( cabecalho ) );
        meu_arquivo.close();
    }
    else {
        meu_arquivo.close();
        throw std::runtime_error( "Atualizando cabecalho: Arquivo não existe!" );

    }
}

void escreve_funcionario( int pos ) {
    meu_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str(), ios::binary | ios::in | ios::out );
    if ( meu_arquivo ) {
        meu_arquivo.seekp( pos, ios::beg );
        meu_arquivo.write( ( const char* )( &meu_funcionario ), sizeof( funcionario ) );
        meu_arquivo.close();
    }
    else {
        meu_arquivo.close();
        throw std::runtime_error( "Escrevendo funcionario: Arquivo não existe!" );

    }
}

funcionario le_funcionario( int pos ) {
    meu_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str(), ios::binary | ios::in );
    funcionario meu_funcionario_leitura;
    if ( meu_arquivo ) {
        meu_arquivo.seekg( pos, ios::beg );
        meu_arquivo.read( ( char* )( &meu_funcionario_leitura ), sizeof( funcionario ) );
        meu_arquivo.close();
        return meu_funcionario_leitura;
    }
    else {
        meu_arquivo.close();
        throw std::runtime_error( "Lendo funcionario: Arquivo não existe!" );

    }

}

void insere() {
    le_cabecalho();
    long int pos_escrita = sizeof( cabecalho ) + ( sizeof( funcionario ) * meu_cabecalho.quantidade_registros );
    escreve_funcionario( pos_escrita );
    meu_cabecalho.quantidade_registros++;
    atualiza_cabecalho();
}

// Função retorna struct funcionario e a posicao dele no arquivo
funcionario buscaPorNome( string nome, int& pos ) {
    funcionario meu_funcionario_busca;
    meu_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str(), ios::binary | ios::in );
    meu_arquivo.seekg( 0, ios::end );
    int i = 0;
    meu_arquivo.seekg( 0, ios::beg );
    meu_arquivo.read( ( char* )&meu_cabecalho, sizeof( cabecalho ) );
    while ( i < meu_cabecalho.quantidade_registros ) {
        meu_arquivo.read( ( char* )&meu_funcionario_busca, sizeof( funcionario ) );
        if ( strcmp( nome.c_str(), meu_funcionario_busca.nome ) == 0 ) {
            meu_arquivo.close();
            pos = i;
            return meu_funcionario_busca;
        }
        i++;
    }
    meu_arquivo.close();
    throw runtime_error( "Busca: Nome nao encontrado!" );
}
funcionario buscaPorId( int id, int& pos ) {
    funcionario meu_funcionario_busca;
    meu_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str(), ios::binary | ios::in );
    meu_arquivo.seekg( 0, ios::end );
    int i = 0;
    meu_arquivo.seekg( 0, ios::beg );
    meu_arquivo.read( ( char* )&meu_cabecalho, sizeof( cabecalho ) );
    while ( i < meu_cabecalho.quantidade_registros ) {
        meu_arquivo.read( ( char* )&meu_funcionario_busca, sizeof( funcionario ) );
        if ( meu_funcionario_busca.identificacao == id ) {
            meu_arquivo.close();
            pos = i;
            return meu_funcionario_busca;
        }
        i++;
    }
    meu_arquivo.close();
    throw runtime_error( "Busca: Identificacao nao encontrado!" );
}
funcionario buscaPorSalario( float salario, int& pos ) {
    funcionario meu_funcionario_busca;
    meu_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str(), ios::binary | ios::in );
    meu_arquivo.seekg( 0, ios::end );
    int i = 0;
    meu_arquivo.seekg( 0, ios::beg );
    meu_arquivo.read( ( char* )&meu_cabecalho, sizeof( cabecalho ) );
    while ( i < meu_cabecalho.quantidade_registros ) {
        meu_arquivo.read( ( char* )&meu_funcionario_busca, sizeof( funcionario ) );
        if ( meu_funcionario_busca.salario == salario ) {
            meu_arquivo.close();
            pos = i;
            return meu_funcionario_busca;
        }
        i++;
    }
    meu_arquivo.close();
    throw runtime_error( "Busca: Salario nao encontrado!" );
}
funcionario busca( int& pos ) {
    char comando;
    string nome;
    int id;
    float salario;
    do {
        cout << "\n ______________________________________________________________________________________"
            << "\n|                                     BUSCA                                            |"
            << "\n| N - Busca por nome     | S - Busca por salario     | I - Busca por identificacao     |"
            << "\n| C - Cancelar Operacao  |                           |                                 |"
            << "\n|________________________|___________________________|_________________________________|"
            << "\n|Digite a comando: ";
        cin >> comando;
        switch ( comando ) {
            case 'N':
            case 'n':
                cout << "Digite o nome: ";
                cin >> nome;
                return buscaPorNome( nome, pos );
                break;
            case 'S':
            case 's':
                cout << "Digite o salario: ";
                cin >> salario;
                return buscaPorSalario( salario, pos );
                break;
            case 'I':
            case 'i':
                cout << "Digite o id: ";
                cin >> id;
                return buscaPorId( id, pos );
                break;
            case 'C':
            case 'c':
                throw runtime_error( "Busca: Operacao cancelada!!" );
                break;
            default:
                cout << "Comando invalido\n";
                break;
        }
    } while ( comando != 'c' );
    throw runtime_error( "Busca: Erro na busca!" );
}

void imprimir() {
    meu_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str(), ios::binary | ios::in );
    if ( meu_arquivo ) {
        meu_arquivo.seekg( 0, ios::beg );
        int cont = 0;
        meu_arquivo.read( ( char* )&meu_cabecalho, sizeof( cabecalho ) );
        cout << meu_cabecalho << endl;
        while ( cont < meu_cabecalho.quantidade_registros ) {
            meu_arquivo.seekg( ( cont * sizeof( funcionario ) ) + sizeof( cabecalho ) );
            meu_arquivo.read( ( char* )&meu_funcionario, sizeof( funcionario ) );
            cout << meu_funcionario << endl;
            cont++;
        }
        meu_arquivo.close();
    }
    else {

        meu_arquivo.close();
        throw std::runtime_error( "Imprimindo: Arquivo não existe!" );
    }

}


void le_arquivo_input( string nome ) {
    arquivo_input.open( nome.c_str() );
    if ( arquivo_input ) {
        while ( arquivo_input >> meu_funcionario ) {
            insere();
        }
        arquivo_input.close();
    }
    else {
        arquivo_input.close();
        throw std::runtime_error( "Leitura de arquivo input: Arquivo não existe!" );
    }
}

void atualizacao() {
    int posicao_do_funcionario;
    char comando;
    cout << "\n ______________________________________________________________________________________"
        << "\n|                                     ATUALIZACAO                                      |"
        << "\n|Como voce quer buscar o funcionario?                                                  |";
    meu_funcionario = busca( posicao_do_funcionario );
    posicao_do_funcionario = ( sizeof( funcionario ) * posicao_do_funcionario ) + sizeof( cabecalho );
    do {
        cout << "\nFuncionario para ser alterado:\n" << meu_funcionario;
        cout << " ______________________________________________________________________________________"
            << "\n|                                     ATUALIZACAO                                      |"
            << "\n| N - Alterar nome     | S - Alterar Salario     | I - Alterar Id                      |"
            << "\n| A - Alterar tudo     | F - Finalizar Atualizacao                                     |"
            << "\n|______________________________________________________________________________________|"
            << "\n|Digite a comando: ";
        cin >> comando;
        switch ( comando ) {
            case 'F':
            case 'f':
                throw runtime_error( "Atualizacao: Operacao finalizada!" );
                break;

            case 'N':
            case 'n':
                cout << "Digite o novo nome: ";
                cin >> meu_funcionario.nome;
                escreve_funcionario( posicao_do_funcionario );
                cout << "Nome do funcionario atualizado com sucesso!\n";
                break;

            case 'S':
            case 's':
                cout << "Digite o novo salario: ";
                cin >> meu_funcionario.salario;
                escreve_funcionario( posicao_do_funcionario );
                cout << "Salario do funcionario atualizado com sucesso!\n";
                break;

            case 'I':
            case 'i':
                cout << "Digite a nova identificacao: ";
                cin >> meu_funcionario.identificacao;
                escreve_funcionario( posicao_do_funcionario );
                cout << "Identificacao do funcionario atualizado com sucesso!\n";
                break;

            case 'A':
            case 'a':
                saidaLeitura();
                cin >> meu_funcionario;
                escreve_funcionario( posicao_do_funcionario );
                cout << "Funcionario atualizado com sucesso!\n" << meu_funcionario;
                comando = 'f';
                break;

            default:
                cout << "Comando invalida!\n";
                break;
        }
    } while ( comando != 'f' );
}

void remocao() {
    int pos, pos_aux, cont;
    char comando;
    cout << "\n ______________________________________________________________________________________"
        << "\n|                                       REMOCAO                                        |"
        << "\n|Como voce quer buscar o funcionario?                                                  |";
    meu_funcionario = busca( cont );
    do {
        cout << "______________________________________________________________________________________\n"
            << "Funcionario:\n" << meu_funcionario
            << "______________________________________________________________________________________\n"
            << "Voce deseja excluir esse funcionario?\nS - sim  | N - nao | O - Outro\nDigite a opcao: ";
        cin >> comando;
        switch ( comando ) {
            case 'S':
            case 's':
                comando = 's';
                break;

            case 'O':
            case 'o':
                meu_funcionario = busca( cont );
                break;

            case 'N':
            case 'n':
                throw runtime_error( "Remocao: Operacao cancelada!" );
                break;

            default:
                cout << "Comando invalido\n";
                break;
        }
    } while ( comando != 's' );

    while ( cont < meu_cabecalho.quantidade_registros ) {
        pos = ( sizeof( funcionario ) * cont ) + sizeof( cabecalho );
        pos_aux = pos + sizeof( funcionario );
        meu_funcionario = le_funcionario( pos_aux );
        escreve_funcionario( pos );
        cont++;
    }
    meu_cabecalho.quantidade_registros--;
    atualiza_cabecalho();
    cout << "Funcionario removido com sucesso!\n";

}

ofstream abri_arquivo;

void menu() {
    char operacao;
    string nome;
    int pos;
    do {
        cout << "\n _____________________________________________________________________________________________"
            << "\n|                                            MENU                                             |"
            << "\n| I - Insere funcionario      | P - Imprimir funcionarios     | U - Atualizar funcionario     |"
            << "\n| B - Buscar funcionario      | A - Inserir por arquivo       | F - Finalizar programa        |"
            << "\n| R - Remove funcionario      | L - Remove todos funcionarios |                               |"
            << "\n|_____________________________|_______________________________|_______________________________|"
            << "\n|Digite a comando: ";
        cin >> operacao;
        try {
            switch ( operacao ) {
                case 'I':
                case 'i':
                    cout << "Insercao:\n";
                    saidaLeitura();
                    cin >> meu_funcionario;
                    insere();
                    break;
                case 'B':
                case 'b':
                    meu_funcionario = busca( pos );
                    cout << "Funcionario:\n" << meu_funcionario;
                    break;
                case 'R':
                case 'r':
                    remocao();
                    break;
                case 'U':
                case 'u':
                    atualizacao();
                    break;
                case 'F':
                case 'f':
                    cout << "Finalizando!\n";
                    operacao = 'f';
                    break;
                case 'P':
                case 'p':
                    cout << "Imprimindo: \n";
                    imprimir();
                    break;
                case 'A':
                case 'a':
                    cout << "Digite p para nome padrao ou digite o nome do arquivo: ";
                    cin >> nome;
                    if ( nome == "p" ) { nome = NOME_ARQUIVO_INPUT; }
                    le_arquivo_input( nome );
                    break;
                case 'L':
                case 'l':
                    abri_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str(), ios::out );
                    abri_arquivo.close();
                    meu_cabecalho.quantidade_registros = 0;
                    atualiza_cabecalho();
                    cout << "Todos funcionarios removidos!\n";
                    break;
                default:
                    cout << "Comando Invalido\n";
                    break;
            }
        }
        catch ( runtime_error& e ) {
            cerr << e.what() << '\n';
        }
    } while ( operacao != 'f' );
}

int main() {
    meu_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str() );
    if ( meu_arquivo ) {
        meu_arquivo.close();
    }
    else {
        meu_arquivo.close();
        abri_arquivo.open( NOME_ARQUIVO_PRINCIPAL.c_str(), ios::out );
        abri_arquivo.close();
    }
    menu();

    return 0;
}