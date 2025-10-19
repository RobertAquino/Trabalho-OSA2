#include "../includes/Aluno.hpp"
#include <iostream>
#include <sstream>
#include <vector>

void Aluno::parser(std::string linha)
{
 std::stringstream ss(linha);
        std::string campo;

        // Se o campo da matricula não for vazia, salva
        std::getline(ss, campo, ',');
        if (!campo.empty())
        {
            matricula = stoi(campo);
        }

        // Nome e Curso são char. Então temos que garantir que não ultrapasse o tamanho maximo
        std::getline(ss, campo, ',');
        std::snprintf(nome, sizeof(nome), "%s", campo.c_str());
        /*
        snprinft faz uma copia do conteudo lido garantido que vai respeitar o tamanho maximo
        Ex: Se a string tiver 52 char só vai copiar 49 e adicionar "/0" no final
        std::snprintf(salva a copia, tamanho maximo a ser copiado, indica que e para fazer uma copia, copia o conteudo da variavel)
        */

        std::getline(ss, campo, ',');
        std::snprintf(curso, sizeof(nome), "%s", campo.c_str());
}
void Aluno::display()
{
    std::cout << matricula << " " << nome << " " << curso << std::endl;
}