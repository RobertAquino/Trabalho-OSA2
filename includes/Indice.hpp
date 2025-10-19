#ifndef INDICE_HPP
#define INDICE_HPP

#include <vector>;
#include "Aluno.hpp"

class Indice
{
public:
    int matricula;
    long byte_offset; // Posição do registro no arquivo de dados
    void organizar(std::vector<Indice> &indices);


private:
    void desce(std::vector<Indice> &indices, int tamanho, int no);
    void troca(std::vector<Indice> &indices, int i, int j);
};

#endif