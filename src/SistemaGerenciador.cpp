#include "../includes/SistemaGerenciador.hpp"
#include <iostream>
#include <sstream>

void SistemaGerenciador::iniciar()
{
    int opcao;
    do
    {
        std::cout << "Sistema Gerenciador de Alunos"<<std::endl;
        std::cout <<"-------------------------------"<<std::endl;
        std::cout << "1. Gerar Arquivo de Dados a partir do CSV"<<std::endl;
        std::cout << "2 - Gerar Arquivo de indice"<<std::endl;
        std::cout << "3 - Buscar Aluno Matrícula\n"<<std::endl;
        std::cout << "0 - Sair"<<std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao)
        {
        case 1:
            gerarArquivoDados();
            break;
        case 2:
            gerarArquivoIndice();
            break;
        case 3:
            buscarRegistroPorMatricula();
            break;
        }
    } while (opcao != 0);
}

void SistemaGerenciador::gerarArquivoDados()
{
    Aluno aluno;
    std::ifstream fileCSV(arquivoCSV);
    std::ofstream fileBin(arquivoDados, std::ios::binary);
    std::string linha;

    if (!fileCSV)
    {
        std::cout << "Erro ao abrir o arquivo CSV" << std::endl;
    }

    if (!fileBin)
    {
        std::cout << "Erro ao abiri o arquivo binario" << std::endl;
    }

    while (std::getline(fileCSV, linha))
    {
        std::stringstream ss(linha);
        std::string campo;

        // Se o campo da matricula não for vazia, salva
        std::getline(ss, campo, ',');
        if (campo.empty())
        {
            aluno.matricula = std::stoi(campo);
        }

        // Nome e Curso são char. Então temos que garantir que não ultrapasse o tamanho maximo
        std::getline(ss, campo, ',');
        std::snprintf(aluno.nome, sizeof(aluno.nome), "%s", campo.c_str());
        /*
              snprinft faz uma copia do conteudo lido garantido que vai respeirar o tamanho maximo
              Ex: Se a string tiver 52 char só vai copiar 49 e adicionar "/0"
              std::snprintf(salva a copia, tamanho maximo a ser copiado, indica que e para fazer uma copia, copia o conteudo da variavel)
        */

        std::getline(ss, campo, ',');
        std::snprintf(aluno.curso, sizeof(aluno.nome), "%s", campo.c_str());

        // Salva no arquivo binario
        escreverRegistro(fileBin, aluno);
    }
}

void SistemaGerenciador::escreverRegistro(std::ofstream &out, const Aluno &aluno)
{
    out.write(reinterpret_cast<const char *>(&aluno), sizeof(Aluno));
}

// Essa função vai servir para os indices
bool SistemaGerenciador::lerRegistro(std::ifstream &in, Aluno &aluno, long offset)
{
}