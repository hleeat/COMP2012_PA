#include "quadraticProbingHashTable.h"
int QuadraticProbingHashTable::hi(string k, int i) const
{
    return (hash(k,m)+i*i)%m;
}
QuadraticProbingHashTable:: QuadraticProbingHashTable(int m, int (*hash)(string, int))
:OpenAddressingHashTable(m,*hash)
{}