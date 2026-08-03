#include<bits/stdc++.h>
using namespace std;

const string ARQUIVO_DADOS = "contas.bin";
const string ARQUIVO_CONTADOR = "contador.bin";

#define ull unsigned long long
#define ll long long

struct ContaBancaria{
    ull      nroConta;
    char     dtAbertura[45];
    double   saldoConta;
    int      CLIENTE_idCliente;
    int      AGENCIA_idAGENCIA;
    char     tipoConta[45];
    int      digitoConta;
};

// Inicializa os arquivos a serem utilizados pelo programa
void inicializar_arquivos(){

    // Cria um arquivo de dados e depois o fecha
    ofstream arquivo_dados(ARQUIVO_DADOS, ios::binary|ios::trunc);
    arquivo_dados.close();

    // Cria o arquivo do contador, escreve 0 nele e depois o fecha
    ofstream arquivo_contador(ARQUIVO_CONTADOR, ios::binary|ios::trunc);
    ull qnt = -1;
    arquivo_contador.write(reinterpret_cast<char*>(&qnt), sizeof(qnt));
    arquivo_contador.close();
}

// Lê e incrementa o contador de contas
// Retorna a posicao onde a nova conta vai ser inserida
ull proximaConta(){

    // Le do arquivo a posicao da ultima conta
    fstream arq_cnt(ARQUIVO_CONTADOR, ios::binary|ios::in|ios::out);
    ull pos;
    arq_cnt.read(reinterpret_cast<char*>(&pos), sizeof(pos));

    // Incrementa a posicao
    pos++;

    // Escreve a nova posicao
    arq_cnt.seekp(0);
    arq_cnt.write(reinterpret_cast<char*>(&pos), sizeof(pos));

    // Retorna a nova posicao
    return pos;
}

void inserirConta(){

    // Pega a proxima posicao onde vai ser inserida a conta
    ull id = proximaConta();

    // Cria uma struct onde serao preenchidas os dados pelo terminal
    ContaBancaria c;
    c.nroConta = id;
    cout << "Criando conta " << id << endl;
    
    cout << "Data abertura: ";   cin.ignore(); cin.getline(c.dtAbertura,45);
    cout << "Saldo: ";           cin >> c.saldoConta;
    cout << "ID cliente: ";      cin >> c.CLIENTE_idCliente;
    cout << "ID agencia: ";      cin >> c.AGENCIA_idAGENCIA;
    cout << "Tipo conta: ";      cin.ignore(); cin.getline(c.tipoConta,45);
    cout << "Digito: ";          cin >> c.digitoConta;

    // Grava a struct no arquivo de dados
    fstream arq_dados(ARQUIVO_DADOS, ios::binary|ios::in|ios::out|ios::app);
    ll pos = (ll)id * sizeof(ContaBancaria);
    arq_dados.seekp(pos, ios::beg);
    arq_dados.write(reinterpret_cast<char*>(&c), sizeof(c));
    arq_dados.close();
}

// Apenas retorna quantas contas ja existem
ull getContador(){

    // Le do arquivo a posicao da ultima conta
    fstream arq_cnt(ARQUIVO_CONTADOR, ios::binary|ios::in|ios::out);
    ull pos;
    arq_cnt.read(reinterpret_cast<char*>(&pos), sizeof(pos));

    return pos;
}

void consultarConta(){
    // Le o numero da conta desejada
    ull nro;
    cout << "Numero da conta: ";
    cin >> nro;

    // Caso o numero seja maior que a quantidade de contas retorna
    ull cnt = getContador();
    if(nro < 0 || nro > cnt){
        cout << "Id invalido" << endl;
        return;
    }

    // Calcula o deslocamento
    ll pos = (ll)nro * sizeof(ContaBancaria);

    // Le a conta na posicao requerida
    ifstream arq_dados(ARQUIVO_DADOS, ios::binary);
    arq_dados.seekg(pos, ios::beg);
    
    ContaBancaria conta;
    arq_dados.read(reinterpret_cast<char*>(&conta), sizeof(conta));
    arq_dados.close();

    cout<< "\n     Conta "   << conta.nroConta << "\n"
        << "Data abertura: " << conta.dtAbertura << "\n"
        << "Saldo:         " << conta.saldoConta << "\n"
        << "Cliente ID:    " << conta.CLIENTE_idCliente << "\n"
        << "Agencia ID:    " << conta.AGENCIA_idAGENCIA << "\n"
        << "Tipo conta:    " << conta.tipoConta << "\n"
        << "Digito:        " << conta.digitoConta << "\n";
}

void imprimirContas() {
    ull cnt = getContador();
    if (cnt == (ull)-1) {
        cout << "Nenhuma conta cadastrada.\n";
        return;
    }

    ifstream arq_dados(ARQUIVO_DADOS, ios::binary);
    if (!arq_dados) {
        cerr << "Erro na abertura do arquivo\n";
        return;
    }

    cout << "\nListando " << cnt + 1 << " conta(s)" << "\n";
    for (ull id = 0; id <= cnt; ++id) {

        // Calcula a posicao
        ll pos = (ll)id * sizeof(ContaBancaria);
        arq_dados.seekg(pos, ios::beg);

        ContaBancaria c;
        arq_dados.read(reinterpret_cast<char*>(&c), sizeof(c));

        cout << "\nNumero conta:  " << c.nroConta << "\n"
             << "Data abertura: " << c.dtAbertura       << "\n"
             << "Saldo:         " << c.saldoConta       << "\n"
             << "Cliente ID:    " << c.CLIENTE_idCliente<< "\n"
             << "Agencia ID:    " << c.AGENCIA_idAGENCIA<< "\n"
             << "Tipo conta:    " << c.tipoConta        << "\n"
             << "Digito:        " << c.digitoConta      << "\n";
    }

    arq_dados.close();
}

int main(){

    // Caso nao existam os arquivos os inicializa
    ifstream f1(ARQUIVO_DADOS), f2(ARQUIVO_CONTADOR);
    if(!f1.good()||!f2.good()) inicializar_arquivos();

    int operacao;
    do {
        cout << "   Opcoes\n"
             << "1 Incluir Conta\n"
             << "2 Consultar Conta\n"
             << "3 Listar Contas\n"
             << "0 Sair\n"
             << "Opcao: ";
        cin >> operacao;
        if(operacao == 1) inserirConta();
        else if(operacao == 2) consultarConta();
        else if(operacao == 3) imprimirContas();
        else cout << "Opcao invalida" << endl;
    } while(operacao != 0);
    return 0;
}