#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

template<typename T>
class array
{

public:
    array();
    array(int size);
    array(int size, T init);
    ~array();

    int size();
    T &operator[](int idx);
    void pushb(T value);

private:
    std::vector<T> elems;
};

template<typename T>
array<T>::array() {}

template<typename T>
array<T>::array(int size)
{
    elems = std::vector<T>(size);
}

template<typename T>
array<T>::array(int size, T init)
{
    elems = std::vector<T>(size, init);
}

template<typename T>
array<T>::~array() {}

template<typename T>
int array<T>::size()
{
    return elems.size();
}

template<typename T>
T &array<T>::operator[](int idx)
{
    if (idx < 0)
    {
        return elems[elems.size() + idx + 1];
    }

    return elems[idx];
}

template<typename T>
void array<T>::pushb(T value)
{
    elems.push_back(value);
}

#endif
