#include <fstream>
#include <string>

typedef struct
{
    string nome;
    string sigla;
    float valor;
} Cripto;

void split(string vetor[], string str, string deli = " ")
{
    int start = 0;
    int end = str.find(deli);
    int i = 0;
    while (end != -1)
    {
        vetor[i] = str.substr(start, end - start);
        i++;
        start = end + deli.size();
        end = str.find(deli, start);
    }
    vetor[i] = str.substr(start, end - start);
}

int conectarComBase(string nomeArquivo, Cripto lista[], int n)
{
    ifstream procuradorLeitura;
    int indice = 0;

    // abrir e associar o arquivo com seu procurador - formatado leitura
    procuradorLeitura.open(nomeArquivo);

    if (!procuradorLeitura)
        return indice;

    // percorrer o procurador
    string linha;
    while (!procuradorLeitura.eof() && indice < n)
    {
        // para cada linha percorrida do procurador, splitar por ;
        getline(procuradorLeitura, linha);
        if (linha != "")
        {

            // inserir na lista as partes splitadas (valor e data)
            string vetorLinha[3];
            split(vetorLinha, linha, ";");

            lista[indice].nome = vetorLinha[0];
            lista[indice].sigla = vetorLinha[1];
            lista[indice].valor = stof(vetorLinha[2]); // Mudança de stoi para stof

            indice++;
        }
    }

    procuradorLeitura.close();

    return indice;
}

void exibirLista(Cripto lista[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Cripto : " << lista[i].nome << " | Sigla : " << lista[i].sigla << " | Valor : " << lista[i].valor << endl;
    }
}

void gravarArquivo(const string &nomeArquivo, Cripto lista[], int totalCadastrados)
{
    ofstream procuradorEscrita;
    procuradorEscrita.open(nomeArquivo, ios::out | ios::trunc);

    for (int i = 0; i < totalCadastrados; i++)
    {
        procuradorEscrita << lista[i].nome << ";" << lista[i].sigla << ";" << lista[i].valor << endl;
    }

    procuradorEscrita.close();
}

bool verificarDuplicidade(Cripto lista[], int totalCadastrados, string nome)
{
    for (int i = 0; i < totalCadastrados; i++)
    {
        if (lista[i].nome == nome)
        {
            return true;
        }
    }
    return false;
}

int acresentarCripto(Cripto lista[], int totalCadastrados)
{
    string nome, sigla;
    float valor;

    cout << "Nome da Moeda: ";
    getline(cin, nome);

    if (verificarDuplicidade(lista, totalCadastrados, nome))
    {
        cout << "Criptomoeda ja cadastrada! Tente novamente." << endl;
        return totalCadastrados; // Retorna o total sem alterar
    }

    cout << "Sigla da Moeda: ";
    getline(cin, sigla);
    cout << "Valor da Moeda: ";
    cin >> valor;
    cin.ignore(); // Ignorar a nova linha restante no buffer

    // Adicionar o registro
    lista[totalCadastrados].nome = nome;
    lista[totalCadastrados].sigla = sigla;
    lista[totalCadastrados].valor = valor;
    totalCadastrados++;

    // Persistir no arquivo
    gravarArquivo("criptos.csv", lista, totalCadastrados);

    return totalCadastrados; // Retorna o novo total
}

int removerCripto(Cripto lista[], int totalCadastrados)
{
    string nome;
    cout << "Nome da Moeda a ser removida : ";
    getline(cin, nome);

    // Procurar o nome na lista
    for (int i = 0; i < totalCadastrados; i++)
    {
        if (lista[i].nome == nome)
        {
            for (int j = i; j < totalCadastrados - 1; j++)
            {
                lista[j] = lista[j + 1];
            }
            totalCadastrados--; // Diminuir o total de cadastrados
            cout << "Cripto removida com sucesso.\n";

            // Persistir as alterações no arquivo
            gravarArquivo("criptos.csv", lista, totalCadastrados);

            return totalCadastrados; // Retorna o novo total
        }
    }

    cout << "Registro nao encontrado.\n";
    return totalCadastrados; // Retorna o total original se nada foi removido
}

int menu(Cripto lista[], int totalCadastrados, int n)
{
    int opcao;
    do
    {
        system("cls");
        system("cls");
        cout << "MENU\n";
        cout << "1 - Cadastrar Criptomoedas\n";
        cout << "2 - Listar Criptomoedas\n";
        cout << "3 - Remover Criptomoedas\n";
        cout << "4 - Sair\n";
        cin >> opcao;
        fflush(stdin);
        switch (opcao)
        {
        case 1:
            if (totalCadastrados < TAM)
            {
                cout << "Cadastrar Criptomoeda: " << endl;
                totalCadastrados = acresentarCripto(lista, totalCadastrados);
            }
            else
            {
                cout << "Lista cheia!" << endl;
            }
            break;
        case 2:
            if (totalCadastrados > 0)
            {
                cout << "Listar Criptomoedas: " << endl;
                exibirLista(lista, totalCadastrados);
            }
            else
            {
                cout << "Lista vazia!" << endl;
            }

            break;
        case 3:
            if (totalCadastrados > 0)
            {
                totalCadastrados = removerCripto(lista, totalCadastrados);
            }
            else
            {
                cout << "Lista vazia!" << endl;
            }
            break;
        case 4:
            cout << "Saindo da aplicacao!" << endl;
            break;
        default:
            cout << "Opcao invalida!" << endl;
            break;
        }
        system("pause");
    } while (opcao != 4);
    return totalCadastrados;
}
