#include <iostream>
#include <string>
#define TAM 100

using namespace std;

#include "metodos.h"

int main()
{
    Cripto lista[TAM];
    int totalCadastrados = 0;
    
    // conectar com a base
    totalCadastrados = conectarComBase("criptos.csv", lista, TAM);

    // gerar menu
    totalCadastrados = menu(lista, totalCadastrados, TAM);
    return 1;
}
