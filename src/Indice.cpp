#include "../includes/Indice.hpp"
#include "../includes/SistemaGerenciador.hpp"

void Indice::organizar(std::vector<Indice> &indices)
{
    int n = indices.size();

    // Constrói o heap máximo
    for (int i = n / 2 - 1; i >= 0; i--)
        desce(indices, n, i);

    // Extrai elementos do heap um por um
    for (int i = n - 1; i >= 1; i--)
    {
        troca(indices, 0, i); // Move o maior para o fim
        desce(indices, i, 0); // Restaura heap nas posições restantes
    }
}

void Indice::desce(std::vector<Indice> &indices, int tamanho, int no)
{
    int maior = no;
    int fe = 2 * no + 1;
    int fd = 2 * no + 2;

    if (fe < tamanho && indices[fe].byte_offset > indices[maior].byte_offset)
        maior = fe;
    if (fd < tamanho && indices[fd].byte_offset > indices[maior].byte_offset)
        maior = fd;

    if (maior != no)
    {
        troca(indices, no, maior);
        desce(indices, tamanho, maior);
    }
}

void Indice::troca(std::vector<Indice> &indices, int i, int j)
{
    Indice temp = indices[i];
    indices[i] = indices[j];
    indices[j] = temp;
}
