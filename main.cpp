#include "SistemaGerenciador.hpp"

int main()
{
    // Define os nomes dos arquivos
    std::string alunos = "data/alunos_mil";
    SistemaGerenciador sistema("alunos.csv", "alunos.dat", "indices.dat");

    // Inicia a execucao do sistema (menu, etc.)
    sistema.iniciar();
    return 0;
}