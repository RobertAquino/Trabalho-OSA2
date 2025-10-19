#include "SistemaGerenciador.hpp"
#include <iostream>

int main()
{
    // Define os nomes dos arquivos
    int opcao;
    bool valido = false;
    std::string fileCSV;
    do
    {
        std::cout << "Escolha o Arquivo para ser lido" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cout << "1. 'alunos_mil'" << std::endl;
        std::cout << "2 - 'alunos_100mil" << std::endl;
        std::cout << "3 - 'alunos_1milhao'" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao)
        {
        case 1:
            fileCSV = "data/alunos_mil.csv";
            std::cout << std::endl;
            valido = true;
            break;
        case 2:
            fileCSV = "data/alunos_100mil.csv";
            std::cout << std::endl;
            valido = true;
            break;
        case 3:
            fileCSV = "data/alunos_1milhao.csv";
            std::cout << std::endl;
            valido = true;
            break;

        default:
            std::cout << "Numero invalido" << std::endl;
            break;
        }
    } while (!valido);

    SistemaGerenciador sistema(fileCSV, "data/alunos.dat", "data/indices.dat");

    // Inicia a execucao do sistema (menu, etc.)
    sistema.iniciar();
    return 0;
}
