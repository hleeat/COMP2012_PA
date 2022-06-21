// TODO: Implement the member functions of Node (Part (B), except the output operator)
//             and the graph operations (Part (C))

template <typename T>
Node<T>::Node(const T &val)
{
    this->val = val;
    out = nullptr;
    capacity = 0;
    size_p = 0;
}
template <typename T>
Node<T>::Node(const Node<T> &that)
{
    this->val = that.val;
    this->out = nullptr;
    this->capacity = 0;
    this->size_p = 0;
}
template <typename T>
Node<T>::~Node()
{
    delete[] out;
    out = nullptr;
}
template <typename T>
T &Node<T>::operator*()
{
    return this->val;
}
template <typename T>
const T &Node<T>::operator*() const
{
    return this->val;
}
template <typename T>
unsigned int Node<T>::degree() const
{
    unsigned int temp = 0;
    for (int i = 0; i < size_p; i++)
    {
        if (out[i].is_null()==false)
            temp++;
    }
    return temp;
}
template <typename T>
unsigned int Node<T>::size() const
{
    return this->size_p;
}
template <typename T>
SmartPtr<Node<T>> Node<T>::operator[](unsigned int i) const
{
    // SmartPtr<Node<T>> temp;
    // temp.unset();
    // if (out[i].is_null())
    //     return temp;
    return out[i];
}
template <typename T>
void Node<T>::add(SmartPtr<Node<T>> n)
{
    if (n.is_null()==true)
        return;
    else if(n.operator->()==this) return;
    else
    {
        if (this->size_p!=0)
        {
            for (int i = 0; i < this->size_p; i++)
            {
                if (this->out[i] == n)
                    return;
            }
            if (this->capacity == this->size_p)
            {
                SmartPtr<Node<T>> *temp = new SmartPtr<Node<T>>[this->capacity*2];
                for (int i = 0; i < this->size_p; i++)
                {
                    temp[i] = this->out[i];
                }
                delete[] this->out;
                this->out=temp;
                temp=nullptr;
                this->capacity =this->capacity* 2;
            }
        }
        else{
            this->capacity=this->init_capacity;
            this->out = new SmartPtr<Node<T>>[this->capacity];
        }
        this->out[this->size_p] = n;
        this->size_p++;
    }
}
template <typename T>
void Node<T>::remove(SmartPtr<Node<T>> n)
{
    if(n.is_null()) return;
    for (int i = 0; i < size_p; i++)
    {
        if (out[i] == n)
            out[i].unset();
    }
}
template <typename T>
bool Node<T>::exists(SmartPtr<Node<T>> n) const
{
    if (n.is_null()==false)
    {
        for (int i = 0; i < size_p; i++)
        {
            if (out[i] == n)
                return true;
        }
    }
    return false;
}
template <typename T>
SmartPtr<Node<T>> Node<T>::find(T val) const
{
    SmartPtr<Node<T>> temp;
    for (int i = 0; i < this->size_p; i++)
    {
        if(this->out[i].is_null()) continue;
        if (this->out[i]->operator*() == val)
            return out[i];
    }
    return temp;
}

template <typename T>
SmartPtr<Node<T>> new_node(const T &val)
{
    return Node<T>(val);
}
template <typename T>
void remove_node(SmartPtr<Node<T>> n)
{
    if (n.is_null())
        return;
    else
    {
        for (int i = 0; i < n.operator->()->size(); i++)
        {
            if(n.operator->()->operator[](i).is_null()==false)
            {
                n.operator->()->operator[](i)->remove(n);
                n.operator->()->remove(n.operator->()->operator[](i));
            }
        }
    }
}
template <typename T>
void add_edge(SmartPtr<Node<T>> n1, SmartPtr<Node<T>> n2)
{
    if (n1.is_null() || n2.is_null())
        return;
    if (n1 == n2)
        return;
    if (n1.operator->()->exists(n2) == true && n2.operator->()->exists(n1) == true)
        return;
    n1.operator->()->add(n2);
    n2.operator->()->add(n1);
}
template <typename T>
void remove_edge(SmartPtr<Node<T>> n1, SmartPtr<Node<T>> n2)
{
    if (n1.is_null() || n2.is_null())
        return;
    if (n1.operator->()->exists(n2) == false && n2.operator->()->exists(n1) == false)
        return;
    n1.operator->()->remove(n2);
    n2.operator->()->remove(n1);
}
template <typename T>
set<Node<T>*> BFS(SmartPtr<Node<T>> root)
{
    queue<Node<T>*> q;
    q.push(root.operator->());
    set<Node<T>*> s;
    s.insert(root.operator->());
    while (!q.empty())
    {
        Node<T>* cur= q.front();
        q.pop();
        for (int i = 0; i < cur->size(); i++)
        {
            if (((*cur)[i]).is_null() == false)
            {
                Node<T> *next = ((*cur)[i]).operator->();
                typename set<Node<T> *>::iterator ss;
                ss = s.find(next);
                if (ss == s.end())
                {
                    q.push(next);
                    s.insert(next);
                }
            }
        }
    }
    return s;
}
template <typename T>
void DFS(SmartPtr<Node<T>> root, set<Node<T>*> s)
{
    typename set<Node<T> *>::iterator s1;
    s1 = s.find(root);
    if(s1!=s.end())
    {
        return;
    }
    s.insert(root);
    for (int i = 0 ; i < root.operator->()->size(); i++)
    {
        if((root[i]).is_null() == false)
        {
            Node<T>* next = ((*root)[i]).operator->();
            DFS(next,s);
        }
    }
}
template <typename T>
void remove_graph(SmartPtr<Node<T>> root)
{
    if (root.is_null())
        return;
    else
    {
        set<Node<T> *> tt(BFS(root));
        if (!tt.empty())
        {
            typename set<Node<T> *>::iterator iter1;
            SmartPtr<Node<T>>* n=new SmartPtr<Node<T>> [tt.size()];
            int i=0;
            for (iter1 = tt.begin(); iter1 != tt.end(); iter1++)
            {
                n[i]=find(root,(*iter1)->operator*());
                i++;
            }
            for(int t=0;t<tt.size();t++)
            {
                remove_node(n[t]);
            }
            delete[] n;
            n=nullptr;
        }
    }
}

template <typename T>
SmartPtr<Node<T>> find(SmartPtr<Node<T>>const root, T val)
{
    SmartPtr<Node<T>>temp;
    if (root.is_null())
        return temp;
    else
    {
        set<Node<T> *> tt(BFS(root));
        if (!tt.empty())
        {
            typename set<Node<T> *>::iterator iter1;
            for (iter1 = tt.begin(); iter1 != tt.end(); iter1++)
            {
                if ((*iter1)->find(val).is_null() == false)
                    return (*iter1)->find(val);
            }
            return temp;
        }
        return temp;
    }
    
}
template <typename T>
bool reachable(SmartPtr<Node<T>> root, SmartPtr<Node<T>> dest)
{
    if (root.is_null() || dest.is_null())
        return false;
    if (root == dest)
        return true;
    else
    {
        set<Node<T> *> tt(BFS(root));
        if (!tt.empty())
        {
            typename set<Node<T> *>::iterator iter1;
            for (iter1 = tt.begin(); iter1 != tt.end(); iter1++)
            {
                if (*iter1 == dest.operator->())
                    return true;
            }
        }
    }
    return false;
}
