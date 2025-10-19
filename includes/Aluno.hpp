#ifndef ALUNO_HPP
#define ALUNO_HPP
#include <string>
class Aluno
{
public:
    int matricula;
    char nome[50];
    char curso[30];

public:
    void parser(std::string linha);
    void display();
};

#endif