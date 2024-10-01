#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

#define isbn 2

using namespace std;

typedef struct 
{
    string titulo;
    string autor;
    string isbn;
    int copias;
} livros;


bool isNumeric(const string &str) // Pego no Chat GPT/Copilot para saber quando é numero ou letra
{
    for (char const &c : str)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

int solicitarQuantidadeNomes()
{
    int qntLivros;
    do
    {
        cout << "Digite a quantidade de livros para cadastrar: ";
        cin >> qntLivros;

        if (cin.fail())
        {                                                        // verifica se o usuário inseriu algo que não é um número válido
            cin.clear();                                         // se o cin ta errado ele para de aceitar novas entradas
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignora caracter até encontrar uma nova linha
            cout << "Quantidade de nomes invalida, coloque uma valida" << endl;
        }
        else if (qntLivros <= 0)
        {
            cout << "Quantidade deve ser maior que zero. Tente novamente." << endl;
        }

        // O loop continua enquanto a entrada for invalida ou a quantidade for <= 0
    } while (cin.fail() || qntLivros <= 0);

    return qntLivros; // Retorna a quantidade valida
}

void acrescentarLivros(vector<livros> &livros, int qntLivros)
{
    for (int i = 0; i < qntLivros; i++)
    {
        livros tempLivro;
        char op;
        bool cadastrado = false;

        cout << "Digite o titulo do Livro " << i + 1 << " : " << endl;
        cin.ignore(); // Limpa o buffer antes de ler o título
        getline(cin, tempTitulo);

        // Verificar se o livro já foi cadastrado
        for (size_t j = 0; j < livros.size(); j++)
        {
            if (tempLivro.titulo == livros[j].titulo)
            {
                cadastrado = true;
                int soma;
                cout << "Livro ja cadastrado, deseja acrescentar novas copias? (S/N)" << endl;
                cin >> op;

                switch (op)
                {
                case 'S':
                case 's':
                    cout << "Quantas copias deseja acrescentar? " << endl;
                    cin >> soma;
                    livros[j].copias += soma;
                    cout << "Quantidade de copias acrescentadas!" << endl;
                    break;
                case 'N':
                case 'n':
                    cout << "Copias nao acrescentadas." << endl;
                    break;
                default:
                    cout << "Opcao invalida!" << endl;
                    break;
                }
                break;
            }
        }

        // Se o livro não foi cadastrado, adiciona-o à lista
        if (!cadastrado)
        {
            cout << "Digite o autor do Livro " << i + 1 << " : " << endl;
            getline(cin, tempAutor);

            cout << "Digite a ISBN do Livro " << i + 1 << " : " << endl;
            cin >> tempISBN;
            if (tempISBN.length() != isbn || !isNumeric(tempISBN))
            {
                do
                {
                    cout << "ISBN deve ter " << isbn << " digitos e conter apenas numeros" << endl;
                    cin >> tempISBN;
                } while (tempISBN.length() != isbn || !isNumeric(tempISBN));
            }

            cout << "Digite a quantidade de copias do Livro " << i + 1 << " : " << endl;
            cin >> tempCopias;
            cin.ignore();

            titulo.push_back(tempTitulo);
            autor.push_back(tempAutor);
            ISBN.push_back(tempISBN);
            copias.push_back(tempCopias);
        }
    }
    cout << "Livro cadastrado com sucesso!" << endl;
}

void apagarLivro(vector<string> &titulo, vector<string> &autor, vector<string> &ISBN, vector<int> &copias)
{
    string procurar;
    if (ISBN.empty())
    {
        cout << "Nenhum Livro Cadastrado." << endl;
    }
    else
    {
        cout << "Digite a ISBN do livro que deseje apagar : " << endl;
        cin >> procurar;
        for (size_t i = 0; i < ISBN.size(); i++)
        {
            if (procurar == ISBN[i])
            {
                char resposta;
                cout << "------->Livro Encontrado!<-------" << endl;
                cout << "->Titulo : " << titulo[i] << endl;
                cout << "->Autor : " << autor[i] << endl;
                cout << "->ISBN : " << ISBN[i] << endl;
                cout << "->Quantidade de copias : " << copias[i] << endl;
                cout << ">--------------------------------<\n " << endl;

                cout << "Deseja realmente apagar o livro? (S/N)" << endl;
                cin >> resposta;
                switch (resposta)
                {
                case 'S':
                case 's':
                    titulo.erase(titulo.begin() + i);
                    autor.erase(autor.begin() + i);
                    ISBN.erase(ISBN.begin() + i);
                    copias.erase(copias.begin() + i);
                    cout << "Livro apagado com sucesso! :D\n " << endl;
                    break;
                case 'N':
                case 'n':
                    cout << "Livro nao apagado :)" << endl;
                    break;
                default:
                    cout << "Opcao invalida!" << endl;
                    break;
                }
            }
            else
            {
                cout << "Livro nao encontrado :(" << endl;
            }
        }
    }
}

void buscarLivro(const vector<string> &titulo, const vector<string> &autor, const vector<string> &ISBN, const vector<int> &copias)
{
    string procurar;

    cout << "Digite a ISBN do livro que deseje buscar : " << endl;
    cin >> procurar;

    for (size_t i = 0; i < ISBN.size(); i++)
    {
        if (procurar == ISBN[i])
        {
            cout << "------->Livro Encontrado!<-------" << endl;
            cout << "->Titulo : " << titulo[i] << endl;
            cout << "->Autor : " << autor[i] << endl;
            cout << "->ISBN : " << ISBN[i] << endl;
            cout << "->Quantidade de copias : " << copias[i] << endl;
            cout << ">--------------------------------<\n " << endl;
        }
        else
        {
            cout << "Livro nao encontrado :(" << endl;
        }
    }
}

void emprestarLivro(const vector<string> &titulo, const vector<string> &autor, const vector<string> &ISBN, vector<int> &copias, vector<string> &nome, vector<tm> datasAtuais, vector<string> &datasDevolucao, vector<int> &qntcopias)
{
    string procurar, nomeEmprestimo;

    // Captura a data atual
    auto agora = chrono::system_clock::now();
    auto dataAtual = chrono::system_clock::to_time_t(agora);
    tm *tmAtual = localtime(&dataAtual);

    // Adiciona a data atual ao vetor
    datasAtuais.push_back(*tmAtual);

    cout << "Digite o titulo do livro que quer emprestar: ";
    cin >> procurar;

    for (size_t i = 0; i < titulo.size(); i++)
    {
        if (procurar == titulo[i])
        {
            if (copias[i] > 0)
            {
                cout << "Nome para emprestimo: ";
                cin >> nomeEmprestimo;
                nome.push_back(nomeEmprestimo);

                string dataDevolucao;
                cout << "Digite a data de devolucao (DD-MM-YYYY): ";
                cin >> dataDevolucao;

                // Converte a dataDevolucao (string) no formato DD-MM-YYYY para tm
                tm dataDevolucaoTm = {}; // Formula pega por ia
                istringstream ss(dataDevolucao);
                ss >> get_time(&dataDevolucaoTm, "%d-%m-%Y");

                // Verifica se a data de devolução é posterior à data atual
                if (dataDevolucaoTm.tm_year > tmAtual->tm_year || // Formula pega por ia
                    (dataDevolucaoTm.tm_year == tmAtual->tm_year && dataDevolucaoTm.tm_mon > tmAtual->tm_mon) ||
                    (dataDevolucaoTm.tm_year == tmAtual->tm_year && dataDevolucaoTm.tm_mon == tmAtual->tm_mon && dataDevolucaoTm.tm_mday > tmAtual->tm_mday))
                {
                    // Se a data de devolução for válida, armazena
                    datasDevolucao.push_back(dataDevolucao);
                }
                else
                {
                    cout << "Erro: A data de devolucao deve ser posterior à data atual.\n";
                }

                cout << "Quantidade de copias desejada : ";
                int tempQntCopias;
                cin >> tempQntCopias;
                qntcopias.push_back(tempQntCopias);

                if (tempQntCopias <= copias[i])
                {
                    copias[i] -= tempQntCopias;
                }
                else
                {
                    cout << "Copias do livro insuficientes.\n";
                }
                cout << "Livro emprestado com sucesso! :D\n";
            }
            else
            {
                cout << "Copias do livro insuficientes.\n";
            }
            return;
        }
    }
    cout << "Livro nao encontrado.\n";
}

void devolucaoLivro(const vector<string> &titulo, const vector<string> &autor, const vector<string> &ISBN, vector<int> &copias, vector<string> &nome, vector<tm> datasAtuais, vector<string> &datasDevolucao, vector<int> &qntcopias)
{
    string procurar;
    char op;
    cout << "Digite o titulo do livro para devolucao" << endl;
    cin >> procurar;

    bool encontrou = false;

    for (size_t i = 0; i < titulo.size(); i++)
    {
        if (procurar == titulo[i])
        {
            encontrou = true;
            cout << "------->Livro Encontrado!<-------" << endl;
            cout << "->Titulo : " << titulo[i] << endl;
            cout << "->Autor : " << autor[i] << endl;
            cout << "->ISBN : " << ISBN[i] << endl;
            cout << "->Copias : " << copias[i] << endl;
            cout << "->Nome da pessoa que alugou : " << nome[i] << endl;
            cout << ">--------------------------------<\n " << endl;

            cout << "Deseja devolver as copias? (S/N)" << endl;
            cin >> op;

            switch (op)
            {
            case 'S':
            case 's':
            {
                // Captura a data atual
                auto agora = chrono::system_clock::now();
                auto dataAtual = chrono::system_clock::to_time_t(agora);
                tm *tmAtual = localtime(&dataAtual);

                // Converte a data de devolução armazenada para tm
                tm dataDevolucaoTm = {};
                istringstream ss(datasDevolucao[i]);
                ss >> get_time(&dataDevolucaoTm, "%d-%m-%Y");

                // Verifica se a data atual é posterior à data de devolução
                if (difftime(dataAtual, mktime(&dataDevolucaoTm)) > 0)
                {
                    cout << "A data de devolucao foi ultrapassada. Multa de R$ 5,00 a ser paga!" << endl;
                }

                // Atualiza as copias
                copias[i] += qntcopias[i];
                nome.erase(nome.begin() + i);
                qntcopias.erase(qntcopias.begin() + i);
                cout << "Livro devolvido com sucesso!" << endl;
            }
            break;
            case 'N':
            case 'n':
                cout << "Livro nao devolvido" << endl;
                break;

            default:
                cout << "Opcao invalida!" << endl;
                break;
            }

            break;
        }
    }

    // Se o livro não foi encontrado após o loop
    if (!encontrou)
    {
        cout << "Livro nao encontrado :p" << endl;
    }
}

void listarLivro(const vector<string> &titulo, const vector<string> &autor, const vector<string> &ISBN, const vector<int> &copias)
{
    if (ISBN.empty())
    {
        cout << "Nenhum Livro Cadastrado." << endl;
    }
    else
    {
        int soma = 0;
        system("cls");
        cout << "<---- Livros cadastrados ---->\n " << endl;
        cout << "Quantidade de livros cadastrados : " << soma + 1 << "\n " << endl;
        for (size_t i = 0; i < ISBN.size(); i++)
        {
            soma++;
            cout << "------->Livro " << i + 1 << "<-------" << endl;
            cout << "->Titulo : " << titulo[i] << endl;
            cout << "->Autor : " << autor[i] << endl;
            cout << "->ISBN : " << ISBN[i] << endl;
            cout << "->Quantidade de copias : " << copias[i] << endl;
            cout << ">--------------------------------<\n " << endl;
        }
    }
}
