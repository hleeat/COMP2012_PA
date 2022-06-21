#include "shop.h"
#include <iostream>
#include <cctype> //hint: you may use the isupper function in it
using std::cout;
using std::endl;
//HashTable(int m, int (*hash)(string, int)) : m(m), hash(hash), activeCellCount(0), comparisonCount(0), printSteps(false) {}; 
Shop::Shop(HashTable *fireTable, HashTable *iceTable, HashTable *lightningTable):fireTable(fireTable),iceTable(iceTable),lightningTable(lightningTable)
{
    profit=0;
}
Shop::~Shop()
{
    delete fireTable;
    fireTable=nullptr;
    delete iceTable;
    iceTable=nullptr;
    delete lightningTable;
    lightningTable=nullptr;
}
string preff(string name)
{
    string pre="";
    if(name.find("Fire")==0)
    {
        for(int i=0;i<4;i++)
        {
            pre+=name[i];
        }
    }
    else if(name.find("Ice")==0)
    {
        for(int i=0;i<3;i++)
        {
            pre+=name[i];
        }
    }
    else if(name.find("Lightning")==0)
    {
        for(int i=0;i<9;i++)
        {
            pre+=name[i];
        }
    }
    return pre;
}
string suff(string name)
{
    string suf="";
    if(name.find("Fire")==0)
    {
        for(int i=4;i<name.length();i++)
        {
            suf+=name[i];
        }
    }
    else if(name.find("Ice")==0)
    {
        for(int i=3;i<name.length();i++)
        {
            suf+=name[i];
        }
    }
    else if(name.find("Lightning")==0)
    {
        for(int i=4;i<name.length();i++)
        {
            suf+=name[i];
        }
    }
    return suf;
}
bool Shop::stockUp(string name, int quantity, int price) const
{
    string pre=preff(name);
    string suf=suff(name);
    HashTable* temp=getTable(pre);
    if(temp->get(suf)!=nullptr)
    {
        temp->get(suf)->quantity+=quantity;
        if(temp->get(suf)->price!=price)
        {
            temp->get(suf)->price=price;
        }
    }
    else
    {
        Magic *t=new Magic{pre,suf,price,quantity};
        bool a=temp->add(t);
        if(a==false)
        {
            return false;
        }
        //delete t;
        t=nullptr;
    }
    return true;
}
bool Shop::sell(string name, int quantity)
{
    string pre=preff(name);
    string suf=suff(name);
    HashTable* temp=getTable(pre);
    if(temp->get(suf)!=nullptr)
    {
        if(temp->get(suf)->quantity<quantity)
        {
            return false;
        }
        else if(temp->get(suf)->quantity==quantity)
        {
            temp->get(suf)->quantity-=quantity;
            profit+=temp->get(suf)->price*quantity;
            temp->remove(temp->get(suf)->suffix);
            return true;
        }
        else
        {
            temp->get(suf)->quantity-=quantity;
            profit+=temp->get(suf)->price*quantity;
            return true;
        }
    }
    return false;
}
HashTable* Shop::getTable(string prefix) const
{
    if(prefix=="Fire") return fireTable;
    else if(prefix=="Ice") return iceTable;
    else if(prefix=="Lightning") return lightningTable;
    else return nullptr;
}