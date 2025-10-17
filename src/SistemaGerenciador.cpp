#include "../includes/SistemaGerenciador.hpp"

void SistemaGerenciador::gerarArquivoDadosCSV()
{
    Aluno aluno;
    std::ifstream file(arquivoCSV);
    while(lerRegistro())
    {

    }
}


bool SistemaGerenciador::lerRegistro(std::ifstream &in, Aluno &aluno, long offset)
    {
        //Criamos esta função para ler primeiramente de um CSV
        ifstream newFile(nomeDoArquivoBase);
        string linha;
        vector<T> reg;
        
        //Verificamos se o arquivo foi aberto corretamente
        if (!newFile.is_open())
        {
            cerr << "ERRO: Nao foi possivel abrir o arquivo CSV: " << nomeDoArquivoBase << std::endl;
            return reg;
        }

        //Pulamos o cabeçalho do arquivo
        getline(newFile, linha); 

        //Comando de repetição usado para ler todas as linhas do CSV
        while (getline(newFile, linha))
        {   
            //Verificamos se a linha esta vazia
            if (linha.empty())
                continue;
            //Criamos um registro e chamados a função lerRegistro, responsável por pegar cada linha,
            //separar os campos do arquivo e colocá-los nos atributos de registro
            T registro;
            registro.lerRegistro(linha);
            
            //Adicionamos o registro em um vector de Registros
            reg.push_back(registro);
        }
        newFile.close();
        return reg;
    }  