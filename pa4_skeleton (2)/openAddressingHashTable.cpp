#include "openAddressingHashTable.h"
void OpenAddressingHashTable::performRehashing()
{
    activeCellCount = 0;
    if (printSteps == true)
        cout << "Rehashing is needed!" << endl;
    int m1 = this->m;
    Cell *temp = new Cell[m1];
    for (int i = 0; i < m1; i++)
    {
        temp[i].magic = this->table[i].magic;
        temp[i].status = this->table[i].status;
        this->table[i].magic = nullptr;
    }
    delete[] this->table;
    this->m = this->m * 2;
    this->table = new Cell[this->m];
    for (int i = 0; i < this->m; i++)
    {
        this->table[i].magic = nullptr;
        this->table[i].status = EMPTY;
    }
    for (int i = 0; i < m1; i++)
    {
        if (temp[i].status == ACTIVE)
        {
            this->add(temp[i].magic);
        }
    }
    if (printSteps == true)
        cout << "Rehashing is done!" << endl;
    for (int i = 0; i < m1; i++)
    {
        temp[i].magic = nullptr;
    }
    delete[] temp;
    temp = nullptr;
}
OpenAddressingHashTable::OpenAddressingHashTable(int m, int (*hash)(string, int))
    : HashTable(m, hash)
{
    activeCellCount = 0;
    comparisonCount = 0;
    printSteps = false;
    this->table = new Cell[this->m];
    for (int i = 0; i < this->m; i++)
    {
        this->table[i].magic = nullptr;
        this->table[i].status = EMPTY;
    }
}
OpenAddressingHashTable::~OpenAddressingHashTable()
{
    for (int i = 0; i < m; i++)
    {
        delete table[i].magic;
        table[i].magic = nullptr;
    }
    delete[] table;
    table = nullptr;
}
bool OpenAddressingHashTable::add(Magic *magic)
{
    int C = 0;
    int R = 0;
    int key = hash(magic->suffix, m);
    if (printSteps == true)
        cout << "hash(\"" << magic->suffix << "\") = " << key << endl;
    if (activeCellCount > (m / 2))
    {
        performRehashing();
        key = hash(magic->suffix, m);
    }
    while (R != m)
    {
        C++;
        if (table[key].status != ACTIVE)
            break;
        if (printSteps == true)
            cout << magic->prefix + magic->suffix << " collided at cell " << key << endl;
        R++;
        key = hi(magic->suffix, C);
    }
    if (R < m)
    {
        if (table[key].status != ACTIVE)
        {
            if (printSteps == true)
                cout << magic->prefix + magic->suffix << " added at cell " << key << endl;
            table[key].status = ACTIVE;
            table[key].magic = magic;
            activeCellCount++;
            comparisonCount += C;
            return true;
        }
        if (printSteps == true)
            cout << magic->prefix + magic->suffix << " cannot be added" << endl;
        comparisonCount += C;
        return false;
    }
    else
    {
        comparisonCount += m;
        if (printSteps == true)
            cout << magic->prefix + magic->suffix << " cannot be added" << endl;
        return false;
    }
}
bool OpenAddressingHashTable::remove(string key)
{
    int C = 0;
    int R = 0;

    int k = hash(key, m);
    if (printSteps == true)
        cout << "hash(\"" << key << "\") = " << k << endl;
    while (R != m)
    {
         C++;
        if (table[k].status == ACTIVE && table[k].magic->suffix == key)
            break;
        if (table[k].status == ACTIVE && table[k].magic->suffix != key)
            R++;
        if (printSteps == true)
            cout << "visited cell " << k << " but could not find it" << endl;
        if (table[k].status == EMPTY)
            break;
        k = hi(key, C);
    }
    if (R < m)
    {
        if (table[k].status != ACTIVE)
        {
            if (printSteps == true)
                cout << key << " cannot be removed" << endl;
            comparisonCount += C;
            return false;
        }
        if(table[k].magic!=nullptr)
        {
            if (table[k].magic->suffix == key && table[k].status == ACTIVE)
            {
                if (printSteps == true)
                    cout << table[k].magic->prefix + table[k].magic->suffix << " removed at cell " << k << endl;
                table[k].status = DELETED;
                delete table[k].magic;
                table[k].magic = nullptr;
                activeCellCount--;
                comparisonCount += C;
                return true;
            }
        }
        if (printSteps == true)
            cout << key << " cannot be removed" << endl;
        comparisonCount += C;
        return false;
    }
    else
    {
        if (printSteps == true)
            cout << key << " cannot be removed" << endl;
        comparisonCount += m;
        return false;
    }
}
Magic *OpenAddressingHashTable::get(string key)
{
    int C = 0;
    int R = 0;

    int k = hash(key, m);
    if (printSteps)
        cout << "hash(\"" << key << "\") = " << k << endl;
    while (R != m)
    {
        C++;
        if (table[k].status == ACTIVE && table[k].magic->suffix == key)
            break;
        if (table[k].status == ACTIVE && table[k].magic->suffix != key)
            R++;
        if (printSteps)
            cout << "visited cell " << k << " but could not find it" << endl;
        if (table[k].status == EMPTY)
            break;
        k = hi(key, C);
    }
    if (R < m)
    {
        if (table[k].status != ACTIVE)
        {
            if (printSteps)
                cout << key << " cannot be found" << endl;
            comparisonCount += C;
            return nullptr;
        }
        if (table[k].magic->suffix == key && table[k].status == ACTIVE)
        {
            if (printSteps)
                cout << table[k].magic->prefix + table[k].magic->suffix << " found at cell " << k << endl;
            comparisonCount += C;
            return table[k].magic;
        }
        if (printSteps)
            cout << key << " cannot be found" << endl;
        comparisonCount += C;
        return nullptr;
    }
    else
    {
        if (printSteps)
            cout << key << " cannot be found" << endl;
        comparisonCount += m;
        return nullptr;
    }
}
int OpenAddressingHashTable::getClusterCount() const
{
    int t = 0, r = 0;
    for (int i = 0; i < m; i++)
    {
        if (table[i].status == ACTIVE && r == 0)
        {
            t++;
            i++;
            while (r <= 1)
            {
                if (i == m)
                {
                    i = 0;
                    r++;
                    continue;
                }
                if (i == 0 && table[i].status == ACTIVE)
                    t--;
                if (table[i].status != ACTIVE)
                    break;
                i++;
            }
        }
        else
            continue;
    }
    return t;
}
int OpenAddressingHashTable::getLargestClusterSize() const
{
    int cluster = getClusterCount();
    if (cluster == 0)
        return 0;
    else
    {
        int *arr = new int[cluster];
        for (int i = 0; i < cluster; i++)
        {
            arr[i] = 0;
        }
        int check = -1;
        for (int i = 0; i < m; i++)
        {
            if (table[i].status != ACTIVE)
            {
                check = i;
                break;
            }
        }
        int b = check + 1;
        int a = 0;
        bool ed = false;
        while (true)
        {
            if (b == m)
                b = 0;
            if (b == check)
            {
                break;
            }
            if (table[b].status == ACTIVE)
            {
                if (a == 0)
                {
                    arr[a] = arr[a] + 1;
                    ed = true;
                    b++;
                    continue;
                }
                arr[a] = arr[a] + 1;
                b++;
                continue;
            }
            if (ed == true)
            {
                a++;
            }
            ed = false;
            b++;
        }
        for (int k = 0; k < cluster - 1; k++)
        {
            for (int h = 0; h < cluster - 1 - k; h++)
            {
                if (arr[h] < arr[h + 1])
                {
                    int temp;
                    temp = arr[h];
                    arr[h] = arr[h + 1];
                    arr[h + 1] = temp;
                }
            }
        }
        int max = arr[0];
        delete[] arr;
        return max;
    }
}
string OpenAddressingHashTable::getClusterSizeSortedList() const
{
    string result = "";
    int cluster = getClusterCount();
    if (cluster == 0)
        return "(empty)";
    else
    {
        int *arr = new int[cluster];
        for (int i = 0; i < cluster; i++)
        {
            arr[i] = 0;
        }
        int check = -1;
        for (int i = 0; i < m; i++)
        {
            if (table[i].status != ACTIVE)
            {
                check = i;
                break;
            }
        }
        int b = check + 1;
        int a = 0;
        bool ed = false;
        while (true)
        {
            if (b == m)
                b = 0;
            if (b == check)
            {
                break;
            }
            if (table[b].status == ACTIVE)
            {
                if (a == 0)
                {
                    arr[a] = arr[a] + 1;
                    ed = true;
                    b++;
                    continue;
                }
                arr[a] = arr[a] + 1;
                b++;
                continue;
            }
            if (ed == true)
            {
                a++;
            }
            ed = false;
            b++;
        }
        for (int k = 0; k < cluster - 1; k++)
        {
            for (int h = 0; h < cluster - 1 - k; h++)
            {
                if (arr[h] < arr[h + 1])
                {
                    int temp;
                    temp = arr[h];
                    arr[h] = arr[h + 1];
                    arr[h + 1] = temp;
                }
            }
        }
        
        result = std::to_string(arr[0]);
        for (int k = 1; k < cluster; k++)
        {
            result = result + "," + std::to_string(arr[k]);
        }
        delete[] arr;
        return result;
    }
    return "(empty)";
}