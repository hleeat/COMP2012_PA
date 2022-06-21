#include "doubleHashingHashTable.h"

DoubleHashingHashTable::DoubleHashingHashTable(int m, int (*hash)(string, int), int (*hash2)(string, int))
:OpenAddressingHashTable(m,*hash),hash2(hash2)
{
}
int DoubleHashingHashTable::hi(string k, int i) const 
{
    int t1=hash(k,m);
    int t2=(i%m*hash2(k,m))%m;
    return (t1+t2)%m;
}


