#include "../includes/SistemaGerenciador.hpp"
#include "../includes/Aluno.hpp"
#include <iostream>
#include <sstream>
#include <vector>

void SistemaGerenciador::iniciar()
{
    //menu de opção
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
    //Abertura dos arquivos e criação de variáveis auxiliares
    Aluno aluno;
    std::ifstream fileCSV(arquivoCSV);
    std::ofstream fileBin(arquivoDados, std::ios::binary);
    std::string linha;

    //Verificações de abertura de arquivo
    if (!fileCSV)
    {
        std::cout << "Erro ao abrir o arquivo CSV" << std::endl;
    }

    if (!fileBin)
    {
        std::cout << "Erro ao abiri o arquivo binario" << std::endl;
    }
    //Pula o cabeçalho
    getline(fileCSV, linha);

    //Faz o parser dos campos 
    while (std::getline(fileCSV, linha))
    {
        aluno.parser(linha);

        // Salva no arquivo binario
        escreverRegistro(fileBin, aluno);
    }
    //Fechamento dos arquivos
    fileCSV.close();
    fileBin.close();
}

void SistemaGerenciador::gerarArquivoIndice()
{
    //Abertura dos arquivos e criação das variáveis auxiliares
    std::ifstream fileBin(arquivoDados, std::ios::binary);
    std::ofstream fileIndice(arquivoIndice);
    long offset = 0;
    Aluno aluno;
    std::vector<Indice> indices;
    Indice in;

    //Faz a leitura e popula o vetor de indices
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

    int tam = indices.size();

    // Grava cada registro do vetor em um arquivo
    for (int i = 0; i < tam; i++)
    {
        fileIndice << indices[i].matricula << ' ' << indices[i].byte_offset << '\n';
    }

    //Fechamento dos arquivos
    fileIndice.close();
    fileBin.close();
}

void SistemaGerenciador::buscarRegistroPorMatricula()
{
    //Aberturas dos arquivos e criação de variáveis auxiliares
    std::ifstream fileIndice(arquivoIndice);
    std::ifstream fileBin(arquivoDados, std::ios::binary);
    int matricula;
    std::vector<Indice> indices;
    std::string linha;

    //Faz o parser e popula um vetor com os registros de índice
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

    //O usuário busca uma matrícula
    std::cout << "Busque uma matricula:" << std::endl;
    std::cin >> matricula;

    //Usamos a função de busca binária para encontra o byte_offset da matrícula
    //no arquivo binário
    busca(matricula, fileBin, indices);

    //Fechamento do arquivo
    fileIndice.close();
    fileBin.close();
}

void SistemaGerenciador::escreverRegistro(std::ofstream &out, const Aluno &aluno)
{
    out.write(reinterpret_cast<const char *>(&aluno), sizeof(Aluno));
}

// Essa função vai servir para os indices
bool SistemaGerenciador::lerRegistro(std::ifstream &in, Aluno &aluno, long offset)
{
    //Posiciona o curso de leitura no inicio de cada registro de aluno
    in.seekg(offset);

    //Verifica se o curso do arquivo acessa uma zona válida
    if (!in)
        return false;

    // Tenta ler o tamanho do próximo registro. Se não conseguir retorna false.
    if (!in.read(reinterpret_cast<char *>(&aluno), sizeof(aluno)))
    {
        return false;
    }

    return true;
}

//Esta função é responsável por fazer uma busca binária com intuito de encontrar as matrículas 
void SistemaGerenciador::busca(int matricula, std::ifstream &in, std::vector<Indice> &indices)
{
    //Declara as variáveis auxiliares
    int ini = 0;
    int fim = indices.size() - 1;
    int meio;
    Aluno aluno;

    //Faz a busca enquanto a posição for válida
    while (ini <= fim)
    {
        meio = (ini + fim) / 2;

        //Se encontra a matrícula, imprime as informações do aluno
        if (indices[meio].matricula == matricula)
        {
            if (lerRegistro(in, aluno, indices[meio].byte_offset))
            {
                aluno.display();
            }
            return;
        }
        //Compara se a matricula esta na segunda metade do vetor
        else if (indices[meio].matricula < matricula)
        {
            ini = meio + 1;
        }
        //Compara se a matricula esta na primeira metade do vetor
        else
        {
            fim = meio - 1;
        }
    }

    std::cout << "Matricula não encontrada!!!" << std::endl;
}