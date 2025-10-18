#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include "Indice.hpp"
#include <vector>

class Heap
{

private:

void HeapSort(std::vector<Indice> indices)
{
    
    for(int i = 1; i < indices.size(); i++)
    {
        sobe(indices, i);
    }
    for(int i = indices.size()-1; i >= 1; i--)
    {
        troca(indices, 0, i);
        desce(indices, 0);
    }

}
void sobe(std::vector<Indice> indices, int no)
{
    if(no == 0)
    return;
    
    int pai = (no - 1)/2;
    if(indices[no] < indices[pai])
    {
        troca(indices, no, pai);
        sobe(indices, pai);
    }
}

void desce(std::vector<Indice> indices, int no)
{
    int fe = 2 * no + 1;
    int fd = 2 * no + 2;

    int min = no;

    if((fd < indices.size()) && (indices[fd].byte_offset < indices[min].byte_offset))
    min = fd;

    if((fe < indices.size()) && (indices[fe].byte_offset < indices[min].byte_offset))
    min = fe;

    if(min != no)
    {
        troca(indices, min, no);
        desce(indices, indices.size(), min);
    }
}

};
#endif