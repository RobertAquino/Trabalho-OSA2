#ifndef SISTEMAGERENCIADOR_HPP
#define SISTEMAGERENCIADOR_HPP

#include <string>
#include <fstream>
#include "Aluno.hpp"
#include "Indice.hpp"
class SistemaGerenciador
{

private:
    std::string arquivoCSV;
    std::string arquivoDados;
    std::string arquivoIndice;

public:
    // Construtor e método principal do menu
    SistemaGerenciador(const std::string &csv, const std::string &dados, const std::string &indice){
        arquivoCSV = csv;
        arquivoDados = dados;
        arquivoIndice = indice;
    };
    SistemaGerenciador() = default;
    void iniciar();
    void busca(int matricula, std::ifstream &in, std::vector<Indice> &indices);

private:
    // Métodos de alto nível para as funcionalidades
    void gerarArquivoDados();
    void gerarArquivoIndice();
    void buscarRegistroPorMatricula();
    // --- Métodos privados para I/O (inspirados na classe Buffer) ---
    void escreverRegistro(std::ofstream &out, const Aluno &aluno);
    bool lerRegistro(std::ifstream &in, Aluno &aluno, long offset);
};

#endif