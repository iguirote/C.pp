#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "metodos.h"

#define TAM 5

using namespace std;

int main()
{
  vector<livros> livros;
  vector<int> copias, qntcopias;
  vector<string> titulo, autor, ISBN, nome, datasDevolucao;
  vector<tm> datasAtuais;
  int opcao;

  do
  {
    system("cls");
    system("cls");
    cout << "Bem vindo a Biblioteca!" << endl;
    cout << "1 - Adicionar Livros" << endl;
    cout << "2 - Remover Livros" << endl;
    cout << "3 - Buscar Livros" << endl;
    cout << "4 - Emprestimos de Livros" << endl;
    cout << "5 - Devolucao de Livros" << endl;
    cout << "6 - Livros Disponiveis" << endl;
    cout << "7 - Sair" << endl;
    cout << "Opcao: ";
    cin >> opcao;
    cin.ignore();
    system("cls");

    switch (opcao)
    {
    case 1:
      int qntLivros;
      qntLivros = solicitarQuantidadeNomes();
      system("cls");
      acrescentarLivros(livros, qntLivros);
      break;
    case 2:
      system("cls");
      apagarLivro(livros);
      break;
    case 3:
      system("cls");
      buscarLivro(livros);
      break;
    case 4:
      system("cls");
      emprestarLivro(livros, nome, datasAtuais, datasDevolucao, qntcopias);
      break;
    case 5:
      system("cls");
      devolucaoLivro(livros, nome, datasAtuais, datasDevolucao, qntcopias);
      break;
    case 6:
      system("cls");
      listarLivro(livros);
      break;
    case 7:
      cout << "Saindo..." << endl;
      break;
    default:
      cout << "Opcao invalida!" << endl;
    }
    system("pause");
  } while (opcao != 7);

  return 0;
}
