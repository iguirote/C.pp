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
