// TODO: Implement the output operator<< for SmartPtr

template<typename T>
ostream& operator<<(ostream& os, const SmartPtr<T>& sp)
{
    os<<"SmartPtr(";
    if(sp.is_null()==false)
    {
        os<<sp.operator*()<<",";
        os<<*(sp.count);
    }
    os<<")";
    return os;
}