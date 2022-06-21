// TODO: Implement the output operator<< for Node

template <typename T>
ostream &operator<<(ostream &os, const Node<T> &n)
{
    os << "Node(";
    os << n.operator*();
    os << ",{";
    int count=0;

    if (n.size() != 0 )
    {
        for (int i = 0; i < n.size(); i++)
        {
            if (n[i].is_null() == true)
                continue;
            else
            {
                count++;
                if (count == n.degree())
                    os << n[i]->operator*();
                else
                    os << n[i]->operator*() << ",";
            }
        }
    }
    os << "})";
    return os;
}