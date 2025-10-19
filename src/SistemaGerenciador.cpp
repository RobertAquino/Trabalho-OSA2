#include "../includes/SistemaGerenciador.hpp"
#include "../includes/Aluno.hpp"
#include <iostream>
#include <sstream>
#include <vector>

void SistemaGerenciador::iniciar()
{
    int opcao;
    do
    {
        std::cout << "Sistema Gerenciador de Alunos" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cout << "1. Gerar Arquivo de Dados a partir do CSV" << std::endl;
        std::cout << "2 - Gerar Arquivo de indice" << std::endl;
        std::cout << "3 - Buscar Aluno Matrícula" << std::endl;
        std::cout << "0 - Sair" << std::endl;
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

    getline(fileCSV, linha);

    while (std::getline(fileCSV, linha))
    {
        aluno.parser(linha);

        // Salva no arquivo binario
        escreverRegistro(fileBin, aluno);
    }
    fileCSV.close();
    fileBin.close();
}

void SistemaGerenciador::gerarArquivoIndice()
{
    std::ifstream fileBin(arquivoDados, std::ios::binary);
    std::ofstream fileIndice(arquivoIndice);
    long offset = 0;
    Aluno aluno;
    std::vector<Indice> indices;
    Indice in;

    while (lerRegistro(fileBin, aluno, offset))
    {
        Indice indice;
        indice.matricula = aluno.matricula;
        indice.byte_offset = offset;
        offset += sizeof(Aluno);
        indices.push_back(indice);
    }

    // Ordena o vetor
    in.organizar(indices);

    // Grava cada registro do vetor em um arquivo

    int tam = indices.size();
    for (int i = 0; i < tam; i++)
    {
        fileIndice << indices[i].matricula << ' ' << indices[i].byte_offset << '\n';
    }
}

void SistemaGerenciador::buscarRegistroPorMatricula()
{
    std::ifstream fileIndice(arquivoIndice);
    std::ifstream fileBin(arquivoDados, std::ios::binary);
    int matricula;
    std::vector<Indice> indices;
    std::string linha;

    while (std::getline(fileIndice, linha))
    {

        std::stringstream ss(linha);
        std::string campo;
        Indice indice;
        std::getline(ss, campo, ' ');
        if (!campo.empty())
        {
            indice.matricula = stoi(campo);
        }
        std::getline(ss, campo, ' ');
        if (!campo.empty())
        {
            indice.byte_offset = stoi(campo);
        }
        indices.push_back(indice);
    }

    std::cout << "Busque uma matricula:" << std::endl;
    std::cin >> matricula;

    busca(matricula, fileBin, indices);
}

void SistemaGerenciador::escreverRegistro(std::ofstream &out, const Aluno &aluno)
{
    out.write(reinterpret_cast<const char *>(&aluno), sizeof(Aluno));
}

// Essa função vai servir para os indices
bool SistemaGerenciador::lerRegistro(std::ifstream &in, Aluno &aluno, long offset)
{
    in.seekg(offset);

    if (!in)
        return false;

    // Tenta ler o tamanho do próximo registro. Se não conseguir retorna false.
    if (!in.read(reinterpret_cast<char *>(&aluno), sizeof(aluno)))
    {
        return false;
    }

    return true;
}

void SistemaGerenciador::busca(int matricula, std::ifstream &in, std::vector<Indice> &indices)
{
    int ini = 0;
    int fim = indices.size();
    int meio;
    Aluno aluno;
    SistemaGerenciador gerenciador;

    while (fim > ini)
    {
        meio = (ini + fim) / 2;

        if (indices[meio].matricula == matricula)
        {
            if (lerRegistro(in, aluno, indices[meio].byte_offset))
            {
                aluno.display();
            }
            return;
        }
        else if (indices[meio].matricula < matricula)
        {
            ini = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    std::cout << "Matirucla não encontrada!!!" << std::endl;
}