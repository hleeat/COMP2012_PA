// TODO: Implement the member functions of SmartPtr (Part (A), except the output operator)


template <typename T>
SmartPtr<T>::SmartPtr()
{
    ptr = nullptr;
    count = nullptr;
}
template <typename T>
SmartPtr<T>::SmartPtr(const T &val)
{
    ptr = new T(val);
    count = new unsigned int(1);
}
template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T> &that)
{
    if (that.ptr!=nullptr)
    {
        this->ptr = that.ptr;
        this->count = that.count;
        *(this->count) = *(this->count) + 1;
    }
    else
    {
        this->ptr = nullptr;
        this->count = nullptr;
    }
}
template <typename T>
SmartPtr<T>::~SmartPtr()
{
    if (count != nullptr)
    {
        *(count) = *(count)-1;
        if (*(count) == 0)
        {
            delete count;
            count = nullptr;
            delete ptr;
            ptr = nullptr;
        }
    }
    ptr=nullptr;
    count=nullptr;
}
template <typename T>
SmartPtr<T> &SmartPtr<T>::operator=(const SmartPtr<T> &that)
{
    if (this->ptr != that.ptr)
    {
        this->unset();
    }
    if (that.ptr!=nullptr)
    {
        this->ptr = that.ptr;
        this->count = that.count;
        *(this->count) = *(this->count) + 1;
    }
    else
    {
        this->ptr = that.ptr;
        this->count = that.count;
    }
    return *this;
}
template <typename T>
void SmartPtr<T>::set(const T &val)
{
    if(this->ptr!=nullptr)
    {
        if (*(this->ptr) != val)
        {
            this->unset();
        }
    }
    this->ptr = new T(val);
    this->count = new unsigned int(1);
}
template <typename T>
void SmartPtr<T>::unset()
{
    if (count != nullptr)
    {
        *(count) = *(count)-1;
        if (*(count) == 0)
        {
            delete count;
            count = nullptr;
            delete ptr;
            ptr = nullptr;
        }
    }
    ptr=nullptr;
    count=nullptr;
}
template <typename T>
bool SmartPtr<T>::is_null() const
{
    if (ptr == nullptr)
        return true;
    return false;
}
template <typename T>
bool SmartPtr<T>::operator==(const SmartPtr<T> &that) const
{
    if (this->ptr == that.ptr)
        return true;
    return false;
}
template <typename T>
bool SmartPtr<T>::operator!=(const SmartPtr<T> &that) const
{
    if (this->ptr != that.ptr)
        return true;
    return false;
}
template <typename T>
T &SmartPtr<T>::operator*() const
{
    return *(this->ptr);
}
template <typename T>
T *SmartPtr<T>::operator->() const
{
    if (ptr == nullptr)
        return 0;
    return ptr;
}